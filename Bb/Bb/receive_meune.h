#pragma once
#include "..//db/db_user.h"



//�����, ������� ��������� ������� ��� ������ � ������������
class receive_menu
{

public:

	void Switch(db_user user);

protected:

	void Menu();

	int ParseAnswer(int munber);

	db_user* _user = NULL;

};

