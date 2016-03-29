#include <iostream>
using namespace std;

#include "cv.h"
#include "highgui.h"
#include "Histogram1D.h"

int main()
{
	cv::Mat image = cv::imread("car.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	cv::namedWindow("Image");
	cv::imshow("Image", image);
	
	
	// The histogram object
	Histogram1D hist;
	cv::MatND histo = hist.getHistogram(image);
	// Loop over each bin
	for (int i = 0; i<256; i++)
		cout << "Value " << i << " = " << histo.at<float>(i) << endl;
	
	//Display a histogram as an image
	cv::namedWindow("Histogram");
	cv::imshow("Histogram", hist.getHistogramImage(image));;
	
	// Createing a binary image by  thresholding
	cv::Mat thresholded;
	cv::threshold(image, thresholded, 60, 255, cv::THRESH_BINARY);
	// Display the thresholded image
	cv::namedWindow("Binary Image");
	cv::imshow("Binary Image",thresholded);
	cv::imwrite("binary.bmp", thresholded);


	// create an image inversion table
	uchar lookup[256];
	cv::Mat lookupM(1,256,CV_8U);
	for (int i = 0; i < 256; i++)
	{
		lookup[i] = 255 - i;
		lookupM.at<uchar>(i) = lookup[i];
	}
	// Apply lookup and display negative image
	cv::namedWindow("Negative image");
	cv::imshow("Negative image", hist.applyLookUp(image, lookupM));

	// Stretch the image ignoring bins with less than 5 pixels
	cv::Mat str = hist.stretch(image, 20);
	cv::namedWindow("Stretched Image");
	cv::imshow("Stretched Image", str);

	// Equalize the image
	cv::Mat eq = hist.equalize(image);
	cv::namedWindow("Equalized Image");
	cv::imshow("Equalized Image", eq);
	cv::namedWindow("Equalized Histogram");
	cv::imshow("Equalized Histogram", hist.getHistogramImage(eq));
	
	
	cv::waitKey();
	return 0;
}