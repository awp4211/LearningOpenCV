#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

//using .ptr and []
void colorReduce0(cv::Mat & image, int div = 64)
{
	int nl = image.rows;
	int nc = image.cols  * image.channels();

	for (int j = 0; j < nl; j++)
	{
		uchar * data = image.ptr<uchar>(j);
		for (int i = 0; i < nc; i++)
		{
			data[i] = data[i] / div * div + div / 2;
		}
	}
}

//using .ptr and * ++
void colorReduce1(cv::Mat &image, int div = 64)
{
	int nl = image.rows;
	int nc = image.cols * image.channels();

	for (int j = 0; j < nl; j++)
	{
		uchar * data = image.ptr<uchar>(j);
		for (int i = 0; i < nc; i++)
		{
			*data++ = *data / div*div + div / 2;
		}
	}
}

//using .ptr and * ++ and modulo
void colorReduce2(cv::Mat & image, int div = 64)
{
	int nl = image.rows;
	int nc = image.cols * image.channels();
	for (int j = 0; j < nl; j++)
	{
		uchar * data = image.ptr<uchar>(j);
		for (int i = 0; i < nc; i++)
		{
			int v = *data;
			*data++ = v - v%div + div / 2;
		}
	}
}

// using .ptr and * ++ and bitwise
void colorReduce3(cv::Mat &image, int div = 64) 
{
	int nl = image.rows; 
	int nc = image.cols * image.channels(); 
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	// mask used to round the pixel value
	uchar mask = 0xFF << n; // e.g. for div=16, mask= 0xF0
	for (int j = 0; j<nl; j++) 
	{
		uchar* data = image.ptr<uchar>(j);
		for (int i = 0; i<nc; i++) 
		{
			*data++ = *data&mask + div / 2;
		}               
	}
}

// direct pointer arithmetic
void colorReduce4(cv::Mat &image, int div = 64) 
{
	int nl = image.rows; 
	int nc = image.cols * image.channels(); 
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	int step = image.step; // effective width
	uchar mask = 0xFF << n; // e.g. for div=16, mask= 0xFF
	uchar *data = image.data;
	for (int j = 0; j<nl; j++) {
		for (int i = 0; i < nc; i++) {
			*(data + i) = *data&mask + div / 2;
		}
		data += step;  // next line
	}
}


#define NTESTS 14
#define NITERATIONS 20

int main()
{
	int64 t[NTESTS], tinit;
	cv::Mat image1;
	cv::Mat image2;
	for (int i = 0; i<NTESTS; i++)
		t[i] = 0;
	int n = NITERATIONS;
	for (int k = 0; k < n; k++)
	{
		cout << k << " of" << n << endl;

		image1 = cv::imread("car.jpg");
		//using .ptr and []
		tinit = cv::getTickCount();
		colorReduce0(image1);
		t[0] += cv::getTickCount() - tinit;

		image1 = cv::imread("car.jpg");
		// using .ptr and * ++ 
		tinit = cv::getTickCount();
		colorReduce1(image1);
		t[1] += cv::getTickCount() - tinit;

		image1 = cv::imread("car.jpg");
		// using .ptr and * ++ 
		tinit = cv::getTickCount();
		colorReduce2(image1);
		t[2] += cv::getTickCount() - tinit;

		image1 = cv::imread("car.jpg");
		// using .ptr and * ++ and bitwise
		tinit = cv::getTickCount();
		colorReduce3(image1);
		t[3] += cv::getTickCount() - tinit;

		image1 = cv::imread("car.jpg");
		// using direct pointer arithmetic
		tinit = cv::getTickCount();
		colorReduce4(image1);
		t[4] += cv::getTickCount() - tinit;
	}


	// print average execution time
	std::cout << std::endl << "-------------------------------------------" << std::endl << std::endl;
	std::cout << "using .ptr and [] =" << 1000.*t[0] / cv::getTickFrequency() / n << "ms" << std::endl;
	std::cout << "using .ptr and * ++ =" << 1000.*t[1] / cv::getTickFrequency() / n << "ms" << std::endl;
	std::cout << "using .ptr and * ++ and modulo =" << 1000.*t[2] / cv::getTickFrequency() / n << "ms" << std::endl;
	std::cout << "using .ptr and * ++ and bitwise =" << 1000.*t[3] / cv::getTickFrequency() / n << "ms" << std::endl;
	std::cout << "using direct pointer arithmetic =" << 1000.*t[4] / cv::getTickFrequency() / n << "ms" << std::endl;
	std::cout << "using .ptr and * ++ and bitwise with image.cols * image.channels() =" << 1000.*t[5] / cv::getTickFrequency() / n << "ms" << std::endl;
	std::cout << "using .ptr and * ++ and bitwise (continuous) =" << 1000.*t[6] / cv::getTickFrequency() / n << "ms" << std::endl;
	std::cout << "using .ptr and * ++ and bitwise (continuous+channels) =" << 1000.*t[7] / cv::getTickFrequency() / n << "ms" << std::endl;
	std::cout << "using Mat_ iterator =" << 1000.*t[8] / cv::getTickFrequency() / n << "ms" << std::endl;
	std::cout << "using Mat_ iterator and bitwise =" << 1000.*t[9] / cv::getTickFrequency() / n << "ms" << std::endl;
	std::cout << "using MatIterator_ =" << 1000.*t[10] / cv::getTickFrequency() / n << "ms" << std::endl;
	std::cout << "using at =" << 1000.*t[11] / cv::getTickFrequency() / n << "ms" << std::endl;
	std::cout << "using input/output images =" << 1000.*t[12] / cv::getTickFrequency() / n << "ms" << std::endl;
	std::cout << "using overloaded operators =" << 1000.*t[13] / cv::getTickFrequency() / n << "ms" << std::endl;

	cv::namedWindow("Image Result");
	cv::imshow("Image Result", image1);
	cv::waitKey();
}