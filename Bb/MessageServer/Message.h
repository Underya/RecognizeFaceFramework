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

//���������, ������� ��������� ����� ���������
class MESSAGESERVER_API Message
{
public:
	
	//������� ������ ��������� ��� ����������
	Message();

	//�������� ��������� �� JSON ���������
	Message(const char* JSONbuff, int size);

	//������ ��������� �� JSON 
	void Parse(const char* JSONbuff, int size);

	//������ ��� ��������� ����������

	//������� ID ������������ ��������
	void SetIdEmployee(int id);
	//������� ��� ��������
	void SetFirstName(std::string firstName);
	//������� ������� ��������
	void SetLastName(std::string family);
	//������� ��������
	void SetMidName(std::string lastName);
	//������� ����� � ����� �������������
	void SetTime(time_t t);
	//�������� ������� �����
	void SetCurrentTime();
	//�������� ������, � ������� ��������� ������������
	void AddGroup(int idGroup, std::string NameGroup);
	//������� ������� ��� ������������
	void AddRule(int idRule, std::string NameRule);
	//���������� ���������� � ������������
	void AddInfo(std::string info);
	//���������� ������ � �����������
	void AddPremiseList(std::vector<std::string> listPremise);

	//�������� ��������� � ���� ������� ���� ��� ��������
	const char* GetMessageToSend();

	//������ ��� ��������� ���������� �� ���������

	//�������� id ������������
	int GetId();
	//�������� ��� ������������
	std::string GetFirstName();
	//�������� ������� ������������
	std::string GetLastName();
	//��������� �������
	std::string GetMidName();
	//�������� ����� �������������
	tm GetTime();
	//�������� ������ �����
	std::vector<std::pair<int, std::string>> GetGroupList();
	//�������� ������ ������
	std::vector<std::pair<int, std::string>> GetRulesList();
	//��������� �������������� ���������� �� ���������
	std::string GetInfo();
	//��������� ������ ���������
	std::vector<std::string> GetListPremise();

	//�������� ����� ���������
	int GetSizeMessageToSend();

protected:

	//������ ���� string ����������� � ������� ������ ���� char *, �  ���������� ������, ���������� �� ������ �� ���������� ������� � ������
	void SetInBuffer(std::string in, char* out, int& index);

	//������ ��������� � ������
	int _size_mess = 0;

	//��������������� ���������� � �������������, ������� ������������ ��� ��������, ��� �������� �� ���������
	//id ��������
	int _m_id = 0;
	//��� � ������� � ��������
	std::string _m_name = "";
	std::string _m_family = "";
	std::string _l_name = "";
	//���� �������������
	std::string _m_data = "";
	//����� �������������
	std::string _m_time = "";
	//��� ������, � ������� ����������� ������������
	std::vector<std::pair<int, std::string>> _m_groups;
	//��� �������, ������� ������� � �������, ������� ���������� ������������
	std::vector<std::pair<int, std::string>> _m_rules;
	//�������������� ����������, ������� ����� ���� ���������� � �����
	std::string _m_info_for_file = "";
	//������ �� ����� �����������
	std::vector<std::string> _listPremise;
};

