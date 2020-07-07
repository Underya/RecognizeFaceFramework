#pragma once

#include <string>

#include "db_connect.h"

//�����, �������������� ������ user ��
class DB_API db_user :
	public db_row
{
public:

	//�������� ID �������
	int GetId();

	//�������� ��� �������
	std::string GetName();

	//�������� �������� �������
	std::string GetDescription();

	//�������� ��� ������������
	void SetName(std::string name);

	//�������� �������� ������������
	void SetDescription(std::string description);

	//���������� ������ ������������
	static db_user AddNewUser(std::string name, std::string description);

	//�������� ���������� � ������������ �� ��
	void Delete() override;

	//����������� ��� ��������� �������������
	//���� ����� ������������ ����,  - ������� �������������� � ��� ������
	//����� - ������� ����������
	static db_user* LoginToUser(std::string name);

	//��������� ������ � ���������� ������������
	void LinkGroup(int id_group);

	//�������� ������ �� ���������� ������������
	void UnLinkGroup(int id_group);

protected:

	//���������� ������������ �� ���������
	db_user();

	//�������� ������������ ����������������� � ��������� �������
	db_user(int id);

	//���������� ���������� �� ������� � ��
	void _db_update();

	//ID ������ � ��
	int _id;

	//��� ������������
	std::string _name;

	//�������� ������������
	std::string _description;

	//���������� � ��
	db_connect _connect;

	//�������� �����, ��������������� � ��������
	const static std::string tableName;
	const static std::string addProcedureName;
	const static std::string editProcedureName;
	const static std::string deleteProcedureName;
};

