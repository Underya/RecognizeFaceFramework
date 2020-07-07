#pragma once

#define MAX_ELEMENT_SIZE 20
//����������� �������������, ����������� ��� ���� �������� ��� ���� ������
#define ALL_RULES_CODE -1
//����������� �������������, ����������� ��� ���� �������� ��� ���� �����
#define ALL_GROUP_CODE -1

#ifdef MESSAGESERVER_EXPORTS
#define MESSAGESERVER_API __declspec(dllexport)
#else
#define MESSAGESERVER_API __declspec(dllimport)
#endif


//���� �� ������ � �������
class MESSAGESERVER_API grPair
{
public:

	//�������� �������
	void AddRule(int id_rule);

	//�������� ������
	void AddGroup(int id_group);

	bool AnyRule();

	bool AnyGroup();

	//���������� ������, ���� ����� ������� ���� � ����
	bool HasRule(int id_rule);

	//���������� ������, ���� ����� ������ ���� � ����
	bool HasGroup(int id_group);

protected:

	//�������� �� ���� ����������� ��� ����� �������
	bool _all_group = false;

	//�������� �� ���� ����������� ��� ����� ������
	bool _all_rule = false;

	//������� �������� � ������ �����
	int _groupIndex = 0;

	//������ �� ����� �������� � ����
	int _groupList[MAX_ELEMENT_SIZE];

	//������� ������� � ������ ������
	int _ruleIndex = 0;

	//������ �� ����� ��������� � ����
	int _ruleList[MAX_ELEMENT_SIZE];
};

