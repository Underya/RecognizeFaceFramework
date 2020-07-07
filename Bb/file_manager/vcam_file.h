#pragma once
#include <iostream>
#include <string>


#ifdef FILEMANAGER_EXPORTS
#define FILEMANAGER_API __declspec(dllexport)
#else
#define FILEMANAGER_API __declspec(dllimport)
#endif


//���������� � ������ �� �����
struct FILEMANAGER_API vcam_file
{
	//����� ������. IP ��� Web
	std::string address;

	//������� ������
	std::string position;

	//������������ ������
	std::string description;

	//������������� ������ � ���� ������
	int id;

	//�� ���������
	int id_premise;

	//������������� ������ � ���� ������
	std::string id_str() { return std::to_string(id); }

	//��������, �������� �� ����� ������
	bool AddressIsNumber() 
	{
		for (int i = 0; i < address.size(); i++) {
			if (!isdigit(address[i])) return false;
		}

		return true;
	}

	//����������� ������ � ���� �����
	int GetAddressNumber() {
		if (!AddressIsNumber()) {
			throw std::exception("Execption! Address in not number");
		}
		return atoi(address.c_str());
	}
};
