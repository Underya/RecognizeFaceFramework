#include "group_menu.h"
using namespace std;

#include "../db/db_employee.h"
#include "questions_user.h"

void group_menu::Switch(db_user* user)
{
	_user = user;
	questions_user q;

	//���� ��� ����������� ����� - ���������
	db_group::LoadedAllGroup(_user->GetId());
	try {
		while (true)
		{
			q.ClearConsole();
			int res = q.SendQuestInt("�������� ��������", { "����������� ������", "����������� ��� ������",
				"����������� ��� ������ � �������������",
				"��������� ������", "�������� ������",
				"�������� ������","�������� ������", "������� ������",
				"�����" });

			int act = ParseAnswer(res);

			if (act == -1)
				break;
		}
	}
	catch (...) {
		cout << "��������� ����������� ������!";
	}
}


void group_menu::ShowAllGroup() {

	std::vector<db_group> v = db_group::GetAllGroupToDB();

	for (auto iter = v.begin(); iter != v.end(); iter++) {
		ShowOneGroup(*iter);
	}
}

void group_menu::ShowGroup(db_user* _user)
{

	std::vector<db_group> v = db_group::GetAllGroup();
	for (auto iter = v.begin(); iter != v.end(); iter++) {
		ShowOneGroup(*iter);
	}
}

void group_menu::ShowGroupAndEmloyee()
{
	vector<db_group> g = db_group::GetAllGroupToDB();
	//������� ����� ���������� � ������
	for (auto iter = g.begin(); iter != g.end(); iter++) {
		cout << "id:" << iter->GetId() << " ��������:" << iter->GetName() << "\n";
		//����� ���������� ��� ���� ���������� � ������
		vector<db_employee>* ve = db_employee::GetEmployeeWithCondition(*iter);

		for (auto emp = ve->begin(); emp != ve->end(); emp++) {
			cout << "     " << "id:" << emp->GetId() << " ���:" <<
				emp->GetLastName() << " " << emp->GetFirstName() << " " << emp->GetMidleName() << ";\n";
		}

		cout << "-----------------------------------\n\n";

		delete ve;
	}
}

int group_menu::SelectGroup() {
	int id = -1;
	while (true)
	{
		string sid;
		cin >> sid;
		id = atoi(sid.c_str());
		//��������, ���� �� ������ � ����� id
		try {
			db_group check(id);
		}
		catch (...) {
			cout << "�� ������� ������� ������ � ����� id!\n";
			cout << "������� id ������:";
			continue;
		}

		break;
	}
	return id;
}

void group_menu::LinkGroup()
{
	questions_user q;
	q.ClearConsole();

	ShowAllGroup();
	cout << "�������� ������, ������� ����� ��������� � ������������:";
	int id_g = SelectGroup();


	//������� ��������� ��������� ������ � ������������
	try {
		_user->LinkGroup(id_g);
	}
	catch (...) {
		cout << "�� ������� ��������� ������ � ������� ������������!\n";
		q.WaitPressSay();
		return;
	}

	cout << "����� ������� ���������!\n";
	q.WaitPressSay();
	return;
}

void group_menu::UnLinkGroup()
{
	questions_user q;
	q.ClearConsole();

	ShowGroup(_user);
	cout << "�������� ������, ������� ����� ��������:";
	int id_g = SelectGroup();


	//������� ��������� ��������� ������ � ������������
	try {
		_user->UnLinkGroup(id_g);
	}
	catch (...) {
		cout << "������ �������� �� ������������!\n";
		q.WaitPressSay();
		return;
	}

	cout << "����� ������� ��������!\n";
	q.WaitPressSay();
	return;
}

int group_menu::ParseAnswer(int number)
{
	questions_user q;
	//����� ������ ��������� �����
	if (number == 1) {
		ShowGroup(_user);
		q.WaitPressSay();
	}

	//�������� ��� ������
	if (number == 2) {
		ShowAllGroup();
		q.WaitPressSay();
	}

	//��������� ���� ����� � �� ��������������
	if (number == 3) {
		q.ClearConsole();
		ShowGroupAndEmloyee();
		q.WaitPressSay();
	}

	//�������� �����
	if (number == 4) {
		LinkGroup();
		db_group::LoadedAllGroup(_user->GetId());
	}

	//�������� ������
	if (number == 5) {
		UnLinkGroup();
		db_group::LoadedAllGroup(_user->GetId());
	}

	//�������� ����� ������
	if (number == 6) {
		AddNewGroup();
	}

	//�������� ���������� � ������
	if (number == 7) {
		EditGroup();
	}
	
	if (number == 8) {
		DeletGroup();
		db_group::LoadedAllGroup(_user->GetId());
	}

	//�����
	if (number == 9)
		return -1;

	return 1;
}

void group_menu::AddNewGroup()
{
	questions_user q;
	string name, desc;
	cout << "������� ���������� ��� ����� ������\n";
	name = q.GetParametr("��������");
	desc = q.GetParametr("��������");
	int new_id = -1;

	try {
		db_group gr = db_group::AddNewGroup(name, desc);
		new_id = gr.GetId();
	}
	catch (...) {
		cout << "�� ������� ������� ����� ������!\n";
		q.WaitPressSay();
		return;
	}
	cout << "������ ������� �������!\n";
	int res = q.SendQuestInt("��������� ����� ������ � �������� ������������?", { "��", "���" });
	if (res == 1) {
		_user->LinkGroup(new_id);
		cout << "������ ������� ���������!";
	}
	q.WaitPressSay();	
}

void group_menu::EditGroup()
{
	questions_user q;
	q.ClearConsole();
	ShowGroup(_user);
	cout << "�������� ������ ��� ���������:";
	int res = SelectGroup();
	q.ClearConsole();
	db_group g(res);
	ShowOneGroup(g);

	string name, desc;
	name = q.GetParametr("����� ���");
	desc = q.GetParametr("��������");

	try {
		g.SetName(name);
		g.SetDescript(desc);
	}
	catch (...) {
		cout << "�� ������� �������� ����������!\n";
		q.WaitPressSay();
		return;
	}
	q.ClearConsole();
	ShowOneGroup(g);
	cout << "���������� ���� ������� ��������!\n";
	db_group::LoadedAllGroup(_user->GetId());
	q.WaitPressSay();
	return;
}

void group_menu::DeletGroup()
{
	questions_user q;
	q.ClearConsole();
	ShowGroup(_user);

	cout << "������� id ������ ��� ��������:";
	int res = SelectGroup();

	db_group g(res);
	try {
		g.Delete();
	}
	catch (...) {
		cout << "�� ������� ������� ������!\n";
		q.WaitPressSay();
		return;
	}

	cout << "������ ������� �������!\n";
	q.WaitPressSay();
	return;
}

void group_menu::ShowOneGroup(db_group gr)
{
	cout << "id:" << gr.GetId() << " ��������: " << gr.GetName() << " ��������:" << gr.GetDesc() << "\n";
}
