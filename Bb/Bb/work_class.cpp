#include "work_class.h"
#include "questions_user.h"
#include "..//RecognitionBB/PremiseCheck.h"
#include "receive_menu.h"

void work_class::Start(db_user* user)
{
	questions_user q;
	q.ClearConsole();
	cout << "Начало работы приложения...\n";
	_user = user;
	//Инциализация и начало работы
	StartWork();
	//Переход в меню
	std::this_thread::sleep_for(std::chrono::seconds(2));
	Menu();

}

void work_class::Menu()
{
	questions_user q;
	try {
		while (true) {
			q.ClearConsole();
			int res = q.SendQuestInt("Возможные действия", { "Начать показ", "Закончить показ", "Помещения", "Сотрудники"
				, "Выход" });
			if (res == 1) {
				bb.m10_startShow();
			}

			if (res == 2) {
				bb.m10_endShow();
			}

			if (res == 3) {
				ShowPremiseEmployee();
				q.WaitPressSay();
			}

			if (res == 4) {
				ShowEmployeePremise();
				q.WaitPressSay();
			}

			//Выход
			if (res == 5) {
				exit(1);
			}
		}
	}
	catch (...) {
		std::cout << "Произошла неизвестная ошибка!";
	}
}


void work_class::ShowPremiseEmployee()
{
	PremiseCheck pc;

	auto info = pc.GetPremiseEmplyee();

	string space = "   ";

	for (auto premise = info.begin(); premise != info.end(); premise++) {
		cout << "Помещение:" << premise->first << ":\n";
		auto vec_emp = premise->second;
		for (auto emp = vec_emp.begin(); emp != vec_emp.end(); emp++) {
			cout << space << *emp << "\n";
		}
		cout << "\n";
	}
}

void work_class::ShowEmployeePremise()
{
	PremiseCheck pc;
	std::vector<std::pair< db_employee, std::string>> vector = pc.GetEmployeePremise();

	for (auto iter = vector.begin(); iter != vector.end(); iter++) {
		db_employee employee = iter->first;
		cout << employee.GetFirstName() << " " << employee.GetLastName() << " " << employee.GetMidleName() << ":";
		cout << iter->second << "\n";
	}
}



void work_class::StartWork()
{
	//Авторизация с логином пользователя
	bb.m2_Authorization(_user->GetName());
	//Загрузка групп и камер
	bb.m3_LoadGroupAndCamera();
	//Загрузка сотрудников и лиц
	bb.m4_LoadEmployeeAndFace();
	//Создание распознавателей и обработчиков 
	bb.m5_CreateRecognizerAndHandler(1, 10.0, 20.0);
	//Получение всего списка получателей
	recipients_list rl;
	//Добавление получателей
	bb.m6_AddReceiver(rl.GetFileReceiver());
	//Запуск системы
	bb.m8_Start();
}


