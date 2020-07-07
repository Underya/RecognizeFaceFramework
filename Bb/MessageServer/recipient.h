#pragma once

#include <vector>
#include <string>
#include <thread>

#include "grPair.h"
#include "SendServer.h"


//���������� ���������
//��� �� ������ ������ � �����
class MESSAGESERVER_API Recipient
{
public:

	//����������� � ��������� ������ � ����� ����� ���������, ���������� ����������
	//������ 127.0.0.1:8000
	Recipient(std::string IPV4_PORT);
	
	//����������� � ���������� ��������� ������ � �����
	Recipient(std::string IPV4, std::string port);

	//���� � ����� ���� ������� ����� �����
	Recipient();

	//���������� IPV4 ����� ����������
	void SetAddress(std::string addressIPV4);

	//���������� ���� ����������
	void SetPortRecepient(std::string port);

	//��������� �������������� ���������
	void SetAddInfo(std::string addInfo);

	//��������� �������������� ����������, ������� ������������ � ����������
	std::string GetAddInfo();

	//��������� IPV4 ������, ���������� � ��������
	std::string GetAddress();
	
	//��������� ������ �����, ���������� � ��������
	std::string GetPort();

	//��������, ���� �� ���������� ��������� ��������� � ������� � ��������, ��� �������������� �������� � ����������
	bool CheckList(std::vector<int> id_rule_list, std::vector<int> id_group_list);

	//���������� ������, ����� ������� ����� ����������� ���������
	void SetSendServer(SendServer* server);

	//��������� ��������� 
	//���� ����������� ������ ��� ����
	//�� ��� ��������� ������ ������
	void SendMess(Message message);

	//���������� ����� ����
	void AddPair(grPair pair);

	//���������� ����� ����
	void AddPair(std::vector<int> group, std::vector<int> rule);

	//���� �� ������� ���������� ��������� ���������
	bool HasErrorMessage();

protected:

	//��������, �������� �� ������� ���� ��� ��������� �������
	bool ChekPair(grPair pair, std::vector<int> id_rule_list, std::vector<int> id_group_list);

	//��������� �� ������ ��� �������� ���������
	SendServer* _sendMess = NULL;

	//�������������� ���������
	std::string _add_info = "";

	//IPV4 ������
	std::string _address = "";

	//���� ����������
	std::string _port = "";

	//������ ��� ��� �������� ��������
	std::vector<grPair> _pairList;

};

