#pragma once

#include "Message.h"
#include "winsock_init.h"

//����� �������� ������, ������� ������� � ���������� ���������
class MESSAGESERVER_API BasedSocket : 
	winsock_init
{
public:

	BasedSocket(std::string IPV4, std::string port);

	virtual ~BasedSocket();

	//�������� ����� �������� ������
	std::string GetAddress();

	//�������� ���� �������� ������
	std::string GetPort();

protected:

	//�������� ������ ������ 
	//��� ����������� ��������� ���������� ��� ������������
	void CreateSocket();

	//��������������� ��� �����
	int _socket = -1;

	//���������� �� ������ ������
	addrinfo* _info = NULL;

	//IPV4 ������� ������
	std::string _address;
	
	//����, � ������� ������������ �����
	std::string _port;

	//��������� ����������� ���������� �� ������ � ����, ������� ��� �������
	addrinfo * GetAddressInformation();

};

