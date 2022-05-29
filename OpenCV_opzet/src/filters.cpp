#include "include/ocv_utils.h"

void guassian_filter(cv::Mat* img) 
{	
	cv::Mat output_img;
	cv::Mat gaussian_blur;

	cv::cvtColor(*img, output_img, cv::COLOR_BGR2GRAY);
	cv::cvtColor(*img, gaussian_blur, cv::COLOR_BGR2GRAY);

	cv::GaussianBlur(gaussian_blur, gaussian_blur, cv::Size(5,5), 500, 500);

	cv::imshow("Original img", *img);
	cv::imshow("B/W filter", output_img);
	cv::imshow("Gaussian filter", gaussian_blur);
	cv::waitKey(0);
}

void custom_convolution_filter(cv::Mat* img) 
{
	//Vul matrix met enen met kernel grootte van 3x3
	cv::Mat kernel = cv::Mat::ones(cv::Size(3, 3), CV_16F);

	//Normaliseer alle elementen
	kernel /= 9;

	cv::Mat copy_img;

	cv::filter2D(*img, copy_img, -1, kernel);

	cv::imshow("Original img", *img);
	cv::imshow("Custom blur img", copy_img);
	cv::waitKey(0);
}

void sharpen_image(cv::Mat* img) 
{
	cv::Mat sharpened_img;
	cv::Mat kernel = (cv::Mat_<double>(3, 3) <<
												 0, -1, 0,
												-1, 5, -1,
												 0, -1 ,0);
	
	cv::filter2D(*img, sharpened_img, -1, kernel);

	cv::imshow("Original img", *img);
	cv::imshow("Sharpened img", sharpened_img);
	cv::waitKey(0);
}

void makeshift_canny(cv::Mat* img) 
{
	cv::Mat canny_img;
	cv::Mat kernel = (cv::Mat_<double>(3, 3) <<
		0, -2, 0,
		-2, 8, -2,
		0, -2, 0);
	cv::filter2D(*img, canny_img, -1, kernel);

	cv::imshow("Original img", *img);
	cv::imshow("Canny img", canny_img);
	cv::waitKey(0);
}

void bilateral_filter(cv::Mat* img)
{
	cv::Mat bilateral_img;

	cv::bilateralFilter(*img, bilateral_img, 9, 150, 150);

	cv::imshow("Original img", *img);
	cv::imshow("Bilateral filter", bilateral_img);
	cv::waitKey(0);
}

void erode_balls(cv::Mat* img)
{
	cv::Mat output_img;
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7,7));
	cv::dilate(*img, output_img, kernel);

	cv::imshow("Original img", *img);
	cv::imshow("Eroded img", output_img);
	cv::waitKey(0);
}
