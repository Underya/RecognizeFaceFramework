#pragma once
#include "SendSocket.h"
#include "BlowfishCoder.h"

//Отправка сообщений на различные сервера
class MESSAGESERVER_API SendServer :
	public SendSocket
{
public:

	//Создания нового объекта 
	//addressIPV4 - адрес, с какого сокета будут отправлятся сообщения
	//port - порт сокеат
	//encdode - флаг, указывающий, надо ли кодировать отправляемые сообщения
	SendServer(std::string addressIPV4, std::string port, bool encode = false);
		
	//Установка нового кодера
	//Например, для смены ключа или размера блока
	void SetCoder(BlowfishCoder* coder);

	//Указание, отправляются ли закодированные или обычные сообщения
	bool HasCoder();

	//Получение адреса сервера
	std::string GetAddress();

	//Получение порта сервера
	std::string GetPort();

	//Метод для парралельной отправки сообшений
	void operator()(Message message, std::string address, std::string port);

	//Была ли ошибка при отправке последненго сообщения
	bool ErrorMessageSend();

protected:

	//Кодер сообщений
	BlowfishCoder * _coder;

	//Указать, что была ошибка при последней передече
	void TrueError();

	//Указать, что ошибок не было
	void FalseError();

	//Флаг, указывающий, был ли ошибка при отправке сообщения из другого потока
	std::string *_hasErrorLastMess = NULL;

	//Флаг, указывающий, надо ли кодировать сообщения
	bool _encode = false;

	//Во время подготовки сообщения, его возможно придётся кодировать
	char* PrepateToSend(const char* message, int size, int& newSize) override;
};

