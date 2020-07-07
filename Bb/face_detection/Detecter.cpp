#include "pch.h"
#include "Detecter.h"
#include "opencv2/core/ocl.hpp"
#include "opencv2/imgproc.hpp" 
using namespace cv;
#include <stdio.h>

using namespace dlib;

std::vector<OneFrame> Detecter::ScanFrame(OneFrame oneFrame) {
	//Массив для всех лиц, найденых в кадре
	std::vector<OneFrame> result;

	clock_t start = clock();
	//Получение всего массива лиц с фотографии
	dlib::cv_image<dlib::rgb_pixel> cv_im(oneFrame.frame.getMat(ACCESS_RW));

	for (auto face : detector(cv_im)) {
		//auto shape = sp(cv_im, face);
		dlib::matrix<dlib::rgb_pixel> face_chip;
		dlib::chip_dims chd(150, 150);
		dlib::chip_details cd(face,chd, 0.25);
		extract_image_chip(cv_im, cd, face_chip);
		OneFrame f;
		f = face_chip;
		//f = dlib::toMat(face_chip);
		result.push_back(f);
	}
	

	clock_t finish = clock();
	double dur = (double)(finish - start) / CLOCKS_PER_SEC;
	/*
	//Если лиц не обнаружено - конец обработки
	if (faces.size() == 0) return result;

	OneFrame f2 = oneFrame.frame;
	cv::UMat frame;
	frame = f2.frame;
	//Каждое лицо - вырезается на отдельный фрейм
	for (int i = 0; i < faces.size(); i++) {
		//cv::Point center(faces[i].x + faces[i].width * 0.5, faces[i].y + faces[i].height * 0.5);
		//ellipse(frame, center, cv::Size(faces[i].width * 0.5, faces[i].height * 0.5), 0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0);
		//Вырезание лиц на каждом кадре
		UMat newFrame(frame, faces[i]);
		OneFrame o = newFrame;
		result.push_back(o);
	}

	*/
	return result;
}

Detecter::Detecter() {
	
	detector = dlib::get_frontal_face_detector();
	dlib::deserialize("shape_predictor_5_face_landmarks.dat") >> sp;

}

Detecter::~Detecter() {
}