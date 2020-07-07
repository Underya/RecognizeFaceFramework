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
	//����������� � ������
	Bind();
	//������ �������������
	int result = listen(_socket, SOMAXCONN);
	//���� �� ������� ������ �������������
	if (result == SOCKET_ERROR) {
		throw std::exception("Exception! Not Succes Listen!");
	}

	//���������� ���������� ���������
	while (true) {
		result = ReceiveMess();

		//std::cout << "Not Recevice Mess\n";

		//���� ��������� 0 - �� ��, ���������� ���������
		if (result == 0) continue;
		//���� ��������� -1 - �� �� ������� ������� ����������
		if (result == -1) {
			std::cout << "Not Success accept\n";
		}
		//���� ��������� -2 - �� �� ������� ������� ���������
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
	//�������� � ������
	int result = bind(_socket, _info->ai_addr, (int)_info->ai_addrlen);
	if (result == SOCKET_ERROR) {
		throw std::exception("Exception! Not bin this address!");
	}
	//��������, ��� ���������� ������� �����������
	_bind = true;

}

int ListenSocket::ReceiveMess()
{
	//���������� ��� ������ ����������� ���������
	int client_socket = -1;
	//�������� �������� � �������� ����������
	client_socket = accept(_socket, NULL, NULL);
	if (client_socket == INVALID_SOCKET) {
		return -1;
	}

	//������ ��� ���������
	char *buff = new char[_maxMessageSize]();
	//��������� ���������
	int sizeMessage = recv(client_socket, buff, _maxMessageSize, 0);
	//���� ������ ��������� ����� 0 - �� ��� �������� ����������
	if (sizeMessage == 0) {
		closesocket(client_socket);
		shutdown(client_socket, 0);
		//�������� ����������, �������� ����������
		delete [_maxMessageSize]buff;
		return 0;
	}
	//���� ������ - �� ��� ������
	if (sizeMessage < 0) {
		closesocket(client_socket);
		delete [_maxMessageSize]buff;
		//������� ������
		return - 2;
	}
	//�������� 0 ������ � ����� ������
	buff[sizeMessage] = 0;

	//�������������� ������ � ���������
	Message cMessage = ParseBufferText(buff, sizeMessage);

	//����� �������, ������� ��������� ���������
	int result = ParseMessage(cMessage);

	//������ ����������
	
	//�������� ������ �� ��� �������
	delete[_maxMessageSize]buff;

	//�������� ����������
	closesocket(client_socket);
	return 0;
}

int ListenSocket::ParseMessage(Message message)
{
	//������ ���� �����
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
	//���� - ����� ������ �� �����
	*/
	return 0;
}
