#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

void sharpen(const cv::Mat &image, cv::Mat & result)
{
	result.create(image.size(), image.type());
	for (int j = 1; j < image.rows - 1; j++)
	{
		//previous row
		const uchar * previous = image.ptr<const uchar>(j - 1);
		//current row
		const uchar * current = image.ptr<const uchar>(j);
		//next row
		const uchar * next = image.ptr<const uchar>(j + 1);

		uchar * output = result.ptr<uchar>(j);

		for (int i = 1; i < image.cols - 1; i++)
		{
			*output++ = cv::saturate_cast<uchar>(5 * current[i] - current[i - 1] - current[i + 1] - previous[i] - next[i]);
		}
	}
	//set the unprocess pixels to 0
	result.row(0).setTo(cv::Scalar(0));
	result.row(result.rows - 1).setTo(cv::Scalar(0));
	result.col(0).setTo(cv::Scalar(0));
	result.col(result.cols - 1).setTo(cv::Scalar(0));
}

void sharpen2(const cv::Mat & image, cv::Mat & result)
{
	result.create(image.size(), image.type());
	int step = image.step1();
	const uchar* previous = image.data;
	const uchar* current = image.data + step;
	const uchar* next = image.data + 2 * step;
	uchar * output = result.data + step;
	for (int j = 1; j < image.rows - 1; j++)
	{
		for (int i = 1; i < image.cols - 1; i++)
		{
			output[i] = cv::saturate_cast<uchar>(5 * current[i] - current[i - 1] - current[i + 1] - previous[i] - next[i]);
		}
		previous += step;
		current += step;
		next += step;
		output += step;
	}
	result.row(0).setTo(cv::Scalar(0));
	result.row(result.rows - 1).setTo(cv::Scalar(0));
	result.col(0).setTo(cv::Scalar(0));
	result.col(result.cols - 1).setTo(cv::Scalar(0));
}

void sharpen2D(const cv::Mat & image, cv::Mat & result)
{
	//Construct kernel(all enteries initialized to -)
	cv::Mat kernel(3, 3, CV_32F, cv::Scalar(0));
	kernel.at<float>(1, 1) = 5.0;
	kernel.at<float>(2, 1) = -1.0;
	kernel.at<float>(1, 0) = -1.0;
	kernel.at<float>(1, 2) = -1.0;
	//filter the image
	cv::filter2D(image, result, image.depth(), kernel);
}

int main()
{
	cv::Mat image = cv::imread("car.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		return 0;
	}
	cv::Mat result;
	result.create(image.size(), image.type());

	double time = static_cast<double>(cv::getTickCount());
	sharpen(image, result);
	time = (static_cast<double>(cv::getTickCount() - time) / cv::getTickFrequency());
	cout << " time = " << time << endl;
	cv::namedWindow("Image");
	cv:imshow("Image", result);
	
	image = cv::imread("car.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	time = static_cast<double>(cv::getTickCount());
	sharpen2D(image, result);
	time = (static_cast<double>(cv::getTickCount() - time) / cv::getTickFrequency());
	cout << "time 2D = " << time << endl;

	cv::namedWindow("Image 2D");
	cv::imshow("Image 2D", result);

	cv::waitKey();
	return 0;
}