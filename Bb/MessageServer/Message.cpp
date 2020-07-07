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
	//Объект для хранения
	Document jsonMessage;

	//Перевод в строку
	char* str = new char[4096];
	memcpy(str, buff, size);
	str[size] = 0;

	//Попытка разбора
	bool HasError = jsonMessage.ParseInsitu(str).HasParseError();
	if (HasError) {
		throw exception("Exception! Not parse mess");
	}

	const char* receiver = NULL;

	//Получения данных
	//id
	SetIdEmployee(jsonMessage["id"].GetInt());
	//Имя
	receiver = jsonMessage["name"].GetString();
	SetFirstName(receiver);
	//Фамилия
	receiver = jsonMessage["family"].GetString();
	SetLastName(receiver);
	//Отчество
	receiver = jsonMessage["l_name"].GetString();
	SetMidName(receiver);

	//Если есть дата
	if (jsonMessage.HasMember("time")) {
		_m_time = jsonMessage["time"].GetString();
		_m_data = jsonMessage["data"].GetString();
	}
	
	//Если есть группы
	if (jsonMessage.HasMember("groups")) {
		Value arr(kArrayType);
		arr = jsonMessage["groups"].GetArray();
		for (auto iter = arr.Begin(); iter != arr.End(); iter++) {
			int id = (*iter)["id"].GetInt();
			receiver = (*iter)["name"].GetString();
			AddGroup(id, receiver);
		}
	}

	//Если есть правила
	if (jsonMessage.HasMember("rules")) {
		Value arr(kArrayType);
		arr = jsonMessage["rules"].GetArray();
		for (auto iter = arr.Begin(); iter != arr.End(); iter++) {
			int id = (*iter)["id"].GetInt();
			receiver = (*iter)["name"].GetString();
			AddRule(id, receiver);
		}
	}

	//Если есть помещения
	if (jsonMessage.HasMember("premise")) {
		Value arr(kArrayType);
		arr = jsonMessage["premise"].GetArray();
		for (auto iter = arr.Begin(); iter != arr.End(); iter++) {
			receiver = iter->GetString();

			_listPremise.push_back(receiver);
		}
	}

	//Если есть дополнительная информация
	if (jsonMessage.HasMember("info")) {
		receiver = jsonMessage["info"].GetString();
		AddInfo(receiver);
	}

	//Удаление буффера из под строки
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
	//Получение составляющей даты
	string data = "";
	data += to_string(time.tm_year + 1900) + "-";
	data += to_string(time.tm_mon + 1) + "-";
	data += to_string(time.tm_mday);
	//Сохарнение информации
	_m_data = data;
	//Получение составщяющей времени
	string times = "";
	times += to_string(time.tm_hour) + ".";
	times += to_string(time.tm_min) + ".";
	times += to_string(time.tm_sec);
	//Сохранение результата
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
	//Буффер для сообщения
	char* mess = new char[4096]();
	const char* mess2;

	//Заполнение значений
	//Если какой то поле не запонено - то оно не добавляется в сообщение

	//Создание документа
	Document jsonMess;
	//И указание, что это объект, что бы добавлять в него значения
	jsonMess.SetObject();
	//Объект для выделения памяти
	Document::AllocatorType& alloc = jsonMess.GetAllocator();

	//Ид
	jsonMess.AddMember("id", GetId(), alloc);
	//Имя
	jsonMess.AddMember("name", GetFirstName(), jsonMess.GetAllocator());
	//Фамилия
	jsonMess.AddMember("family", GetLastName(), alloc);
	//Отчество
	jsonMess.AddMember("l_name", GetMidName(), alloc);
	
	//Если они есть
	if (_m_time != "") {
		jsonMess.AddMember("time", _m_time, alloc);
		jsonMess.AddMember("data", _m_data, alloc);
	}

	//Если есть группы
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
	//Если есть правила
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

	//Если есть помещения
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

	//Если есть доп информация
	if (_m_info_for_file != "") {
		jsonMess.AddMember("info", GetInfo(), alloc);
	}

	//Перевод в формат строки
	StringBuffer buff2;
	PrettyWriter<StringBuffer> wtiter(buff2);
	jsonMess.Accept(wtiter);
	mess2 = buff2.GetString();
	_size_mess = buff2.GetSize();
	//mess - имеет ограниченную область видимости
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
	//Создание объекта времени
	tm time;

	//Инициализировать значение 0
	memset(&time, 0, sizeof(time));

	//Разбор строки
	string buff = "";

	//Если есть информация о дате
	if (_m_data != "") {
		int i = 0;
		int size = _m_data.size();

		//Получение года
		for (; _m_data[i] != '-'; i++) buff += _m_data[i];
		//Установка года
		time.tm_year = atoi(buff.c_str()) - 1900;
		//Получение месяца
		buff = "";
		for (i++; _m_data[i] != '-'; i++) buff += _m_data[i];
		//Установка месяца
		time.tm_mon = atoi(buff.c_str()) - 1;
		//Получение дня
		buff = "";
		for (i++; i < size; i++) buff += _m_data[i];
		//Установка дня
		time.tm_mday = atoi(buff.c_str());
		buff = "";
	}

	//Если есть информация о времени
	if (_m_time != "") {
		int i = 0;
		int size = _m_time.size();

		//Получение часов
		for (; _m_time[i] != '.'; i++)  buff += _m_time[i];
		//Установка часов
		time.tm_hour = atoi(buff.c_str());
		buff = "";
		//Получение минут
		for (i++; _m_time[i] != '.'; i++)  buff += _m_time[i];
		//Установка минут
		time.tm_min = atoi(buff.c_str());
		buff = "";
		//Получение секунд
		for (i++; i < size; i++)  buff += _m_time[i];
		//Установка секунд
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
	//Если не было вычислена длина сообщения
	//То она вычисляется
	if (_size_mess == 0) {
		const char* s = GetMessageToSend();
		delete s;
	}
	return _size_mess;
}

void Message::SetInBuffer(std::string in, char* out, int& index)
{
	//Получение размера строки
	int strSize = in.size();
	//Переход к первому не заполенному символу
	for (int i = 0; i < strSize; i++) {
		out[index++] = in[i];
	}

}
