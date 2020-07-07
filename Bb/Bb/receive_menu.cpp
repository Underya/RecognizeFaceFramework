#include "receive_menu.h"
#include "..//MessageServer/notificationServer.h"
#include "Configuration.h"
#include "questions_user.h"

using namespace std;

std::string recipients_list::rec_name = "rec";

void recipients_list::Switch(db_user *user)
{
	_user = user;
	Menu();
}

std::vector<std::string> recipients_list::GetFileReceiver()
{
	vector<string> all_file;
	//��������� ����� ������ ��� 

	//�������� ����� ��������� �������
	//rec1:path
	//rec2:path2
	int num = 1;
	string paramrs_name = GetNameParams(rec_name, num);

	try {
		Configuration conf;
		while (conf.HasParamert(paramrs_name)) {
			//���� ���� ����� ��������, �� �� ����������� � ������
			all_file.push_back(conf.GetParametr(paramrs_name));
			//������� � ���������� ������
			num++;
			paramrs_name = GetNameParams(rec_name, num);
		}
	}
	catch (...) {
		std::cout << "��������� ����������� ������!";
	}
	return all_file;
}

void recipients_list::ShowAllReceive()
{
	//��������� ���� ������
	vector<string> all_name = GetFileReceiver();

	//�������
	int num = 1;

	for (auto iter = all_name.begin(); iter != all_name.end(); iter++) {
		cout << num << ") ";
		ShowInfoOner(*iter);
		num++;
	}

}

void recipients_list::ShowInfoOner(std::string path)
{
	notificationServer ns;
	try {
		ns.AddNewRecipient(path);
		std::vector<Recipient> vec = ns.GetListRecepient();
		Recipient r = vec[0];
		cout << "����:" << path << " �����:" << r.GetAddress() << " ����:" << r.GetPort() << "\n";
	}
	catch (...) {
		cout << "����:" << path << " �� ������� ������� ��� ���������\n";
	}
	cout << "----------------------------\n";
}

std::string recipients_list::GetNameParams(std::string params, int number)
{
	return params + std::to_string(number);
}

void recipients_list::AddReceiver()
{
	string path;
	questions_user q;
	path = q.GetParametr("������� ���� � �����");

	try {
		notificationServer ns;
		ns.AddNewRecipient(path);
	} catch(...) {
		cout << "�� ������� ��������� ����. ��������, �� �� ������� JSON\n";
		q.WaitPressSay();
		return;
	}

	//��������� ���������� ��������
	int num = GetNexttNumber();

	//���������� � ����
	Configuration conf;
	string name = GetNameParams(rec_name, num);
	conf.SetParametr(name, path);
	conf.Save();
	cout << "���������� ��������!\n";
	q.WaitPressSay();
}

int recipients_list::GetNexttNumber()
{
	int num = 1;
	Configuration conf;

	string paramrs_name = GetNameParams(rec_name, num);

	while (conf.HasParamert(paramrs_name)) {
		num++;
		paramrs_name = GetNameParams(rec_name, num);
	}

	return num;
}

void recipients_list::DeleteRecipient()
{
	int num = GetNexttNumber() - 1;
	questions_user q;
	vector<string> vec;
	for (int i = 1; i <= num; i++) vec.push_back(to_string(i));

	int del_num = q.SendQuestInt("������� ����� ���������� ��� �������� ��� �� ������", vec);
	//�������� �� ������
	try {
		Configuration conf;
		string name = GetNameParams(rec_name, del_num);
		conf.DeteleParametr(name);
		//������ ���� �������� ��� ��������, ������� ������ ���
		string next_name = GetNameParams(rec_name, del_num + 1);
		while (conf.HasParamert(next_name)) {
			conf.SetParametr(name, conf.GetParametr(next_name));
			name = next_name;
			del_num++;
			next_name = GetNameParams(rec_name, del_num + 1);
		}
		//��������� �������� ���������
		conf.DeteleParametr(name);
		conf.Save();
	}
	catch (...) {
		cout << "�� ������� ������� ����������!\n";
		q.WaitPressSay();
		return;
	}

	cout << "�������� ��� ������� �����!\n";
	q.WaitPressSay();
	return;
}

void recipients_list::Menu()
{
	questions_user q;
	

	while (true) {
		q.ClearConsole();
		ShowAllReceive();
		int res = q.SendQuestInt("�������� ��������", { "��������", "�������", "�����" });

		res = ParseAnswer(res);

		//���� �������� -1 - �� �����
		if (res == -1)
			break;
	}
}

int recipients_list::ParseAnswer(int number)
{
	//����������
	if (number == 1) {
		AddReceiver();
	}

	if (number == 2) {
		DeleteRecipient();
	}

	//�����
	if (number == 3) {
		return -1;
	}
	return 1;
}
