#pragma once

#include <thread>
#include <mutex>
#include <queue>

#include "ListenSocket.h"
#include "BlowfishCoder.h"

//Сервер прослушивющий сообщения по определённому адресу и порту
class MESSAGESERVER_API ListenServer:
	public ListenSocket
{
public:

	ListenServer(std::string addressIPV4, std::string port, bool EncoderMessage = false);

	//ЗАмена кодера по умолчанию на другой
	//Например, для смены длины блока или ключа
	void SetCoder(BlowfishCoder* NewCoder);

	//Указание, получает ли объект кодированные сообщения
	bool HasCoder();

	//Полученеи количества сообщений
	int CountMess();
	
	//Запуск сервера для прослушивания
	void Start();

	//Получение первого в очереди сообщения
	Message GetMessag();

	//Если есть сообщение - то его получение
	//Иначе - ожидание прибытия сообщения
	//(Синхронный метод)
	Message WaitMessage();

	//Перегрузка оператора для нового потока
	void operator()();

protected:

	//Прегрузка метода разбора сообщений
	int ParseMessage(Message message) override;

	//Перегрузка метода преобразования текста в объект сообщения, так как теперь оно может быть зашифровано
	Message ParseBufferText(char* buffer, int sizeMessage) override;

	//Добавление сообщения в очередь
	void AddMessage(Message message);

	//Запуск указанного серверва для прослушивания в отдельный поток
	static void StartNewListenThread(ListenServer *_server);

	//Вектор со всеми сообщениями
	std::queue<Message>* _queueMessage = NULL;

	//Мьютекс объект для синхронизации операций
	std::mutex * _mutex  = NULL;

	//Класс для кодирования и декодировния сообщений
	BlowfishCoder *  _coder = NULL;

	//Флаг, указывающий, будут ли ВСЕ приходящие сообщения закодироваными, или нет
	bool _encoderMessage = false;
};

