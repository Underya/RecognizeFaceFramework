#pragma once
#include "questions_user.h"
#include "..//db/db_user.h"

class export_menu
{
public:

	//�������������� ��� ���������� 
	void Export(db_user *user);

protected:

	//������� ���������� 
	void Export_employee();

	//������� ����� � ����� � �����������
	void Export_group();

	//������� �����
	void Export_camera();

	//������� ���������
	void Export_premise();

	//������� ������
	void Export_rules();

	//�������� ������ � ������������
	void Clear_Info();

	std::string Transform_vector_to_string(float* desc);

	//���������� � ����������� � ������������
	db_user *_user = NULL;
};

