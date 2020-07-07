#include "pch.h"
#include "ListenMassage.h"


ListenMassage::ListenMassage(std::string ip_addr)
{
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		throw "Exception";
	}

	ZeroMemory(&hints, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	result = getaddrinfo(ip_addr.c_str(), "8000", &hints, &addr);

	if (result != 0) {
		WSACleanup();
		throw "Exception2";
	}

	listen_socket = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
	if (listen_socket == INVALID_SOCKET) {
		freeaddrinfo(addr);
		WSACleanup();
		throw "Exception3";
	}

	//Привязка к адресу
	result = bind(listen_socket, addr->ai_addr, (int)addr->ai_addrlen);

	if (result == SOCKET_ERROR) {
		freeaddrinfo(addr);
		closesocket(listen_socket);
		WSACleanup();
		return;
	}

	if (listen(listen_socket, SOMAXCONN) == SOCKET_ERROR) {
		closesocket(listen_socket);
		WSACleanup();
		return;
	}

	AccessConstruct = true;
}


ListenMassage::~ListenMassage()
{
	if (AccessConstruct) {
		closesocket(listen_socket);
		WSACleanup();
	}
}

void ListenMassage::list()
{
	while (true) {
		ListenConnect();
	}
}

void ListenMassage::GetMess(std::string mess)
{

}



void ListenMassage::SendMess(const char * Mess, const char * addres)
{
	//Надо создать новый сокет

	struct addrinfo *addr2 = NULL;

	struct  addrinfo clientif;
	ZeroMemory(&clientif, sizeof(hints));

	clientif.ai_family = AF_INET;
	clientif.ai_socktype = SOCK_STREAM;
	clientif.ai_protocol = IPPROTO_TCP;
	clientif.ai_flags = AI_PASSIVE;

	int result = getaddrinfo(addres, "8000", &clientif, &addr2);

	int clientSock = socket(addr2->ai_family,addr2->ai_socktype, addr2->ai_protocol );

	int connect_res =  connect(clientSock, addr2->ai_addr, addr2->ai_addrlen);

	std::string mess = "mess_count:" + std::to_string(count_mess++);
	int len;
	len = strlen(mess.c_str());
	result = send(clientSock, mess.c_str(), len, 0);
	std::cout << "res:" << result << "\n";
}


void ListenMassage::ListenConnect()
{
	// Принимаем входящие соединения
	int client_socket = accept(listen_socket, NULL, NULL);
	if (client_socket == INVALID_SOCKET) {
		throw "Exception";
	}

	const int max_client_buffer_size = 1024;
	char buf[max_client_buffer_size];

	int result = recv(client_socket, buf, max_client_buffer_size, 0);

	if (result == SOCKET_ERROR) {
		std::cout << "recv failed" << result << "\n";
	}
	else if (result == 0) {
		// соединение закрыто клиентом
		std::cout << "connection closed...\n";
	}
	else if (result > 0) {
		// Мы знаем фактический размер полученных данных, поэтому ставим метку конца строки
		// В буфере запроса.
		buf[result] = '\0';

		std::cout << buf << "\n";

		closesocket(client_socket);

		return;
		std::stringstream response; // сюда будет записываться ответ клиенту
		std::stringstream response_body; // тело ответа

		// Данные успешно получены
		// формируем тело ответа (HTML)
		response_body << "<title>Test C++ HTTP Server</title>\n"
			<< "<h1>Test page</h1>\n"
			<< "<p>This is body of the test page...</p>\n"
			<<  "<h2>Request headers</h2>\n"
			<< "<pre>" << buf << "</pre>\n"
			<< "<em><small>Test C++ Http Server</small></em>\n"
			<< "<p>count connect :" << std::to_string(numeric_count);

		numeric_count++;

		// Формируем весь ответ вместе с заголовками
		response << "HTTP/1.1 200 OK\r\n"
			<< "Version: HTTP/1.1\r\n"
			<< "Content-Type: text/html; charset=utf-8\r\n"
			<< "Content-Length: " << response_body.str().length()
			<< "\r\n\r\n"
			<< response_body.str();


		// Отправляем ответ клиенту с помощью функции send
		result = send(client_socket, response.str().c_str(),
			response.str().length(), 0);

		if (result == SOCKET_ERROR) {
			// произошла ошибка при отправле данных
			std::cout << "send failed: " << WSAGetLastError() << "\n";
		}
		// Закрываем соединение к клиентом
		closesocket(client_socket);
	}
}
