#pragma once
#include <iostream>
#include <list>
#include <string>

#ifdef DB_EXPORTS
#define DB_API __declspec(dllexport)
#else
#define DB_API __declspec(dllimport)
#endif

//Условие, которое передаётся в параметрах 
//При получение некоторого множетсва объектов с информацией из БД
//(Например - камеры, расположенные на одном заводе)
class DB_API Condition
{
public:

	Condition();

	//добавить название группы, которое необходимо учесть 
	void AddGroup(int id_group);

	//Все группы, которые необходимо получить
	std::list<int> GetGroup();

	//Очищение списка груп
	void ClearGroup();

	//Добавление помещения, информация о котором необходимо получить
	void AddPremise(int id_premise);

	std::list<int> GetPremise();

	void ClearPremise();



private:
	//Список групп, которые надо получить
	std::list<int> _group;

	std::list<int> _premise;
};

