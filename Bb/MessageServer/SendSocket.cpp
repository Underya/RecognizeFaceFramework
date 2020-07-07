#include "pch.h"
#include "SendSocket.h"

std::vector<std::string> SendSocket::_list_address;

//Список всех сокетов, по которым проиходит отправка
std::vector<int> SendSocket::_list_sock;

SendSocket::SendSocket(std::string address, std::string port) : BasedSocket(address, port)
{
}

SendSocket::~SendSocket()
{

}

void SendSocket::SendMess(Message message, std::string address, std::string port)
{
	//int sock = -1;
	////Поиск адреса и порт среди всех известных
	//SearchAddress(address, port);

	////Если не был найден адрес
	//if (_postionInList == -1) {
	//	//Добавить в список
	//	AddAdress(address, port);
	//	//Добавить его сокет
	//	AddNewSock(address, port);
	//	//Попытаться соедениться
	//	TryConnect();
	//}
	//

	////Попытка отправить сообщение
	//if (!TrySendMess(message)) {
	//	std::cout << "error";
	//}

	//return;
	//Получение адреса клиента
	addrinfo* clientAddress = GetClientAddress(address, port);
	//Полученик сокета клиента для отправки сообщений
	int clientSock = socket(clientAddress->ai_family, clientAddress->ai_socktype, clientAddress->ai_protocol);
	
	//Провекра, удалось получить сокет
	if (clientSock == SOCKET_ERROR) {
		throw std::exception("Exception! Not Success get client socket!");
	}

	//Попытка соедениться
	int connect_result =  connect(clientSock, clientAddress->ai_addr, clientAddress->ai_addrlen);
	
	//Если не удалось открыть соеденение
	if (connect_result != 0) {
		int error_code = WSAGetLastError();
		std::string error_str = "" + std::to_string(error_code);
		//std::cout << error_str << "\n";
		throw std::exception("Exception! Not success connect to client socket!");
	}

	//Отправка сообщения
	const char* buff = message.GetMessageToSend();
	int size = message.GetSizeMessageToSend();
	int newSize = 0;
	const char* sendBuff = PrepateToSend(buff, size, newSize);
	int send_size_mess = send(clientSock, sendBuff, newSize, 0);

	//Отправка сообщения для закрытия соеденения
	send(clientSock, "", 0, 0);

	//Удаление памяти из под буффера сообщения
	delete[newSize]sendBuff;
	delete[size]buff;

	//Очищение информации об адресе
	freeaddrinfo(clientAddress);
	//Закрытие соеденения с клиентом
	closesocket(clientSock);
	shutdown(clientSock, 0);
}


char* SendSocket::PrepateToSend(const char* message, int size, int& newSize)
{
	newSize = size;
	char* newMess = new char[size]();
	memcpy(newMess, message, size);
	return newMess;
}

addrinfo* SendSocket::GetClientAddress(std::string address, std::string port)
{
	//Создание структуры предварительной информации
	struct addrinfo clientif;
	ZeroMemory(&clientif, sizeof(clientif));

	clientif.ai_family = AF_INET;
	clientif.ai_socktype = SOCK_STREAM;
	clientif.ai_protocol = IPPROTO_TCP;
	clientif.ai_flags = AI_PASSIVE;

	//Структура для записи результат
	struct addrinfo* clientAddress = NULL;

	int result = getaddrinfo(address.c_str(), port.c_str() , &clientif, &clientAddress);

	//Проврека, удалось ли получить результат
	if (result != 0) {
		if (WSANOTINITIALISED == result) {

		}
		throw std::exception("Exception! Not get client address info!");
	}

	return clientAddress;
}
