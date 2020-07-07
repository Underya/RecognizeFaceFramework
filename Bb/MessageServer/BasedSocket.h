#pragma once

#include "Message.h"
#include "winsock_init.h"

//Класс простого сокета, который слушает и отправляет сообщения
class MESSAGESERVER_API BasedSocket : 
	winsock_init
{
public:

	BasedSocket(std::string IPV4, std::string port);

	virtual ~BasedSocket();

	//Получать адрес текущего сокета
	std::string GetAddress();

	//Получить порт текущего сокета
	std::string GetPort();

protected:

	//Создание самого сокета 
	//При отпарвлении сообщений необходимо его переиздавать
	void CreateSocket();

	//Непосредственно сам сокет
	int _socket = -1;

	//Информация об адресе сокета
	addrinfo* _info = NULL;

	//IPV4 аддресс сокета
	std::string _address;
	
	//Порт, с которым ассоциирован сокет
	std::string _port;

	//Получение необходимой информации об адресе в виде, удобном для системы
	addrinfo * GetAddressInformation();

};

