#pragma once
#include "..//RecognitionBB/RecognitionBB.h"
#include "Initialization.h"

//�������� ������, ������ ��� ������ � �����������
class Main_menu
{
public:

	void Start();

protected:


	//�������������� ������� ����� ��������������
	void Initializate();

	//������ �������
	int ParseAnswer(int result);
	
	void LoadInformation();

	//��������, ���� �� ����� ���������� �� ������
	bool _import = false;

	db_user *_user = NULL;

	Initialization i;
};

