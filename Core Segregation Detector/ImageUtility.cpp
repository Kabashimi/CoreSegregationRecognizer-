#include "ImageUtility.h"



ImageUtility::ImageUtility()
{
}

cv::Mat ImageUtility::ImageLoad(std::string path)
{
	//std::cout << "Image load: ";
	cv::Mat src, src_gray;
	src = cv::imread(path, CV_LOAD_IMAGE_COLOR);

	if (!src.data)
	{
		//std::cout << "FAILURE\n";
		exit(1);
	}

	//std::cout << "SUCCESS\n";
	return src;
}

System::Drawing::Bitmap^ ImageUtility::DrawBitmap(cv::Mat src)
{
	System::Drawing::Bitmap^ bitmap = gcnew System::Drawing::Bitmap(src.cols, src.rows);
	for (int i = 0; i < src.cols-1; i++) {
		for (int j = 0; j < src.rows-1; j++) {
			cv::Scalar colour = src.at<cv::Vec3b>(cv::Point(i, j));
			bitmap->SetPixel(i, j, System::Drawing::Color::FromArgb(colour.val[2], colour.val[1], colour.val[0]));
			//bitmap->SetPixel(j, i, System::Drawing::Color::White);
		}
	}
	System::Drawing::Bitmap^ scaleBitmap = gcnew System::Drawing::Bitmap(bitmap, src.cols/3, src.rows/3);
	return scaleBitmap;
}
