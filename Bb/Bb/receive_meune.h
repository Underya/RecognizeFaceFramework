#pragma once
#include "..//db/db_user.h"



//Класс, который реализует функции для работы с получателями
class receive_menu
{

public:

	void Switch(db_user user);

protected:

	void Menu();

	int ParseAnswer(int munber);

	db_user* _user = NULL;

};

