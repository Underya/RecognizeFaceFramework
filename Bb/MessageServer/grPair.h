#pragma once

#define MAX_ELEMENT_SIZE 20
//Специальный идентификатор, указывающий что пара работает для всех правил
#define ALL_RULES_CODE -1
//Специальный идентификатор, указывающий что пара работает для всех групп
#define ALL_GROUP_CODE -1

#ifdef MESSAGESERVER_EXPORTS
#define MESSAGESERVER_API __declspec(dllexport)
#else
#define MESSAGESERVER_API __declspec(dllimport)
#endif


//Пара из группы и правила
class MESSAGESERVER_API grPair
{
public:

	//Добавить правило
	void AddRule(int id_rule);

	//Добавить группу
	void AddGroup(int id_group);

	bool AnyRule();

	bool AnyGroup();

	//Возвращает истину, если такое правило есть в паре
	bool HasRule(int id_rule);

	//Возвращает истину, если такоя группа есть в паре
	bool HasGroup(int id_group);

protected:

	//Является ли пара исполняемой при любом правиле
	bool _all_group = false;

	//Является ли пара исполняемой при любой группе
	bool _all_rule = false;

	//Текущая позииция в списке групп
	int _groupIndex = 0;

	//Список со всеми группами в паре
	int _groupList[MAX_ELEMENT_SIZE];

	//Текущая позиция в списке правил
	int _ruleIndex = 0;

	//Список со всеми правилами в паре
	int _ruleList[MAX_ELEMENT_SIZE];
};

