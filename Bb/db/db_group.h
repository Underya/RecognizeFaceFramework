#pragma once
#include "db_row.h"
#include "db_connect.h"

#include <vector>

//������, � ������� ������� ������������
class DB_API db_group :
	public db_row
{
public:

	//�������� ��������� ������� �� id
	db_group(int id);

	//������ ��������� �������
	~db_group();

	//���������� ����� ���
	void SetName(std::string name);

	//���������� ����� ���������
	void SetDescript(std::string description);

	//��������� ���������� � ������
	void SnapEmployee(int id_employee);

	//���������� �����
	void UnLinkEmployee(int id_employee);

	//�������� ���� �����, �������������� �������
	static void LoadedAllGroup(int id_user);

	//����� ������ ��� ���������� ����� ���� �����
	static std::list<db_group> GetSnapGoup(int id_employee);

	//��������� ���������� �� ��� ����������� ������, ��� �������� � �����������
	static std::list<db_group*> GetLinkGroup(int id_employee);

	//���������� ����� ������
	static db_group AddNewGroup(std::string name, std::string descriptor);

	//�������� ��� ����������� � ���������� ������
	static  std::vector<db_group> GetAllGroup();

	//�������� ��� ������ �� ��
	static std::vector<db_group> GetAllGroupToDB();

	//������� ������ �� ������
	void Delete() override;

	//����� ������ ����� ���� ����� �� ����� 
	static int SerachGroup(std::string name);

	//��������� ID ������
	int GetId();

	//��������� ����� ������
	std::string GetName();

	//��������� �������� ������
	std::string GetDesc();

private:

	//��������, �������� �� ��������� � ��������� id � ������
	bool CheckEmployeeId(int id_employee);

	//������ id �����������, ������� ��������� � ������
	std::list<int> id_employee;

	//�������� ������� ������
	std::string _name;

	//�������� ������� ������
	std::string _descript;

	//�����, ���������� ��� ��������� ���������� �� �������� ������
	void _db_update();

	//��� ������� �����, ������� ������� � ������ �������������
	static std::list<db_group> all_group;

	//��������� ��� ������ �������� �� ��
	//�������� ������� � �����������
	const static std::string db_table_name;
	const static std::string add_proc_name;
	const static std::string edit_proc_name;
	const static std::string delete_proc_name;
};

