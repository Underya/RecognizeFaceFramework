#pragma once

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include <iostream>
#include <string>
#include <vector>
#include <time.h>

#ifdef MESSAGESERVER_EXPORTS
#define MESSAGESERVER_API __declspec(dllexport)
#else
#define MESSAGESERVER_API __declspec(dllimport)
#endif

//Сообщение, которое передаётся между объектами
class MESSAGESERVER_API Message
{
public:
	
	//Создать пустое сообщение для наполнения
	Message();

	//Создание сообщения из JSON сообщения
	Message(const char* JSONbuff, int size);

	//Разбор сообщения из JSON 
	void Parse(const char* JSONbuff, int size);

	//Методы Для установки информации

	//Указать ID распознаного человека
	void SetIdEmployee(int id);
	//Указать имя человека
	void SetFirstName(std::string firstName);
	//Указать фамилию человека
	void SetLastName(std::string family);
	//Указать отчество
	void SetMidName(std::string lastName);
	//Указать место и время распознования
	void SetTime(time_t t);
	//Добавить текущее время
	void SetCurrentTime();
	//Добавить группу, к которой относится пользователь
	void AddGroup(int idGroup, std::string NameGroup);
	//Указать правило для пользователя
	void AddRule(int idRule, std::string NameRule);
	//Добавочная информация о пользователе
	void AddInfo(std::string info);
	//Добавление списка с помещениями
	void AddPremiseList(std::vector<std::string> listPremise);

	//Получить сообщение в виде буффера типа для отправки
	const char* GetMessageToSend();

	//Методы для получения информации из сообщения

	//Получить id пользователя
	int GetId();
	//Получить имя пользователя
	std::string GetFirstName();
	//Получить фамилию пользователя
	std::string GetLastName();
	//Получение фамилии
	std::string GetMidName();
	//Получить время распознования
	tm GetTime();
	//Получить список групп
	std::vector<std::pair<int, std::string>> GetGroupList();
	//Получить список правил
	std::vector<std::pair<int, std::string>> GetRulesList();
	//Получение дополнительной информации из сообщения
	std::string GetInfo();
	//Получение списка помещений
	std::vector<std::string> GetListPremise();

	//Получить длину сообщения
	int GetSizeMessageToSend();

protected:

	//Строка типа string добавляется в большую строку типа char *, и  изменяется индекс, укзаывющий на первый не заполенный элемент в строке
	void SetInBuffer(std::string in, char* out, int& index);

	//Размер сообщения в байтах
	int _size_mess = 0;

	//Непосредственно информация о распозновании, которая используется для передачи, или получена из сообщения
	//id человека
	int _m_id = 0;
	//Имя и фамилия и отчество
	std::string _m_name = "";
	std::string _m_family = "";
	std::string _l_name = "";
	//Дата распознования
	std::string _m_data = "";
	//Время распознования
	std::string _m_time = "";
	//Все группы, к которым принадлежит пользователь
	std::vector<std::pair<int, std::string>> _m_groups;
	//Все правила, которые связаны с камерой, которая распознала пользователя
	std::vector<std::pair<int, std::string>> _m_rules;
	//Дополнительная информация, которая может быть определена в файле
	std::string _m_info_for_file = "";
	//Список со всеми помещениями
	std::vector<std::string> _listPremise;
};

