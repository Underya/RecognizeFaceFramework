#include "receive_menu.h"
#include "..//MessageServer/notificationServer.h"
#include "Configuration.h"
#include "questions_user.h"

using namespace std;

std::string recipients_list::rec_name = "rec";

void recipients_list::Switch(db_user *user)
{
	_user = user;
	Menu();
}

std::vector<std::string> recipients_list::GetFileReceiver()
{
	vector<string> all_file;
	//Получение всего списка имён 

	//Названия лежат следующим образом
	//rec1:path
	//rec2:path2
	int num = 1;
	string paramrs_name = GetNameParams(rec_name, num);

	try {
		Configuration conf;
		while (conf.HasParamert(paramrs_name)) {
			//Если есть такой параметр, то он добавляется в вектор
			all_file.push_back(conf.GetParametr(paramrs_name));
			//Переход к следующему пункту
			num++;
			paramrs_name = GetNameParams(rec_name, num);
		}
	}
	catch (...) {
		std::cout << "Произошла неизвестная ошибка!";
	}
	return all_file;
}

void recipients_list::ShowAllReceive()
{
	//Получение всех файлов
	vector<string> all_name = GetFileReceiver();

	//Счётчик
	int num = 1;

	for (auto iter = all_name.begin(); iter != all_name.end(); iter++) {
		cout << num << ") ";
		ShowInfoOner(*iter);
		num++;
	}

}

void recipients_list::ShowInfoOner(std::string path)
{
	notificationServer ns;
	try {
		ns.AddNewRecipient(path);
		std::vector<Recipient> vec = ns.GetListRecepient();
		Recipient r = vec[0];
		cout << "Файл:" << path << " Адерс:" << r.GetAddress() << " Порт:" << r.GetPort() << "\n";
	}
	catch (...) {
		cout << "Файл:" << path << " Не удалось открыть или разборать\n";
	}
	cout << "----------------------------\n";
}

std::string recipients_list::GetNameParams(std::string params, int number)
{
	return params + std::to_string(number);
}

void recipients_list::AddReceiver()
{
	string path;
	questions_user q;
	path = q.GetParametr("Введите путь к файлу");

	try {
		notificationServer ns;
		ns.AddNewRecipient(path);
	} catch(...) {
		cout << "Не удалось разборать файл. Возможно, он не формата JSON\n";
		q.WaitPressSay();
		return;
	}

	//Получение последнего параметр
	int num = GetNexttNumber();

	//Добавление в файл
	Configuration conf;
	string name = GetNameParams(rec_name, num);
	conf.SetParametr(name, path);
	conf.Save();
	cout << "Получатель добавлен!\n";
	q.WaitPressSay();
}

int recipients_list::GetNexttNumber()
{
	int num = 1;
	Configuration conf;

	string paramrs_name = GetNameParams(rec_name, num);

	while (conf.HasParamert(paramrs_name)) {
		num++;
		paramrs_name = GetNameParams(rec_name, num);
	}

	return num;
}

void recipients_list::DeleteRecipient()
{
	int num = GetNexttNumber() - 1;
	questions_user q;
	vector<string> vec;
	for (int i = 1; i <= num; i++) vec.push_back(to_string(i));

	int del_num = q.SendQuestInt("Введите номер получателя для удаления его из списка", vec);
	//Удаления из списка
	try {
		Configuration conf;
		string name = GetNameParams(rec_name, del_num);
		conf.DeteleParametr(name);
		//Теперь надо сдвинуть все элементы, которые вышего его
		string next_name = GetNameParams(rec_name, del_num + 1);
		while (conf.HasParamert(next_name)) {
			conf.SetParametr(name, conf.GetParametr(next_name));
			name = next_name;
			del_num++;
			next_name = GetNameParams(rec_name, del_num + 1);
		}
		//Последний параметр удаляется
		conf.DeteleParametr(name);
		conf.Save();
	}
	catch (...) {
		cout << "Не удалось удалить получателя!\n";
		q.WaitPressSay();
		return;
	}

	cout << "Параметр был успешно удалён!\n";
	q.WaitPressSay();
	return;
}

void recipients_list::Menu()
{
	questions_user q;
	

	while (true) {
		q.ClearConsole();
		ShowAllReceive();
		int res = q.SendQuestInt("Выберите действие", { "Добавить", "Удалить", "Выход" });

		res = ParseAnswer(res);

		//Если вернулся -1 - то выход
		if (res == -1)
			break;
	}
}

int recipients_list::ParseAnswer(int number)
{
	//Добавление
	if (number == 1) {
		AddReceiver();
	}

	if (number == 2) {
		DeleteRecipient();
	}

	//Выход
	if (number == 3) {
		return -1;
	}
	return 1;
}
