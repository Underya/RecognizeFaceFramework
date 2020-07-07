#include "pch.h"
#include "grPair.h"

void grPair::AddRule(int id_rule)
{
	//�������, �� �������� �� ���� �����
	if (id_rule == ALL_RULES_CODE) _all_rule = true;
	//���������� ������ �������
	_ruleList[_ruleIndex++] = id_rule;
}

void grPair::AddGroup(int id_group)
{
	//��������,�� �������� �� ���� �����
	if (id_group == ALL_GROUP_CODE) _all_group = true;
	//���������� ����� ������
	_groupList[_groupIndex++] = id_group;
}

bool grPair::AnyRule()
{
	return _all_rule;
}

bool grPair::AnyGroup()
{
	return _all_group;
}

bool grPair::HasRule(int id_rule)
{
	//��������, �� ����������� �� ���� ��� ����� �������
	if (_all_rule) return true;
	//���� ���� ����� ����� ������ - ������� ������
	for (int i = 0; i < _ruleIndex; i++) {
		if (_ruleList[i] == id_rule) return true;
	}
		
	return false;
}

bool grPair::HasGroup(int id_group)
{
	//��������, �� ����������� �� ���� ��� ����� ������
	if (_all_group) return true;
	for (int i = 0; i < _groupIndex; i++) {
		if (_groupList[i] == id_group) return true;
	}
	return false;
}
