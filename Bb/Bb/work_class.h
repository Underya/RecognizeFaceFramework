#pragma once
#include "..//RecognitionBB/RecognitionBB.h"
//�����, ������� �������� �� ������ ����������
class work_class
{
public:

	//������ ������ ���������� � �������������, 
	void Start(db_user  *user);

	//������� ������ ���������, � ���� ����������� � ��
	void ShowPremiseEmployee();

	//�������� ������ �����������, � ��� ��� ���������
	void ShowEmployeePremise();

protected:

	void Menu();

	db_user *_user = NULL;

	//������ �������
	void StartWork();

	RecognitionBB bb;
};

