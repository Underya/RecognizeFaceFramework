#pragma once
#include "db_connect.h"
#include <string>
#include <vector>

//������, ������������� � ����������� � ��������� �� ��
class DB_API db_premise :
	public db_row
{
public:

	//�������� ��������� �������
	db_premise(int id);

	//����������� �� ���������
	~db_premise();

	//ID ������� �������
	int GetId();

	//�������� ��������� 
	//�������� -1 ������� ��������
	void SetParrent(int id_premise);

	//�������� �������
	std::string GetName();

	//������� ����� ������������ �������
	void SetName(std::string new_name);

	//�������� �������
	std::string GetDesc();

	//������� ����� �������� �������
	void SetDesc(std::string new_description);
	
	//��������� ID ������
	int GetIdParent();

	//�������� �������� ��� �������� ������� ���������
	db_premise AddNewChlidren(std::string Name, std::string Desc = "");

	//��������� ������� �� ����� �������� ��� �������� ���������
	std::vector<db_premise> GetAllParent();

	//�������� ��� ��������� � �� ���������
	static std::vector<db_premise> GetAllPremise();

	//�������� ����� ������ � ���������
	static db_premise AddNewPremise(std::string Name, std::string Desc = "", int id_parent = -1);

	//�������� �������� �������
	void Delete() override;

protected:

	//���������� ���������� �� ������� � ��
	void _db_update();

	//������������� ������ �� ��
	int _id = -1;
	//������������
	std::string _name;
	//��������
	std::string _descrtipt;
	//������������� ������������� ���������
	int _id_parent = -1;

	//��������� �� ���������� � ��
	db_connect _connect;

	//���������� � �������, � ������� ������ ������
	const static std::string table_name;
	const static std::string add_proc_name;
	const static std::string edit_proc_name;
	const static std::string delete_proc_name;
};

