#pragma once
#include <string>

//�����, ������� ��������� ���������� ���������� �� �������, � ���� � ���, �����������
class Initialization
{
public:

	//������ ��������
	void Start();

	//��������, ������� �� ���������� �� ������
	bool HasImport();

	std::string GetAdress();

	std::string GetPort();

	std::string GetDBName();

	std::string GetUser_Name();

	std::string GetPassword();

protected:

	//����� ��
	std::string _db_address;

	//���� ��
	std::string _port;

	//�������� ��
	std::string _db_name;

	//��� �����������
	std::string _name;

	//������ ������������
	std::string _password;

	//��������� ����������� � ���, ��� ������������ ��������������
	void SetImportInfo();

	//�������� ���������� � ��
	void LoadDB();

	//�������� ���������� �� �������
	void LoadImport();

	//��������, ���� �� ��������� 
	bool ConfigEmpty();

	//��������� ������ ��� ������� ������ ���������
	void StartDialog();

	//������ � ������������� ��� ��������� ���������� � ��
	void DBDialog();

	//���������� ���������� � �� � ������������� �����
	void SaveDBInfo();

	//���� �����������, ��� ���������� ������ �� ������
	bool _import = false;
};

