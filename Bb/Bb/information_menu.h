#pragma once
#include "..//db/db_user.h"

//����, � ������� ���������� �������� � ��������� ����������
class information_menu
{
public:

	//������������� � ��� �������������� ����
	void SwitchInformMenu(db_user *user);

protected:

	//������ ������ 
	int ParseAnswer(int number);

	db_user* _user = NULL;
};

