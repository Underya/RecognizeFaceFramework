#pragma once
#include "BasedSocket.h"

//Сокет, который прослушивает сообщения
class MESSAGESERVER_API ListenSocket :
	public BasedSocket
{
public:

	//Создание сокета нового сокета
	//И указание, по какому адресу и порту он будет прослушивать сообщение
	ListenSocket(std::string IPV4, std::string port);

	virtual ~ListenSocket();


protected:

	//Начало прослушивания сообщений сокетом
	virtual void Listen();
	
	//Максимальеный размер отправляемого и получаемого сообщения
	static int _maxMessageSize;

	//Преобразование полученного из буффера текста в сообщение
	virtual Message ParseBufferText(char *text, int size);

	//Флаг, удалось ли подключится к соеденению
	bool _bind = false;

	//Флаг, указывающий, находится ли сейчас сокет в состоянии прослушивания
	bool _listen = false;

	//Привязка сокета к указанному адресу
	virtual void Bind();

	//Главная функция приёма сообщений
	virtual int ReceiveMess();

	//Разбор полученного сообщения
	virtual int ParseMessage(Message message);
};

