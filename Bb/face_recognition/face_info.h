#pragma once

#include <string>

using std::string;

//���������� � ����������
class employee_info
{
public:

	//�����
	int GetId();

	int GetOtherId();

protected:

	//���
	string _first_name;

	//�������
	string _last_name;

	//��������
	string _mid_name;

	//������������� �������� �� ��
	int _id = -1;

	//������������� �� �� ������ �������
	int _other_id = -1;
};

