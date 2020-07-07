#include "pch.h"
#include "BasedSocket.h"

//������������� ������ ��������
WSADATA BasedSocket::wsaData;

BasedSocket::BasedSocket(std::string address, std::string port) : winsock_init()
{
	_address = address;
	_port = port;
	CreateSocket();
}

BasedSocket::~BasedSocket()
{
	
	//���� ��� ��������������� ����� - ������� ���
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
	//��������� ���������� �� ������
	_info = GetAddressInformation();
	//�������� ������ ������
	_socket = socket(_info->ai_family, _info->ai_socktype, _info->ai_protocol);
	//���� �� ������� ������� �����
	if (_socket == INVALID_SOCKET) {
		//�������, ��� ����� �� ��� ������
		_socket = -1;
		//�������� ������
		throw std::exception("Exception! Not create Socket");
	}
}

addrinfo * BasedSocket::GetAddressInformation()
{
	//�������� ������� � ���� ���������� � �����������
	addrinfo hints;
	//�������� ������ �� ���� ����� ���������
	ZeroMemory(&hints, sizeof(hints));
	
	//����� ������ ������
	struct addrinfo * my_address;

	//��������, ��� ������������
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	//����� �������, ������� ������� ������ ���������� �� ������
	int result = getaddrinfo(_address.c_str(), _port.c_str(), &hints, &my_address);

	//��������, ������� �� �������� ����������
	if (result != 0) {
		//�������� ������, ��� ��� �� ������� �������� ���������� � ������
		throw std::exception("Exception! Not access address information");
	}

	return my_address;
}

