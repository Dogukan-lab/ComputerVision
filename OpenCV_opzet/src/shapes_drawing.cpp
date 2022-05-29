
#include <opencv2/core/hal/interface.h>

#include "include/ocv_utils.h"
#include <iostream>

#define CIRCLE_RADIUS 100

/*
	This file will create it's own image.
	Drawing shapes and text.
*/
void create_shapes() 
{
	cv::Mat img(600, 800, CV_8UC3, cv::Scalar(255, 255, 255));
	cv::Scalar colour_of_circle(0, 69, 255); // Dit is de kleur oranje
	cv::Point center_of_image(400, 300);

	cv::Rect rectangle (300, 266, 200, 60);

	//Circle method
	cv::circle(img, center_of_image, CIRCLE_RADIUS, colour_of_circle);
	cv::circle(img, cv::Point(400, 300), 155, cv::Scalar(0, 255, 255), cv::FILLED);

	//Rect method
	cv::rectangle(img, rectangle, cv::Scalar(255, 255, 255), 3);

	//Line method
	cv::line(img, cv::Point(290, 500), cv::Point(700, 296), cv::Scalar(0, 0, 0), 3);


	//Put text method
	cv::putText(img, "Hello test here", 
					cv::Point(rectangle.x + (rectangle.width / 6), 
								rectangle.y + (rectangle.height / 2)),
					cv::FONT_HERSHEY_COMPLEX,
					0.5f,
					cv::Scalar(0, 0, 0),
					2);

	cv::imshow("Image created", img);
	cv::waitKey(0);
}