#include "pch.h"
#include "SendSocket.h"

std::vector<std::string> SendSocket::_list_address;

//������ ���� �������, �� ������� ��������� ��������
std::vector<int> SendSocket::_list_sock;

SendSocket::SendSocket(std::string address, std::string port) : BasedSocket(address, port)
{
}

SendSocket::~SendSocket()
{

}

void SendSocket::SendMess(Message message, std::string address, std::string port)
{
	//int sock = -1;
	////����� ������ � ���� ����� ���� ���������
	//SearchAddress(address, port);

	////���� �� ��� ������ �����
	//if (_postionInList == -1) {
	//	//�������� � ������
	//	AddAdress(address, port);
	//	//�������� ��� �����
	//	AddNewSock(address, port);
	//	//���������� �����������
	//	TryConnect();
	//}
	//

	////������� ��������� ���������
	//if (!TrySendMess(message)) {
	//	std::cout << "error";
	//}

	//return;
	//��������� ������ �������
	addrinfo* clientAddress = GetClientAddress(address, port);
	//��������� ������ ������� ��� �������� ���������
	int clientSock = socket(clientAddress->ai_family, clientAddress->ai_socktype, clientAddress->ai_protocol);
	
	//��������, ������� �������� �����
	if (clientSock == SOCKET_ERROR) {
		throw std::exception("Exception! Not Success get client socket!");
	}

	//������� �����������
	int connect_result =  connect(clientSock, clientAddress->ai_addr, clientAddress->ai_addrlen);
	
	//���� �� ������� ������� ����������
	if (connect_result != 0) {
		int error_code = WSAGetLastError();
		std::string error_str = "" + std::to_string(error_code);
		//std::cout << error_str << "\n";
		throw std::exception("Exception! Not success connect to client socket!");
	}

	//�������� ���������
	const char* buff = message.GetMessageToSend();
	int size = message.GetSizeMessageToSend();
	int newSize = 0;
	const char* sendBuff = PrepateToSend(buff, size, newSize);
	int send_size_mess = send(clientSock, sendBuff, newSize, 0);

	//�������� ��������� ��� �������� ����������
	send(clientSock, "", 0, 0);

	//�������� ������ �� ��� ������� ���������
	delete[newSize]sendBuff;
	delete[size]buff;

	//�������� ���������� �� ������
	freeaddrinfo(clientAddress);
	//�������� ���������� � ��������
	closesocket(clientSock);
	shutdown(clientSock, 0);
}


char* SendSocket::PrepateToSend(const char* message, int size, int& newSize)
{
	newSize = size;
	char* newMess = new char[size]();
	memcpy(newMess, message, size);
	return newMess;
}

addrinfo* SendSocket::GetClientAddress(std::string address, std::string port)
{
	//�������� ��������� ��������������� ����������
	struct addrinfo clientif;
	ZeroMemory(&clientif, sizeof(clientif));

	clientif.ai_family = AF_INET;
	clientif.ai_socktype = SOCK_STREAM;
	clientif.ai_protocol = IPPROTO_TCP;
	clientif.ai_flags = AI_PASSIVE;

	//��������� ��� ������ ���������
	struct addrinfo* clientAddress = NULL;

	int result = getaddrinfo(address.c_str(), port.c_str() , &clientif, &clientAddress);

	//��������, ������� �� �������� ���������
	if (result != 0) {
		if (WSANOTINITIALISED == result) {

		}
		throw std::exception("Exception! Not get client address info!");
	}

	return clientAddress;
}
