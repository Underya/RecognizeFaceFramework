#pragma once
#include "db_rule.h"
#include "db_vcam.h"
#include <list>

//��������� ������, ������� �������������� ����������� �� ��������
class DB_API rules_collection
{
public:

	rules_collection();

	~rules_collection();

	//���������� ���� ������, ��������� � �������
	//��� ����� ���������
	void AppendRule(db_vcam vcam);

	//���������� ���� ������, ��������� � ����������
	void AppendRule(db_premise premise);

	//��������� ���� ������, ��������� � �������
	void LoadAlRuleLinkCam(db_vcam vcam);

	//��������� ���� ������, ��������� � �������
	void LoadAlRuleLinkCam(int id_vcam);

	//��������� ���������� ��� ���� ��������, ��� ���������� � ���������
	std::vector<std::pair<int, std::string>> GetAllRule();

	//��������� ������ ���������� ��� ���� ��������, ��� ���������� � ���������
	std::list<db_rule> GetAllRuleFull();

	//���������� ������� ������ ��� ������ ������ (�� ���� ��� ����� �������)
	void AppendRuleForOnePremmis(db_premise premise);

protected:

	//���������� � ��������� �������, ���� ������ ��� � ���������
	void TryAppend(db_rule rule);

	//���������� � ����� ������
	db_connect _connect;
	
	//���������� ������� � ���������� ������ ��� ������������
	void AppendListFromQuery(std::string query);

	//������ ���� ������
	std::list<db_rule> _rules;

};

