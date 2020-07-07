#include "pch.h"
#include "db_user.h"

using namespace std;

const std::string db_user::tableName = "\"user\"";
const std::string db_user::addProcedureName = "adduser";
const std::string db_user::editProcedureName = "edituser";
const std::string db_user::deleteProcedureName = "deleteuser";

int db_user::GetId()
{
	return _id;
}

std::string db_user::GetName()
{
	return _name;
}

std::string db_user::GetDescription()
{
	return _description;
}

void db_user::SetName(std::string name)
{
	_name = name;
	_db_update();
}

void db_user::SetDescription(std::string description)
{
	_description = description;
	_db_update();
}

db_user db_user::AddNewUser(std::string name, std::string description)
{
	db_connect _connect;
	//������������ ���������� ��� ������ ���������
	list<string> params = { name, description };
	//����� ��������� � ��������� id
	int new_id = _connect.ExecuteAddProcedure(addProcedureName, &params);
	return db_user(new_id);
}

void db_user::Delete() {
	list<string> params = { to_string(_id) };
	this->_connect.ExecuteProcedure(deleteProcedureName, &params);
}

db_user *db_user::LoginToUser(std::string name)
{
	db_connect _connect;
	//����� ���������, ������� ���������, ���� �� ����� ������������ � ��
	//� ���������� ��� id, ���� ����, � -1, ���� ����
	list<string> params = { name };
	int id = _connect.ExecuteAddProcedure("loginuser", &params);

	//���� ��� ������ ������������ - �������� ������
	if (id == -1) throw exception("Exception! Not found this user!");

	//������������ ������� ������������
	return new db_user(id);
}

void db_user::LinkGroup(int id_group)
{
	db_connect _connect;
	string query = "";
	list<string> params;
	params.push_back(to_string(id_group));
	params.push_back(to_string(GetId()));
	_connect.ExecuteProcedure("linkgroupuser", &params);
}

void db_user::UnLinkGroup(int id_group)
{
	db_connect _connect;
	string query = "";
	list<string> params;
	params.push_back(to_string(id_group));
	params.push_back(to_string(GetId()));
	_connect.ExecuteProcedure("unlinkgroupuser", &params);
}

db_user::db_user()
{
}

db_user::db_user(int id)
{
	_id = id;
	//��������� ���������� �� ������� �� ��
	pg_result* res = _connect.GetOneRowById(tableName, _id);
	//������ �����������
	_name = PQgetvalue(res, 0, 1);
	_description = PQgetvalue(res, 0, 2);
}

void db_user::_db_update()
{
	//�������� ����������
	std::list<string> params = { to_string(_id), _name, _description };
	//���������� ���������
	_connect.ExecuteProcedure(editProcedureName, &params);
}
