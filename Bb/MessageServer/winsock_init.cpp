#include "pch.h"
#include "winsock_init.h"


int winsock_init::count_use_winsok = 0;

winsock_init::winsock_init()
{
	//�������, ��� �������� ����� ������
	AddNewObj();
}

winsock_init::~winsock_init()
{
	//�������, ��� ��������� ������ ������
	CloseObj();
}

void winsock_init::AddNewObj()
{
	//���� �� ����� �� ���� ��������� �������� - ��������������� WSAS
	if(count_use_winsok == 0)
		InitialWinsock();
	//��������� ���������� ��������
	count_use_winsok++;
}

void winsock_init::CloseObj()
{
	count_use_winsok--;
	//���� �� �������� �������� - ������� wsas
	CloseWinsock();
}

void winsock_init::InitialWinsock()
{
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		throw std::exception("Exception! Not WSAStartup");
	}
}

void winsock_init::CloseWinsock()
{
	WSACleanup();
}
