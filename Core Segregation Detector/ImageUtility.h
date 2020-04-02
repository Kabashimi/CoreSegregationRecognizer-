#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

ref class ImageUtility
{
public:
	ImageUtility();
	cv::Mat ImageLoad(std::string);
	System::Drawing::Bitmap^ DrawBitmap(cv::Mat);
};

