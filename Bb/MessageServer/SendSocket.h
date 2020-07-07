#pragma once
#include "BasedSocket.h"

//����� ��� �������� ��������� �� ������ ������
class MESSAGESERVER_API SendSocket :
	public BasedSocket
{
public:

	//����� � ����, � ������� ����� ����������� ���������
	SendSocket(std::string address, std::string port);

	virtual ~SendSocket();

	//����������� ��������� �� ��������� ���� � �����
	virtual void SendMess(Message message, std::string address, std::string port);

protected:

	addrinfo* clientAddress = NULL;

	//���������� ��������� � �������
	virtual char* PrepateToSend(const char* message, int size, int &newSize);

	struct addrinfo* GetClientAddress(std::string address, std::string port);

	//������ ���� ��������, �� ������� ����� ����������� ��������
	static std::vector<std::string> _list_address;

	//������ ���� �������, �� ������� ��������� ��������
	static std::vector<int> _list_sock;

	//������� �������� ������ � ��������
	int _postionInList = -1;
};



