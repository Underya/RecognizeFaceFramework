#include "pch.h"
#include "Message.h"
using namespace std;
using namespace rapidjson;

Message::Message()
{
}

Message::Message(const char* buff, int size)
{
	Parse(buff, size);
}

void Message::Parse(const char* buff, int size)
{
	//������ ��� ��������
	Document jsonMessage;

	//������� � ������
	char* str = new char[4096];
	memcpy(str, buff, size);
	str[size] = 0;

	//������� �������
	bool HasError = jsonMessage.ParseInsitu(str).HasParseError();
	if (HasError) {
		throw exception("Exception! Not parse mess");
	}

	const char* receiver = NULL;

	//��������� ������
	//id
	SetIdEmployee(jsonMessage["id"].GetInt());
	//���
	receiver = jsonMessage["name"].GetString();
	SetFirstName(receiver);
	//�������
	receiver = jsonMessage["family"].GetString();
	SetLastName(receiver);
	//��������
	receiver = jsonMessage["l_name"].GetString();
	SetMidName(receiver);

	//���� ���� ����
	if (jsonMessage.HasMember("time")) {
		_m_time = jsonMessage["time"].GetString();
		_m_data = jsonMessage["data"].GetString();
	}
	
	//���� ���� ������
	if (jsonMessage.HasMember("groups")) {
		Value arr(kArrayType);
		arr = jsonMessage["groups"].GetArray();
		for (auto iter = arr.Begin(); iter != arr.End(); iter++) {
			int id = (*iter)["id"].GetInt();
			receiver = (*iter)["name"].GetString();
			AddGroup(id, receiver);
		}
	}

	//���� ���� �������
	if (jsonMessage.HasMember("rules")) {
		Value arr(kArrayType);
		arr = jsonMessage["rules"].GetArray();
		for (auto iter = arr.Begin(); iter != arr.End(); iter++) {
			int id = (*iter)["id"].GetInt();
			receiver = (*iter)["name"].GetString();
			AddRule(id, receiver);
		}
	}

	//���� ���� ���������
	if (jsonMessage.HasMember("premise")) {
		Value arr(kArrayType);
		arr = jsonMessage["premise"].GetArray();
		for (auto iter = arr.Begin(); iter != arr.End(); iter++) {
			receiver = iter->GetString();

			_listPremise.push_back(receiver);
		}
	}

	//���� ���� �������������� ����������
	if (jsonMessage.HasMember("info")) {
		receiver = jsonMessage["info"].GetString();
		AddInfo(receiver);
	}

	//�������� ������� �� ��� ������
	delete[]str;
}

void Message::SetIdEmployee(int id)
{
	_m_id = id;
}

void Message::SetFirstName(std::string firstName)
{
	_m_name = firstName;
}

void Message::SetLastName(std::string family)
{
	_m_family = family;
}

void Message::SetMidName(std::string lastName)
{
	_l_name = lastName;
}

void Message::SetTime(time_t t)
{
	tm time;
	localtime_s(&time, &t);
	//��������� ������������ ����
	string data = "";
	data += to_string(time.tm_year + 1900) + "-";
	data += to_string(time.tm_mon + 1) + "-";
	data += to_string(time.tm_mday);
	//���������� ����������
	_m_data = data;
	//��������� ������������ �������
	string times = "";
	times += to_string(time.tm_hour) + ".";
	times += to_string(time.tm_min) + ".";
	times += to_string(time.tm_sec);
	//���������� ����������
	_m_time = times;
}

void Message::SetCurrentTime()
{
	SetTime(time(NULL));
}

void Message::AddGroup(int idGroup, std::string NameGroup)
{
	_m_groups.push_back({idGroup, NameGroup});
}

void Message::AddRule(int idRule, std::string NameRule)
{
	_m_rules.push_back({idRule, NameRule});
}

void Message::AddInfo(std::string info)
{
	_m_info_for_file = info;
}

void Message::AddPremiseList(std::vector<std::string> listPremise)
{
	_listPremise = listPremise;
}

const char* Message::GetMessageToSend()
{
	//������ ��� ���������
	char* mess = new char[4096]();
	const char* mess2;

	//���������� ��������
	//���� ����� �� ���� �� �������� - �� ��� �� ����������� � ���������

	//�������� ���������
	Document jsonMess;
	//� ��������, ��� ��� ������, ��� �� ��������� � ���� ��������
	jsonMess.SetObject();
	//������ ��� ��������� ������
	Document::AllocatorType& alloc = jsonMess.GetAllocator();

	//��
	jsonMess.AddMember("id", GetId(), alloc);
	//���
	jsonMess.AddMember("name", GetFirstName(), jsonMess.GetAllocator());
	//�������
	jsonMess.AddMember("family", GetLastName(), alloc);
	//��������
	jsonMess.AddMember("l_name", GetMidName(), alloc);
	
	//���� ��� ����
	if (_m_time != "") {
		jsonMess.AddMember("time", _m_time, alloc);
		jsonMess.AddMember("data", _m_data, alloc);
	}

	//���� ���� ������
	if (GetGroupList().size() != 0) {
		std::vector<std::pair<int, std::string>> list = GetGroupList();
		Value value(kArrayType);
		for (int i = 0, max = list.size(); i < max; i++) {
			Value pairval;
			pairval.SetObject();
			pairval.AddMember("id", list[i].first, alloc);
			pairval.AddMember("name", list[i].second, alloc);
			value.PushBack(pairval, alloc);
		}
		jsonMess.AddMember("groups", value, alloc);
	}
	//���� ���� �������
	if (GetRulesList().size() != 0) {
		std::vector<std::pair<int, std::string>> list = GetRulesList();
		Value value(kArrayType);
		for (int i = 0, max = list.size(); i < max; i++) {
			Value pairval;
			pairval.SetObject();
			pairval.AddMember("id", list[i].first, alloc);
			pairval.AddMember("name", list[i].second, alloc);
			value.PushBack(pairval, alloc);
		}
		jsonMess.AddMember("rules", value, alloc);
	}

	//���� ���� ���������
	if (GetListPremise().size() != 0) {
		std::vector<std::string> list = GetListPremise();
		Value value(kArrayType);
		for (int i = 0, max = list.size(); i < max; i++) {
			Value obj;
			obj.SetObject();
			obj.SetString(list[i], alloc);
			
			value.PushBack(obj, alloc);
		}
		jsonMess.AddMember("premise", value, alloc);
	}

	//���� ���� ��� ����������
	if (_m_info_for_file != "") {
		jsonMess.AddMember("info", GetInfo(), alloc);
	}

	//������� � ������ ������
	StringBuffer buff2;
	PrettyWriter<StringBuffer> wtiter(buff2);
	jsonMess.Accept(wtiter);
	mess2 = buff2.GetString();
	_size_mess = buff2.GetSize();
	//mess - ����� ������������ ������� ���������
	memcpy(mess, mess2, _size_mess);
	return mess;
}

int Message::GetId()
{
	return _m_id;
}

std::string Message::GetFirstName()
{
	return _m_name;
}

std::string Message::GetLastName()
{
	return _m_family;
}

std::string Message::GetMidName()
{
	return _l_name;
}

tm Message::GetTime()
{
	//�������� ������� �������
	tm time;

	//���������������� �������� 0
	memset(&time, 0, sizeof(time));

	//������ ������
	string buff = "";

	//���� ���� ���������� � ����
	if (_m_data != "") {
		int i = 0;
		int size = _m_data.size();

		//��������� ����
		for (; _m_data[i] != '-'; i++) buff += _m_data[i];
		//��������� ����
		time.tm_year = atoi(buff.c_str()) - 1900;
		//��������� ������
		buff = "";
		for (i++; _m_data[i] != '-'; i++) buff += _m_data[i];
		//��������� ������
		time.tm_mon = atoi(buff.c_str()) - 1;
		//��������� ���
		buff = "";
		for (i++; i < size; i++) buff += _m_data[i];
		//��������� ���
		time.tm_mday = atoi(buff.c_str());
		buff = "";
	}

	//���� ���� ���������� � �������
	if (_m_time != "") {
		int i = 0;
		int size = _m_time.size();

		//��������� �����
		for (; _m_time[i] != '.'; i++)  buff += _m_time[i];
		//��������� �����
		time.tm_hour = atoi(buff.c_str());
		buff = "";
		//��������� �����
		for (i++; _m_time[i] != '.'; i++)  buff += _m_time[i];
		//��������� �����
		time.tm_min = atoi(buff.c_str());
		buff = "";
		//��������� ������
		for (i++; i < size; i++)  buff += _m_time[i];
		//��������� ������
		time.tm_sec = atoi(buff.c_str());
		buff = "";
	}

	return time;
}

std::vector<std::pair<int, std::string>> Message::GetGroupList()
{
	return _m_groups;
}

std::vector<std::pair<int, std::string>> Message::GetRulesList()
{
	return _m_rules;
}

std::string Message::GetInfo()
{
	return _m_info_for_file;
}

std::vector<std::string> Message::GetListPremise()
{
	return _listPremise;
}

int Message::GetSizeMessageToSend()
{
	//���� �� ���� ��������� ����� ���������
	//�� ��� �����������
	if (_size_mess == 0) {
		const char* s = GetMessageToSend();
		delete s;
	}
	return _size_mess;
}

void Message::SetInBuffer(std::string in, char* out, int& index)
{
	//��������� ������� ������
	int strSize = in.size();
	//������� � ������� �� ����������� �������
	for (int i = 0; i < strSize; i++) {
		out[index++] = in[i];
	}

}
