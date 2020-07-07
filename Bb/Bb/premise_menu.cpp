#include "premise_menu.h"
#include "questions_user.h"
#include "..//db/db_vcam.h"

using namespace std;

void premise_menu::Switch(db_user* user)
{
	_user = user;
	questions_user q;
	
	try {
		while (true)
		{
			q.ClearConsole();
			int res = q.SendQuestInt("�������� ��������", { "�������� ���������", "�������� ��� ���������",
				"�������� ���������", "�������� ���������", "������� ���������", "�����" });

			res = ParseAnswer(res);

			if (res == -1) {
				break;
			}
		}
	} catch(...) {
		std::cout << "��������� ����������� ������!";
	}
}

std::string premise_menu::ShowOne(db_premise prem)
{
	string info = "";
	info += "id:" + to_string(prem.GetId()) + " ��������:" + prem.GetName();
	return info;
}

int premise_menu::ParseAnswer(int number)
{
	//����� ��������� ���������
	if (number == 1) {
		questions_user q;
		q.ClearConsole();
		ShowPremise();
		q.WaitPressSay();
	}

	//�������� ��� ���������
	if (number == 2) {
		questions_user q;
		q.ClearConsole();
		ShowAllPremise();
		q.WaitPressSay();
	}

	//���������� ������ ���������
	if (number == 3) {
		AddPremise();
	}

	//��������� ���������
	if (number == 4) {
		EdietePremise();
	}

	//������� ���������
	if (number == 5) {
		DeletePremise();
	}

	//�����
	if (number == 6)
		return -1;
	return 1;
}

void premise_menu::ShowPremise()
{
	vector<db_vcam> v = db_vcam::GetAllLinkVcam(*_user);

	vector<db_premise> vd;
	
	for (auto iter = v.begin(); iter != v.end(); iter++) {
		if (iter->GetPremise().GetId() != -1) {
			vd.push_back(iter->GetPremise());
		}
	}

	//����� ����������
	for (auto iter = vd.begin(); iter != vd.end(); iter++) {
		cout << ShowOne(*iter);
		cout << "\n";
		ShowParent(iter->GetId());
		cout << "-----------------------------\n\n";
	}
}

void premise_menu::ShowParent(int id_premise)
{
	db_premise prem(id_premise);
	string str = "-->";
	//������� �����������
	int level = 0;
	string space = "   ";

	while (prem.GetIdParent() != -1) {
		string tab = "";
		for (int i = 0; i < level; i++) tab += space;
		db_premise parrentPrem(prem.GetIdParent());
		cout << tab << str << ShowOne(parrentPrem) << "\n";
		prem = parrentPrem;
		level++;
	}
}

void premise_menu::ShowAllPremise()
{
	vector<db_premise> vp = db_premise::GetAllPremise();

	for (auto iter = vp.begin(); iter != vp.end(); iter++) {
		cout << ShowOne(*iter);
		cout << "\n";
		ShowParent(iter->GetId());
		cout << "-----------------------------\n\n";
	}
}

void premise_menu::AddPremise()
{
	questions_user q;
	string name, desc;
	int parent_id = -1;

	name = q.GetParametr("��������");
	desc = q.GetParametr("��������");
	parent_id = atoi(q.GetParametr("id �������� ��� -1").c_str());

	try {
		db_premise::AddNewPremise(name, desc, parent_id);
	}
	catch (...) {
		cout << "�� ������� ������� ����� ���������!\n";
		q.WaitPressSay();
		return;
	}

	cout << "��������� ���� ������� �������!\n";
	q.WaitPressSay();
}

void premise_menu::EdietePremise()
{
	questions_user q;
	q.ClearConsole();
	ShowPremise();

	cout << "������� id ��������� ��� ���������:";
	int id = SelectPremise();
	db_premise p(id);
	q.ClearConsole();
	cout << ShowOne(p) << "\n\n";

	string name, desc;
	int parent_id = -1;
	name = q.GetParametr("������� ����� ���");
	desc = q.GetParametr("������� ����� ����������");
	parent_id = atoi(q.GetParametr("������� ������������ ��������� ��� -1").c_str());

	try {
		p.SetName(name);
		p.SetDesc(desc);
		if (parent_id != -1) {
		}
	}
	catch (...) {
		cout << "�� ������� �������� ���������� � ���������!\n";
		q.WaitPressSay();
		return;
	}

	q.ClearConsole();
	cout << ShowOne(p) << "\n\n";
	cout << "���������� ���� ������� ���������\n";
	q.WaitPressSay();
}

void premise_menu::DeletePremise()
{
	questions_user q;
	q.ClearConsole();
	ShowPremise();

	cout << "������� id ��������� ��� ��������:";
	int id = SelectPremise();
	db_premise p(id);

	try {
		p.Delete();
	}
	catch (...) {
		cout << "�� ������� ������� ���������!\n" << "��������, � ���� ���� ������� ��������\n";
		q.WaitPressSay();
		return;
	}

	cout << "���������� ���� ������� �������!\n";
	q.WaitPressSay();
}

int premise_menu::SelectPremise()
{
	int id = -1;
	while (true)
	{
		string sid;
		cin >> sid;
		id = atoi(sid.c_str());
		//��������, ���� �� ��������� � ����� id
		try {
			db_premise check(id);
		}
		catch (...) {
			cout << "�� ������� ������� ��������� � ����� id!\n";
			cout << "������� id ������:";
			continue;
		}

		break;
	}
	return id;
}
