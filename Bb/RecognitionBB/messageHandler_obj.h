#pragma once
#include "../MessageServer/notificationServer.h"
#include "thread_obj.h"
#include "timer_list.h"

class messageHandler_obj :
	public thread_obj
{
public:
	
	messageHandler_obj(std::string address, std::string port);

	//Добавление списка путей к JSON файлам получателей
	void SetListRecepient(std::vector<std::string> filePath);

	//Добавление одиночного получателя 
	void AddRecepient(std::vector<Recipient> listRecipient);

	simple_pipe<Message>* GetMyPipe();

protected:

	simple_pipe<Message>* _messPipe = NULL;

	std::string _address = "";

	std::string _port = "";


	//Вектор путей к JSON файлам, в которых описаны получатели
	std::vector<std::string> _filePath;

	std::vector<Recipient> _listRecepient;

	//Метод, который вызывается, когда поток начинает работать
	virtual void ThreadMethod() override;

	int ParseMessageRetInt();

	void EndWork();

	virtual void ParseMessage();

	//Метод, в котором разибраются сообщения для контроля
	virtual void ParseControlMess() override;

	//Метод, который создаёт сервер для отправки сообщений
	void CreateNotServ();

	notificationServer* _server = NULL;
};

