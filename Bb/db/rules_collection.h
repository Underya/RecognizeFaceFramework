#pragma once
#include "db_rule.h"
#include "db_vcam.h"
#include <list>

//Коллекция правил, которая самостоятельно избавляется от повторов
class DB_API rules_collection
{
public:

	rules_collection();

	~rules_collection();

	//Добавление всех правил, связанных с камерой
	//Без учёта помещений
	void AppendRule(db_vcam vcam);

	//Добавление всех правил, свяазнных с помещением
	void AppendRule(db_premise premise);

	//Получение ВСХЕ правил, связанных с камерой
	void LoadAlRuleLinkCam(db_vcam vcam);

	//Получение ВСХЕ правил, связанных с камерой
	void LoadAlRuleLinkCam(int id_vcam);

	//Получение информации обо всех правилах, что содержатся в коллекции
	std::vector<std::pair<int, std::string>> GetAllRule();

	//Получение полной информации обо всех правилах, что содержатся в коллекции
	std::list<db_rule> GetAllRuleFull();

	//Добавление правила только для одного здания (То есть без учёта предков)
	void AppendRuleForOnePremmis(db_premise premise);

protected:

	//Добавление в коллекцию правила, если такого нет в коллекции
	void TryAppend(db_rule rule);

	//Соедененеи с базой данных
	db_connect _connect;
	
	//Выполнение запроса и заполнение списка его результатами
	void AppendListFromQuery(std::string query);

	//Список всех правил
	std::list<db_rule> _rules;

};

