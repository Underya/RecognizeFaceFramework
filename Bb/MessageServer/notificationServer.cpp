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
	//Если был, то удалить старый севрер
	if (_server != NULL) delete _server;
	_server = server;
	//Установить новый сервер всем объектам
	SetAllServer();
}

void notificationServer::AddNewRecipient(Recipient recepient)
{
	_list_recip.push_back(recepient);
}

void notificationServer::AddNewRecipient(std::string fileFullPath)
{
	//Открытие файла для чтения
	rapidjson::Document doc;
	std::string text = GetTextForFile(fileFullPath);
	//Попытка открытия
	if (doc.ParseInsitu((char*)text.c_str()).HasParseError()) {
		//Если произошла ошибка
		//То выкинуить исключение
		throw std::exception("Exception! Not parse JSON-document");
	}
	//Создание нового объекта для получения сообщения
	std::string buffer = "";
	//Получение адреса
	buffer = doc["address"].GetString();
	//Создание объекта по указанному адресу
	Recipient recipent(buffer);
	//Получение доп инфы, если такая есть
	if (doc.HasMember("infa")) {
		recipent.SetAddInfo(doc["infa"].GetString());
	}
	//Разбор информации об группах и правилах
	rapidjson::Value arr, elem;
	//Получение массива
	arr = doc["pair"];
	//Цикл по всем элементам
	for (auto iter = arr.Begin(); iter != arr.End(); iter++) {
		//Создание новой пары
		grPair newPair;
		//Добавление в пару всех групп
		elem = (*iter)["groups"];
		for (auto group = elem.Begin(); group != elem.End(); group++) newPair.AddGroup(group->GetInt());
		//Добавление в пару всех правил
		elem = (*iter)["rules"];
		for (auto rule = elem.Begin(); rule != elem.End(); rule++) newPair.AddRule(rule->GetInt());
		//Добавление группы в список групп получателя
		recipent.AddPair(newPair);
	}
	//После получения всей информации, добавление к получателю сервера
	if (_server != NULL)
		recipent.SetSendServer(_server);
	//Добавление в список получателей
	AddNewRecipient(recipent);
}

void notificationServer::SendChekMess(Message mess)
{
	//Создание списка ID
	std::vector<int> idgroup;
	std::vector<std::pair<int, std::string>> list;
	list = mess.GetGroupList();
	for (auto iter = list.begin(); iter != list.end(); iter++)
		idgroup.push_back(iter->first);
	std::vector<int> idrule;
	list = mess.GetRulesList();
	for (auto iter = list.begin(); iter != list.end(); iter++)
		idrule.push_back(iter->first);
	//Вызов функции отправления
	SendChekMess(mess, idrule, idgroup);
}

void notificationServer::SendChekMess(Message mess, std::vector<int> id_rule, std::vector<int> id_group)
{
	//Цикл по всем получателям
	for (auto iter = _list_recip.begin(); iter != _list_recip.end(); iter++) {
		//Если подходит, то проходит отправка сообщения
		if (iter->CheckList(id_rule, id_group)) {
			//Отправка сообщения, через 
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
	//Открытие файла, и чтение из него всего текста
	std::string text = "", buff = "";
	//Открытие файла
	std::fstream file(fileFullPath);
	//Чтение построчно)))
	while (std::getline(file, buff)) text += buff;
	//Вовзращание объекта
	return text;
}

void notificationServer::SetAllServer()
{
	//Для каждого объект устанвливается сервер
	for (auto iter = _list_recip.begin(); iter != _list_recip.end(); iter++)
		iter->SetSendServer(_server);
}
