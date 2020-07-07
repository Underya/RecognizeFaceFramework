#include "Main_menu.h"
#include "questions_user.h"
#include "information_menu.h"
#include "work_class.h"
#include "export_menu.h"

#include <iostream>
using namespace std;

void Main_menu::Start()
{
	//Инициализация
	Initializate();

	questions_user qu;

	try {
		//Бесконечный цикл
		while (true) {
			//Очистка экрана
			qu.ClearConsole();

			//Задание вопроса
			int res = qu.SendQuestInt("Главное меню", { "Старт","Информация", "Экспорт" ,"Выход" });

			//Обрабтка ответа
			ParseAnswer(res);

		}
	}
	catch (...) {
		std::cout << "Произошла неизвестная ошибка!";
	}
}


void Main_menu::Initializate()
{
	system("chcp 1251");
	questions_user q;
	q.ClearConsole();

	//Запуск проверки начальных данных для старта
	i.Start();
	
	//Взятие начальной информации
	LoadInformation();
}

int Main_menu::ParseAnswer(int result)
{
	questions_user qu;
	//Старт
	if (result == 1) {
		work_class wc;
		wc.Start(_user);
	}


	//Экспорт
	if (result == 3) {
		export_menu exm;
		exm.Export(_user);
	}

	//Выход из приложения
	if (result == 4) {
		exit(1);
		//Удержание ответа на консоли для ознакомления
		qu.WaitPressSay();
	}

	//Информация
	if (result == 2) {
		//Если не импортируется информация, то её можно имзенить
		if (!_import) {
			information_menu im;
			im.SwitchInformMenu(_user);
		}
	}

	//Экспорт
	if (result == 3) {
		
	}

	return 1;
}

void Main_menu::LoadInformation()
{
	//Если БД, то к ней происходит подключение
	db_manager::SetConnectInfo(i.GetAdress(), i.GetPort(), i.GetUser_Name(), i.GetPassword(), i.GetDBName(), false);
	//Получение ид пользователя
	Ipcofnig ip;
	//И запрос на логин
	try {
		_user = db_user::LoginToUser(ip.GetIpV4());
	}
	catch (...) {
		std::cout << "Не существует пользователя с таким IP v4:" << ip.GetIpV4() << "\n";
	}
}
