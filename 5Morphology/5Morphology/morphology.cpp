#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

/*
int main()
{
	cv::Mat image = cv::imread("binary.bmp");
	cv::namedWindow("Image");
	cv::imshow("Image", image);
	//Erode the image
	cv::Mat eroded;
	cv::erode(image, eroded, cv::Mat());

	cv::namedWindow("Eroded Image");
	cv::imshow("Eroded Image", eroded);

	// Dilate the image
	cv::Mat dilated;
	cv::dilate(image, dilated, cv::Mat());

	// Display the dialted image
	cv::namedWindow("Dilated Image");
	cv::imshow("Dilated Image", dilated);


	// Erode the image with a larger s.e
	cv::Mat element(7, 7, CV_8U, cv::Scalar(1));
	cv::erode(image, eroded, element);
	cv::namedWindow("Eroded Image (7x7)");
	cv::imshow("Eroded Image (7x7)", eroded);

	// Erode the image 3 times.
	cv::erode(image, eroded, cv::Mat(), cv::Point(-1, -1), 3);
	cv::namedWindow("Eroded Image (3 times)");
	cv::imshow("Eroded Image (3 times)", eroded);

	// Close the image
	cv::Mat element5(5, 5, CV_8U, cv::Scalar(1));
	cv::Mat closed; cv::morphologyEx(image, closed, cv::MORPH_CLOSE, element5);
	cv::namedWindow("Closed Image");
	cv::imshow("Closed Image", closed);

	// Open the image
	cv::Mat opened;
	cv::morphologyEx(image, opened, cv::MORPH_OPEN, element5);
	cv::namedWindow("Opened Image");
	cv::imshow("Opened Image", opened);

	// Close and Open the image
	cv::morphologyEx(image, image, cv::MORPH_CLOSE, element5);
	cv::morphologyEx(image, image, cv::MORPH_OPEN, element5);
	cv::namedWindow("Closed and Opened Image");
	cv::imshow("Closed and Opened Image", image);
	cv::imwrite("binaryGroup.bmp", image);


	cv::waitKey();
	return 0;
}
*/