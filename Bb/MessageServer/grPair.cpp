#include "pch.h"
#include "grPair.h"

void grPair::AddRule(int id_rule)
{
	//Провека, не является ли спец кодом
	if (id_rule == ALL_RULES_CODE) _all_rule = true;
	//Добавление нового правила
	_ruleList[_ruleIndex++] = id_rule;
}

void grPair::AddGroup(int id_group)
{
	//Проверка,не являетля ли спец кодом
	if (id_group == ALL_GROUP_CODE) _all_group = true;
	//Добавление новой группы
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
	//Проверка, не применяется ли пара при любом правиле
	if (_all_rule) return true;
	//Если есть такой среди правил - вернуть истину
	for (int i = 0; i < _ruleIndex; i++) {
		if (_ruleList[i] == id_rule) return true;
	}
		
	return false;
}

bool grPair::HasGroup(int id_group)
{
	//Проверка, не применяется ли пара при любой группе
	if (_all_group) return true;
	for (int i = 0; i < _groupIndex; i++) {
		if (_groupList[i] == id_group) return true;
	}
	return false;
}
