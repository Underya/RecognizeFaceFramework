#pragma once
#include "../db/db_user.h"
#include "db_vcam.h"

//Класс, который показывает, используеот информацю о камерах
class camera_menu
{
public:

	void Switch(db_user* user);

	//Метод выводит все камеры и предлагает пользователю выбрать по id
	int SelectCamera();

	//Показать информацию об одной камере
	void ShowOneCamera(db_vcam cam);

protected:

	//Добавление новой камеры
	void AddNewCamera();

	//Изменение информации о камере
	void EditCameraInfo();

	//Удалить информацию о камере
	void DeletCamera();

	//Разбор ответов пользователей
	int ParseAnswer(int number);

	//Показ информации о то, какие камеры связанны с данным пользователем
	void ShowInformation();

	db_user* _user = NULL;
};

