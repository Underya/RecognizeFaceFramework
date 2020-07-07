#include "pch.h"

#include <fstream>
#include "notificationServer.h"

notificationServer::notificationServer(SendServer * server)
{
	_server = server;
}

notificationServer::notificationServer()
{
}

void notificationServer::SetSendServer(SendServer * server)
{
	//���� ���, �� ������� ������ ������
	if (_server != NULL) delete _server;
	_server = server;
	//���������� ����� ������ ���� ��������
	SetAllServer();
}

void notificationServer::AddNewRecipient(Recipient recepient)
{
	_list_recip.push_back(recepient);
}

void notificationServer::AddNewRecipient(std::string fileFullPath)
{
	//�������� ����� ��� ������
	rapidjson::Document doc;
	std::string text = GetTextForFile(fileFullPath);
	//������� ��������
	if (doc.ParseInsitu((char*)text.c_str()).HasParseError()) {
		//���� ��������� ������
		//�� ��������� ����������
		throw std::exception("Exception! Not parse JSON-document");
	}
	//�������� ������ ������� ��� ��������� ���������
	std::string buffer = "";
	//��������� ������
	buffer = doc["address"].GetString();
	//�������� ������� �� ���������� ������
	Recipient recipent(buffer);
	//��������� ��� ����, ���� ����� ����
	if (doc.HasMember("infa")) {
		recipent.SetAddInfo(doc["infa"].GetString());
	}
	//������ ���������� �� ������� � ��������
	rapidjson::Value arr, elem;
	//��������� �������
	arr = doc["pair"];
	//���� �� ���� ���������
	for (auto iter = arr.Begin(); iter != arr.End(); iter++) {
		//�������� ����� ����
		grPair newPair;
		//���������� � ���� ���� �����
		elem = (*iter)["groups"];
		for (auto group = elem.Begin(); group != elem.End(); group++) newPair.AddGroup(group->GetInt());
		//���������� � ���� ���� ������
		elem = (*iter)["rules"];
		for (auto rule = elem.Begin(); rule != elem.End(); rule++) newPair.AddRule(rule->GetInt());
		//���������� ������ � ������ ����� ����������
		recipent.AddPair(newPair);
	}
	//����� ��������� ���� ����������, ���������� � ���������� �������
	if (_server != NULL)
		recipent.SetSendServer(_server);
	//���������� � ������ �����������
	AddNewRecipient(recipent);
}

void notificationServer::SendChekMess(Message mess)
{
	//�������� ������ ID
	std::vector<int> idgroup;
	std::vector<std::pair<int, std::string>> list;
	list = mess.GetGroupList();
	for (auto iter = list.begin(); iter != list.end(); iter++)
		idgroup.push_back(iter->first);
	std::vector<int> idrule;
	list = mess.GetRulesList();
	for (auto iter = list.begin(); iter != list.end(); iter++)
		idrule.push_back(iter->first);
	//����� ������� �����������
	SendChekMess(mess, idrule, idgroup);
}

void notificationServer::SendChekMess(Message mess, std::vector<int> id_rule, std::vector<int> id_group)
{
	//���� �� ���� �����������
	for (auto iter = _list_recip.begin(); iter != _list_recip.end(); iter++) {
		//���� ��������, �� �������� �������� ���������
		if (iter->CheckList(id_rule, id_group)) {
			//�������� ���������, ����� 
			iter->SendMess(mess);
		}
	}
}

std::vector<Recipient> notificationServer::GetListRecepient()
{
	return this->_list_recip;
}

std::vector<std::string> notificationServer::GetAddressErrorMessage()
{
	std::vector<std::string> vec;

	for (auto iter = _list_recip.begin(); iter != _list_recip.end(); iter++) {
		if (iter->HasErrorMessage()) {
			vec.push_back(iter->GetAddress());
		}
	}

	return vec;
}


std::string notificationServer::GetTextForFile(std::string fileFullPath)
{
	//�������� �����, � ������ �� ���� ����� ������
	std::string text = "", buff = "";
	//�������� �����
	std::fstream file(fileFullPath);
	//������ ���������)))
	while (std::getline(file, buff)) text += buff;
	//����������� �������
	return text;
}

void notificationServer::SetAllServer()
{
	//��� ������� ������ �������������� ������
	for (auto iter = _list_recip.begin(); iter != _list_recip.end(); iter++)
		iter->SetSendServer(_server);
}
