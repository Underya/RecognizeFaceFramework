#pragma once
#include "BasedSocket.h"

//�����, ������� ������������ ���������
class MESSAGESERVER_API ListenSocket :
	public BasedSocket
{
public:

	//�������� ������ ������ ������
	//� ��������, �� ������ ������ � ����� �� ����� ������������ ���������
	ListenSocket(std::string IPV4, std::string port);

	virtual ~ListenSocket();


protected:

	//������ ������������� ��������� �������
	virtual void Listen();
	
	//������������� ������ ������������� � ����������� ���������
	static int _maxMessageSize;

	//�������������� ����������� �� ������� ������ � ���������
	virtual Message ParseBufferText(char *text, int size);

	//����, ������� �� ����������� � ����������
	bool _bind = false;

	//����, �����������, ��������� �� ������ ����� � ��������� �������������
	bool _listen = false;

	//�������� ������ � ���������� ������
	virtual void Bind();

	//������� ������� ����� ���������
	virtual int ReceiveMess();

	//������ ����������� ���������
	virtual int ParseMessage(Message message);
};

