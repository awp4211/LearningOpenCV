#include <iostream>
#include <iomanip>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "LaplacianZC.h"

using namespace std;

int main()
{
	cv::Mat image = cv::imread("car.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	cv::namedWindow("Original Image");
	cv::imshow("Original Image", image);

	// Compute Sobel X derivative
	cv::Mat sobelX;
	cv::Sobel(image, sobelX, CV_8U, 1, 0, 3, 0.4, 128);
	cv::namedWindow("Sobel X Image");
	cv::imshow("Sobel X Image", sobelX);

	// Compute Sobel Y derivative
	cv::Mat sobelY;
	cv::Sobel(image, sobelY, CV_8U, 0, 1, 3, 0.4, 128);
	cv::namedWindow("Sobel Y Image");
	cv::imshow("Sobel Y Image", sobelY);

	// Compute norm of Sobel
	cv::Sobel(image, sobelX, CV_16S, 1, 0);
	cv::Sobel(image, sobelY, CV_16S, 0, 1);
	cv::Mat sobel;
	// Compute the L1 norm
	sobel = abs(sobelX) + abs(sobelY);
	double sobmin, sobmax;
	cv::minMaxLoc(sobel, &sobmin, &sobmax);
	cout << " Sobel value range : " << sobmin << " " << sobmax << endl;

	// Print window pixel values
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			std::cout << std::setw(5) << static_cast<int>(sobel.at<short>(i + 135, j + 362)) << " ";
			std::cout << std::endl;
		}
	}
	cout << endl;
	cout << endl;

	

	// Conversion to 8-bit image
	// sobelImage = -alpha * sobel +255
	cv::Mat sobelImage;
	sobel.convertTo(sobelImage, CV_8U, -255. / sobmax, 255);
	cv::namedWindow("Sobel Iamge");
	cv::imshow("Sobel Iamge", sobelImage);
	
	// Apply threshold to Sobel norm (low threshold value)
	cv::Mat sobelThresholded;
	cv::threshold(sobelImage, sobelThresholded, 255, 255, cv::THRESH_BINARY);
	cv::namedWindow("Binary Sobel Image (high)");
	cv::imshow("Binary Sobel Image (high)",sobelThresholded);

	// Compute Laplacian 3*3
	cv::Mat laplace;
	cv::Laplacian(image, laplace, CV_8U, 1, 1, 128);
	cv::namedWindow("Laplacian Image");
	cv::imshow("Laplacian Image", laplace);

	// Compute Laplacian using LaplacianZC class
	LaplacianZC laplacian;
	laplacian.setAperture(7);
	cv::Mat flap = laplacian.computeLaplacian(image);
	double lapmin, lapmax;
	cv::minMaxLoc(flap, &lapmin, &lapmax);
	std::cout << "Laplacian value range=[" << lapmin << "," << lapmax << "]\n";
	laplace = laplacian.getLaplacianImage();
	cv::namedWindow("Laplacian Image (7x7)");
	cv::imshow("Laplacian Image (7x7)", laplace);

	cv::waitKey();
	return 0;
}