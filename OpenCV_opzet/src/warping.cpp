#include "include/ocv_utils.h"

constexpr auto WARPED_IMG_WIDTH = 565;
constexpr auto WARPED_IMG_HEIGHT = 711;

void convert_warped_ROI(cv::Mat* img_src)
{
	cv::Mat matrix, img_warped;

	/*cv::Point point_1(112, 0);
	cv::Point point_2(345, 0);
	cv::Point point_3(345, 280);
	cv::Point point_4(112, 280);*/

	cv::Point2f src_dobbelsteen[4] = { {46, 92}, {166, 130},
							{64, 165}, {159, 202}};
	cv::Point2f src_computer[4] = { {113, 40}, {241, 114},
									{113, 154}, {241, 228} };
	cv::Point2f dst[4] = { {0.0f, 0.0f}, 
							{WARPED_IMG_WIDTH, 0.0f},
							{0.0f, WARPED_IMG_HEIGHT}, 
							{WARPED_IMG_WIDTH,WARPED_IMG_HEIGHT}
							};

	matrix = cv::getPerspectiveTransform(src_computer, dst);
	cv::warpPerspective(*img_src, 
		img_warped, 
		matrix, 
		cv::Point(WARPED_IMG_WIDTH, WARPED_IMG_HEIGHT));

	cv::imshow("Original image", *img_src);
	cv::imshow("Warped image", img_warped);
	cv::waitKey(0);
}