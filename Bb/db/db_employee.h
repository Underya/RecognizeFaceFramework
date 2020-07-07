#pragma once
#include <vector>
#include "db_face.h"
#include "db_group.h"

//��������� ��� ������ ������, � �������� ���� ���� � ���� ������
class DB_API db_employee :
	public db_row
{
public:

	//������ ��������� �� ���������� � ��, � ����� �� id
	db_employee(int id);

	db_employee();

	~db_employee();

	//������ ��� ��������� ���������� � ����������

	//��� ����������
	std::string GetFirstName();
	//������� ����������
	std::string GetLastName();
	//�������� ����������
	std::string GetMidleName();
	//�������� id � ������ �������
	//-1 - ��������� id
	int GetOtherId();

	//��������� �������� ����������
	std::string GetDescrInfo();
	//��������� ������ ���� ��� ����������
	std::list<db_face> GetListDescr();
	//��������� id ������
	int GetId();
	//������ ��� ��������� ����������

	//������ ���
	void SetFirstName(std::string F_Name);
	//������ �������
	void SetLastName(std::string L_Name);
	//������ ��������
	void SetMidName(std::string M_Name);
	//������ ������������� � ������ �������
	void SetOtherId(int other_id);

	//�������� �������� ����������
	void SetDescrInfo(std::string info);

	//���������� � ���������� ������ �����������, ���������� � ������� ���������� � ��
	void AddNewDescriptor(float* desc);
	
	//���������� � ���������� ������ �����������, ���������� � ������� ���������� � ��
	void AddNewDescriptor(std::string desc);

	//�������� ������ ���������� � ���������� � �� � ��
	static db_employee* AddNewEmployee(std::string first_name, std::string last_name, std::string midle_name, std::string descInfo = "", int other_id = -1);
	
	//�������� ������� � ���������� � ��� ����� �� ��
	void Delete() override;

	//��������� ������ ���� �����������, ���������� ��� �������
	static std::vector<db_employee >* GetEmployeeWithCondition(db_group group);

	//��������� ������ ��� �����������, �� ������ ���� �����
	static std::vector<db_employee >* GetEmployeeWithCondition(std::vector<db_group> groups);

	//���������� ��������� ���������
	//��� ����, ��� �� ��� ����� ���������� ����� ������
	friend bool DB_API operator== (const db_employee& c1, const db_employee& c2);

private:

	//������ �����, � ������� �������� ������ ���������
	std::list<db_group*> _my_groups;

	//������������ ����������

	//���
	std::string _f_name;
	//�������
	std::string _l_name;
	//��������
	std::string _m_name;

	//�������� ����������
	std::string _descr;

	//������������� 
	int _other_id = -1; 


	//������ �� ����� ������ ����������
	std::list<db_face> _faceList;

	//���������� � ��
	db_connect *_connect;

	//��������� ���� ��������� � �������� ������������ �� ��
	void _ReviewAllDesc();

	//���������� ���������� �� ���������� � ��
	void _db_update() override;

	//��������� ��� ������ �������� �� ��
	//�������� ������� � �����������
	const static std::string db_table_name;
	const static std::string add_proc_name;
	const static std::string edit_proc_name;
	const static std::string delete_proc_name;
};

