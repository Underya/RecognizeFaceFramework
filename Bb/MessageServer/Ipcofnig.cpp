#include "pch.h"
#include "Ipcofnig.h"

using namespace std;

Ipcofnig::Ipcofnig()
{
}

Ipcofnig::~Ipcofnig()
{
}

std::string Ipcofnig::GetIpV4()
{
	//����� �������, ������� ����� ���������� IP
	return GetIp(4);
}

std::string Ipcofnig::GetIpV6()
{
	return GetIp(6);
}

std::string Ipcofnig::GetIp(int ver)
{
	//������, � ������� ����� ������� �����
	string result = "";
	//��� IP
	vector<pair<string, int>> vec = GetMyIp();
	//����� ������ ���������� ������
	for (auto iter = vec.begin(); iter != vec.end(); iter++) {
		//���� ������ ��������
		if (iter->second == ver)
			//�� ������������ �����
			return iter->first;
	}

	return result;
}

std::vector < std::pair<std::string, int>> Ipcofnig::GetMyIp()
{
	//��������� ����� ����� ����������
	char cbuff[200];
	if (gethostname(cbuff, sizeof(cbuff)) == SOCKET_ERROR) {
		throw std::exception("Exception! Not get host name!");
	}
	//�������� ������ �������
	addrinfo inf;
	//��������� ������
	addrinfo* res;
	//������� �� ��������� �������� � ������
	addrinfo* next = NULL;

	//�������� ������
	memset(&inf, 0, sizeof(inf));
	//��������, ��� ��� ��������� ������ V4 ������
	inf.ai_protocol = IPPROTO_IPV4;

	//��������� ������ �������
	int erro_code = getaddrinfo(cbuff, NULL, &inf, &res);

	//������ ������, ������� ����� ����������
	if (erro_code != 0) {
		std::string error_text;
		error_text = "Exception! Not receive address! Error code:" + std::to_string(erro_code);
		throw std::exception(error_text.c_str());
	}

	//���������� ��� �������� ���� �����������
	vector<pair<string, int>> vec;

	//������ ��� ��������� ������������� �����������
	std::string buffer;

	//�������� ����� ������
	next = res;

	while (next != NULL) {
		//��������� ��������� ������ ��� �������� ��������
		sockaddr_in* adr = (sockaddr_in*)next->ai_addr;
		//��������� ������ � ���� ����������
		inet_ntop(adr->sin_family, &(adr->sin_addr), cbuff, sizeof(cbuff));
		//���������� ������ � ���� ������ ���������
		buffer = cbuff;
		//���� ����� �� ������
		if (!IsEmptyAddr(buffer)) {
			//�� �� ����������� � ������ �������
			vec.push_back({ buffer, GetV(adr) });
		}
		//������� � ���������� �������� � ������
		next = next->ai_next;
	}

	return vec;
}

int Ipcofnig::GetV(sockaddr_in* addr)
{
	if (addr->sin_family == AF_INET) return 4;
	if (addr->sin_family == AF_INET6) return 6;
	return 0;
}

bool Ipcofnig::IsEmptyAddr(std::string addr)
{
	if (addr.size() < 2) return true;
	if (addr[0] == ':' && addr[1] == ':') return true;
	return false;
}
