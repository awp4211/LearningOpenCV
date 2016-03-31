#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


/*
int main()
{
	// Read input image
	cv::Mat image = cv::imread("car.jpg", 0);
	cv::namedWindow("Original Image");
	cv::imshow("Original Image", image);

	// Blur the image
	cv::Mat result;
	cv::GaussianBlur(image, result, cv::Size(5, 5), 1.5);

	// Display the blurred image
	cv::namedWindow("Gaussian filtered Image");
	cv::imshow("Gaussian filtered Image", result);

	// Get the gaussian kernel (1.5)
	cv::Mat gauss = cv::getGaussianKernel(9, 1.5, CV_32F);

	// Display kernel values
	cv::Mat_<float>::const_iterator it = gauss.begin<float>();
	cv::Mat_<float>::const_iterator itend = gauss.end<float>();
	std::cout << "[";
	for (; it != itend; ++it) {
		std::cout << *it << " ";
	}
	std::cout << "]" << std::endl;

	// Get the gaussian kernel (0.5)
	gauss = cv::getGaussianKernel(9, 0.5, CV_32F);

	// Display kernel values
	it = gauss.begin<float>();
	itend = gauss.end<float>();
	std::cout << "[";
	for (; it != itend; ++it) {
		std::cout << *it << " ";
	}
	std::cout << "]" << std::endl;

	// Blur the image with a mean filter
	cv::blur(image, result, cv::Size(5, 5));
	cv::namedWindow("Mean filtered image");
	cv::imshow("Mean filtered image", result);

	// Reduce
	cv::Mat reduce(image.rows / 2, image.cols / 2, CV_8U);
	for (int i = 0; i < reduce.rows; i++)
	{
		for (int j = 0; j < reduce.cols; j++)
			reduce.at<uchar>(i, j) = image.at<uchar>(i * 2, j * 2);
	}
	cv::namedWindow("Reduce");
	cv::imshow("Reduce", reduce);

	cv::waitKey();
	return 0;
}

*/