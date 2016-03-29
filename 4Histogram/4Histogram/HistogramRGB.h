#pragma once
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>


class HistogramRGB
{
private:
	int histSize[3];
	float hranges[2];
	const float * ranges[3];
	int channels[3];
public:
	HistogramRGB() {
		histSize[0] = histSize[1] = histSize[2] = 255;
		hranges[0] = 0.0;
		hranges[1] = 255.0;
		ranges[0] = hranges;
		ranges[1] = hranges;
		ranges[2] = hranges;
		channels[0] = 0;
		channels[1] = 1;
		channels[2] = 2;
	}

	//Compute the histogram
	cv::MatND getHistogram(const cv::Mat & image)
	{
		cv::MatND hist;
		//BGR color hisstogram
		//BGR Range
		hranges[0] = 0.0;
		hranges[1] = 255.0;
		//the three channels
		channels[0] = 0;
		channels[1] = 1;
		channels[2] = 2;
		// Compute histogram
		cv::calcHist(&image,
			1,				// histogram of 1 image only
			channels,		// the channels used
			cv::Mat(),		// no mask is used
			hist,			// the resule histogram
			3,				// 3d histogram
			histSize,		// number of bins
			ranges			// pixel value range
		);
		return hist;
	}

	// compute the sparse histogram
	cv::SparseMat getSparseHistogram(const cv::Mat &image)
	{
		cv::SparseMat hist(3, histSize, CV_32F);

		// BGR color histogram
		hranges[0] = 0.0;
		hranges[1] = 255.0;
		channels[0] = 0;
		channels[1] = 1;
		channels[2] = 2;

		// Compute histogram
		cv::calcHist(&image,
			1,
			channels,
			cv::Mat(),
			hist,
			3,
			histSize,
			ranges
		);
		return hist;
	}
};