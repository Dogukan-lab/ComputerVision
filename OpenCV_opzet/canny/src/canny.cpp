#include "../cannyUtils.h"

cv::Mat src, dst_img;
int threshold1;
int threshold2;

//static void on_trackbar(int, void*)
//{
//	alpha = (double)alpha_slider / 100;
//	beta = (1.0 - alpha);
//	cv::GaussianBlur(src1, dst, cv::Size(3,3), 3);
//	cv::Canny(src1, dst, alpha, beta);
//	cv::imshow("Linear Blend", dst);
//}

static void init(std::string img_path) 
{
	src = cv::imread(img_path);

	threshold1 = 0;
	threshold2 = 0;


	if (src.empty()) return;

	cv::namedWindow("Canny_Operator", (800, 600));

	cv::createTrackbar("Threshold 1",
		"Canny_Operator",
		&threshold1,
		255);
	cv::createTrackbar("Threshold 2",
		"Canny_Operator",
		&threshold2,
		255);

	cv::GaussianBlur(src, src, cv::Size(3, 3), 5, 0);
}

void run()
{

	init("resources/icecream.png");

	while(true) 
	{
		cv::Canny(src, dst_img, threshold1, threshold2);

		cv::imshow("WOW", dst_img);

		cv::waitKey(1);
	}
}