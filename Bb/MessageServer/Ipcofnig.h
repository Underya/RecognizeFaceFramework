#pragma once

#include <iostream>
#include <string>
#include <vector>
//Подключается для использования необходимых библиотек
#include "winsock_init.h"

//Класс предоставляет некоторые сведения о сетевом устройстве системы
class MESSAGESERVER_API Ipcofnig :
	winsock_init
{
public:

	Ipcofnig();

	~Ipcofnig();

	//Полученеи IP версии V4
	std::string GetIpV4();

	//Получение IP версии V6
	std::string GetIpV6();
	

protected:

	//Получение IP, помеченного укзанной версии
	std::string GetIp(int ver);

	//Получение всех IP адресов данного устройства
	std::vector<std::pair<std::string, int>> GetMyIp();

	//Получение номера версии протокола адреса (4 для IP_V4 и 6 для IP_V6 соотвественно)
	int GetV(sockaddr_in* addr);

	//Проверка, является ли адрес пустым
	bool IsEmptyAddr(std::string addr);
};

