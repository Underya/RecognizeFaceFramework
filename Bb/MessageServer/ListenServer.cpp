#include "pch.h"
#include "ListenServer.h"

ListenServer::ListenServer(std::string address, std::string port, bool EncoderMessage) : ListenSocket(address, port)
{
	//�������� ����������� ��������
	_queueMessage = new std::queue<Message>();
	_encoderMessage = EncoderMessage;
	_coder = new BlowfishCoder();
	_mutex = new std::mutex();
}

void ListenServer::SetCoder(BlowfishCoder* NewCoder)
{
	//���� ��� ������ ��������, ��� ���� �������
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
	//�������� ���������
	while (CountMess() == 0);
	//��������� ���������
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
	//���� �� �������� ������ ����������� ���������
	if (_encoderMessage) {
		int newSize = 0;
		char* uncodingText = NULL;
		//�� ������� ������ ���� ������������ �����
		uncodingText = _coder->UnCodind(buffer, sizeMessage, newSize);
		//������� �� ���� ���������
		Message mess(uncodingText, newSize);
		//������� ��������� ������
		delete[newSize] uncodingText;
		//������� ���������
		return mess;
	} 

	//���� �� �������� ������ �������� ���������
	//�� ���������� ���
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
