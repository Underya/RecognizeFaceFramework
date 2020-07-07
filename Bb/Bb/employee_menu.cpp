#include "employee_menu.h"
#include "..//db/db_group.h"
#include "questions_user.h"
#include "..//face_recognition/face_manager.h"

using namespace std;

void employee_menu::Switch(db_user* user)
{
	//Сохранение информации о пользователе
	_user = user;

	db_group::LoadedAllGroup(_user->GetId());

	questions_user q;

	//Цикл для работы в нём
	try {
		while (true) {
			q.ClearConsole();

			//Выввод возможных действий
			int res = q.SendQuestInt("Выберите действие", { "Показать сотрудников" , "Показать сотрудников с группами",
				"Добавить нового", "Изменить информацию", "Изменить группы",
				"Добавить фото к сотруднику", "Удалить", "Выход" });

			res = ParseAnswer(res);

			//Если вернулось -1, то конец цикла
			if (res == -1)
				break;
		}
	}
	catch (...) {
		cout << "Произошла неизвестная ошибка!";
	}
}

int employee_menu::ParseAnswer(int number)
{
	questions_user q;
	//Показ сотрудников без групп
	if (number == 1) {
		ShowInfo();
		q.WaitPressSay();
	}

	//Показать сотрудников с группами
	if (number == 2) {
		ShowInfoAndGroup();
		q.WaitPressSay();
	}

	//Добавление нового сотрудника
	if (number == 3) {
		AddEmployee();
	}

	//Изменить информацию о сотруднике
	if (number == 4) {
		EditEmployee();
	}

	//Изменение группы сотрудников
	if (number == 5) {
		EditeEmployeeGroup(0);
	}

	//Добавление нового фота к сотруднику
	if (number == 6) {
		AddNewPhoto();
	}

	//Удалить сотрудника
	if (number == 7) {
		DeleteEmployee();
	}

	//Выйти из меню
	if (number == 8) 
		return -1;
	return 0;
}

void employee_menu::ShowOne(db_employee employee)
{
	
	cout << "id:" << employee.GetId() << " ";
	cout << "ФИО: " << employee.GetFirstName() << " "
		<< employee.GetLastName() << " " << employee.GetMidleName() << endl;
	if (employee.GetDescrInfo() != "") {
		cout << "Описание:" << employee.GetDescrInfo() << "\n";
	}
	if (employee.GetOtherId() != -1)
		cout << "id в другой системе: " << employee.GetOtherId() << "\n";
	
}

void employee_menu::ShowOneGroup(db_employee employee)
{
	//Загрузка всех групп для сотрудника
	list<db_group> l = db_group::GetSnapGoup(employee.GetId());
	//Вывод всего списка
	for (auto iter = l.begin(); iter != l.end(); iter++) {
		cout << "id группы:" << iter->GetId() << " Название:" << iter->GetName() << "; ";
	}
	cout << "\n";

}

int employee_menu::SelectEmployee()
{

	int id = -1;
	while (true)
	{
		string sid;
		cin >> sid;
		id = atoi(sid.c_str());
		//Проверка, есть ли камера с таким id
		try {
			db_employee check(id);
		}
		catch (...) {
			cout << "Не удалось выбрать сотрудника с таким id!\n";
			cout << "Введите id сотрудника:";
			continue;
		}

		break;
	}
	return id;
}

void employee_menu::ShowInfo()
{
	questions_user q;
	q.ClearConsole();
	std::vector<db_employee> *v = db_employee::GetEmployeeWithCondition(db_group::GetAllGroup());

	for (auto iter = v->begin(); iter != v->end(); iter++) {
		ShowOne(*iter);
		cout << "-------------------------------\n\n";
	}
	
}

void employee_menu::ShowInfoAndGroup()
{
	questions_user q;
	q.ClearConsole();
	std::vector<db_employee>* v = db_employee::GetEmployeeWithCondition(db_group::GetAllGroup());

	for (auto iter = v->begin(); iter != v->end(); iter++) {
		ShowOne(*iter);
		ShowOneGroup(*iter);
		cout << "-------------------------------\n\n";
	}
}

void employee_menu::AddEmployee()
{
	questions_user q;
	q.ClearConsole();
	string f, l, m, desc;
	int other_id = -1, id_group = -1;
	cout << "Введите информацию для добавления нового сотрудника\n";

	f = q.GetParametr("Имя");
	l = q.GetParametr("Фамилия");
	m = q.GetParametr("Отчество");
	other_id = atoi(q.GetParametr("id в другом приложении или -1").c_str());

	desc = q.GetParametr("Описание сотрудника");

	//Группа
	cout << "Далее необходимо ввести группу, с которой должен быть связан пользователь.\n";
	int res = q.SendQuestInt("Показать список связанных групп?", { "Да", "Нет" });

	if (res == 1) {
		group_menu g;

		g.ShowGroup(_user);
	}

	id_group = atoi(q.GetParametr("id группы").c_str());

	try {
		db_group group(id_group);
		db_employee *e = db_employee::AddNewEmployee(f, l, m, desc, other_id);
		group.SnapEmployee(e->GetId());
		delete e;
	}
	catch (...) {
		cout << "Не удалось добавить нового сотрудника!\n";
		q.WaitPressSay();
	}

	cout << "Сотрудник был успешно был добавлен!\n";
	q.WaitPressSay();
}

void employee_menu::AddNewPhoto()
{
	questions_user q;
	q.ClearConsole();
	ShowInfo();
	cout << "Введите id сотрудника для добавления фото:";
	int id = SelectEmployee();
	db_employee emp(id);

	cout << "Введите путь к фото файлу, который вы хотите добавить:";
	string path;
	cin >> path;

	try {
		face_manager fm;
		fm.AddNewFace(1, "", "", "");
		try {
			fm.AddNewPhoto(1, path);
		}
		catch (std::exception e) {
			cout << e.what();
			throw e;
		}

		face f = fm.GetFaceForId(1);
		db_face::AddNewFace(f.GetFloatDescript(0), emp.GetId());
	}
	catch (...) {
		cout << "Не удалось добавить фото!\n";
		q.WaitPressSay();
		return;
	}
	cout << "Фото было успешно добавлено\n";
	q.WaitPressSay();
}

void employee_menu::EditEmployee()
{
	questions_user q;
	//Выбор сотрудника
	q.ClearConsole();
	ShowInfo();
	cout << "Введите id сотрудника для изменения:";
	int id = SelectEmployee();
	db_employee emp(id);

	q.ClearConsole();
	ShowOne(emp);

	string f, l, m, desc;
	int other_id = -1;

	f = q.GetParametr("Новое имя");
	l = q.GetParametr("Новое фамилия");
	m = q.GetParametr("Новое отчество");
	desc = q.GetParametr("Дескриптор");
	other_id = atoi(q.GetParametr("id в другой системе или -1").c_str());

	try {
		
		emp.SetFirstName(f);
		emp.SetLastName(l);
		emp.SetMidName(m);
		emp.SetDescrInfo(desc);
		emp.SetOtherId(other_id);
	}
	catch (...) {
		cout << "Не удалось изменить информацию о сотруднике!\n";
		q.WaitPressSay();
		return;
	}

	q.ClearConsole();
	ShowOne(emp);
	cout << "Информация успешно изменена!\n";
	q.WaitPressSay();
}

void employee_menu::EditeEmployeeGroup(int id)
{
	questions_user q;
	q.ClearConsole();

	ShowInfoAndGroup();

	cout << "Выберите сотрудника для изменения:";
	int res =  SelectEmployee();
	db_employee e(res);

	//Цикл, для данного действия
	while (true) {
		q.ClearConsole();
		ShowOne(e);
		ShowOneGroup(e);

		cout << endl;
		//Выбор, удалить или добавить группу
		int action = q.SendQuestInt("Выберите действие", { "Добавить", "Удалить", "Выход" });

		//Добавление группы
		if (action == 1) {
			AddGroup(e);
		}

		//Удаление группы
		if (action == 2) {
			DeletGroup(e);
		}

		//Выход
		if (action == 3)
			break;
	}
}

void employee_menu::AddGroup(db_employee emp)
{
	group_menu gm;
	gm.ShowAllGroup();
	questions_user q;
	cout << "Введите id группы для добавления:";
	int id_g = gm.SelectGroup();
	db_group g(id_g);
	try {
		g.SnapEmployee(emp.GetId());
	}
	catch (...) {
		cout << "Не удалось добавить группу!\n";
		q.WaitPressSay();
		return;
	}
	
	cout << "Группа была удалена!\n";
	q.WaitPressSay();
	
}

void employee_menu::DeletGroup(db_employee emp)
{
	questions_user q;
	ShowOneGroup(emp);
	cout << "Введите id группы для удаления:";
	group_menu gm;
	int id_g = gm.SelectGroup();
	db_group g(id_g);
	try {
		g.UnLinkEmployee(emp.GetId());
	}
	catch (...) {
		cout << "Не удалось удалить группу!\n";
		q.WaitPressSay();
		return;
	}
	cout << "Группа была успешно удалена!\n";
	q.WaitPressSay();
}

void employee_menu::DeleteEmployee()
{
	questions_user q;
	q.ClearConsole();

	ShowInfo();

	cout << "Введите id сотрудника для удаления:";

	int res = SelectEmployee();

	try {
		db_employee emp(res);
		emp.Delete();
	}
	catch (...) {
		cout << "Не удалось удалить информацию о сотруднике!\n";
		q.WaitPressSay();
		return;
	}
	cout << "Информация была удалена\n";
	q.WaitPressSay();
	return;
}
