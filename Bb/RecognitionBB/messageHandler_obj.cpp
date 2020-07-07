#include "messageHandler_obj.h"

messageHandler_obj::messageHandler_obj(std::string address, std::string port)
{
	_address = address;
	_port = port;
	_messPipe = new simple_pipe<Message>();
}

void messageHandler_obj::SetListRecepient(std::vector<std::string> filePath)
{
	_filePath = filePath;
}

void messageHandler_obj::AddRecepient(std::vector<Recipient> listRecipient)
{
	_listRecepient = listRecipient;
}

simple_pipe<Message>* messageHandler_obj::GetMyPipe()
{
	return _messPipe;
}

void messageHandler_obj::ThreadMethod()
{
	//Создать сервер уведомлений
	CreateNotServ();
	while (true) {
		//Разбор сообщений управления
		int res = ParseMessageRetInt();
		//Если вернулся код -1, то конец работы потока
		if (res == -1) {
			break;
		}

		//Разбор сообщений для отправки
		ParseMessage();
	}
	//Конец работы потока
	EndWork();
}

int messageHandler_obj::ParseMessageRetInt()
{
	if (pipe->GetCountMess() > 0) {
		if (pipe->GetMessag() == ControlMessage::endWork) {
			return -1;
		}
	}
	return 0;
}

void messageHandler_obj::EndWork()
{
	//Указать, что поток закончил работу
	pipe->SetThreadIsEnd();
}

void messageHandler_obj::ParseMessage()
{
	if (_messPipe->GetCountMess() > 0) {
		//Если время истекло отправить сообщение
		_server->SendChekMess(_messPipe->GetMessag());
	}
}

void messageHandler_obj::ParseControlMess()
{
}

void messageHandler_obj::CreateNotServ()
{
	SendServer* ss = new SendServer(_address, _port);
	_server = new notificationServer(ss);
	//Добавление всех слушателей
	for (auto iter = _listRecepient.begin(); iter != _listRecepient.end(); iter++) {
		_server->AddNewRecipient(*iter);
	}
	for (auto iter = _filePath.begin(); iter != _filePath.end(); iter++) {
		_server->AddNewRecipient(*iter);
	}

}
