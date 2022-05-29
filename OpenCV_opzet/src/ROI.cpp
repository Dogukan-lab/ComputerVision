#include "include/ocv_utils.h"

void create_ROI()
{
	std::string path = "resources/wolf.jpg";
	cv::Mat img = cv::imread(path);
	cv::Mat img_scaled;
	cv::Mat img_snipped;

	//std::cout << img.size() << std::endl;

	//image resizing with scaling
	cv::resize(img, img_scaled, cv::Size(), 0.5f, 0.5f);

	//Image resizing / image snipping
	cv::Rect roi(10, 10, 300, 300);

	img_snipped = img(roi);

	cv::imshow("Source image", img);
	cv::imshow("Resized image, schaling", img_scaled);
	cv::imshow("ROI image", img_snipped);

	cv::waitKey(0);
}