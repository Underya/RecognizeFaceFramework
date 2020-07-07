
#pragma once
#include <iostream>
#include <vector>

#ifdef FILEMANAGER_EXPORTS
#define FILEMANAGER_API __declspec(dllexport)
#else
#define FILEMANAGER_API __declspec(dllimport)
#endif


//Структрура содержит информацию, аналогичную информации о лицах
struct FILEMANAGER_API face_info {

	//Идентификатор сотрудника
	int id = -1;

	//Имя сотрудника
	std::string first_name = "";

	//Фамилия сотрудника
	std::string last_name = "";

	//Отчество сотрудника
	std::string mid_name = "";

	//Описание сотрудника
	std::string descinfo = "";

	//Идентификатор человека в системе
	int other_id = -1;

	//Описание фотографии человека
	std::vector<std::string> desc;

	//Идентификаторы описаний
	std::vector<int> id_desc;
};