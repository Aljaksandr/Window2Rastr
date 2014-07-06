#include "PlotCircles.h"


PlotCircles::PlotCircles(const size_t NumX, const size_t NumY, const size_t Radius_)
{
	BigGrid = new cv::Point [NumY*(NumX+1)/2];
	SmallGrid = new cv::Point [(NumY-1)*(NumX-1)/2];

	BigRastrSize = NumY*(NumX+1)/2;
	SmallRastrSize = (NumY-1)*(NumX-1)/2;
	Radius = Radius_;

	for(size_t y = 0; y<NumY; y++)
	{
		for(size_t x = 0; x<(NumX+1)/2; x++)
		{
			BigGrid[y*(NumX+1)/2 + x].x = floor(Radius + 2*sqrt(3.0)*Radius*x + 0.5);
			BigGrid[y*(NumX+1)/2 + x].y = Radius + 2*Radius*y;
		}
	}

	for(size_t y = 0; y<NumY-1; y++)
	{
		for(size_t x = 0; x<(NumX-1)/2; x++)
		{
			SmallGrid[y*(NumX-1)/2 + x].x = floor(Radius + Radius*sqrt(3.0) + 2*sqrt(3.0)*Radius*x + 0.5);
			SmallGrid[y*(NumX-1)/2 + x].y = 2*Radius + 2*Radius*y;
		}
	}
}


PlotCircles::~PlotCircles(void)
{
	delete [] BigGrid;
	delete [] SmallGrid;
}

void PlotCircles::PlotRastr(cv::Mat& Image, const cv::Scalar* const BigGridColors, const cv::Scalar* const SmallGridColors)
{
	for (size_t i = 0; i<BigRastrSize; i++)
	{
		cv::circle(Image, BigGrid[i], Radius, BigGridColors[i], -1, 8, 0);
	}

	for (size_t i = 0; i<SmallRastrSize; i++)
	{
		cv::circle(Image, SmallGrid[i], Radius, SmallGridColors[i], -1, 8, 0);
	}
}
