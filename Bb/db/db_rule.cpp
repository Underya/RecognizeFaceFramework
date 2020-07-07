#include "pch.h"
#include "db_rule.h"
#include <string>

using namespace std;

const  string db_rule::table_name = "\"rule\"";
const  string db_rule::add_proc_name = "addrule";
const  string db_rule::edit_proc_name = "editrule";
const  string db_rule::delete_proc_name = "deleterule";

db_rule::db_rule(int id)
{
	_id = id;
	//Получение информации
	//Получение информации об объекте из БД
	pg_result* res = _connect.GetOneRowById(table_name, _id);
	//Разбор результатов
	_name = PQgetvalue(res, 0, 1);
	_desc = PQgetvalue(res, 0, 2);
}

db_rule::~db_rule()
{
}

int db_rule::GetId()
{
	return _id;
}

string db_rule::GetName()
{
	return _name;
}

void db_rule::SetName(string new_name)
{
	_name = new_name;
	_db_update();
}

string db_rule::GetDesc()
{
	return _desc;
}

void db_rule::SetDesc(string new_desc)
{
	_desc = new_desc;
	_db_update();
}

std::vector<db_rule> db_rule::GetAllRule()
{
	db_connect _connect;
	string query = "select r.id from public.\"rule\" r";

	pg_result* res = _connect.GetRowWithQuerry(query);

	vector<db_rule> all_rule;

	int count = PQntuples(res);

	for (int i = 0; i < count; i++) {
		int id = atoi(PQgetvalue(res, i, 0));
		all_rule.push_back(db_rule(id));
	}

	return all_rule;
}

db_rule db_rule::AddNewRule(string name, string desc)
{
	db_connect _connect;
	//Создание нового объекта
	std::list<string> params = {name, desc};
	//Выполнение процедуры
	int new_id = _connect.ExecuteAddProcedure(add_proc_name, &params);
	return db_rule(new_id);
}

void db_rule::Delete()
{
	list<string> params = { to_string(_id) };
	_connect.ExecuteProcedure(delete_proc_name, &params);
}

void db_rule::LinkCamera(int camera)
{
	LinkedWithRuleCamer(camera, _id);
}

void db_rule::LinkPremise(db_premise premise)
{
	LinkPremise(premise.GetId());
}

void db_rule::LinkPremise(int premise)
{
	LinkedWitRulePremise(premise, _id);
}


void db_rule::LinkedWithRuleCamer(int cam, int rule)
{
	db_connect _connect;
	//Формирование параметров
	std::list<string> params = {to_string(rule), to_string(cam)};
	//Вызов процедуры добавления
	_connect.ExecuteAddProcedure("linkenrulecam", &params);
}

void db_rule::LinkedWithRule(db_premise cam, db_rule rule)
{
	LinkedWitRulePremise(cam.GetId(), rule.GetId());
}

void db_rule::LinkedWitRulePremise(int premise, int rule)
{
	db_connect _connect;
	//Формирование параметров
	std::list<string> params = { to_string(rule), to_string(premise) };
	//Вызов процедуры добавления
	_connect.ExecuteAddProcedure("linkenrulepremise", &params);
}

void db_rule::_db_update()
{
	// Собрание параметров
	std::list<string> params = { to_string(_id), _name, _desc };
	//Выполнение процедуры
	_connect.ExecuteProcedure(edit_proc_name, &params);
}
