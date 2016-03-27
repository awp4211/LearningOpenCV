#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

void salt(cv::Mat &image, int n)
{
	int i, j;
	for (int k = 0; k < n; k++)
	{
		i = rand() % image.cols;
		j = rand() % image.rows;
		if (image.channels() == 1)
		{
			//»Ò¶ÈÍ¼
			image.at<uchar>(j, i) = 255;
		}
		else if (image.channels() == 3)
		{
			image.at<cv::Vec3b>(j, i)[0] = 255;
			image.at<cv::Vec3b>(j, i)[1] = 255;
			image.at<cv::Vec3b>(j, i)[2] = 255;
		}
	}
}

int main()
{
	srand(cv::getTickCount());
	cv::Mat image = cv::imread("F://car.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	cout << image.channels() << endl;
	salt(image, 3000);
	cv::namedWindow("Image");
	cv::imshow("Image", image);
	cv::imwrite("salted.bmp", image);
	cv::waitKey(0);
	return 0;
}