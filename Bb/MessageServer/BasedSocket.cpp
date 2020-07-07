#include "pch.h"
#include "BasedSocket.h"

//Ициниализация общего значения
WSADATA BasedSocket::wsaData;

BasedSocket::BasedSocket(std::string address, std::string port) : winsock_init()
{
	_address = address;
	_port = port;
	CreateSocket();
}

BasedSocket::~BasedSocket()
{
	
	//Если был инициализирован сокет - закрыть его
	if (_socket != -1) {
		closesocket(_socket);
	}
}

std::string BasedSocket::GetAddress()
{
	return _address;
}

std::string BasedSocket::GetPort()
{
	return _port;
}

void BasedSocket::CreateSocket()
{
	//Получение информации об адресе
	_info = GetAddressInformation();
	//Создание самого сокета
	_socket = socket(_info->ai_family, _info->ai_socktype, _info->ai_protocol);
	//Если не удалось создать сокет
	if (_socket == INVALID_SOCKET) {
		//Указать, что сокет не был создан
		_socket = -1;
		//Выкинуть ошибку
		throw std::exception("Exception! Not create Socket");
	}
}

addrinfo * BasedSocket::GetAddressInformation()
{
	//Создание объекта в виде информации с подключеним
	addrinfo hints;
	//Очищение памяти во всех полях структуры
	ZeroMemory(&hints, sizeof(hints));
	
	//Адрес самого сокета
	struct addrinfo * my_address;

	//Указание, что используется
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	//Вызов функции, которая получит полную информацию об адресе
	int result = getaddrinfo(_address.c_str(), _port.c_str(), &hints, &my_address);

	//Проверка, удалось ли получить информацию
	if (result != 0) {
		//Выкинуть ошибку, так как не удалось получить информацию о сокете
		throw std::exception("Exception! Not access address information");
	}

	return my_address;
}

