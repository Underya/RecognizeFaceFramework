#pragma once

#include <map>
#include <string>
#include <fstream>
#include "file_parametr.h"

#ifdef FILEMANAGER_EXPORTS
#define FILEMANAGER_API __declspec(dllexport)
#else
#define FILEMANAGER_API __declspec(dllimport)
#endif

//�����, ������� ��������� ���������� ����� ��������
 class FILEMANAGER_API Configuration : public file_parametr
{
public:

	//�������� ����� � ������������ � ��������� ������
	Configuration(std::string file_name);

	//�������� ����� � ����������� � ������ �� ���������
	Configuration();

	~Configuration();

	//��������� �������� ��������� �� �����
	std::string GetParametr(std::string Name);

	//��������, ���� �� ��������� � �������
	bool IsEmpty();

	//������� �� ����� �������� � �������
	bool HasParamert(std::string Name);

	//������� ��������� ��������
	void DeteleParametr(std::string Name);

	//��������� �������� ��������� �� �����
	void SetParametr(std::string Name, std::string Value);

private:

	//������� �� ����� ���������� �����������
	std::map<std::string, std::string> *mapConfiguration;

	//��������� ���� �������� � ��������� �������
	std::string GetContentList() override;

	//��������� ���� ������ �� ���������� �����
	void ReceiveDate();
};

