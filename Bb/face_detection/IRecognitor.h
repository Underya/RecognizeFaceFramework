#pragma once
#include "OneFrame.h"
#include "information_camera.h"
#include <vector>

//Интерфейс, с помощью который должен наследовать объект для распознования
class FACEDETECTION_API IRecognitor
{
public:
	//Данный метод получает на каждой итерации массив с обнаруженными лицами
	virtual void Recognition(std::vector<OneFrame> vector_frame, information_camera cam) = 0;

	//Метод, вызываемый при окончании работы
	virtual void EndWork() = 0;

	//Идентификатор камеры
	int _id_cam = -1;

};



