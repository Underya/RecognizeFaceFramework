#pragma once

#include"recipient.h"

//Класс, который является передаёт и формирует сообщение всем слушателям
class MESSAGESERVER_API notificationServer
{
public:

	//Создание нового объекта, с указанием сервера отправки
	notificationServer(SendServer * server);

	notificationServer();

	void SetSendServer(SendServer *server);

	//Добавления нового слушателя в список
	void AddNewRecipient(Recipient recepient);

	//Добавление нового слушателя в список
	//из файла в формате JSON
	void AddNewRecipient(std::string fileFullPath);

	//Отправление сообщения всем слушателям, кто попадает под правило
	//Группы и правила беруется из сообщения
	void SendChekMess(Message mess);

	//Отправление сообщения всем слушателям, кто попадает под правило
	void SendChekMess(Message mess, std::vector<int> id_rule, std::vector<int> id_group);

	//Получение всего списка получаталей
	std::vector<Recipient> GetListRecepient();

	//Получение адресов всех слушателей, кому не удалось отправить сообщение
	std::vector<std::string> GetAddressErrorMessage();

protected:

	std::string GetTextForFile(std::string  fileFullPath);

	//Указатель на объект, через который должны отправлятся сообщения
	SendServer *_server = NULL;

	//Список тех, кому надо отправлять сообщения
	std::vector<Recipient> _list_recip;

	//Установка для всех объекто списка нового сервера
	void SetAllServer();

};

