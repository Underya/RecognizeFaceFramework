#pragma once
#include "SendSocket.h"
#include "BlowfishCoder.h"

//�������� ��������� �� ��������� �������
class MESSAGESERVER_API SendServer :
	public SendSocket
{
public:

	//�������� ������ ������� 
	//addressIPV4 - �����, � ������ ������ ����� ����������� ���������
	//port - ���� ������
	//encdode - ����, �����������, ���� �� ���������� ������������ ���������
	SendServer(std::string addressIPV4, std::string port, bool encode = false);
		
	//��������� ������ ������
	//��������, ��� ����� ����� ��� ������� �����
	void SetCoder(BlowfishCoder* coder);

	//��������, ������������ �� �������������� ��� ������� ���������
	bool HasCoder();

	//��������� ������ �������
	std::string GetAddress();

	//��������� ����� �������
	std::string GetPort();

	//����� ��� ������������ �������� ���������
	void operator()(Message message, std::string address, std::string port);

	//���� �� ������ ��� �������� ����������� ���������
	bool ErrorMessageSend();

protected:

	//����� ���������
	BlowfishCoder * _coder;

	//�������, ��� ���� ������ ��� ��������� ��������
	void TrueError();

	//�������, ��� ������ �� ����
	void FalseError();

	//����, �����������, ��� �� ������ ��� �������� ��������� �� ������� ������
	std::string *_hasErrorLastMess = NULL;

	//����, �����������, ���� �� ���������� ���������
	bool _encode = false;

	//�� ����� ���������� ���������, ��� �������� ������� ����������
	char* PrepateToSend(const char* message, int size, int& newSize) override;
};

