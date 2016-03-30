#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


#include "morphoFeature.h"


/*
int main()
{
	cv::Mat image = cv::imread("car.jpg");
	cv::namedWindow("Image");
	cv::imshow("Image", image);

	MorphoFeatures morpho;
	morpho.setThreshold(40);
	
	// Get the edges
	cv::Mat edges;
	edges = morpho.getEdges(image);
	cv::namedWindow("Edge Image");
	cv::imshow("Edge Image", edges);

	// Get the corners
	morpho.setThreshold(-1);
	cv::Mat corners;
	corners = morpho.getCorners(image);
	cv::morphologyEx(corners, corners, cv::MORPH_TOPHAT, cv::Mat());
	cv::threshold(corners, corners, 40, 255, cv::THRESH_BINARY_INV);
	cv::namedWindow("Corner Image");
	cv::imshow("Corner Image", corners);

	
	// Display the corner on the image
	morpho.drawOnImage(corners, image);
	cv::namedWindow("Corners on Image");
	cv::imshow("Corners on Image", image);
	

	cv::waitKey();

	return 0;
}
*/