#pragma once

#include <thread>
#include <mutex>
#include <queue>

#include "ListenSocket.h"
#include "BlowfishCoder.h"

//������ ������������� ��������� �� ������������ ������ � �����
class MESSAGESERVER_API ListenServer:
	public ListenSocket
{
public:

	ListenServer(std::string addressIPV4, std::string port, bool EncoderMessage = false);

	//������ ������ �� ��������� �� ������
	//��������, ��� ����� ����� ����� ��� �����
	void SetCoder(BlowfishCoder* NewCoder);

	//��������, �������� �� ������ ������������ ���������
	bool HasCoder();

	//��������� ���������� ���������
	int CountMess();
	
	//������ ������� ��� �������������
	void Start();

	//��������� ������� � ������� ���������
	Message GetMessag();

	//���� ���� ��������� - �� ��� ���������
	//����� - �������� �������� ���������
	//(���������� �����)
	Message WaitMessage();

	//���������� ��������� ��� ������ ������
	void operator()();

protected:

	//��������� ������ ������� ���������
	int ParseMessage(Message message) override;

	//���������� ������ �������������� ������ � ������ ���������, ��� ��� ������ ��� ����� ���� �����������
	Message ParseBufferText(char* buffer, int sizeMessage) override;

	//���������� ��������� � �������
	void AddMessage(Message message);

	//������ ���������� �������� ��� ������������� � ��������� �����
	static void StartNewListenThread(ListenServer *_server);

	//������ �� ����� �����������
	std::queue<Message>* _queueMessage = NULL;

	//������� ������ ��� ������������� ��������
	std::mutex * _mutex  = NULL;

	//����� ��� ����������� � ������������ ���������
	BlowfishCoder *  _coder = NULL;

	//����, �����������, ����� �� ��� ���������� ��������� ��������������, ��� ���
	bool _encoderMessage = false;
};

