
#pragma once 
#include "..//face_detection/Camera_file.h"
#include "limited_pipe.h"
#include "thread_obj.h"
#include <opencv2/core/ocl.hpp>

//Объект паррелельного распознования 
class RECOGNITIONBB_API  Parralel_Detector_obj :
	public CameraD,
	public thread_obj
{
public:

	//Конструктор с указанием номера камеры
	Parralel_Detector_obj(int num, information_camera information);

	//Конструктор с указанием пути к камере
	Parralel_Detector_obj(std::string path, information_camera information);

protected:

	void SetCameraInfromation(information_camera infrom);

	//Метод вызывается внутри класса Camera_file
	void ControlStep() override;

	//Разбор сообщений управления
	void ParseControlMess() override;

	//Главный метод потока
	void ThreadMethod() override;
};

