#pragma once
#include <string>
#include <time.h>

//Структура распознавания
struct oneRecognit
{
	//Идентификатор записи
	int _id = -1;

	//Идентификатор камеры
	int _id_camera = -1;

	//Идентификатор сотрудника
	int _id_employee = -1;

	//Время распознавания
	time_t _time;
};

