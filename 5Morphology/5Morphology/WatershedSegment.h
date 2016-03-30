#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class WatershedSegemnter 
{
private:
	cv::Mat markers;
public:
	void setMarkers(const cv::Mat & markerImage)
	{
		// convert to image of ints
		markerImage.convertTo(markers, CV_32S);
	}

	cv::Mat process(const cv::Mat &image)
	{
		cv::watershed(image, markers);
		return markers;
	}

	// Return result in the form of an image
	cv::Mat getSegmentation()
	{
		cv::Mat tmp;
		// all segment with label higher than 255
		// will be assigned value 255
		markers.convertTo(tmp, CV_8U);
		return tmp;
	}

	// Return watershed in the form of an image
	cv::Mat getWatersheds()
	{
		cv::Mat tmp;
		markers.convertTo(tmp, CV_8U, 255, 255);
		return tmp;
	}
};