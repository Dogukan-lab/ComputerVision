#include "include/ocv_utils.h"
#include "../canny/cannyUtils.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


int main() 
{
	cv::Mat img = cv::imread("resources/kerstballen.png");
	//create_ROI(); //Opdracht 1.2
	//create_shapes(); //Opdracht 1.3
	//convert_warped_ROI(&img); //Opdracht 1.4
	//guassian_filter(&img); //Opdracht 2.1
	//custom_convolution_filter(&img); //Opdracht 2.1.5
	
	//Opdracht 2.1.6
	//sharpen_image(&img); 
	//bilateral_filter(&img);
	//makeshift_canny(&img);

	//Opdracht 2.3
	//erode_balls(&img);

	//run(); Opdracht 2.2

	//detection_colour(&img);

	pick_colour();
}


