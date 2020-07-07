#include "rule_menu.h"
#include "questions_user.h"
#include "..//db/rules_collection.h"
#include "premise_menu.h"
#include "camera_menu.h"

using namespace std;

void rule_menu::Switch(db_user* user)
{
	_user = user;
	questions_user qu;

	try {
		while (true) {
			qu.ClearConsole();

			int res = qu.SendQuestInt("Выебрите действие", { "Показать правила", "Показать все правила", "Показать Камеры-правила",
				"Показать Помещения-правила", "Добавить правило", "Изменить правило",
				"Изменить связь с помещениями", "Изменить связь с камерами", "Удали правило","Выход" });

			res = ParseAnswer(res);

			if (res == -1)
				break;
		}
	}
	catch (...) {
		std::cout << "Произошла неизвестная ошибка!";
	}

}

int rule_menu::ParseAnswer(int number)
{
	questions_user q;
	//Показать правила
	if (number == 1) {
		q.ClearConsole();
		ShowLink(_user);
		q.WaitPressSay();
	}

	//Показать ВСЕ правила
	if (number == 2) {
		q.ClearConsole();
		ShowAll();
		q.WaitPressSay();
	}

	//Показать камеру и часть правила, связанные с ней
	if (number == 3) {
		q.ClearConsole();
		ShowLinkCam();
		q.WaitPressSay();
	}

	//Вывод помещения правила
	if (number == 4) {
		q.ClearConsole();
		ShowLinkPremise();
		q.WaitPressSay();
	}

	//Добавление правила
	if (number == 5) {
		AddRule();
	}

	//Изменение правила
	if (number == 6) {
		EditRule();
	}

	//Изменить связь с помещением
	if (number == 7) {
		EditRulePremise();
	}

	if (number == 8) {
		EditRuleCamera();
	}

	//Выход
	if (number == 10) {
		return -1;
	}

	return 1;
}

void rule_menu::ShowOne(db_rule rule)
{
	cout << "id:"  << rule.GetId() << " Название:" << rule.GetName() << " Описание:" << rule.GetDesc() << "\n"; 
}

void rule_menu::ShowLink(db_user* _user)
{
	rules_collection rc;
	//Собрание всех правил для камер
	
	//Разбор всех камер
	vector<db_vcam> v = db_vcam::GetAllLinkVcam(*_user);

	for (auto iter = v.begin(); iter != v.end(); iter++) {
		rc.LoadAlRuleLinkCam(iter->GetId());
	}

	//Вывод всех правил
	list<db_rule> l = rc.GetAllRuleFull();
	for (auto iter = l.begin(); iter != l.end(); iter++) {
		ShowOne(*iter);
		cout << "-----------------------------------------\n";
	}
	cout << "\n";
}

void rule_menu::ShowRuleForCamera(db_vcam cam)
{
	string str = " -->";
	//Сбор всех правил для данной камеры без учёта помещений
	rules_collection rc;
	rc.AppendRule(cam);
	list<db_rule> current_cam_rule = rc.GetAllRuleFull();
	for (auto rule = current_cam_rule.begin(); rule != current_cam_rule.end(); rule++) {
		cout << str;
		ShowOne(*rule);
	}
}

void rule_menu::ShowAll()
{
	vector<db_rule> all_rule = db_rule::GetAllRule();

	for (auto iter = all_rule.begin(); iter != all_rule.end(); iter++) {
		ShowOne(*iter);
		cout << "-----------------------------------------\n";
	}
}

void rule_menu::ShowLinkCam()
{
	vector<db_vcam> vec = db_vcam::GetAllLinkVcam(*_user);
	string str = " -->";
	//Вывод всех камер
	for (auto iter = vec.begin(); iter != vec.end(); iter++) {
		cout << "id:" << iter->GetId() << " Адрес:" << iter->GetAddress() << " Описание:" << iter->GetDescription() << "\n";
		
		ShowRuleForCamera(*iter);

		string space = "     ";
		//Теперь показ всех правил, которые идут от помещения
		if (iter->GetPremise().GetId() != -1) {
			db_premise p = iter->GetPremise();
			cout << space << "id: " << p.GetId() << " Название помещения:" << p.GetName() << " Описание:" << p.GetDesc() << "\n";
			//Получение всех правил
			rules_collection rule_premise;
			rule_premise.AppendRule(p);
			//Вывод всех правил помещения
			list<db_rule> premise_rule = rule_premise.GetAllRuleFull();
			for (auto rule = premise_rule.begin(); rule != premise_rule.end(); rule++) {
				cout << space << space << str;
				ShowOne(*rule);
			}
 		}

		cout << "-----------------------------------------\n";
	}
}

void rule_menu::ShowLinkPremise()
{
	//Получение всего списка помещений, связанных с текущих пользователем
	//Все камеры
	vector<db_vcam> vec = db_vcam::GetAllLinkVcam(*_user);
	//Для каждой камеры проверяем помещение
	string str = " -->";
	string space = "     ";
	for (auto camera = vec.begin(); camera != vec.end(); camera++) {
		if (camera->GetPremise().GetId() != -1) {
			//Вывод помешения
			db_premise p = camera->GetPremise();
			cout << "id: " << p.GetId() << " Название помещения:" << p.GetName() << " Описание:" << p.GetDesc() << "\n";
			//Вывод всех правил для него
			rules_collection rule_premise;
			rule_premise.AppendRuleForOnePremmis(p);
			//Вывод всех правил помещения
			list<db_rule> premise_rule = rule_premise.GetAllRuleFull();
			for (auto rule = premise_rule.begin(); rule != premise_rule.end(); rule++) {
				cout << space << str;
				ShowOne(*rule);
			}
		}
		
		
		cout << "-----------------------------------------\n";
	}

}

void rule_menu::AddRule()
{
	questions_user qu;
	cout << "Введите информацию о новом правиле\n";
	string name, desc;

	int new_id = -1;

	name = qu.GetParametr("Название");
	desc = qu.GetParametr("Описание");

	try {
		new_id = db_rule::AddNewRule(name, desc).GetId();

	}
	catch (...) {
		cout << "Не удалось добавить новое правило!\n";
		qu.WaitPressSay();
	}

	cout << "\n";
	ShowOne(db_rule(new_id));
	cout << "Правило успешно добавлено!\n";
	qu.WaitPressSay();
}

int rule_menu::SelectRule()
{

	int id = -1;
	while (true)
	{
		string sid;
		cin >> sid;
		id = atoi(sid.c_str());
		//Проверка, есть ли камера с таким id
		try {
			db_rule check(id);
		}
		catch (...) {
			cout << "Не удалось выбрать правило с таким id!\n";
			cout << "Введите id правила:";
			continue;
		}

		break;
	}
	return id;
}

void rule_menu::EditRule()
{
	questions_user q;
	q.ClearConsole();
	ShowLink(_user);
	//Введите id правила для изменения
	int id = SelectRule();
	db_rule rule(id);
	q.ClearConsole();
	ShowOne(rule);
	cout << "\n";
	cout << "Введите новые данные";
	string name, desc;
	name = q.GetParametr("Новое название");
	desc = q.GetParametr("Новое описание");
	try {
		rule.SetName(name);
		rule.SetDesc(desc);
	}
	catch (...) {
		cout << "Не удалось изменить правило!\n";
		q.WaitPressSay();
	}

	q.ClearConsole();
	ShowOne(rule);
	cout << "Правило было успешно изменено!\n";
	q.WaitPressSay();
}

void rule_menu::EditRulePremise()
{
	questions_user q;
	q.ClearConsole();
	premise_menu pm;
	ShowRulePremiseNotParrent();
	cout << "Введите id помещния для изменния связанных с ним правил";
	int id = pm.SelectPremise();

	while (true) {
		q.ClearConsole();
		db_premise premise(id);
		cout << pm.ShowOne(premise) << "\n";
		//Показ связанных с ним правил
		rules_collection rules;
		rules.AppendRuleForOnePremmis(premise);
		list<db_rule> list_rule = rules.GetAllRuleFull();
		string str = " -->";
		string space = "     ";
		for (auto rule = list_rule.begin(); rule != list_rule.end(); rule++) {
			cout << str << space;
			ShowOne(*rule);
		}

		int res = q.SendQuestInt("Выберите действие", { "Добавить правило", "Удалить правило", "Выход" });
		//Закрыть меню
		if (res == 1) {
			AppendRulePremise(premise);
		}

		if (res == 2) {
			DeleteRulePremise(premise);
		}

		if (res == 3) {
			break;
		}
	}

}

void rule_menu::EditRuleCamera()
{
	questions_user q;
	q.ClearConsole();
	ShowLinkCam();
	camera_menu cm;
	cout << "Введите id камеры для изменения правил камеры:";
	int id = cm.SelectCamera();
	db_vcam cam(id);

	while (true) {
		q.ClearConsole();
		cm.ShowOneCamera(cam);
		//Показать все правила для камеры
		ShowRuleForCamera(cam);

		int res = q.SendQuestInt("Выберите действие", { "Добавить правило", "Удалить правило", "Выход" });

		if (res == 1) {
			AppendRuleCamera(id);
		}

		if (res == 2) {
			DeleteRuleCamera(id);
		}

		if (res == 3) {
			break;
		}

	}
}

void rule_menu::AppendRuleCamera(int id_cam)
{
	questions_user q;
	//Показ всех правил
	q.ClearConsole();
	ShowAll();
	cout << "Введите id правила для добавления:";
	int id_rule = SelectRule();

	try {
		db_rule::LinkedWithRuleCamer(id_cam, id_rule);
	}
	catch (...) {
		cout << "Не удалось связать правило!\n";
		q.WaitPressSay();
		return;
	}

	cout << "Связь была успешно добавлена!\n";
	q.WaitPressSay();
}

void rule_menu::DeleteRuleCamera(int id_cam)
{
	questions_user q;
	q.ClearConsole();

	db_vcam cam(id_cam);
	rules_collection rc;
	rc.AppendRule(cam);
	list<db_rule> l = rc.GetAllRuleFull();

	for (auto iter = l.begin(); iter != l.end(); iter++) {
		ShowOne(*iter);
	}

	cout << "Введите id правила, которое надо удалить:";
	int res = SelectRule();

	try {

	}
	catch (...) {
		cout << "Не удалось удалить правило!\n";
		q.WaitPressSay();
		return;
	}
	cout << "Правило было успешно удалено\n";
	q.WaitPressSay();
}

void rule_menu::ShowRulePremiseNotParrent()
{
	//Получение всего списка помещений, связанных с текущих пользователем
	//Все камеры
	vector<db_vcam> vec = db_vcam::GetAllLinkVcam(*_user);
	//Для каждой камеры проверяем помещение
	string str = " -->";
	string space = "     ";
	for (auto camera = vec.begin(); camera != vec.end(); camera++) {
		if (camera->GetPremise().GetId() != -1) {
			//Вывод помешения
			db_premise p = camera->GetPremise();
			cout << "id: " << p.GetId() << " Название помещения:" << p.GetName() << " Описание:" << p.GetDesc() << "\n";
			//Вывод всех правил для него
			rules_collection rule_premise;
			rule_premise.AppendRuleForOnePremmis(p);
			//Вывод всех правил помещения
			list<db_rule> premise_rule = rule_premise.GetAllRuleFull();
			for (auto rule = premise_rule.begin(); rule != premise_rule.end(); rule++) {
				cout << space << str;
				ShowOne(*rule);
			}
		}


		cout << "-----------------------------------------\n";
	}
}

void rule_menu::AppendRulePremise(db_premise prem)
{
	questions_user q;
	q.ClearConsole();
	ShowAll();
	cout << "Введите id правила для добавления:";
	int id = SelectRule();
	db_rule rule(id);
	try {
		rule.LinkedWitRulePremise(prem.GetId(), id);
	}
	catch (...) {
		cout << "Не удалось связать правило и помещение!\n";
		q.WaitPressSay();
		return;
	}
	cout << "Правило было успешно добавлено!";
	q.WaitPressSay();

}

void rule_menu::DeleteRulePremise(db_premise prem)
{
	questions_user q;
	q.ClearConsole();
	rules_collection rc;
	string str = "  -->";
	rc.AppendRuleForOnePremmis(prem);
	list<db_rule> rules = rc.GetAllRuleFull();
	for (auto rule = rules.begin(); rule != rules.begin(); rule++) {
		cout << str;
		ShowOne(*rule);
	}
	cout << "Введите id правила:";
	int id = SelectRule();

	db_rule rule(id);
	try {
	}
	catch (...) {
		cout << "Не удалось удалить правило!\n";
		q.WaitPressSay();
		return;
	}

	cout << "Правило было успешно удалено!\n";
	q.WaitPressSay();
	return;
}

