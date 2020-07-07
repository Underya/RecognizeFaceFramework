#include "pch.h"
#include "rules_collection.h"

using namespace std;

rules_collection::rules_collection()
{

}

rules_collection::~rules_collection()
{

}

void rules_collection::AppendRule(db_vcam vcam)
{
	int id_cam = vcam.GetId();
	//Запрос на все связанные с камерой правила
	string query = "select id_rule from rule_link_camera where id_camera = ";
	query += to_string(id_cam);
	
	//Заполнение списка
	AppendListFromQuery(query);
}


void rules_collection::AppendRule(db_premise premise)
{
	//Заполнение списка правилами самого помещения
	AppendRuleForOnePremmis(premise);
	
	//Заполнение списка правилами предков помещения
	vector<db_premise> parents = premise.GetAllParent();
	
	//Циклическйи разбор
	for (auto iter = parents.begin(); iter != parents.end(); iter++) {
		db_premise premise = *iter;
		//Заполнение списка правила предка и его предков
		AppendRuleForOnePremmis(premise);
	}
}

void rules_collection::LoadAlRuleLinkCam(db_vcam vcam)
{
	AppendRule(vcam);
	if (vcam.GetPremise().GetId() != -1) {
		AppendRule(vcam.GetPremise());
	}
}

void rules_collection::LoadAlRuleLinkCam(int id_vcam)
{
	LoadAlRuleLinkCam(db_vcam(id_vcam));
}

std::vector<std::pair<int, string>> rules_collection::GetAllRule()
{
	//Получение упрощённой информации об правилах
	vector<std::pair<int, string>> coll;

	//Цикл по всему списку правил
	for (auto iter = _rules.begin(); iter != _rules.end(); iter++) {
		pair<int, string> rule;
		rule.first = iter->GetId();
		rule.second = iter->GetName();
		coll.push_back(rule);
	}

	return coll;
}

std::list<db_rule> rules_collection::GetAllRuleFull()
{
	return _rules;
}

void rules_collection::TryAppend(db_rule rule)
{
	//Проверка, есть ли в списке правило с таким же id
	for (auto iter = _rules.begin(); iter != _rules.end(); iter++) {
		if (iter->GetId() == rule.GetId()) return;
	}

	//Если нет одинаковых 
	//До происходит добавление в список
	_rules.push_back(rule);
}

void rules_collection::AppendRuleForOnePremmis(db_premise premise)
{
	//Формирование запроса
	string query = "Select id_rule from rule_link_premise where id_premise =";
	query += to_string(premise.GetId());
	//Запрос на добавление
	AppendListFromQuery(query);
}

void rules_collection::AppendListFromQuery(string query)
{
	PGresult* res = _connect.GetRowWithQuerry(query);
	//Разбор результатов
	for (int i = 0; i < PQntuples(res); i++) {
		int id_rule = atoi(PQgetvalue(res, i, 0));
		TryAppend(db_rule(id_rule));
	}
}
