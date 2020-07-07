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


//Класс, инициализирующий работу с winsock
//Все классы, использующие winsock, должны наследовать его
class MESSAGESERVER_API winsock_init
{
public:

	winsock_init();

	virtual ~winsock_init();

protected:

	//Количество объектов, использющих winsock
	static int count_use_winsok;

	//Общий для всех объектов объект с инфой о соеднении
	static WSADATA wsaData;

	//Создание нового объетка, использующего winsock
	static void AddNewObj();

	//Закрытие объекта, использующего winsock
	static void CloseObj();

	//Инициализация WSAS
	static void InitialWinsock();

	//Закрытие WSAS
	static void CloseWinsock();
};

