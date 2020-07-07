#include "../MessageServer/ListenServer.h"

using namespace std;

//Объект для получения сообщений
ListenServer* server = NULL;

//Вывод информации о том, кто слушает
void ShowInfo(std::string address, std::string port) {
	cout << "Адрес:" << address << " Порт:" << port << " Без шифрования\n\n";
}

//Показ информации об сообщении
void ShowMess(Message message) {
	cout << "id:" << message.GetId() << "\n";
	cout << "Имя: " << message.GetFirstName() << " Фамилия:" << message.GetLastName() << " Отчество:" << message.GetMidName() << "\n";

	tm t = message.GetTime();

	cout << "Время: " << t.tm_hour << ":" << t.tm_min << ":" << t.tm_sec << " " << t.tm_mday << "." << t.tm_mon + 1 << "." << t.tm_year + 1900 << "\n";

	vector<pair<int, string>> temp;
	temp = message.GetGroupList();
	cout << "Группы:\n";
	for (auto iter = temp.begin(); iter != temp.end(); iter++) {
		cout << "id:" << iter->first << " Название:" << iter->second << "\n";
	}
	temp = message.GetRulesList();
	cout << "Правила:\n";
	for (auto iter = temp.begin(); iter != temp.end(); iter++) {
		cout << "id:" << iter->first << " Название:" << iter->second << "\n";
	}
	
}


void main() {

	//Информация об адресах
	std::string address = "127.0.0.10";
	std::string port = "90000";
	//Создание объекта и информации о нём
	server = new ListenServer(address, port);

	system("chcp 1251");

	//Начало прослушивания
	server->Start();

	ShowInfo(address, port);

	//Цикл внутри которого происходит разбор сообщений
	while (true)
	{
		//Ожидание сообщения
		Message mess = server->WaitMessage();

		//Разбор сообщения и вывода информации о нём
		ShowMess(mess);
		cout << "\n";
	}
}