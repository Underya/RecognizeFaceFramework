#pragma once

#include"recipient.h"

//�����, ������� �������� ������� � ��������� ��������� ���� ����������
class MESSAGESERVER_API notificationServer
{
public:

	//�������� ������ �������, � ��������� ������� ��������
	notificationServer(SendServer * server);

	notificationServer();

	void SetSendServer(SendServer *server);

	//���������� ������ ��������� � ������
	void AddNewRecipient(Recipient recepient);

	//���������� ������ ��������� � ������
	//�� ����� � ������� JSON
	void AddNewRecipient(std::string fileFullPath);

	//����������� ��������� ���� ����������, ��� �������� ��� �������
	//������ � ������� �������� �� ���������
	void SendChekMess(Message mess);

	//����������� ��������� ���� ����������, ��� �������� ��� �������
	void SendChekMess(Message mess, std::vector<int> id_rule, std::vector<int> id_group);

	//��������� ����� ������ �����������
	std::vector<Recipient> GetListRecepient();

	//��������� ������� ���� ����������, ���� �� ������� ��������� ���������
	std::vector<std::string> GetAddressErrorMessage();

protected:

	std::string GetTextForFile(std::string  fileFullPath);

	//��������� �� ������, ����� ������� ������ ����������� ���������
	SendServer *_server = NULL;

	//������ ���, ���� ���� ���������� ���������
	std::vector<Recipient> _list_recip;

	//��������� ��� ���� ������� ������ ������ �������
	void SetAllServer();

};

