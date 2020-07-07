#include "pch.h"
#include "Configuration.h"
using namespace std;

Configuration::Configuration(std::string file_name) : file_parametr(file_name)
{
	//��������� ������ ��� �����
	mapConfiguration = new map<string, string>();

	//���������� �����
	ReceiveDate();
}

Configuration::Configuration() : file_parametr("Config.txt")
{
	//��������� ������ ��� �����
	mapConfiguration = new map<string, string>();

	//���������� �����
	ReceiveDate();
}

Configuration::~Configuration()
{
	//�������� ����� �����
	delete mapConfiguration;
}

string Configuration::GetParametr(string Name)
{
	return mapConfiguration->at(Name);
}

bool Configuration::IsEmpty()
{
	//���� ���������� �������� � ������� �������, ������� ������
	if (mapConfiguration->size() == 0)
		return true;
	else
		return false;
}

bool Configuration::HasParamert(string Name)
{
	auto res = mapConfiguration->find(Name);
	//���� ������ ������� ���
	if (res == mapConfiguration->end()) return false;
	//�����, ����� ������ ����
	return true;
}

void Configuration::DeteleParametr(std::string Name)
{
	mapConfiguration->erase(Name);
}

void Configuration::SetParametr(std::string Name, std:: string Value)
{
	//��������, ���� �� ����� ������ � �������
	bool res = HasParamert(Name);
	
	//���� ������ ������� ��� � �������, �� ��������� �� ������� � ��������
	if (!res) {
		//����������� ����� ������
		//�������� ������� ���� ��� ������� � �������
		mapConfiguration->insert(make_pair(Name, Value));
	}
	//����� - ���������� ������
	else {
		mapConfiguration->operator[](Name) = Value;
	}
}


string Configuration::GetContentList()
{
	string Content = "";

	//��������� ���� ��������� � ��������� ����
	for (auto iter = mapConfiguration->begin(); iter != mapConfiguration->end(); iter++) {
		Content += iter->first + ":" + iter->second + ";\n";
	}

	return Content;
}


void Configuration::ReceiveDate()
{
	CloseFile();
	OpenFileForRead();

	//������ ��� ���������� �������� �� �����
	string line;
	//�������� ��������� � ��� ��������
	string name, value;
	//������ ����� �����
	while (getline(*_rFile, line)) {
		if (line == "") continue;
		//������ ���������� ������
		GetValueForString(line, name, value);
		mapConfiguration->insert(make_pair(name, value));
	}
	
}
