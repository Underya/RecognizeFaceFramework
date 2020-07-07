#pragma once

#include <string>

using std::string;

//Информация о сотруднике
class employee_info
{
public:

	//Получ
	int GetId();

	int GetOtherId();

protected:

	//Имя
	string _first_name;

	//Фамилия
	string _last_name;

	//Отчество
	string _mid_name;

	//Идентификатор человека из БД
	int _id = -1;

	//Идентификатор БД из другой системы
	int _other_id = -1;
};

