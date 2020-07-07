#pragma once
#include <string>
#include <list>
#include "db_connect.h"

//������� �����
//������������ ������, ��������� �� ������� �� ������� � ��
class DB_API db_row_obj
{

public:

	//��� �������� ������� ���������� �������, ��� ���������� ������� � ��������� � ��� �������
	db_row_obj(std::string table_name, std::string func_add_name, std::string func_edit_name, std::string func_delete_name);

	virtual ~db_row_obj();

	void ShowInfo();

protected:

	//id ������ ��, � ������� ����������� ������
	int id;

	//�������, ������� ���������� ��� ��������� ���������� �� ������
	virtual void Update(std::list<std::string> params);

	//���������� � ����� ������
	db_connect* connect;

	//���������� �� ��������� � �������� ��������
	static std::string _table_name;
	static std::string _func_add_name;
	static std::string _func_edit_name;
	static std::string _func_delete_name;

};

