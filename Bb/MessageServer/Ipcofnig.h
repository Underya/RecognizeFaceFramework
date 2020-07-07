#pragma once

#include <iostream>
#include <string>
#include <vector>
//������������ ��� ������������� ����������� ���������
#include "winsock_init.h"

//����� ������������� ��������� �������� � ������� ���������� �������
class MESSAGESERVER_API Ipcofnig :
	winsock_init
{
public:

	Ipcofnig();

	~Ipcofnig();

	//��������� IP ������ V4
	std::string GetIpV4();

	//��������� IP ������ V6
	std::string GetIpV6();
	

protected:

	//��������� IP, ����������� �������� ������
	std::string GetIp(int ver);

	//��������� ���� IP ������� ������� ����������
	std::vector<std::pair<std::string, int>> GetMyIp();

	//��������� ������ ������ ��������� ������ (4 ��� IP_V4 � 6 ��� IP_V6 �������������)
	int GetV(sockaddr_in* addr);

	//��������, �������� �� ����� ������
	bool IsEmptyAddr(std::string addr);
};

