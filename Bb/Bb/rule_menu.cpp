#include "rule_menu.h"
#include "questions_user.h"
#include "..//db/rules_collection.h"
#include "premise_menu.h"
#include "camera_menu.h"

using namespace std;

void rule_menu::Switch(db_user* user)
{
	_user = user;
	questions_user qu;

	try {
		while (true) {
			qu.ClearConsole();

			int res = qu.SendQuestInt("�������� ��������", { "�������� �������", "�������� ��� �������", "�������� ������-�������",
				"�������� ���������-�������", "�������� �������", "�������� �������",
				"�������� ����� � �����������", "�������� ����� � ��������", "����� �������","�����" });

			res = ParseAnswer(res);

			if (res == -1)
				break;
		}
	}
	catch (...) {
		std::cout << "��������� ����������� ������!";
	}

}

int rule_menu::ParseAnswer(int number)
{
	questions_user q;
	//�������� �������
	if (number == 1) {
		q.ClearConsole();
		ShowLink(_user);
		q.WaitPressSay();
	}

	//�������� ��� �������
	if (number == 2) {
		q.ClearConsole();
		ShowAll();
		q.WaitPressSay();
	}

	//�������� ������ � ����� �������, ��������� � ���
	if (number == 3) {
		q.ClearConsole();
		ShowLinkCam();
		q.WaitPressSay();
	}

	//����� ��������� �������
	if (number == 4) {
		q.ClearConsole();
		ShowLinkPremise();
		q.WaitPressSay();
	}

	//���������� �������
	if (number == 5) {
		AddRule();
	}

	//��������� �������
	if (number == 6) {
		EditRule();
	}

	//�������� ����� � ����������
	if (number == 7) {
		EditRulePremise();
	}

	if (number == 8) {
		EditRuleCamera();
	}

	//�����
	if (number == 10) {
		return -1;
	}

	return 1;
}

void rule_menu::ShowOne(db_rule rule)
{
	cout << "id:"  << rule.GetId() << " ��������:" << rule.GetName() << " ��������:" << rule.GetDesc() << "\n"; 
}

void rule_menu::ShowLink(db_user* _user)
{
	rules_collection rc;
	//�������� ���� ������ ��� �����
	
	//������ ���� �����
	vector<db_vcam> v = db_vcam::GetAllLinkVcam(*_user);

	for (auto iter = v.begin(); iter != v.end(); iter++) {
		rc.LoadAlRuleLinkCam(iter->GetId());
	}

	//����� ���� ������
	list<db_rule> l = rc.GetAllRuleFull();
	for (auto iter = l.begin(); iter != l.end(); iter++) {
		ShowOne(*iter);
		cout << "-----------------------------------------\n";
	}
	cout << "\n";
}

void rule_menu::ShowRuleForCamera(db_vcam cam)
{
	string str = " -->";
	//���� ���� ������ ��� ������ ������ ��� ����� ���������
	rules_collection rc;
	rc.AppendRule(cam);
	list<db_rule> current_cam_rule = rc.GetAllRuleFull();
	for (auto rule = current_cam_rule.begin(); rule != current_cam_rule.end(); rule++) {
		cout << str;
		ShowOne(*rule);
	}
}

void rule_menu::ShowAll()
{
	vector<db_rule> all_rule = db_rule::GetAllRule();

	for (auto iter = all_rule.begin(); iter != all_rule.end(); iter++) {
		ShowOne(*iter);
		cout << "-----------------------------------------\n";
	}
}

void rule_menu::ShowLinkCam()
{
	vector<db_vcam> vec = db_vcam::GetAllLinkVcam(*_user);
	string str = " -->";
	//����� ���� �����
	for (auto iter = vec.begin(); iter != vec.end(); iter++) {
		cout << "id:" << iter->GetId() << " �����:" << iter->GetAddress() << " ��������:" << iter->GetDescription() << "\n";
		
		ShowRuleForCamera(*iter);

		string space = "     ";
		//������ ����� ���� ������, ������� ���� �� ���������
		if (iter->GetPremise().GetId() != -1) {
			db_premise p = iter->GetPremise();
			cout << space << "id: " << p.GetId() << " �������� ���������:" << p.GetName() << " ��������:" << p.GetDesc() << "\n";
			//��������� ���� ������
			rules_collection rule_premise;
			rule_premise.AppendRule(p);
			//����� ���� ������ ���������
			list<db_rule> premise_rule = rule_premise.GetAllRuleFull();
			for (auto rule = premise_rule.begin(); rule != premise_rule.end(); rule++) {
				cout << space << space << str;
				ShowOne(*rule);
			}
 		}

		cout << "-----------------------------------------\n";
	}
}

void rule_menu::ShowLinkPremise()
{
	//��������� ����� ������ ���������, ��������� � ������� �������������
	//��� ������
	vector<db_vcam> vec = db_vcam::GetAllLinkVcam(*_user);
	//��� ������ ������ ��������� ���������
	string str = " -->";
	string space = "     ";
	for (auto camera = vec.begin(); camera != vec.end(); camera++) {
		if (camera->GetPremise().GetId() != -1) {
			//����� ���������
			db_premise p = camera->GetPremise();
			cout << "id: " << p.GetId() << " �������� ���������:" << p.GetName() << " ��������:" << p.GetDesc() << "\n";
			//����� ���� ������ ��� ����
			rules_collection rule_premise;
			rule_premise.AppendRuleForOnePremmis(p);
			//����� ���� ������ ���������
			list<db_rule> premise_rule = rule_premise.GetAllRuleFull();
			for (auto rule = premise_rule.begin(); rule != premise_rule.end(); rule++) {
				cout << space << str;
				ShowOne(*rule);
			}
		}
		
		
		cout << "-----------------------------------------\n";
	}

}

void rule_menu::AddRule()
{
	questions_user qu;
	cout << "������� ���������� � ����� �������\n";
	string name, desc;

	int new_id = -1;

	name = qu.GetParametr("��������");
	desc = qu.GetParametr("��������");

	try {
		new_id = db_rule::AddNewRule(name, desc).GetId();

	}
	catch (...) {
		cout << "�� ������� �������� ����� �������!\n";
		qu.WaitPressSay();
	}

	cout << "\n";
	ShowOne(db_rule(new_id));
	cout << "������� ������� ���������!\n";
	qu.WaitPressSay();
}

int rule_menu::SelectRule()
{

	int id = -1;
	while (true)
	{
		string sid;
		cin >> sid;
		id = atoi(sid.c_str());
		//��������, ���� �� ������ � ����� id
		try {
			db_rule check(id);
		}
		catch (...) {
			cout << "�� ������� ������� ������� � ����� id!\n";
			cout << "������� id �������:";
			continue;
		}

		break;
	}
	return id;
}

void rule_menu::EditRule()
{
	questions_user q;
	q.ClearConsole();
	ShowLink(_user);
	//������� id ������� ��� ���������
	int id = SelectRule();
	db_rule rule(id);
	q.ClearConsole();
	ShowOne(rule);
	cout << "\n";
	cout << "������� ����� ������";
	string name, desc;
	name = q.GetParametr("����� ��������");
	desc = q.GetParametr("����� ��������");
	try {
		rule.SetName(name);
		rule.SetDesc(desc);
	}
	catch (...) {
		cout << "�� ������� �������� �������!\n";
		q.WaitPressSay();
	}

	q.ClearConsole();
	ShowOne(rule);
	cout << "������� ���� ������� ��������!\n";
	q.WaitPressSay();
}

void rule_menu::EditRulePremise()
{
	questions_user q;
	q.ClearConsole();
	premise_menu pm;
	ShowRulePremiseNotParrent();
	cout << "������� id �������� ��� �������� ��������� � ��� ������";
	int id = pm.SelectPremise();

	while (true) {
		q.ClearConsole();
		db_premise premise(id);
		cout << pm.ShowOne(premise) << "\n";
		//����� ��������� � ��� ������
		rules_collection rules;
		rules.AppendRuleForOnePremmis(premise);
		list<db_rule> list_rule = rules.GetAllRuleFull();
		string str = " -->";
		string space = "     ";
		for (auto rule = list_rule.begin(); rule != list_rule.end(); rule++) {
			cout << str << space;
			ShowOne(*rule);
		}

		int res = q.SendQuestInt("�������� ��������", { "�������� �������", "������� �������", "�����" });
		//������� ����
		if (res == 1) {
			AppendRulePremise(premise);
		}

		if (res == 2) {
			DeleteRulePremise(premise);
		}

		if (res == 3) {
			break;
		}
	}

}

void rule_menu::EditRuleCamera()
{
	questions_user q;
	q.ClearConsole();
	ShowLinkCam();
	camera_menu cm;
	cout << "������� id ������ ��� ��������� ������ ������:";
	int id = cm.SelectCamera();
	db_vcam cam(id);

	while (true) {
		q.ClearConsole();
		cm.ShowOneCamera(cam);
		//�������� ��� ������� ��� ������
		ShowRuleForCamera(cam);

		int res = q.SendQuestInt("�������� ��������", { "�������� �������", "������� �������", "�����" });

		if (res == 1) {
			AppendRuleCamera(id);
		}

		if (res == 2) {
			DeleteRuleCamera(id);
		}

		if (res == 3) {
			break;
		}

	}
}

void rule_menu::AppendRuleCamera(int id_cam)
{
	questions_user q;
	//����� ���� ������
	q.ClearConsole();
	ShowAll();
	cout << "������� id ������� ��� ����������:";
	int id_rule = SelectRule();

	try {
		db_rule::LinkedWithRuleCamer(id_cam, id_rule);
	}
	catch (...) {
		cout << "�� ������� ������� �������!\n";
		q.WaitPressSay();
		return;
	}

	cout << "����� ���� ������� ���������!\n";
	q.WaitPressSay();
}

void rule_menu::DeleteRuleCamera(int id_cam)
{
	questions_user q;
	q.ClearConsole();

	db_vcam cam(id_cam);
	rules_collection rc;
	rc.AppendRule(cam);
	list<db_rule> l = rc.GetAllRuleFull();

	for (auto iter = l.begin(); iter != l.end(); iter++) {
		ShowOne(*iter);
	}

	cout << "������� id �������, ������� ���� �������:";
	int res = SelectRule();

	try {

	}
	catch (...) {
		cout << "�� ������� ������� �������!\n";
		q.WaitPressSay();
		return;
	}
	cout << "������� ���� ������� �������\n";
	q.WaitPressSay();
}

void rule_menu::ShowRulePremiseNotParrent()
{
	//��������� ����� ������ ���������, ��������� � ������� �������������
	//��� ������
	vector<db_vcam> vec = db_vcam::GetAllLinkVcam(*_user);
	//��� ������ ������ ��������� ���������
	string str = " -->";
	string space = "     ";
	for (auto camera = vec.begin(); camera != vec.end(); camera++) {
		if (camera->GetPremise().GetId() != -1) {
			//����� ���������
			db_premise p = camera->GetPremise();
			cout << "id: " << p.GetId() << " �������� ���������:" << p.GetName() << " ��������:" << p.GetDesc() << "\n";
			//����� ���� ������ ��� ����
			rules_collection rule_premise;
			rule_premise.AppendRuleForOnePremmis(p);
			//����� ���� ������ ���������
			list<db_rule> premise_rule = rule_premise.GetAllRuleFull();
			for (auto rule = premise_rule.begin(); rule != premise_rule.end(); rule++) {
				cout << space << str;
				ShowOne(*rule);
			}
		}


		cout << "-----------------------------------------\n";
	}
}

void rule_menu::AppendRulePremise(db_premise prem)
{
	questions_user q;
	q.ClearConsole();
	ShowAll();
	cout << "������� id ������� ��� ����������:";
	int id = SelectRule();
	db_rule rule(id);
	try {
		rule.LinkedWitRulePremise(prem.GetId(), id);
	}
	catch (...) {
		cout << "�� ������� ������� ������� � ���������!\n";
		q.WaitPressSay();
		return;
	}
	cout << "������� ���� ������� ���������!";
	q.WaitPressSay();

}

void rule_menu::DeleteRulePremise(db_premise prem)
{
	questions_user q;
	q.ClearConsole();
	rules_collection rc;
	string str = "  -->";
	rc.AppendRuleForOnePremmis(prem);
	list<db_rule> rules = rc.GetAllRuleFull();
	for (auto rule = rules.begin(); rule != rules.begin(); rule++) {
		cout << str;
		ShowOne(*rule);
	}
	cout << "������� id �������:";
	int id = SelectRule();

	db_rule rule(id);
	try {
	}
	catch (...) {
		cout << "�� ������� ������� �������!\n";
		q.WaitPressSay();
		return;
	}

	cout << "������� ���� ������� �������!\n";
	q.WaitPressSay();
	return;
}

