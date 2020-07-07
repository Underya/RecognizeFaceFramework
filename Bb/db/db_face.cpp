#include "pch.h"
#include "db_face.h"
#include <string>
#include <list>
using namespace std;

//�������� ����� ����������
const string db_face::db_table_name = "face";
const string db_face::add_proc_name = "addface";
const string db_face::edit_proc_name = "editface";
const string db_face::delete_proc_name = "deleteface";
int db_face::descriptSize = 128;

db_face::db_face(int id)
{
	//�������� ������ ��������� � ��
	connect = new db_connect();
	//��������� ������ ��� ������ �� �����
	descript = new float[128]();
	//��������� �������� id
	this->_id = id;

	//��������� ���������� �� ��
	PGresult* res = connect->GetOneRowById(db_table_name, id);

	//������� ���������� ���������� � ������
	this->id_employee = atoi(PQgetvalue(res, 0, 2));
	//���������� ������������� �� ������
	SetDescriptFromChar(PQgetvalue(res, 0, 1));
}

db_face::~db_face()
{
	//�������� ���������� ������
}

int db_face::GetId()
{
	return _id;
}

int db_face::GetIdEmployee()
{
	return id_employee;
}

float* db_face::GetDescriptor()
{
	return descript;
}

int db_face::GetDescriptorSize()
{
	return descriptSize;
}

void db_face::ShowInfo()
{
	cout << "Face. id:" << _id;
	cout << " id_empl:" << id_employee << endl;
}

void db_face::Delete()
{
	//������������ ���������� ��� �������
	list<string> l;
	l.push_back(to_string(_id));
	//����� ���������
	connect->ExecuteProcedure(delete_proc_name, &l);
}

db_face* db_face::AddNewFace(float* descriptor, int id_employe)
{
	//�������� ������ ���������� � ��
	db_connect c;
	//�������� ����������
	//���������� ������ �����������
	string desc = db_face::TransformToString(descriptor);
	//������������� ����������
	string id_e = to_string(id_employe);
	//������ ��� �������� ���������� � �������
	list<string> params;
	params.push_back(desc);
	params.push_back(id_e);

	//����� �������� ���������� � ��������� id ����� ������
	int new_id =  c.ExecuteAddProcedure(db_face::add_proc_name, &params);

	//�������� ������ �������
	db_face *nf = new db_face(new_id);
	//����������� �������
	return nf;
}

int db_face::SearchFace(float* descriptor)
{
	//�������� ������ ���������� � ��
	db_connect c;
	//�������� ����������
	//���������� ������ �����������
	string desc = db_face::TransformToString(descriptor);
	//�������� ������ � �����������
	list<string> params;
	params.push_back(desc);
	int search_id = -1;
	//����� �������� �� ������ ���
	try {
		search_id = c.ExecuteAddProcedure("searchface", &params);
	}
	catch (...) {
		return -1;
	}
	//����������� ����������
	return search_id;
}

int db_face::SearchFace(string descriptor)
{
	//�������� ������ ���������� � ��
	db_connect c;

	descriptor = "{" + descriptor;

	//��� ������� ������ ���� �������� �� ,
	for (int i = 0; i < descriptor.size(); i++) {
		if (descriptor[i] == ' ') descriptor[i] = ',';
	}

	descriptor[descriptor.size() - 1] = '}';

	//�������� ������ � �����������
	list<string> params;
	params.push_back(descriptor);

	//����� �������� �� ������ ���
	int search_id = c.ExecuteAddProcedure("searchface", &params);

	//����������� ����������
	return search_id;

}

void db_face::SetDescriptFromChar(char* descr)
{
	//���������� ������ ����� ��������� ������
	//{1.0,2.0,10e-8,...}
	//����� - descriptorSize �����
	//������, ����������� �� ��, ����� ������� ������ �����������
	int indexFloat = 0;
	//������, � ������� �������� ������������ ������ ������
	int indexStr = 1;

	//������, ���� ������������ ������� �� ����������� ������
	char buff[30];
	//������ ��� �������
	int indexBuff = 0;

	//���������� ����������� ��� ��������
	for (int size = descriptSize; indexFloat < size; indexFloat++) {
		//���������� �������
		indexBuff = 0;
		while (descr[indexStr] != ',' && descr[indexStr] != '}') {
			buff[indexBuff++] = descr[indexStr++];
		}
		//�������� �� ����� ������ � �������
		buff[indexBuff] = 0;
		//����������� ������ ������� � �����
		descript[indexFloat] = atof(buff);
		//���������� ������� ���������������, ����� descr[indexStr] == ','
		//������� � ���������� �������, ����������� ������
		indexStr++;
	}

}

string db_face::TransformToString(float* desc)
{
	//���������� ��� ���������� ����������
	string result = "{";
	//������ ���� ����������

	for (int i = 0; i < descriptSize; i++) {
		result += std::to_string(desc[i]) + ",";
	}

	//��������� ������ "," ���������� �� "}"
	result[result.size() - 1] = '}';

	return result;
}

void db_face::_db_update()
{

}
