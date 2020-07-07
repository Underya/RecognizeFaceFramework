#pragma once
#include <string>
#include <list>
#include "db_connect.h"

//Базовый класс
//Представляет объект, созданный по строчке из таблицы в БД
class DB_API db_row_obj
{

public:

	//При создании объекта необходимо указать, как называются таблица и связанные с ним функции
	db_row_obj(std::string table_name, std::string func_add_name, std::string func_edit_name, std::string func_delete_name);

	virtual ~db_row_obj();

	void ShowInfo();

protected:

	//id строки БД, с которой ассоцирован объект
	int id;

	//Функция, которая вызывается при изменении информации об объкте
	virtual void Update(std::list<std::string> params);

	//Соеденение с базой данных
	db_connect* connect;

	//Информация об связанных с таблицей объектах
	static std::string _table_name;
	static std::string _func_add_name;
	static std::string _func_edit_name;
	static std::string _func_delete_name;

};

