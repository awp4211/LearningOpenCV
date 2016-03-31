#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class LaplacianZC {
private:
	cv::Mat img;
	cv::Mat laplace;
	// Aperture size of the laplacian kernel
	int aperture;
public:
	LaplacianZC():aperture(3){}
	// Compute the floating point laplacian
	cv::Mat computeLaplacian(const cv::Mat& image) {
		// Compute Laplacian
		cv::Laplacian(image, laplace, CV_32F, aperture);
		img = image.clone();
		return laplace;
	}
	
	// 返回8位图像存储的Laplacian结果
	cv::Mat getLaplacianImage(double scale = -1.0) {
		if(scale < 0)
		{
			double lapmin, lapmax;
			cv::minMaxLoc(laplace, &lapmin, &lapmax);
			scale = 127 / std::max(-lapmin, lapmax);
		}
		cv::Mat laplaceImage;
		laplace.convertTo(laplaceImage, CV_8U, scale, 128);
		return laplaceImage;
	}

	int getAperture() {
		return aperture;
	}

	void setAperture(int a) {
		this->aperture = a;
	}
};