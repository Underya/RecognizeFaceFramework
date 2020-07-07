
#pragma once
#include "Parralel_Detector_obj.h"
#include "Control_Thread.h"

//Класс, который сканирует изображения с камеры в отдельном потоке
//И, если установлен детектор и распознователь - обнаруживает и распознаёт
class RECOGNITIONBB_API  Parralel_Scaner_camera :
	public Control_Thread
{
public:

	//Создание сканера для указанной камеры
	Parralel_Scaner_camera(std::string Path, information_camera information);

	//Создание сканера для указанной камеры
	Parralel_Scaner_camera(int num, information_camera information);

	//Установка детектора для 
	void SetDetecter(Detecter *detecter);

	//Установка распознователя 
	void SetRecognitor(IRecognitor* recognitor);
	
	//Задать id для камеры
	void SetId(int id);

	//Получение id камеры
	int GetId();

	//Установка имени для камеры
	void SetName(std::string name);

	//Получение имени камеры
	std::string GetName();

	//Запуск работы камеры
	void StartWork();

	//Остановка камеры
	void EndWork();

	//Начать вывод изображения
	void StartShow();

	//Конец вывода изображения
	void EndShow();

private:

	//Ид камеры
	int _id = -1;

	//Название камеры. Используется для окна вывода
	std::string _name = "";

	//Создание нового объекта для обнаружения
	thread_obj* CreateNewObj() override;

	//Создание нового объекта потока
	void OpenNewThread() override;

	//Путь к камере
	std::string path = "";
	
	//Номер USB камеры
	int _numer_cam;

	Detecter* _detecter = NULL;

	IRecognitor* _recognitor = NULL;

	information_camera _information;
};

