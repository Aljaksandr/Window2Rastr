#pragma once

#include <opencv2/core/core.hpp>
#include <math.h>

class PlotCircles
{
public:
	PlotCircles(const size_t NumX, const size_t NumY, const size_t Radius_);
	virtual ~PlotCircles(void);
	void PlotRastr(cv::Mat& Image, const cv::Scalar* const BigGridColors, const cv::Scalar* const SmallGridColors);
private:
	cv::Point* BigGrid;
	cv::Point* SmallGrid;

	size_t  BigRastrSize, SmallRastrSize, Radius;
};

