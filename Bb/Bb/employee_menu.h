#pragma once
#include "../db/db_user.h"
#include "..//db/db_employee.h"
#include "group_menu.h"	

//Меню информации о пользователе
class employee_menu
{
public :

	void Switch(db_user* user);

protected:

	//Разбор ответов
	int ParseAnswer(int number);

	//Показ инфомрации об одном сотруднике
	void ShowOne(db_employee employee);

	//Показать группы, связанные с сотрудников
	void ShowOneGroup(db_employee employee);

	//Выбор сотрудника
	int SelectEmployee();

	//Показать информацию обо всех связанных с данным пользователем сотрудников
	void ShowInfo();

	//Показать информацию с сотрудниками
	void ShowInfoAndGroup();

	//Добавить нового сотрудника
	void AddEmployee();

	//Добавление нового фото к сотруднику
	void AddNewPhoto();

	//Изменить информацию о сотруднике
	void EditEmployee();

	//Изменить список групп, связанных с сотрудником
	void EditeEmployeeGroup(int id);

	//Добавить пользователю группу
	void AddGroup(db_employee emp);

	//удалить от пользователя группу
	void DeletGroup(db_employee emp);

	//Удалить сотрудника
	void DeleteEmployee();


	db_user* _user = NULL;
};

