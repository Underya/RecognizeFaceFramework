#pragma once

#ifdef FACERECOGNITION_EXPORTS
#define  FACERECOGNITION_API __declspec(dllexport)
#else
#define FACERECOGNITION_API __declspec(dllimport)
#endif


#include <string>
using  std::string;

//Информация о сотруднике
class FACERECOGNITION_API employee_info
{
public:

	//Создание сотрудника
	employee_info(int id, string name, string family, string mid_name, string db_description = "");

	//Получить идентификатор сотрудника
	int GetId();

	//Установить идентификатор сотрудника
	void SetId(int id);

	//Поулчить идентификатор сотрудника из другой системы
	int GetOtherId();

	//Установить идентификатор сотрудника из другой системы
	void SetOtherId(int other_id);

	//Получить имя сотрудника
	string GetFirstName();

	//Установить имя сотрудника
	void SetFisrtName(string name);

	//Получить фамилии сотрудника
	string GetLastName();

	//Уставноить фамилию сотрудника
	void SetLastName(string family);

	//Получить отчество сотрудника
	string GetMidName();

	//Установить отчество сотрудника
	void SetMidName(string mid_name);

	//Получение описние сотрдуника из БД
	string GetDBDescriptor();

	//Установить дескриптор из БД
	void SetDBDescriptor(string db_descriptor);

protected:

	//Имя
	string _first_name;

	//Фамилия
	string _last_name;

	//Отчество
	string _mid_name;

	//Описание сотрудника из БД
	string _db_description = "";

	//Идентификатор человека из БД
	int _id = -1;

	//Идентификатор БД из другой системы
	int _other_id = -1;
};

