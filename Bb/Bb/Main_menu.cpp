#include "Main_menu.h"
#include "questions_user.h"
#include "information_menu.h"
#include "work_class.h"
#include "export_menu.h"

#include <iostream>
using namespace std;

void Main_menu::Start()
{
	//�������������
	Initializate();

	questions_user qu;

	try {
		//����������� ����
		while (true) {
			//������� ������
			qu.ClearConsole();

			//������� �������
			int res = qu.SendQuestInt("������� ����", { "�����","����������", "�������" ,"�����" });

			//�������� ������
			ParseAnswer(res);

		}
	}
	catch (...) {
		std::cout << "��������� ����������� ������!";
	}
}


void Main_menu::Initializate()
{
	system("chcp 1251");
	questions_user q;
	q.ClearConsole();

	//������ �������� ��������� ������ ��� ������
	i.Start();
	
	//������ ��������� ����������
	LoadInformation();
}

int Main_menu::ParseAnswer(int result)
{
	questions_user qu;
	//�����
	if (result == 1) {
		work_class wc;
		wc.Start(_user);
	}


	//�������
	if (result == 3) {
		export_menu exm;
		exm.Export(_user);
	}

	//����� �� ����������
	if (result == 4) {
		exit(1);
		//��������� ������ �� ������� ��� ������������
		qu.WaitPressSay();
	}

	//����������
	if (result == 2) {
		//���� �� ������������� ����������, �� � ����� ��������
		if (!_import) {
			information_menu im;
			im.SwitchInformMenu(_user);
		}
	}

	//�������
	if (result == 3) {
		
	}

	return 1;
}

void Main_menu::LoadInformation()
{
	//���� ��, �� � ��� ���������� �����������
	db_manager::SetConnectInfo(i.GetAdress(), i.GetPort(), i.GetUser_Name(), i.GetPassword(), i.GetDBName(), false);
	//��������� �� ������������
	Ipcofnig ip;
	//� ������ �� �����
	try {
		_user = db_user::LoginToUser(ip.GetIpV4());
	}
	catch (...) {
		std::cout << "�� ���������� ������������ � ����� IP v4:" << ip.GetIpV4() << "\n";
	}
}
