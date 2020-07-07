#pragma once

#include <opencv2/opencv.hpp>
#include <dlib/dnn.h>

#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/image_io.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/opencv.h>


#ifdef FACEDETECTION_EXPORTS
#define FACEDETECTION_API __declspec(dllexport)
#else
#define FACEDETECTION_API __declspec(dllimport)
#endif


//������ ����� ������������ ��� �������� ������ ����� �� ����� ����� ������� ��������
//� ��������� �� ������������ ��� ������� ��� ������ Mat �� OpenCV

class FACEDETECTION_API OneFrame
{
public:
	//�����������, ��������� �� ������� Mat ������ OneFrame
	OneFrame(cv::UMat frame) {
		this->frame = frame;
	}

	OneFrame() {

	}

	OneFrame& operator=(const cv::UMat& right) {
		this->frame = right;
		return *this;
	}

	OneFrame& operator=(const cv::Mat& right) {
		this->frame = right.getUMat(cv::ACCESS_RW);
		return *this;
	}

	//���������� ������� � ���� UMat
	operator cv::UMat() { return frame; }
	 
	//���������� � ���� Mat
	operator cv::Mat() { return frame.getMat(cv::ACCESS_RW); }

	//���������� � ���� ������� dlib ��� ����
	OneFrame& operator=(const dlib::matrix<dlib::rgb_pixel> right) {
		this->dlib_frame = right;
		return *this;
	}
	

	//���������� � ���� InputArray ��� ������� face_multidetectd
	operator cv::InputArray() { return frame; }
	operator cv::InputOutputArray() { return frame; }

	dlib::matrix<dlib::rgb_pixel> dlib_frame;


	//���������� �������
	cv::UMat frame;
};

