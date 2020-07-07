#include "pch.h"
#include "SendServer.h"

SendServer::SendServer(std::string addressIPV4, std::string port, bool encode) : SendSocket(addressIPV4, port)
{
	_encode = encode;
	_hasErrorLastMess = new std::string();
}

void SendServer::SetCoder(BlowfishCoder* coder)
{
	//Замена кодера на новый
	_coder = coder;
}

bool SendServer::HasCoder()
{
	return _encode;
}

std::string SendServer::GetAddress()
{
	return this->_address;
}

std::string SendServer::GetPort()
{
	return _port;
}

void SendServer::operator()(Message message, std::string address, std::string port)
{
	try {
		SendMess(message, address, port);
	}
	catch (...) {
		TrueError();
		return;
	}
	FalseError();
}

bool SendServer::ErrorMessageSend()
{
	if (*_hasErrorLastMess == "t") return true;
	return false;
}

void SendServer::TrueError()
{
	//указать, что была ошибка
	_hasErrorLastMess->operator=( "t");
}

void SendServer::FalseError()
{
	_hasErrorLastMess->operator=("f");
}

char* SendServer::PrepateToSend(const char* message, int size, int& newSize)
{
	//Если надо кодировать
	if (_encode) {
		char* encodeMessage = _coder->Coding(message, size, newSize);
		return encodeMessage;
	} else {
		newSize = size;
		char* newMess = new char[size]();
		memcpy(newMess, message, size);
		return newMess;
	}
}
