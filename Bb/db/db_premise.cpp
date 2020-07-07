#include "pch.h"
#include "db_premise.h"
using namespace std;

const  string db_premise::table_name = "premise";
const  string db_premise::add_proc_name = "addpremise";
const  string db_premise::edit_proc_name = "editpremise";
const  string db_premise::delete_proc_name = "deletepremise";

db_premise::db_premise(int id)
{
	_id = id;
	//Если значенеи id == -1, то создаётся пустой объект
	if (_id == -1) {
		return;
	}
	//Получение информации об объекте из БД
	pg_result *res =  _connect.GetOneRowById(table_name, _id);
	//Разбор результатов
 	_name = PQgetvalue(res, 0, 1);
	_descrtipt = PQgetvalue(res, 0, 2);
	//Id_parent у объекта может отсуствовать (придёт пустая строка)
	string id_parent = PQgetvalue(res, 0, 3);
	//Тогда его значение = -1
	if (id_parent == "") {
		_id_parent = -1;
	} else {
		_id_parent = atoi(id_parent.c_str());
	}
}

db_premise::~db_premise()
{
}

int db_premise::GetId()
{
	return _id;
}

void db_premise::SetParrent(int id_premise)
{
	std::list<std::string> params = {std::to_string(_id), std::to_string(id_premise)};
	_connect.ExecuteProcedure("editepremiseparent", &params);
}

string db_premise::GetName()
{
	return _name;
}

void db_premise::SetName(string new_name)
{
	_name = new_name;
	_db_update();
}

string db_premise::GetDesc()
{
	return _descrtipt;
}

void db_premise::SetDesc(string new_description)
{
	_descrtipt = new_description;
	_db_update();
}

int db_premise::GetIdParent()
{
	return _id_parent;
}

db_premise db_premise::AddNewPremise(string Name, string Desc, int id_parent)
{
	//Формирование параетров
	//Если нет родителя, то есть id_parent == -1
	//То вместо этого отправляется пустая строка
	string parent = "null";
	if (id_parent != -1) parent = to_string(id_parent);
	//Формирование параметров
	list<string> params = { Name, Desc, parent };
	db_connect _connect;
	int new_id = _connect.ExecuteAddProcedure(add_proc_name, &params);
	//Создание нового объекта
	db_premise new_premise(new_id);
	return new_premise;
}

void db_premise::Delete()
{
	list<string> l = { to_string(_id) };
	this->_connect.ExecuteAddProcedure(delete_proc_name, &l);
}

db_premise db_premise::AddNewChlidren(string Name, string Desc)
{
	return AddNewPremise(Name, Desc, _id);
}

vector<db_premise> db_premise::GetAllParent()
{
	vector<db_premise> parents;

	db_premise currParent(_id);

	//Цикл, в ходе которого формируется вектор предков
	while (currParent.GetIdParent() != -1) {
		//Если у текущего узла есть предок
		//То для него создаётся объект
		currParent = db_premise(currParent.GetIdParent());
		//И он сохраняется в вектор пердков
		parents.push_back(currParent);
	}

	return parents;
}

std::vector<db_premise> db_premise::GetAllPremise()
{
	vector<db_premise> prem;
	db_connect conn;

	string q = "select r.id from public.premise r";

	pg_result* res = conn.GetRowWithQuerry(q);

	int count = PQntuples(res);

	for (int i = 0; i < count; i++) {
		int id = atoi(PQgetvalue(res, i, 0));
		db_premise p(id);
		prem.push_back(p);
	}

	return prem;
}

void db_premise::_db_update()
{
	//Собрание параметров
	std::list<string> params = {to_string(_id), _name, _descrtipt};
	//Выполнение процедуры
	_connect.ExecuteProcedure(edit_proc_name, &params);
}
