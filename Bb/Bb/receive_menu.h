#pragma once
#include "..//db/db_user.h"

#include <vector>
#include <string>

//�����, ������� ��������� ������� ��� ������ � ������������
class recipients_list
{

public:

	void Switch(db_user* user);

	//��������� ����� ������ �����������
	std::vector<std::string> GetFileReceiver();

protected:

	//����� ���� �����������
	void ShowAllReceive();

	//�������� ���������� �� ���� ����������
	void ShowInfoOner(std::string path);

	std::string GetNameParams(std::string params, int number);

	//�������� ������ ����������
	void AddReceiver();

	//�������� ��������� ����� �������������� 
	int GetNexttNumber();

	//������� �� ������
	void DeleteRecipient();

	void Menu();

	int ParseAnswer(int munber);

	db_user* _user = NULL;

	static std::string rec_name;
};

