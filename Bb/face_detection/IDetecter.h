#pragma once
#include "OneFrame.h"
#include "opencv2/opencv.hpp"

//Интерфейса для объекта
//С помощью которого происходит обнаружение на изображении лиц
class FACEDETECTION_API IDetecter
{
public:
	//Сканирование изображения
	//OneFrame of - Изображение, на котором и происходит сканирование
	virtual OneFrame ScanFrame(OneFrame of) = 0;
		
};
