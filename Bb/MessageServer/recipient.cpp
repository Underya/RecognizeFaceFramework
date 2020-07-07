#include "pch.h"
#include "recipient.h"

Recipient::Recipient(std::string IPV4_PORT)
{
	//���������� �����������
	int midlIndex = 0;
	midlIndex = IPV4_PORT.find(':', 0);
	//��������� � ��������� ������
	std::string address = IPV4_PORT.substr(0, midlIndex);
	SetAddress(address);
	//��������� � ��������� �����
	std::string port = IPV4_PORT.substr(midlIndex + 1, IPV4_PORT.size() - midlIndex);
	SetPortRecepient(port);
}

Recipient::Recipient(std::string IPV4, std::string port)
{
	SetAddress(IPV4);
	SetPortRecepient(port);
}

Recipient::Recipient()
{
}

void Recipient::SetAddress(std::string address)
{
	_address = address;
}

void Recipient::SetPortRecepient(std::string port)
{
	_port = port;
}

void Recipient::SetAddInfo(std::string addInfo)
{
	_add_info = addInfo;
}

std::string Recipient::GetAddInfo()
{
	return _add_info;
}

std::string Recipient::GetAddress()
{
	if (_address == "") throw std::exception("Exception! Not set Address recipient");
	return _address;
}

std::string Recipient::GetPort()
{
	if (_port == "") throw std::exception("Exception! Not set Port recipient");
	return _port;
}

bool Recipient::CheckList(std::vector<int> rule, std::vector<int> group)
{

	//��������� ��� ���� ���
	for (auto iter = _pairList.begin(); iter != _pairList.end(); iter++) {
		//���� ���� �� ���� ���� ��������
		if (ChekPair(*iter, rule, group)) {
			return true;
		}
	}

	return false;
}

void Recipient::SetSendServer(SendServer* server)
{
	_sendMess = server;
}

void Recipient::SendMess(Message message)
{
	//���� ��� �������
	if (_sendMess == NULL)
		//�������� ����������
		throw std::exception("Exception! SendsServer is NULL!");
	//���������� � ��������� ��� ����������
	message.AddInfo(_add_info);
	//����������� ���������
	
	_sendMess->operator()(message, _address, _port);
	//std::thread t(*_sendMess, message, _address, _port);
	//t.detach();
}

void Recipient::AddPair(grPair pair)
{
	//���������� ����� ����
	_pairList.push_back(pair);
}

void Recipient::AddPair(std::vector<int> group, std::vector<int> rule)
{
	//�������� ����� ����, � � ��� ����������� ��������
	grPair newPair;
	for (auto iter = group.begin(); iter != group.end(); iter++) newPair.AddGroup(*iter);
	for (auto iter = rule.begin(); iter != rule.end(); iter++) newPair.AddRule(*iter);
	//���������� ���� � ���������
	AddPair(newPair);
}

bool Recipient::HasErrorMessage()
{
	if (_sendMess->ErrorMessageSend()) return true;
	return false;
}

bool Recipient::ChekPair(grPair pair, std::vector<int> id_rule_list, std::vector<int> id_group_list)
{
	//��������, �������� �� �������
	bool HasRule = false;
	//��������, �������� �� ������
	bool HasGroup = false;

	//�������� ������
	if (pair.AnyRule()) {
		HasRule = true;
	}
	else {
		//���� ���� � ���� ������ � ������ �������
		for (auto iter = id_rule_list.begin(); iter != id_rule_list.end(); iter++) {
			if (pair.HasRule(*iter)) {
				HasRule = true;
				break;
			}
		}
	}

	//���� �� ������� �� �������, ��� ������ ��������� �����
	if (!HasRule) return false;

	if (pair.AnyGroup()) {
		HasGroup = true;
	}
	else {
		//�������� �����
		for (auto iter = id_group_list.begin(); iter != id_group_list.end(); iter++) {
			if (pair.HasGroup(*iter)) {
				HasGroup = true;
				break;
			}
		}

	}
	//���� ��� ������� ��������
	if (HasRule && HasGroup) {
		//�� ��������, ��� ���� ��������
		return true;
	}

	return false;
}
