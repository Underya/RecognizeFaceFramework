#pragma once
#include "..//db/db_user.h"

//Меню, в котором происходит просмотр и изменение информации
class information_menu
{
public:

	//Переключиться в это информационное меню
	void SwitchInformMenu(db_user *user);

protected:

	//Разбор ответа 
	int ParseAnswer(int number);

	db_user* _user = NULL;
};

