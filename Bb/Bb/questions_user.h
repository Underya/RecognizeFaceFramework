#pragma once

#include <string>
using std::string;
#include <vector>


//����� ��� ����, ��� �� �������� ������� ������������ 
class questions_user
{
public:

	//�������� ������ �������
	void ClearConsole();

	//����� ����� ������, � ���������� ����� ���������� ������
	int SendQuestInt(string quest_text, std::vector<string> varinats);

	//�����, ������� ���������� ������������ ��������� �� ������ ���� ������ ������ �� �������� ���������
	string SendQuest(string quest_text, std::vector<string> varinats);

	//����� ���������� ������������ ������ �������� ��� ���������
	//� ���������� �������� ���������
	string GetParametr(string name_params);

	//��������, ��� ��� ���������� ���� ����� �������
	//� �������� �������
	void WaitPressSay();

	//��������, ���� ������������ �� ����� �������
	void WaitPress();
};

