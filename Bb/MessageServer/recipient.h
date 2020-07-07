#pragma once

#include <vector>
#include <string>
#include <thread>

#include "grPair.h"
#include "SendServer.h"


//Получатель сообщения
//Сам он обычно описан в файле
class MESSAGESERVER_API Recipient
{
public:

	//Конструктор с указанием адреса и порта одним параетром, разделённым двоеточием
	//Пример 127.0.0.1:8000
	Recipient(std::string IPV4_PORT);
	
	//Констркутор с раздельным указанием адреса и порта
	Recipient(std::string IPV4, std::string port);

	//Порт и адрес надо указать через метод
	Recipient();

	//Установить IPV4 адрес получателя
	void SetAddress(std::string addressIPV4);

	//Установить порт получателя
	void SetPortRecepient(std::string port);

	//Установка дополнительной инормации
	void SetAddInfo(std::string addInfo);

	//Получение дополнительной информации, которая пересылается с сообщением
	std::string GetAddInfo();

	//Получение IPV4 адреса, связанного с объектом
	std::string GetAddress();
	
	//Получение номера порта, связанного с объектом
	std::string GetPort();

	//Проверка, надо ли отправлять сообщение сотрудниу с правами и группами, чьи идентификаторы переданы в параметрах
	bool CheckList(std::vector<int> id_rule_list, std::vector<int> id_group_list);

	//Установить объект, через который будут отправлятся сообщения
	void SetSendServer(SendServer* server);

	//Отправить сообщение 
	//Если отправитель указал доп инфо
	//То оно добавится внутри класса
	void SendMess(Message message);

	//Добавление новой пары
	void AddPair(grPair pair);

	//Добавление новой пары
	void AddPair(std::vector<int> group, std::vector<int> rule);

	//Было ли успешно отправлено последнее сообщение
	bool HasErrorMessage();

protected:

	//Проверка, подходят ли условия пары под указанные условия
	bool ChekPair(grPair pair, std::vector<int> id_rule_list, std::vector<int> id_group_list);

	//Указатель на объект для отправки сообщений
	SendServer* _sendMess = NULL;

	//Дополнительная инормация
	std::string _add_info = "";

	//IPV4 адресс
	std::string _address = "";

	//Порт получателя
	std::string _port = "";

	//Список пар для текущего адресата
	std::vector<grPair> _pairList;

};

