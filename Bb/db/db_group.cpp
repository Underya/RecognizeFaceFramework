#include "pch.h"
#include "db_group.h"
using namespace std;
#include <string>

//����������� ����� �������
const string db_group::db_table_name = "public.group";
const string db_group::add_proc_name = "addgroup";
const string db_group::edit_proc_name = "editgroup";
const string db_group::delete_proc_name = "deletegroup";

std::list<db_group> db_group::all_group;

db_group::db_group(int id)
{
	db_connect connect;
	PGresult *res = connect.GetOneRowById(db_table_name, id);
	//��������� ����������
	this->_id = id;
	_name = PQgetvalue(res, 0, 1);
	_descript = PQgetvalue(res, 0, 2);
	//��������� id ���� ��������� �����������
	res = connect.GetRowWithQuerry("SELECT ID_employee FROM public.employee_group where id_group =" + std::to_string(id));
	//������ ����������� � ���������� � ������
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

	//������ �����������
	for (int i = 0; i < PQntuples(res); i++) {
		db_group newg(atoi(PQgetvalue(res, i, 0)));
		gv.push_back(newg);
	}

	all_group = gv;
}

std::list<db_group> db_group::GetSnapGoup(int id_employee)
{
	db_connect connect;
	//������ �� ��� id ���� �����, ��������� � �������������
	PGresult* res = connect.GetRowWithQuerry("Select id_group from public.employee_group where id_employee = " + std::to_string(id_employee));

	//������ ����������� ������
	std::list<db_group> groups;

	for (int i = 0; i < PQntuples(res); i++) {
		db_group newg(atoi(PQgetvalue(res, i, 0)));
		groups.push_back(newg);
	}

	return groups;
}

std::list<db_group*> db_group::GetLinkGroup(int id_employee)
{
	//��������� ������
	std::list<db_group*> link_group;

	//����� ���� ����� ��� ����������
	for (auto iter = all_group.begin(); iter != all_group.end(); iter++) {
		if (iter->CheckEmployeeId(id_employee)) {
			//���� ��������� �������� � ������, �� ������ ����������� ������
			link_group.push_back(&*iter);
		}
	}

	return link_group;
}

//�������� ����� ������
db_group db_group::AddNewGroup(string name, string descriptor)
{
	db_connect conn;
	//��������� ��� ������ ���������
	list<string> params = {name, descriptor};
	int id_new_obj = conn.ExecuteAddProcedure(add_proc_name, &params);
	//�������� ������� ��� ����� ������
	db_group newGroup(id_new_obj);
	//���������� ����� ������ � ������ ���� �����
	all_group.push_back(newGroup);
	//����������� �������
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
	//�������� ������ �������
	string query = "select g.id from public.\"group\" g ";

	PGresult* res  = conn.GetRowWithQuerry(query);
	int count = PQntuples(res);
	
	for (int i = 0; i < count; i++) {
		//��������� ����������
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
	//�������� ������ �������
	string query = "select g.id from public.\"group\" g where lower(g.\"name\") = lower('" + name + "')";
	//���������� �������
	PGresult *res = conn.GetRowWithQuerry(query);
	//���� ���� ����������
	if (PQntuples(res))
		//������� ��������� id
		return atoi(PQgetvalue(res, 0, 0));

	//���� ��� �����������, ������� -1
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
	//�������� ����� ����� ��������� - ������
	db_connect connect;
	//������������ ����������

	connect.GetRowWithQuerry("SELECT public.addemployeegroup(" + to_string(id_employee) + "," + to_string(_id) + ");");
}

void db_group::UnLinkEmployee(int id_employee)
{
	//�������� ����� ����� ��������� - ������
	db_connect connect;
	//������������ ����������

	connect.GetRowWithQuerry("SELECT public.deleteemployeegroup(" + to_string(id_employee) + "," + to_string(_id) + ");");
}

bool db_group::CheckEmployeeId(int id_employee)
{
	//����� ����������� id ����� ���� �����������
	for (auto iter = this->id_employee.begin(); iter != this->id_employee.end(); iter++) {
		if (*iter == id_employee) return true;
	}

	return false;
}

void db_group::_db_update()
{
	//����� ������� ��, ������� ��������� ���������� �� �������
	//������������ ����������
	list<string> parametrs = { to_string(_id), _name, _descript};
	//����� ���������
	db_connect conn;
	conn.ExecuteProcedure(edit_proc_name, &parametrs);
}
