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
	//������ �� ��� ��������� � ������� �������
	string query = "select id_rule from rule_link_camera where id_camera = ";
	query += to_string(id_cam);
	
	//���������� ������
	AppendListFromQuery(query);
}


void rules_collection::AppendRule(db_premise premise)
{
	//���������� ������ ��������� ������ ���������
	AppendRuleForOnePremmis(premise);
	
	//���������� ������ ��������� ������� ���������
	vector<db_premise> parents = premise.GetAllParent();
	
	//����������� ������
	for (auto iter = parents.begin(); iter != parents.end(); iter++) {
		db_premise premise = *iter;
		//���������� ������ ������� ������ � ��� �������
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
	//��������� ���������� ���������� �� ��������
	vector<std::pair<int, string>> coll;

	//���� �� ����� ������ ������
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
	//��������, ���� �� � ������ ������� � ����� �� id
	for (auto iter = _rules.begin(); iter != _rules.end(); iter++) {
		if (iter->GetId() == rule.GetId()) return;
	}

	//���� ��� ���������� 
	//�� ���������� ���������� � ������
	_rules.push_back(rule);
}

void rules_collection::AppendRuleForOnePremmis(db_premise premise)
{
	//������������ �������
	string query = "Select id_rule from rule_link_premise where id_premise =";
	query += to_string(premise.GetId());
	//������ �� ����������
	AppendListFromQuery(query);
}

void rules_collection::AppendListFromQuery(string query)
{
	PGresult* res = _connect.GetRowWithQuerry(query);
	//������ �����������
	for (int i = 0; i < PQntuples(res); i++) {
		int id_rule = atoi(PQgetvalue(res, i, 0));
		TryAppend(db_rule(id_rule));
	}
}
