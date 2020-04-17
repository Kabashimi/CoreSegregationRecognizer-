#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

ref class BitmapDrawer
{
public:
	BitmapDrawer(cv::Mat);
	void DrawBitmap();
	System::Drawing::Bitmap^ bitmap;
	bool done = false;

private:
	cv::Mat* mat;
};

