#include "pch.h"
#include "db_employee.h"
#include <string>
using namespace std;

const string db_employee::db_table_name = "employee";
const string db_employee::add_proc_name = "addemployee";
const string db_employee::edit_proc_name = "editemployee";
const string db_employee::delete_proc_name = "deleteemployee";

db_employee::db_employee(int id)
{
	//�������� ����������
	_connect = new db_connect();
	this->_id = id;
	//��������� ���������� � ����� �������
	//��������� ���������� �� ��
	PGresult* res = _connect->GetOneRowById(db_table_name, id);
	_descr = PQgetvalue(res, 0, 1);
	_f_name = PQgetvalue(res, 0, 2);
	_l_name = PQgetvalue(res, 0, 3);
	_m_name = PQgetvalue(res, 0, 4);
	_other_id = atoi(PQgetvalue(res, 0, 5));
	//��������� ���� ������������ ���
	_ReviewAllDesc();
	//��������� ���� �����
	_my_groups = db_group::GetLinkGroup(id);
}

db_employee::db_employee()
{
	this->_id = -1;
	this->_connect = NULL;
	this->_f_name = "Unrecognized";
}

db_employee::~db_employee()
{
	while (_my_groups.size() != 0) _my_groups.pop_front();
}

std::string db_employee::GetFirstName()
{
	return _f_name;
}

std::string db_employee::GetLastName()
{
	return _l_name;
}

std::string db_employee::GetMidleName()
{
	return _m_name;
}

int db_employee::GetOtherId()
{
	return _other_id;
}


string db_employee::GetDescrInfo()
{
	return _descr;
}

list<db_face> db_employee::GetListDescr()
{
	return _faceList;
}

int db_employee::GetId()
{
	return _id;
}

void db_employee::SetFirstName(std::string F_Name)
{
	_f_name = F_Name;
	_db_update();
}

void db_employee::SetLastName(std::string L_Name)
{
	_l_name = L_Name;
	_db_update();
}

void db_employee::SetMidName(std::string M_Name)
{
	_m_name = M_Name;
	_db_update();
}

void db_employee::SetOtherId(int other_id)
{
	_other_id = other_id;
	_db_update();
}

void db_employee::SetDescrInfo(string info)
{
	_descr = info;
	_db_update();
}

void db_employee::AddNewDescriptor(float* desc)
{
	db_face new_face = *db_face::AddNewFace(desc, _id);
	_faceList.push_back(new_face);
}

//������� �� ������ � ��� float
float* GetFloatRes(std::string s) {
	float* res = new float[128]();
	int iarr = 0;
	int is = 0;
	int ibuff = 0;
	char buff[50];
	//���� �� ���� ��������
	for (; iarr < 128; iarr++) {
		ibuff = 0;
		while (s[is] != ' ' && is < s.size()) {
			buff[ibuff++] = s[is++];
		}
		buff[ibuff] = 0;
		res[iarr] = atof(buff);
		is++;
	}

	return res;
}

void db_employee::AddNewDescriptor(std::string desc)
{
	AddNewDescriptor(GetFloatRes(desc));
}

db_employee* db_employee::AddNewEmployee(std::string first_name, std::string last_name, std::string midle_name, std::string descInfo, int other_id)
{
	db_connect newConn;
	//������� � ����������� ��� ����������
	list<string> *params = new list<string>;
	params->push_back(first_name);
	params->push_back(last_name);
	params->push_back(midle_name);
	params->push_back(descInfo);
	params->push_back(std::to_string(other_id));
	//����� ������� ��� ����������
	int id_res = newConn.ExecuteAddProcedure(add_proc_name, params);
	//�������� ������
	delete params;
	//����������� ������ ���������� ������
	return new db_employee(id_res);
}

void db_employee::Delete()
{
	list<string> l = { to_string(_id) };
	_connect->ExecuteProcedure(delete_proc_name, &l);
}


vector<db_employee>* db_employee::GetEmployeeWithCondition(db_group group)
{
	
	vector<db_employee >* list_e = new vector<db_employee >();
	db_connect* conn = new db_connect();

	std::string query = "select id_employee from employee_group where id_group =";
	query += std::to_string(group.GetId());

	PGresult *pg = conn->GetRowWithQuerry(query);

	int rows = PQntuples(pg);

	for (int i = 0; i < rows; i++) {
		//��������� �������� ID
		int id = atoi(PQgetvalue(pg, i, 0));
		//�������� ������� ����������
		db_employee emp(id);
		list_e->push_back(emp);
	}
	//�������� ���������
	delete conn;
	//����������� �����
	return list_e;
}

std::vector<db_employee>* db_employee::GetEmployeeWithCondition(std::vector<db_group> groups)
{

	//������ ��� ���� �����������
	std::vector<db_employee>* all = new vector<db_employee>(),
		//��� ������� ������
		*buff = NULL;
	
	//����� ����������� ��� ������ ������
	for (auto group = groups.begin(); group != groups.end(); group++) {
		buff = db_employee::GetEmployeeWithCondition(*group);

		//������, ��� ������� �������� �����������, ���� �� ����� � �������� �������
		for (auto currEmployee = buff->begin(); currEmployee != buff->end(); currEmployee++) {
			bool HasInVec = false;
			for (auto allEmploeyy = all->begin(); allEmploeyy != all->end(); allEmploeyy++) {
				//����� �� ����������
				if (currEmployee->GetId() == allEmploeyy->GetId()) {
					//���� ����� ��������� ��� ����
					HasInVec = true;
					break;
				}

			}
			//���� ����� ��� ����������� ����������� ��� ������
			//�� ���� �������� ��� � ������
			if(!HasInVec)
				all->push_back(*currEmployee);
		}

		//�������� ������� �� ������� ������
		delete buff;
	}

	return all;
}

void db_employee::_ReviewAllDesc()
{
	//����������� ������
	string query = "select id from face where id_employee=";
	query += std::to_string(_id);
	//������ � ��
	PGresult *res = _connect->GetRowWithQuerry(query);
	//��������� ���������� ����� � ������
	int rows = PQntuples(res);
	//��� ������� ����������� ���� �������� ���� ���������� 
	//� ����������� � ������
	for (int i = 0; i < rows; i++) {
		db_face f = db_face(atoi(PQgetvalue(res, i, 0)));
		//������ ����������� � ������
		_faceList.push_back(f);
	}
	
}

void db_employee::_db_update()
{
	//������ � �����������
	list<string> params = { to_string(_id), _f_name, _l_name, _m_name,  _descr, std::to_string(_other_id) };

	//����� ��������� ��� ���������
	_connect->ExecuteProcedure(edit_proc_name, &params);
}

bool operator==(const db_employee& c1, const db_employee& c2)
{
	if (c1._id == c2._id) return true;
	return false;
}
