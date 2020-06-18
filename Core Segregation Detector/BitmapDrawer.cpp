#include "BitmapDrawer.h"




BitmapDrawer::BitmapDrawer(cv::Mat matrix)
{
	mat = new cv::Mat(matrix);
}

void BitmapDrawer::DrawBitmap()
{
	System::Drawing::Bitmap^ bitmap = gcnew System::Drawing::Bitmap(mat->cols, mat->rows);
	for (int i = 0; i < mat->cols - 1; i++) {
		for (int j = 0; j < mat->rows - 1; j++) {
			cv::Scalar colour = mat->at<cv::Vec3b>(cv::Point(i, j));
			bitmap->SetPixel(i, j, System::Drawing::Color::FromArgb(colour.val[2], colour.val[1], colour.val[0]));
		}
	}
	System::Drawing::Bitmap^ scaleBitmap = gcnew System::Drawing::Bitmap(bitmap, mat->cols / 3, mat->rows / 3);
	this->bitmap = scaleBitmap;
	this->done = true;
}
