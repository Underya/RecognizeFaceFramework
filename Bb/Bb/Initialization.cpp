#include "Initialization.h"
#include "..//file_manager/Configuration.h"
#include "..//MessageServer/BlowfishCoder.h"
#include "questions_user.h"

#define BLOCK_SIZE 256

using namespace std;

void Initialization::Start()
{
	//���� ���� ������, �� ���������� ������ �������������
	if (ConfigEmpty()) {
		StartDialog();
	}
	else {
		//���� ���� �� ������, �� ���� ���������� �������� ����������
		//��������� ���������� � ��
		LoadDB();
		//��������� ���������� �� ������
		LoadImport();
	}
}



bool Initialization::HasImport()
{
	return _import;
}

std::string Initialization::GetAdress()
{
	return _db_address;
}

std::string Initialization::GetPort()
{
	return _port;
}

std::string Initialization::GetDBName()
{
	return _db_name;
}

std::string Initialization::GetUser_Name()
{
	return _name;
}

std::string Initialization::GetPassword()
{
	return _password;
}

void Initialization::SetImportInfo()
{
	Configuration conf;
	if (_import) {
		conf.SetParametr("import", "1");
	}
	else {
		conf.SetParametr("import", "0");
	}
	conf.Save();
}

void Initialization::LoadDB()
{
	//���� ��� �����������, ������ ��������� �� ����
	Configuration c;
	if (!c.HasParamert("has_db")) return;

	//�������� ����������
	//�������� � �������� ��
	ifstream file("config.info", std::ios::in | std::ios::binary);
	char* buff = new char[5000], * res = NULL;
	file.read(buff, 5000);
	//�������� �����
	file.close();
	//�������������
	BlowfishCoder bc(64);
	//��������� ����� �������������� ������
	int size = 0, newSize = 0;
	size = atoi(c.GetParametr("has_db").c_str());
	res = bc.UnCodind(buff, size, newSize);
	string fullStr;
	//��������� �������� � �������� ��
	fullStr = res;
	int position = 0, strPosition = 0;
	strPosition = fullStr.find('\n', position);
	_db_address = fullStr.substr(position, strPosition);
	position = strPosition + 1;
	strPosition = fullStr.find('\n', position);
	_port = fullStr.substr(position, strPosition - position);
	position = strPosition + 1;
	strPosition = fullStr.find('\n', position);
	_db_name = fullStr.substr(position, strPosition - position);
	position = strPosition + 1;
	strPosition = fullStr.find('\n', position);
	_name = fullStr.substr(position, strPosition - position);
	position = strPosition + 1;
	strPosition = fullStr.find('\n', position);
	_password = fullStr.substr(position, strPosition - position);
}

void Initialization::LoadImport()
{
	//���� ����� ���������
	Configuration c;
	if (c.HasParamert("import")) {
		if (c.GetParametr("import") == "1") {
			_import = true;
		}
		if (c.GetParametr("import") == "0") {
			_import = true;
		}
	}
}

bool Initialization::ConfigEmpty()
{
	Configuration conf;

	//���� ���� ������, �� ������
	if (conf.IsEmpty()) {
		return true;
	}

	return false;
}

void Initialization::StartDialog()
{
	questions_user qu;
	int res = qu.SendQuestInt("�������� �������� ����������", { "���� ������", "������ �� ������" });
	//��������� �������
	if (res == 1) {
		//�������� ������
		qu.ClearConsole();
		//����� ������� ��� ���������� ���������� � ��
		DBDialog();
	}

	if (res == 2) {
		//��������, ��� ������������ ������ �� ������
		_import = true;
	}

	//��� ����� �������� ��������� ��������� � ���, ������������ �� ������
	SetImportInfo();
}

void Initialization::DBDialog()
{
	//��������� �������� � �������� ��
	cout << "������� ���������� ��� ����������� � ��." << endl;
	cout << "��������, ������ ���������� ����� ��������� � ������������� ����." << endl;
	cout << "������� ����� �����������" << endl << ">> ";
	cin >> _db_address;
	cout << "������ ���� �����������" << endl << ">> ";
	cin >> _port;
	cout << "������� �������� ���� ������" << endl << ">> ";
	cin >> _db_name;
	cout << "������� ��� ������������" << endl << ">> ";
	cin >> _name;
	cout << "������� ������ ������������" << endl << ">> ";
	cin >> _password;
	system("cls");

	//���������� ���������� ����������
	SaveDBInfo();
}


void Initialization::SaveDBInfo()
{
	BlowfishCoder coder(BLOCK_SIZE);
	//������������� ���������� � �������� �������
	string res = _db_address + "\n" + _port + "\n" + _db_name + "\n" + _name + "\n" + _password + "\n";
	//������� ���� ��� ������
	ofstream file("config.info", std::ios::out | std::ios::binary);
	//����������� ������
	int size = 0, newSize = 0;
	char* codingString = NULL;
	codingString = coder.Coding(res.c_str(), res.size(), newSize);
	//������ � ����
	file.write(codingString, newSize);
	//��������, ��� ���� ����������� � ��
	Configuration conf;
	conf.SetParametr("has_db", std::to_string(newSize));
	conf.Save();
	//�������� �����
	file.close();
	//�������� �������
	delete[newSize]codingString;
}
