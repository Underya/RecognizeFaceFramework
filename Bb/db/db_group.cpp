#include "pch.h"
#include "db_group.h"
using namespace std;
#include <string>

//Обозначение имени таблицы
const string db_group::db_table_name = "public.group";
const string db_group::add_proc_name = "addgroup";
const string db_group::edit_proc_name = "editgroup";
const string db_group::delete_proc_name = "deletegroup";

std::list<db_group> db_group::all_group;

db_group::db_group(int id)
{
	db_connect connect;
	PGresult *res = connect.GetOneRowById(db_table_name, id);
	//Получение информации
	this->_id = id;
	_name = PQgetvalue(res, 0, 1);
	_descript = PQgetvalue(res, 0, 2);
	//Получение id всех связанных сотрудников
	res = connect.GetRowWithQuerry("SELECT ID_employee FROM public.employee_group where id_group =" + std::to_string(id));
	//Разбор результатов и добавление в массив
	for (int i = 0; i < PQntuples(res); i++) {
		this->id_employee.push_back(atoi(PQgetvalue(res, i, 0)));
	}
}

db_group::~db_group()
{
}

void db_group::LoadedAllGroup(int id_user)
{
	db_connect connect;
	std::string query = "select g.id_group from group_user g where g.id_user=";
	query += std::to_string(id_user);
	PGresult* res = connect.GetRowWithQuerry(query);

	list<db_group> gv;

	//Разбор результатов
	for (int i = 0; i < PQntuples(res); i++) {
		db_group newg(atoi(PQgetvalue(res, i, 0)));
		gv.push_back(newg);
	}

	all_group = gv;
}

std::list<db_group> db_group::GetSnapGoup(int id_employee)
{
	db_connect connect;
	//Запрос на все id всех групп, связанных с пользователем
	PGresult* res = connect.GetRowWithQuerry("Select id_group from public.employee_group where id_employee = " + std::to_string(id_employee));

	//Список результатов поиска
	std::list<db_group> groups;

	for (int i = 0; i < PQntuples(res); i++) {
		db_group newg(atoi(PQgetvalue(res, i, 0)));
		groups.push_back(newg);
	}

	return groups;
}

std::list<db_group*> db_group::GetLinkGroup(int id_employee)
{
	//Связанные группы
	std::list<db_group*> link_group;

	//Поиск всех групп для сотрудника
	for (auto iter = all_group.begin(); iter != all_group.end(); iter++) {
		if (iter->CheckEmployeeId(id_employee)) {
			//Есть сотрудник привязан к группе, на группу сохраняется ссылка
			link_group.push_back(&*iter);
		}
	}

	return link_group;
}

//Создание новой группы
db_group db_group::AddNewGroup(string name, string descriptor)
{
	db_connect conn;
	//параметры для вызова процедуры
	list<string> params = {name, descriptor};
	int id_new_obj = conn.ExecuteAddProcedure(add_proc_name, &params);
	//Создание объекта для новой группы
	db_group newGroup(id_new_obj);
	//Добавление новый группы в список всех групп
	all_group.push_back(newGroup);
	//Возвращение объекта
	return newGroup;
}

std::vector<db_group> db_group::GetAllGroup()
{

	std::vector<db_group> vec;

	for (auto iter = all_group.begin(); iter != all_group.end(); iter++) {
		vec.push_back(*iter);
	}

	return vec;
}

std::vector<db_group> db_group::GetAllGroupToDB()
{
	std::vector<db_group> v;
	db_connect conn;
	//Создание текста запроса
	string query = "select g.id from public.\"group\" g ";

	PGresult* res  = conn.GetRowWithQuerry(query);
	int count = PQntuples(res);
	
	for (int i = 0; i < count; i++) {
		//Получение информации
		int id = atoi(PQgetvalue(res, i, 0));
		db_group g(id);
		v.push_back(g);
	}

	return v;
}

void db_group::Delete()
{
	std::list<std::string> l = { std::to_string(_id) };
	db_connect conn;
	conn.ExecuteProcedure(delete_proc_name, &l);
}

int db_group::SerachGroup(string name)
{
	db_connect conn;
	//Создание текста запроса
	string query = "select g.id from public.\"group\" g where lower(g.\"name\") = lower('" + name + "')";
	//Выполнение запроса
	PGresult *res = conn.GetRowWithQuerry(query);
	//Если есть результаты
	if (PQntuples(res))
		//Вернуть найденный id
		return atoi(PQgetvalue(res, 0, 0));

	//Если нет результатов, вернуть -1
	return -1;
}

int db_group::GetId()
{
	return _id;
}

string db_group::GetName()
{
	return _name;
}

string db_group::GetDesc()
{
	return _descript;
}

void db_group::SetName(string name)
{
	_name = name;
	_db_update();
}

void db_group::SetDescript(string description)
{
	_descript = description;
	_db_update();
}

void db_group::SnapEmployee(int id_employee)
{
	//Добавить новую связь сотрудник - группа
	db_connect connect;
	//Формирование параметров

	connect.GetRowWithQuerry("SELECT public.addemployeegroup(" + to_string(id_employee) + "," + to_string(_id) + ");");
}

void db_group::UnLinkEmployee(int id_employee)
{
	//Добавить новую связь сотрудник - группа
	db_connect connect;
	//Формирование параметров

	connect.GetRowWithQuerry("SELECT public.deleteemployeegroup(" + to_string(id_employee) + "," + to_string(_id) + ");");
}

bool db_group::CheckEmployeeId(int id_employee)
{
	//Поиск переданного id среди всех сотрудников
	for (auto iter = this->id_employee.begin(); iter != this->id_employee.end(); iter++) {
		if (*iter == id_employee) return true;
	}

	return false;
}

void db_group::_db_update()
{
	//Вызов функции БД, которая обновляет информацию об объекте
	//Формирование парамтеров
	list<string> parametrs = { to_string(_id), _name, _descript};
	//Вызов процедуры
	db_connect conn;
	conn.ExecuteProcedure(edit_proc_name, &parametrs);
}
