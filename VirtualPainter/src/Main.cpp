#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

cv::Mat img;

struct ColourFilter
{
	unsigned int index;
	cv::Scalar lower;
	cv::Scalar upper;

};

struct ColourPencil
{
	unsigned int colour;
	cv::Point position;

};

std::vector <ColourFilter> filters{
	{ 0,cv::Scalar(46,66,87), cv::Scalar(68,255,255) }, //Green
	{ 1,cv::Scalar(6,215,156), cv::Scalar(40,255,255) }, //Orange
	{ 2,cv::Scalar(0,179,199), cv::Scalar(38,255,255) }, //Yellow
};

std::vector<ColourPencil> colourPencils;
std::vector<cv::Scalar> coloursScalar{ 
	{0, 255, 0}, //Green colour
	{0, 165, 255}, //Orange colour
	{0, 255, 255} //Yellow colour
};

int currentShape = 0;

/*
* Algorithm to detect contours within a range of 1000 pixels and greater
* Saves the center point of the boundingrect to draw with further down the line.
*/
cv::Point getContours(cv::Mat contour_img)
{
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(contour_img, 
		contours, 
		hierarchy, 
		cv::RETR_EXTERNAL, 
		cv::CHAIN_APPROX_SIMPLE);

	std::vector<std::vector<cv::Point>> contourPoly(contours.size());
	std::vector<cv::Rect> boundingRect(contours.size());

	cv::Point pencilTop(0, 0);

	for (int i = 0; i < contours.size(); i++)
	{
		int area = cv::contourArea(contours[i]);

		//std::cout << "Area: " << area << "\n";

		if (area > 400)
		{
			float perimeter = cv::arcLength(contours[i], true);
			cv::approxPolyDP(contours[i], contourPoly[i], 0.02 * perimeter, true);

			boundingRect[i] = cv::boundingRect(contourPoly[i]);

			pencilTop.x = boundingRect[i].x + boundingRect[i].width / 2;
			pencilTop.y = boundingRect[i].y + boundingRect[i].height / 2;
 			

			cv::drawContours(img, contourPoly, i, cv::Scalar(255, 0, 255), 2);
		}
	}
	return pencilTop;
}

/*
* Iterates through every ColourFilter
* When an object is detected a center point of that contour is returned
* Additionally checks if it is a valid point in the space
* Adds points to colourPencils until it stops detecting a certain colour
*/
std::vector<ColourPencil> findColour(cv::Mat img)
{
	cv::Mat out_img;

	cv::cvtColor(img, out_img, cv::COLOR_BGR2HSV);
	for (const auto& filter: filters)
	{
		cv::Mat mask;

		cv::inRange(out_img, filter.lower, filter.upper, mask);

		cv::Point pencilTop = getContours(mask);
		if(pencilTop.x != 0 && pencilTop.y != 0)
			colourPencils.push_back({filter.index, pencilTop});
	}
	return colourPencils;
}

/*
* Iterates through pencils and draws a shape based on the currentShape
* & the position of the pencil, the pencil also has a colour which is used
* in the colours vector to determine the correct colour to output to the screen
*/
void draw(std::vector<ColourPencil> pencils, std::vector<cv::Scalar> colours) 
{
	for (const auto& pencil : pencils) {
		switch (currentShape)
		{
		case 0:
			cv::circle(img, 
				pencil.position, 
				10, 
				colours[pencil.colour], 
				cv::FILLED);
			break;
		case 1:
			cv::rectangle(img,
				cv::Rect(pencil.position.x, pencil.position.y, 50, 50),
				colours[pencil.colour],
				cv::FILLED);

			break;
		case 2:
			cv::ellipse(img, 
				pencil.position, 
				cv::Size(50, 90),
				0, 
				0, 
				360, 
				colours[pencil.colour], 
				cv::FILLED);
			break;
		}
		
	}
}

/*
* Creates a seperate panel for determining shapes
* & calls all necessary functions to operate
*/
int main() 
{
	cv::VideoCapture capture(0);
	cv::Mat video_img;
	cv::namedWindow("Control_panel", cv::WINDOW_AUTOSIZE);
	cv::createTrackbar("Shape", "Control_panel", &currentShape, 2);

	while (true)
	{
		capture.read(img);

		//Find colour
		colourPencils = findColour(img);

		draw(colourPencils, coloursScalar);

		cv::imshow("Main video", img);
		if ((char)cv::waitKey(1) == 27) //Checks if ESC has been pressed
			colourPencils.clear(); //Clears the drawings on the screen
	}
}