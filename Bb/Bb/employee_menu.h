#pragma once
#include "../db/db_user.h"
#include "..//db/db_employee.h"
#include "group_menu.h"	

//���� ���������� � ������������
class employee_menu
{
public :

	void Switch(db_user* user);

protected:

	//������ �������
	int ParseAnswer(int number);

	//����� ���������� �� ����� ����������
	void ShowOne(db_employee employee);

	//�������� ������, ��������� � �����������
	void ShowOneGroup(db_employee employee);

	//����� ����������
	int SelectEmployee();

	//�������� ���������� ��� ���� ��������� � ������ ������������� �����������
	void ShowInfo();

	//�������� ���������� � ������������
	void ShowInfoAndGroup();

	//�������� ������ ����������
	void AddEmployee();

	//���������� ������ ���� � ����������
	void AddNewPhoto();

	//�������� ���������� � ����������
	void EditEmployee();

	//�������� ������ �����, ��������� � �����������
	void EditeEmployeeGroup(int id);

	//�������� ������������ ������
	void AddGroup(db_employee emp);

	//������� �� ������������ ������
	void DeletGroup(db_employee emp);

	//������� ����������
	void DeleteEmployee();


	db_user* _user = NULL;
};

