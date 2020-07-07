
#pragma once
#include <iostream>
#include <vector>

#ifdef FILEMANAGER_EXPORTS
#define FILEMANAGER_API __declspec(dllexport)
#else
#define FILEMANAGER_API __declspec(dllimport)
#endif


//���������� �������� ����������, ����������� ���������� � �����
struct FILEMANAGER_API face_info {

	//������������� ����������
	int id = -1;

	//��� ����������
	std::string first_name = "";

	//������� ����������
	std::string last_name = "";

	//�������� ����������
	std::string mid_name = "";

	//�������� ����������
	std::string descinfo = "";

	//������������� �������� � �������
	int other_id = -1;

	//�������� ���������� ��������
	std::vector<std::string> desc;

	//�������������� ��������
	std::vector<int> id_desc;
};