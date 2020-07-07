#include "questions_user.h"

#include <iostream>
using namespace std;

#include <conio.h>

void questions_user::ClearConsole()
{
	//�������� ������
	system("cls");
}

int questions_user::SendQuestInt(string quest_text, std::vector<string> varinats)
{
	//���������� ���������� �������
	int count = varinats.size();
	//�� ��� ���, ���� �� ����� ��� ������ �����, ����� ���������� ������
	while (true) {
		//����� �������
		cout << quest_text << endl;
		//���������� ��� �������� ������ ������
		int i = 1;
		//����� ��������� ������
		for (auto iter = varinats.begin(); iter != varinats.end(); iter++) {
			cout << i++ << ". " << *iter << endl;
		}
		//����� ����������� ��� �����
		cout << ">> ";
		//���������� ��� ��������� ������
		string answer;
		//�������� ������
		cin >> answer;
		//������� ������������� ����� � �����
		try {
			int num_res = atoi(answer.c_str());
			//���� ����� � �� ���������� ���������
			//��������� ������
			if (num_res < 1 || num_res > count) throw new exception();
			//���� ������ ���������� �������, �� ������� ��� ���������
			return num_res;
		}
		catch (...) {
			cout << "������ �� ���������� ������� ������!" << endl;
			continue;
		}
	}
}

std::string questions_user::SendQuest(string quest_text, vector<std::string> varinats)
{
	//����� ���������� ����� ������, ������� �� ���� ������, ��� ������� � ������
	return varinats[SendQuestInt(quest_text, varinats) - 1];
}

string questions_user::GetParametr(string name_params)
{
	char cres[300];
	string res;
	cout << name_params << ": ";
	cin >> res;
	return res;

}

void questions_user::WaitPressSay()
{
	cout << "��� ����������� ������� ����� �������...";
	WaitPress();
}

void questions_user::WaitPress()
{
	_getch();
}
