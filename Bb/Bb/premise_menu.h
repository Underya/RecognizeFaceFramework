#pragma once

#include "..//db/db_user.h"
#include "..//db/db_premise.h"

//Меню работы с информацией о помещениях
class premise_menu
{
public:

	//Перейти в этом меню
	void Switch(db_user* user);

	//Показать связанные с данным пользователем помещения
	void ShowPremise();

	//Выбор помещения
	int SelectPremise();

	//Показать информацию об одном помещнии
	std::string ShowOne(db_premise prem);

protected:
	
	//Разбор ответа
	int ParseAnswer(int number);

	//Показать всех предков для указнного помещения
	void ShowParent(int id_premise);

	//Показат все помещения в БД
	void ShowAllPremise();

	//Добавить новое помещение
	void AddPremise();

	//Изменить помещеие
	void EdietePremise();

	//Удалить помещение
	void DeletePremise();

	db_user* _user = NULL;
};

