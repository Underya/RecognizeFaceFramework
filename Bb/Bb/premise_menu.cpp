#include "premise_menu.h"
#include "questions_user.h"
#include "..//db/db_vcam.h"

using namespace std;

void premise_menu::Switch(db_user* user)
{
	_user = user;
	questions_user q;
	
	try {
		while (true)
		{
			q.ClearConsole();
			int res = q.SendQuestInt("Выберите действия", { "Показать помещения", "Показать все помещения",
				"Добавить помещение", "Изменить помещение", "Удалить помещения", "Выход" });

			res = ParseAnswer(res);

			if (res == -1) {
				break;
			}
		}
	} catch(...) {
		std::cout << "Произошла неизвестная ошибка!";
	}
}

std::string premise_menu::ShowOne(db_premise prem)
{
	string info = "";
	info += "id:" + to_string(prem.GetId()) + " название:" + prem.GetName();
	return info;
}

int premise_menu::ParseAnswer(int number)
{
	//Показ связанных помещений
	if (number == 1) {
		questions_user q;
		q.ClearConsole();
		ShowPremise();
		q.WaitPressSay();
	}

	//Показать все помещения
	if (number == 2) {
		questions_user q;
		q.ClearConsole();
		ShowAllPremise();
		q.WaitPressSay();
	}

	//Добавление нового помещения
	if (number == 3) {
		AddPremise();
	}

	//Изменение помещения
	if (number == 4) {
		EdietePremise();
	}

	//Удалить помещение
	if (number == 5) {
		DeletePremise();
	}

	//Выход
	if (number == 6)
		return -1;
	return 1;
}

void premise_menu::ShowPremise()
{
	vector<db_vcam> v = db_vcam::GetAllLinkVcam(*_user);

	vector<db_premise> vd;
	
	for (auto iter = v.begin(); iter != v.end(); iter++) {
		if (iter->GetPremise().GetId() != -1) {
			vd.push_back(iter->GetPremise());
		}
	}

	//Вывод информации
	for (auto iter = vd.begin(); iter != vd.end(); iter++) {
		cout << ShowOne(*iter);
		cout << "\n";
		ShowParent(iter->GetId());
		cout << "-----------------------------\n\n";
	}
}

void premise_menu::ShowParent(int id_premise)
{
	db_premise prem(id_premise);
	string str = "-->";
	//Уровень вложенности
	int level = 0;
	string space = "   ";

	while (prem.GetIdParent() != -1) {
		string tab = "";
		for (int i = 0; i < level; i++) tab += space;
		db_premise parrentPrem(prem.GetIdParent());
		cout << tab << str << ShowOne(parrentPrem) << "\n";
		prem = parrentPrem;
		level++;
	}
}

void premise_menu::ShowAllPremise()
{
	vector<db_premise> vp = db_premise::GetAllPremise();

	for (auto iter = vp.begin(); iter != vp.end(); iter++) {
		cout << ShowOne(*iter);
		cout << "\n";
		ShowParent(iter->GetId());
		cout << "-----------------------------\n\n";
	}
}

void premise_menu::AddPremise()
{
	questions_user q;
	string name, desc;
	int parent_id = -1;

	name = q.GetParametr("Название");
	desc = q.GetParametr("Описание");
	parent_id = atoi(q.GetParametr("id родителя или -1").c_str());

	try {
		db_premise::AddNewPremise(name, desc, parent_id);
	}
	catch (...) {
		cout << "Не удалось создать новое помещение!\n";
		q.WaitPressSay();
		return;
	}

	cout << "Помещение было успешно создано!\n";
	q.WaitPressSay();
}

void premise_menu::EdietePremise()
{
	questions_user q;
	q.ClearConsole();
	ShowPremise();

	cout << "Введите id помещения для изменения:";
	int id = SelectPremise();
	db_premise p(id);
	q.ClearConsole();
	cout << ShowOne(p) << "\n\n";

	string name, desc;
	int parent_id = -1;
	name = q.GetParametr("Введите новое имя");
	desc = q.GetParametr("Введите новые дескриптор");
	parent_id = atoi(q.GetParametr("Введите родительское помещение или -1").c_str());

	try {
		p.SetName(name);
		p.SetDesc(desc);
		if (parent_id != -1) {
		}
	}
	catch (...) {
		cout << "Не удалось изменить информацию о помещении!\n";
		q.WaitPressSay();
		return;
	}

	q.ClearConsole();
	cout << ShowOne(p) << "\n\n";
	cout << "Информация была успешно обновлена\n";
	q.WaitPressSay();
}

void premise_menu::DeletePremise()
{
	questions_user q;
	q.ClearConsole();
	ShowPremise();

	cout << "Введите id помещения для удаления:";
	int id = SelectPremise();
	db_premise p(id);

	try {
		p.Delete();
	}
	catch (...) {
		cout << "Не удалось удалить помещение!\n" << "Возможно, у него надо удалить потомков\n";
		q.WaitPressSay();
		return;
	}

	cout << "Информация была успешно удалена!\n";
	q.WaitPressSay();
}

int premise_menu::SelectPremise()
{
	int id = -1;
	while (true)
	{
		string sid;
		cin >> sid;
		id = atoi(sid.c_str());
		//Проверка, есть ли помещение с таким id
		try {
			db_premise check(id);
		}
		catch (...) {
			cout << "Не удалось выбрать помешение с таким id!\n";
			cout << "Введите id группы:";
			continue;
		}

		break;
	}
	return id;
}
