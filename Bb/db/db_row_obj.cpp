#include "pch.h"
#include "db_row_obj.h"

std::string db_row_obj::_table_name = "base_name_table";
std::string db_row_obj::_func_edit_name = "base_name_edit";
std::string db_row_obj::_func_add_name = "base_name_add";
std::string db_row_obj::_func_delete_name = "base_name_delete";

db_row_obj::db_row_obj(std::string table_name, std::string func_add_name, std::string func_edit_name, std::string func_delete_name)
{
	//Сохарнение новой информации
	_table_name = table_name;
	_func_add_name = func_add_name;
	_func_edit_name = func_edit_name;
	_func_delete_name = func_delete_name;
	connect = new db_connect();
	id = -1;
}

db_row_obj::~db_row_obj()
{
	//Удаление соеденения с БД
	delete connect;
}

void db_row_obj::ShowInfo()
{
}

//Вызов соотсветвющей процедуры
void db_row_obj::Update(std::list<std::string> params)
{
	connect->ExecuteAddProcedure(_func_edit_name, &params);
}

