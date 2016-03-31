#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "LineFinder.h"

#define PI 3.1415926

int main()
{

	cv::Mat image = cv::imread("car.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	cv::namedWindow("Original Image");
	cv::imshow("Original Image", image);

	// Canny Algorithm
	cv::Mat contours;
	cv::Canny(image, contours, 125, 350);
	cv::Mat contoursInv;
	cv::threshold(contours, contoursInv, 128, 255, cv::THRESH_BINARY_INV);
	cv::namedWindow("Canny Contours");
	cv::imshow("Canny Contours", contoursInv);


	// Create a test image;
	cv::Mat test(200, 200, CV_8U, cv::Scalar(0));
	cv::line(test, cv::Point(100, 0), cv::Point(200, 200), cv::Scalar(255));
	cv::line(test, cv::Point(0, 50), cv::Point(200, 200), cv::Scalar(255));
	cv::line(test, cv::Point(0, 200), cv::Point(200, 0), cv::Scalar(255));
	cv::line(test, cv::Point(200, 0), cv::Point(0, 200), cv::Scalar(255));
	cv::line(test, cv::Point(100, 0), cv::Point(100, 200), cv::Scalar(255));
	cv::line(test, cv::Point(0, 100), cv::Point(200, 100), cv::Scalar(255));
	cv::namedWindow("Test Image");
	cv::imshow("Test Image", test);
	cv::imwrite("test.bmp", test);
	// Hough tranform for line detection
	std::vector<cv::Vec2f> lines;
	cv::HoughLines(contours, lines, 1, PI / 180, 60);
	// Draw the lines
	cv::Mat result(contours.rows, contours.cols, CV_8U, cv::Scalar(255));
	image.copyTo(result);
	std::cout << "Lines detected: " << lines.size() << std::endl;

	std::vector<cv::Vec2f>::const_iterator it = lines.begin();
	while (it != lines.end()) {
		float rho = (*it)[0];   // first element is distance rho
		float theta = (*it)[1]; // second element is angle theta
			if (theta < PI / 4. || theta > 3.*PI / 4.) { // ~vertical line
			 // point of intersection of the line with first row
			cv::Point pt1(rho / cos(theta), 0);
			// point of intersection of the line with last row
			cv::Point pt2((rho - result.rows*sin(theta)) / cos(theta), result.rows);
			// draw a white line
			cv::line(result, pt1, pt2, cv::Scalar(255), 1);
		}
		else { // ~horizontal line
		   // point of intersection of the line with first column
			cv::Point pt1(0, rho / sin(theta));
			// point of intersection of the line with last column
			cv::Point pt2(result.cols, (rho - result.cols*cos(theta)) / sin(theta));
			// draw a white line
			cv::line(result, pt1, pt2, cv::Scalar(255), 1);
		}
		std::cout << "line: (" << rho << "," << theta << ")\n";
		++it;
	}
	cv::namedWindow("Detected Lines with Hough");
	cv::imshow("Detected Lines with Hough", result);

	// LineFinder

	LineFinder ld;
	ld.setLineLengthAndGap(100, 20);
	ld.setMinVote(80);
	std::vector<cv::Vec4i> li = ld.findLines(contours);
	ld.drawDetectedLines(image);
	cv::namedWindow("Detected Lines with HoughP");
	cv::imshow("Detected Lines with HoughP", image);
	std::vector<cv::Vec4i>::const_iterator it2 = li.begin();
	while (it2 != li.end()) {
		std::cout << "(" << (*it2)[0] << "," << (*it2)[1] << ")-("
			<< (*it2)[2] << "," << (*it2)[3] << ")" << std::endl;
		++it2;
	}


	cv::waitKey();
	return 0;
}