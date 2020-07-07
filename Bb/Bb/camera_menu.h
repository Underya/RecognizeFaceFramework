#pragma once
#include "../db/db_user.h"
#include "db_vcam.h"

//�����, ������� ����������, ����������� ��������� � �������
class camera_menu
{
public:

	void Switch(db_user* user);

	//����� ������� ��� ������ � ���������� ������������ ������� �� id
	int SelectCamera();

	//�������� ���������� �� ����� ������
	void ShowOneCamera(db_vcam cam);

protected:

	//���������� ����� ������
	void AddNewCamera();

	//��������� ���������� � ������
	void EditCameraInfo();

	//������� ���������� � ������
	void DeletCamera();

	//������ ������� �������������
	int ParseAnswer(int number);

	//����� ���������� � ��, ����� ������ �������� � ������ �������������
	void ShowInformation();

	db_user* _user = NULL;
};

