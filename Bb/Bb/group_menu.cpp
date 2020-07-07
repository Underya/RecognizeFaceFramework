#include "group_menu.h"
using namespace std;

#include "../db/db_employee.h"
#include "questions_user.h"

void group_menu::Switch(db_user* user)
{
	_user = user;
	questions_user q;

	//Если нет загруженных групп - загрузить
	db_group::LoadedAllGroup(_user->GetId());
	try {
		while (true)
		{
			q.ClearConsole();
			int res = q.SendQuestInt("Выберите дейсвтие", { "Просмотреть группы", "Просмотреть все группы",
				"Просмотреть все группы и пользователей",
				"Привязать группу", "Отвязать группу",
				"Добавить группу","Изменить группу", "Удалить группу",
				"Выход" });

			int act = ParseAnswer(res);

			if (act == -1)
				break;
		}
	}
	catch (...) {
		cout << "Произошла неизвестная ошибка!";
	}
}


void group_menu::ShowAllGroup() {

	std::vector<db_group> v = db_group::GetAllGroupToDB();

	for (auto iter = v.begin(); iter != v.end(); iter++) {
		ShowOneGroup(*iter);
	}
}

void group_menu::ShowGroup(db_user* _user)
{

	std::vector<db_group> v = db_group::GetAllGroup();
	for (auto iter = v.begin(); iter != v.end(); iter++) {
		ShowOneGroup(*iter);
	}
}

void group_menu::ShowGroupAndEmloyee()
{
	vector<db_group> g = db_group::GetAllGroupToDB();
	//Сначала показ информации о группе
	for (auto iter = g.begin(); iter != g.end(); iter++) {
		cout << "id:" << iter->GetId() << " Название:" << iter->GetName() << "\n";
		//Показ информации обо всех сотруниках в группе
		vector<db_employee>* ve = db_employee::GetEmployeeWithCondition(*iter);

		for (auto emp = ve->begin(); emp != ve->end(); emp++) {
			cout << "     " << "id:" << emp->GetId() << " ФИО:" <<
				emp->GetLastName() << " " << emp->GetFirstName() << " " << emp->GetMidleName() << ";\n";
		}

		cout << "-----------------------------------\n\n";

		delete ve;
	}
}

int group_menu::SelectGroup() {
	int id = -1;
	while (true)
	{
		string sid;
		cin >> sid;
		id = atoi(sid.c_str());
		//Проверка, есть ли камера с таким id
		try {
			db_group check(id);
		}
		catch (...) {
			cout << "Не удалось выбрать группу с таким id!\n";
			cout << "Введите id группы:";
			continue;
		}

		break;
	}
	return id;
}

void group_menu::LinkGroup()
{
	questions_user q;
	q.ClearConsole();

	ShowAllGroup();
	cout << "Выберите группу, которая будет привязана к пользователю:";
	int id_g = SelectGroup();


	//Попытка привязать выбранную группу к пользователю
	try {
		_user->LinkGroup(id_g);
	}
	catch (...) {
		cout << "Не удалось привязать группу к данному пользователю!\n";
		q.WaitPressSay();
		return;
	}

	cout << "Група успешна привязана!\n";
	q.WaitPressSay();
	return;
}

void group_menu::UnLinkGroup()
{
	questions_user q;
	q.ClearConsole();

	ShowGroup(_user);
	cout << "Выберите группу, которая будет отвязана:";
	int id_g = SelectGroup();


	//Попытка привязать выбранную группу к пользователю
	try {
		_user->UnLinkGroup(id_g);
	}
	catch (...) {
		cout << "Группа отвязана от пользователя!\n";
		q.WaitPressSay();
		return;
	}

	cout << "Група успешна отвязана!\n";
	q.WaitPressSay();
	return;
}

int group_menu::ParseAnswer(int number)
{
	questions_user q;
	//Показ только связанных групп
	if (number == 1) {
		ShowGroup(_user);
		q.WaitPressSay();
	}

	//Показать все группы
	if (number == 2) {
		ShowAllGroup();
		q.WaitPressSay();
	}

	//Просмотре всех групп с их пользователями
	if (number == 3) {
		q.ClearConsole();
		ShowGroupAndEmloyee();
		q.WaitPressSay();
	}

	//Привязка групп
	if (number == 4) {
		LinkGroup();
		db_group::LoadedAllGroup(_user->GetId());
	}

	//Отвязать группу
	if (number == 5) {
		UnLinkGroup();
		db_group::LoadedAllGroup(_user->GetId());
	}

	//Добавить новую группу
	if (number == 6) {
		AddNewGroup();
	}

	//Изменить информацию о группе
	if (number == 7) {
		EditGroup();
	}
	
	if (number == 8) {
		DeletGroup();
		db_group::LoadedAllGroup(_user->GetId());
	}

	//Выход
	if (number == 9)
		return -1;

	return 1;
}

void group_menu::AddNewGroup()
{
	questions_user q;
	string name, desc;
	cout << "Введите информацию для новой группы\n";
	name = q.GetParametr("Название");
	desc = q.GetParametr("Описание");
	int new_id = -1;

	try {
		db_group gr = db_group::AddNewGroup(name, desc);
		new_id = gr.GetId();
	}
	catch (...) {
		cout << "Не удалось создать новую группу!\n";
		q.WaitPressSay();
		return;
	}
	cout << "Группа успешно создана!\n";
	int res = q.SendQuestInt("Привязать новую группу к текущему пользователю?", { "Да", "Нет" });
	if (res == 1) {
		_user->LinkGroup(new_id);
		cout << "Группа успешно привязана!";
	}
	q.WaitPressSay();	
}

void group_menu::EditGroup()
{
	questions_user q;
	q.ClearConsole();
	ShowGroup(_user);
	cout << "Выберите группу для изменения:";
	int res = SelectGroup();
	q.ClearConsole();
	db_group g(res);
	ShowOneGroup(g);

	string name, desc;
	name = q.GetParametr("Новое имя");
	desc = q.GetParametr("Описание");

	try {
		g.SetName(name);
		g.SetDescript(desc);
	}
	catch (...) {
		cout << "Не удалось изменить информацию!\n";
		q.WaitPressSay();
		return;
	}
	q.ClearConsole();
	ShowOneGroup(g);
	cout << "Информация была успешно изменена!\n";
	db_group::LoadedAllGroup(_user->GetId());
	q.WaitPressSay();
	return;
}

void group_menu::DeletGroup()
{
	questions_user q;
	q.ClearConsole();
	ShowGroup(_user);

	cout << "Введите id группы для удаления:";
	int res = SelectGroup();

	db_group g(res);
	try {
		g.Delete();
	}
	catch (...) {
		cout << "Не удалось удалить группу!\n";
		q.WaitPressSay();
		return;
	}

	cout << "Группа успешно удалена!\n";
	q.WaitPressSay();
	return;
}

void group_menu::ShowOneGroup(db_group gr)
{
	cout << "id:" << gr.GetId() << " Название: " << gr.GetName() << " Описание:" << gr.GetDesc() << "\n";
}
