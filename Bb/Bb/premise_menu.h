#pragma once

#include "..//db/db_user.h"
#include "..//db/db_premise.h"

//���� ������ � ����������� � ����������
class premise_menu
{
public:

	//������� � ���� ����
	void Switch(db_user* user);

	//�������� ��������� � ������ ������������� ���������
	void ShowPremise();

	//����� ���������
	int SelectPremise();

	//�������� ���������� �� ����� ��������
	std::string ShowOne(db_premise prem);

protected:
	
	//������ ������
	int ParseAnswer(int number);

	//�������� ���� ������� ��� ��������� ���������
	void ShowParent(int id_premise);

	//������� ��� ��������� � ��
	void ShowAllPremise();

	//�������� ����� ���������
	void AddPremise();

	//�������� ��������
	void EdietePremise();

	//������� ���������
	void DeletePremise();

	db_user* _user = NULL;
};

