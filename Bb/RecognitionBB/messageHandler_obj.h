#pragma once
#include "../MessageServer/notificationServer.h"
#include "thread_obj.h"
#include "timer_list.h"

class messageHandler_obj :
	public thread_obj
{
public:
	
	messageHandler_obj(std::string address, std::string port);

	//���������� ������ ����� � JSON ������ �����������
	void SetListRecepient(std::vector<std::string> filePath);

	//���������� ���������� ���������� 
	void AddRecepient(std::vector<Recipient> listRecipient);

	simple_pipe<Message>* GetMyPipe();

protected:

	simple_pipe<Message>* _messPipe = NULL;

	std::string _address = "";

	std::string _port = "";


	//������ ����� � JSON ������, � ������� ������� ����������
	std::vector<std::string> _filePath;

	std::vector<Recipient> _listRecepient;

	//�����, ������� ����������, ����� ����� �������� ��������
	virtual void ThreadMethod() override;

	int ParseMessageRetInt();

	void EndWork();

	virtual void ParseMessage();

	//�����, � ������� ����������� ��������� ��� ��������
	virtual void ParseControlMess() override;

	//�����, ������� ������ ������ ��� �������� ���������
	void CreateNotServ();

	notificationServer* _server = NULL;
};

