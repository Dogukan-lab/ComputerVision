#include "include/ocv_utils.h"
#include <iostream>

int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;

void detection_colour(cv::Mat* img)
{
	cv::Mat out_img;
	if (img->empty()) return;

	cv::cvtColor(*img, out_img, cv::COLOR_BGR2HSV);

	cv::namedWindow("Control_panel", cv::WINDOW_AUTOSIZE);
	cv::createTrackbar("Hue min", "Control_panel", &hmin, 179);
	cv::createTrackbar("Hue max", "Control_panel", &hmax, 179);
	cv::createTrackbar("Sat min", "Control_panel", &smin, 255);
	cv::createTrackbar("Sat max", "Control_panel", &smax, 255);
	cv::createTrackbar("Val min", "Control_panel", &vmin, 255);
	cv::createTrackbar("Val max", "Control_panel", &vmax, 255);



	while (1)
	{
		cv::Scalar lower(hmin, smin, vmin);
		cv::Scalar upper(hmax, smax, vmax);
		cv::inRange(*img, lower, upper, out_img);

		cv::imshow("Kerstballen original", *img);

		cv::imshow("Kerstballen lsd", out_img);
		cv::waitKey(1);
	}
}

void pick_colour()
{
	int ticks = 0;
	cv::VideoCapture cap(0);
	cv::Mat video_img;

	cv::Mat out_img, mask;

	cv::namedWindow("Control_panel", cv::WINDOW_AUTOSIZE);
	cv::createTrackbar("Hue min", "Control_panel", &hmin, 179);
	cv::createTrackbar("Hue max", "Control_panel", &hmax, 179);
	cv::createTrackbar("Sat min", "Control_panel", &smin, 255);
	cv::createTrackbar("Sat max", "Control_panel", &smax, 255);
	cv::createTrackbar("Val min", "Control_panel", &vmin, 255);
	cv::createTrackbar("Val max", "Control_panel", &vmax, 255);


	while (true)
	{
		cap.read(video_img);

		cv::cvtColor(video_img, out_img, cv::COLOR_BGR2HSV);


		cv::Scalar lower(hmin, smin, vmin);
		cv::Scalar upper(hmax, smax, vmax);
		cv::inRange(out_img, lower, upper, mask);

		if (ticks == 100) {
			std::cout << "Min values: " << hmin << "," << smin << "," << vmin <<
				"  Max values: " << hmax << "," << smax << "," << vmax << "\n";
			ticks = 0;
		}
		

		cv::imshow("Video feed", video_img);
		cv::imshow("Colour feed", mask);
		ticks++;
		cv::waitKey(1);
	}
}