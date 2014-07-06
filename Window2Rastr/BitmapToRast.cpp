#include "BitmapToRast.h"


BitmapToRast::BitmapToRast(const size_t NumX_, const size_t NumY_)
{
	NumX = NumX_;
	NumY = NumY_;

	BigRastrSize = NumY*(NumX+1)/2;
	SmallRastrSize = (NumY-1)*(NumX-1)/2;

	BigGridColors = new cv::Scalar [BigRastrSize];
	SmallGridColors = new cv::Scalar [SmallRastrSize];

	BigGrid = new cv::Point [BigRastrSize];
	SmallGrid = new cv::Point [SmallRastrSize];

	Radius = 0;
}


BitmapToRast::~BitmapToRast(void)
{
	delete [] BigGrid;
	delete [] SmallGrid;

	delete [] BigGridColors;
	delete [] SmallGridColors;
}

void BitmapToRast::Convert(cv::Mat& Image)
{
	if(Radius == 0)
	{
		R_x = Image.cols/((NumX-1)*sqrt(3.0) + 2);
		R_y = Image.rows/(2*NumY);

		if (R_x < R_y)
			Radius = R_x;
		else
			Radius = R_y;

		for(size_t y = 0; y<NumY; y++)
		{
			for(size_t x = 0; x<(NumX+1)/2; x++)
			{
				BigGrid[y*(NumX+1)/2 + x].x = floor(R_x + 2*sqrt(3.0)*R_x*x + 0.5);
				BigGrid[y*(NumX+1)/2 + x].y = floor(R_y + 2*R_y*y + 0.5);
			}
		}

		for(size_t y = 0; y<NumY-1; y++)
		{
			for(size_t x = 0; x<(NumX-1)/2; x++)
			{
				SmallGrid[y*(NumX-1)/2 + x].x = floor(R_x + R_x*sqrt(3.0) + 2*sqrt(3.0)*R_x*x + 0.5);
				SmallGrid[y*(NumX-1)/2 + x].y = floor(2*R_y + 2*R_y*y + 0.5);
			}
		}
	}

	for (size_t i = 0; i<BigRastrSize; i++)
	{
		cv::Mat roiMat = Image(cv::Rect(BigGrid[i].x - Radius + 1 , BigGrid[i].y - Radius + 1, 2*Radius-2, 2*Radius-2));
		BigGridColors[i] = mean(roiMat);
	}

	for (size_t i = 0; i<SmallRastrSize; i++)
	{
		cv::Mat roiMat = Image(cv::Rect(SmallGrid[i].x - Radius + 1, SmallGrid[i].y - Radius + 1, 2*Radius-2, 2*Radius-2));
		SmallGridColors[i] = mean(roiMat);
	}

}

cv::Scalar* BitmapToRast::GetBigGridColors(void)
{
	return BigGridColors;
}

cv::Scalar* BitmapToRast::GetSmallGridColors(void)
{
	return SmallGridColors;
}
