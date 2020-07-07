#pragma once
#include "..//db/db_user.h"
#include "..//db/db_group.h"

//Меню для работы с группами
class group_menu
{
public:

	//Переключить на данное меню
	void Switch(db_user* user);

	//Показ вообще всех групп
	void ShowAllGroup();

	//Выбрать группу из существующих
	int SelectGroup();

	//Показать группы для данного пользователя
	void ShowGroup(db_user* _user);

	//Показать группу и всех связанных с ней сотрудиков
	void ShowGroupAndEmloyee();

protected:

	//Связать группу с текущем пользователем
	void LinkGroup();

	//Отвязать группу от текущего пользователя
	void UnLinkGroup();

	//Разбор выбора пользователья
	int ParseAnswer(int number);

	//Добавить новую группу
	void AddNewGroup();

	//Изменить информацию о группе
	void EditGroup();

	//Удалить группу
	void DeletGroup();

	//Показать информацию о группе
	void ShowOneGroup(db_group gr);


	//Текущий пользователь
	db_user* _user = NULL;
};

