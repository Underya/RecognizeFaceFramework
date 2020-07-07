#pragma once 

#include "Detecter.h"
#include "IRecognitor.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include "information_camera.h"


//Реализация интерфейса для работы с видео файлами
//Для реализации используется библиотека OpenCV
class FACEDETECTION_API CameraD:
	public information_camera
{

public:
	//Метод запускает обработку файла
	virtual void Start();
	//Метод останвливает обработку файла, если такая видётся
	virtual void End();

	//Конструктор, который в качестве параметра принимает путь к файлу
	CameraD(std::string path, std::string window_name = "");
	
	//Конструктор, который в качестве параметра принимает номер камеры
	CameraD(int num, std::string window_name = "");

	//Дектруктор класса
	~CameraD();

	//Установка детектора для обнаружения лиц
	void SetDetecter(Detecter *Detect);

	//Установка распознователя
	void SetRecognition(IRecognitor *r);

	//Получить текущий установленный детектор для обнаружения лиц
	Detecter* GetDetecter();

	//Начало вывода изображения на экран
	virtual void StartShow();

	//Конец вывода изображения на экран
	virtual void EndShow();

protected:

	//Выкинуть ошиббу о том, что не удалось открыть ФАЙЛ/Камеру
	void ThrowOpenError();

	//Данный метод вызывается в начале каждого цикла работы программы 
	virtual void ControlStep();

	//Детектор, с помощью которого присходит распознование
	Detecter *myDetecter;

	//Распознователь, с помощтю которого происходит распознование
	IRecognitor* recogn;

	//Указатель на видео файл
	cv::VideoCapture *video_file;

	//Флаг, указывающий, надо ли создавать окно с изображением камеры
	bool _show = false;

	//Флаг, указывающий, надо ли камере отключаться
	bool _work = false;
};

