#pragma once
#include "..//db/db_user.h"
#include "..//db/db_rule.h"
#include "..//db/db_vcam.h"

//Меню, через которое происходит взаимодействие с правилами
class rule_menu
{
public:
	
	//Переключиттся в это меню
	void Switch(db_user* user);

protected:

	//Разбор ответов пользователя
	int ParseAnswer(int number);

	//Вывести информацию об одном правиле
	void ShowOne(db_rule rule);

	//Показать все связанные с данным пользователем правила
	void ShowLink(db_user* _user);

	//Показать все прямые правила для камеры 
	void ShowRuleForCamera(db_vcam cam);

	//Показать все правила
	void ShowAll();

	//Показать все правила, связанные с камерами
	void ShowLinkCam();

	//Показ информации, связанной с конкретным помещением
	void ShowLinkPremise();

	//Добавить камеру
	void AddRule();

	//Выбор правила, существующего в БД
	int SelectRule();

	//Изменить информацию о правиле
	void EditRule();

	//Изменить информацию об связи с помещениями
	void EditRulePremise();

	//Изменить информацию о связе с камера
	void EditRuleCamera();

	//Добавить правило к выбранной камере
	void AppendRuleCamera(int id_cam);

	//Удалить у выбранной камеры правило
	void DeleteRuleCamera(int id_cam);

	//Показать правила только для текущего помещения
	void ShowRulePremiseNotParrent();

	//Выбрать и добавить правило для переданного помещения
	void AppendRulePremise(db_premise prem);

	//ВЫбрать и убрать у выбранного помещения правило
	void DeleteRulePremise(db_premise prem);

	db_user* _user = NULL;
};

