#pragma once
#include "OneFrame.h"
#include <vector>



class FACEDETECTION_API  Detecter 
{
public:
	//Функция, с помощью которой анализируется отдельный кадр видео
	virtual std::vector<OneFrame> ScanFrame(OneFrame oneFrame);

	//Конструктор объекта по умолчнию
	Detecter();
	
	virtual ~Detecter();


protected:

	dlib::frontal_face_detector detector;

	//
	dlib::shape_predictor sp;

	//Классификатор, с помощью которого и происходит обнаружение лиц
};

