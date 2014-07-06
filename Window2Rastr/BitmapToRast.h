#pragma once
#include <opencv2/core/core.hpp>
#include <math.h>


class BitmapToRast
{
public:
	BitmapToRast(const size_t NumX_, const size_t NumY_);
	virtual ~BitmapToRast(void);

	void Convert(cv::Mat& Image);
	cv::Scalar* GetBigGridColors(void);
	cv::Scalar* GetSmallGridColors(void);

private:
	cv::Point* BigGrid;
	cv::Point* SmallGrid;

	cv::Scalar* BigGridColors;
	cv::Scalar* SmallGridColors;

	size_t BigRastrSize, SmallRastrSize, Radius;
	size_t NumX, NumY;
	double R_x, R_y;
};

