#pragma once
#include "..//db/db_user.h"
#include "..//db/db_group.h"

//���� ��� ������ � ��������
class group_menu
{
public:

	//����������� �� ������ ����
	void Switch(db_user* user);

	//����� ������ ���� �����
	void ShowAllGroup();

	//������� ������ �� ������������
	int SelectGroup();

	//�������� ������ ��� ������� ������������
	void ShowGroup(db_user* _user);

	//�������� ������ � ���� ��������� � ��� ����������
	void ShowGroupAndEmloyee();

protected:

	//������� ������ � ������� �������������
	void LinkGroup();

	//�������� ������ �� �������� ������������
	void UnLinkGroup();

	//������ ������ �������������
	int ParseAnswer(int number);

	//�������� ����� ������
	void AddNewGroup();

	//�������� ���������� � ������
	void EditGroup();

	//������� ������
	void DeletGroup();

	//�������� ���������� � ������
	void ShowOneGroup(db_group gr);


	//������� ������������
	db_user* _user = NULL;
};

