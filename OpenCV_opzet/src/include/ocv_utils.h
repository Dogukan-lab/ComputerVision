#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#define IMAGE_WIDTH 800
#define IMAGE_HEIGHT 600

//Simple warping functions
void create_ROI();
void create_shapes();
void convert_warped_ROI(cv::Mat* img_src);

//Convolution filters
void guassian_filter(cv::Mat* img);
void custom_convolution_filter(cv::Mat* img);
void sharpen_image(cv::Mat* img);
void makeshift_canny(cv::Mat* img);
void bilateral_filter(cv::Mat* img);
void erode_balls(cv::Mat* img);

//Simple colour detection
void detection_colour(cv::Mat* img);
void pick_colour();