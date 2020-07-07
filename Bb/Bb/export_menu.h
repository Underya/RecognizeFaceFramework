#pragma once
#include "questions_user.h"
#include "..//db/db_user.h"

class export_menu
{
public:

	//Ёкспоритровать всю информацию 
	void Export(db_user *user);

protected:

	//Ёкспорт сотрудникв 
	void Export_employee();

	//Ёкспорт групп и св€зи с отрудниками
	void Export_group();

	//Ёкспорт камер
	void Export_camera();

	//Ёкспорт помещений
	void Export_premise();

	//Ёкспорт правил
	void Export_rules();

	//ќчищение файлов с сохранени€ми
	void Clear_Info();

	std::string Transform_vector_to_string(float* desc);

	//»нформаци€ о подключении к пользователю
	db_user *_user = NULL;
};

