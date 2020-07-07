#include "pch.h"
#include "ListenServer.h"

ListenServer::ListenServer(std::string address, std::string port, bool EncoderMessage) : ListenSocket(address, port)
{
	//Создание необходимых объектов
	_queueMessage = new std::queue<Message>();
	_encoderMessage = EncoderMessage;
	_coder = new BlowfishCoder();
	_mutex = new std::mutex();
}

void ListenServer::SetCoder(BlowfishCoder* NewCoder)
{
	//Если был старый шифратор, его надо удалить
	if (_coder != NULL) delete _coder;
	_coder = NewCoder;
}

bool ListenServer::HasCoder()
{

	return this->_encoderMessage;
}

int ListenServer::CountMess()
{
	int countMess = 0;
	_mutex->lock();
	countMess = _queueMessage->size();
	_mutex->unlock();
	return countMess;
}

void ListenServer::Start()
{
	ListenServer::StartNewListenThread(this);
}

Message ListenServer::GetMessag()
{
	Message m;
	_mutex->lock();
	m = _queueMessage->front();
	_queueMessage->pop();
	_mutex->unlock();
	return m;
}

Message ListenServer::WaitMessage()
{
	//Ожидание сообщение
	while (CountMess() == 0);
	//Получение сообщения
	return GetMessag();
}

void ListenServer::operator()()
{
	Listen();
}

int ListenServer::ParseMessage(Message message)
{
	AddMessage(message);
	return 0;
}

Message ListenServer::ParseBufferText(char* buffer, int sizeMessage)
{
	//Если мы получаем только шифрованные сообщения
	if (_encoderMessage) {
		int newSize = 0;
		char* uncodingText = NULL;
		//То сначала данный надо расшифровать текст
		uncodingText = _coder->UnCodind(buffer, sizeMessage, newSize);
		//Создать по нему сообщение
		Message mess(uncodingText, newSize);
		//Удалить временный буффер
		delete[newSize] uncodingText;
		//Вернуть сообщение
		return mess;
	} 

	//Если мы получаем только открытые сообщения
	//То возвращаем так
	return Message(buffer, sizeMessage);
}

void ListenServer::AddMessage(Message message)
{
	_mutex->lock();
	_queueMessage->push(message);
	_mutex->unlock();
}

void ListenServer::StartNewListenThread(ListenServer* _server)
{
	std::thread t(*_server);
	t.detach();
}
