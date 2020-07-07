#pragma once
#include "BasedSocket.h"

//Сокет для отправки сообщений на другие сокеты
class MESSAGESERVER_API SendSocket :
	public BasedSocket
{
public:

	//Адрес и порт, с которых будут отправлятся сообщения
	SendSocket(std::string address, std::string port);

	virtual ~SendSocket();

	//Отправление сообщения на указанный порт и адрес
	virtual void SendMess(Message message, std::string address, std::string port);

protected:

	addrinfo* clientAddress = NULL;

	//Подготовка сообщения к отпраке
	virtual char* PrepateToSend(const char* message, int size, int &newSize);

	struct addrinfo* GetClientAddress(std::string address, std::string port);

	//Список всех адрессов, по которым может происходить отправка
	static std::vector<std::string> _list_address;

	//Список всех сокетов, по которым проиходит отправка
	static std::vector<int> _list_sock;

	//Позиция текушего адреса в векторах
	int _postionInList = -1;
};



