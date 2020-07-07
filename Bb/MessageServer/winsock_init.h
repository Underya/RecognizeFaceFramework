#pragma once

#ifdef _WIN64 | _WIN32

#ifndef _WINSOKET_API

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#pragma comment(lib, "Ws2_32.lib")
#define _WINSOKET_API
#endif // _WINSOKET_API
		
#else

#endif //WIN64


#include <iostream>

#ifdef MESSAGESERVER_EXPORTS
#define MESSAGESERVER_API __declspec(dllexport)
#else
#define MESSAGESERVER_API __declspec(dllimport)
#endif


//�����, ���������������� ������ � winsock
//��� ������, ������������ winsock, ������ ����������� ���
class MESSAGESERVER_API winsock_init
{
public:

	winsock_init();

	virtual ~winsock_init();

protected:

	//���������� ��������, ����������� winsock
	static int count_use_winsok;

	//����� ��� ���� �������� ������ � ����� � ���������
	static WSADATA wsaData;

	//�������� ������ �������, ������������� winsock
	static void AddNewObj();

	//�������� �������, ������������� winsock
	static void CloseObj();

	//������������� WSAS
	static void InitialWinsock();

	//�������� WSAS
	static void CloseWinsock();
};

