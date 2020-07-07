#include "pch.h"
#include "ListenSocket.h"
 
int ListenSocket::_maxMessageSize = 4096;

ListenSocket::ListenSocket(std::string IPV4, std::string port) : BasedSocket(IPV4, port)
{
	
}

ListenSocket::~ListenSocket()
{
}

void ListenSocket::Listen()
{
	//Подключение к адресу
	Bind();
	//Начало прослушивания
	int result = listen(_socket, SOMAXCONN);
	//Если не удалось начать прослушивание
	if (result == SOCKET_ERROR) {
		throw std::exception("Exception! Not Succes Listen!");
	}

	//Бесконечно получаемые сообщения
	while (true) {
		result = ReceiveMess();

		//std::cout << "Not Recevice Mess\n";

		//Если вернулось 0 - всё ок, продолжить прослушку
		if (result == 0) continue;
		//Если вернулось -1 - то не удалось принять соеденение
		if (result == -1) {
			std::cout << "Not Success accept\n";
		}
		//Если вернулось -2 - то не удалось приянть сообщение
		if (result == -2) {
			std::cout << "Not Success receive message\n";
		}
	}
}

Message ListenSocket::ParseBufferText(char* text, int size)
{
	return Message(text, size);
}

void ListenSocket::Bind()
{
	//Привязка к адресу
	int result = bind(_socket, _info->ai_addr, (int)_info->ai_addrlen);
	if (result == SOCKET_ERROR) {
		throw std::exception("Exception! Not bin this address!");
	}
	//Указание, что соеденение успешно установлено
	_bind = true;

}

int ListenSocket::ReceiveMess()
{
	//Переменная для сокета отправителя сообщения
	int client_socket = -1;
	//Ожидание отправки и принятия соеденения
	client_socket = accept(_socket, NULL, NULL);
	if (client_socket == INVALID_SOCKET) {
		return -1;
	}

	//Буффер для сообщения
	char *buff = new char[_maxMessageSize]();
	//Получение сообщения
	int sizeMessage = recv(client_socket, buff, _maxMessageSize, 0);
	//Если размер сообщения равен 0 - то это закрытие соеденения
	if (sizeMessage == 0) {
		closesocket(client_socket);
		shutdown(client_socket, 0);
		//Закрытие соеденение, ожидание следующего
		delete [_maxMessageSize]buff;
		return 0;
	}
	//Если меньше - то это ошибка
	if (sizeMessage < 0) {
		closesocket(client_socket);
		delete [_maxMessageSize]buff;
		//Вернуть ошибку
		return - 2;
	}
	//Добавить 0 символ в конец строки
	buff[sizeMessage] = 0;

	//Преобразование текста в сообщение
	Message cMessage = ParseBufferText(buff, sizeMessage);

	//Вызыв функции, которая разбирает сообщение
	int result = ParseMessage(cMessage);

	//Рабзор результата
	
	//Очищение памяти из под буффера
	delete[_maxMessageSize]buff;

	//Закрытие соеденения
	closesocket(client_socket);
	return 0;
}

int ListenSocket::ParseMessage(Message message)
{
	//Выводе всех полей
	/*
	std::cout << message.GetId() << " "<< message.GetName() << " " << message.GetFamily() << " " << message.GetLastName() <<"\n";
	auto groups = message.GetGroupList();
	auto rules = message.GetRulesList();
	for (auto iter = groups.begin(); iter != groups.end(); iter++) {
		std::cout << iter->first << " " << iter->second << " \n";
	}
	for (auto iter = rules.begin(); iter != rules.end(); iter++) {
		std::cout << iter->first << " " << iter->second << " \n";
	}
	if (message.GetTime().tm_year != 0) {
		tm time = message.GetTime();
		std::cout << "date: " << time.tm_year << "." << time.tm_mon + 1 << "." << time.tm_mday << " ";
		std::cout <<"time: " << time.tm_hour;
		std::cout << ":" << time.tm_min << ":" << time.tm_sec;
		std::cout << "\n";
	}
	if (message.GetInfo() != "") std::cout << "info:" << message.GetInfo() << "\n";
	std::cout << "\n\n";
	//Пока - вывод текста на экран
	*/
	return 0;
}
