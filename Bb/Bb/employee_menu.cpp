#include "employee_menu.h"
#include "..//db/db_group.h"
#include "questions_user.h"
#include "..//face_recognition/face_manager.h"

using namespace std;

void employee_menu::Switch(db_user* user)
{
	//���������� ���������� � ������������
	_user = user;

	db_group::LoadedAllGroup(_user->GetId());

	questions_user q;

	//���� ��� ������ � ��
	try {
		while (true) {
			q.ClearConsole();

			//������ ��������� ��������
			int res = q.SendQuestInt("�������� ��������", { "�������� �����������" , "�������� ����������� � ��������",
				"�������� ������", "�������� ����������", "�������� ������",
				"�������� ���� � ����������", "�������", "�����" });

			res = ParseAnswer(res);

			//���� ��������� -1, �� ����� �����
			if (res == -1)
				break;
		}
	}
	catch (...) {
		cout << "��������� ����������� ������!";
	}
}

int employee_menu::ParseAnswer(int number)
{
	questions_user q;
	//����� ����������� ��� �����
	if (number == 1) {
		ShowInfo();
		q.WaitPressSay();
	}

	//�������� ����������� � ��������
	if (number == 2) {
		ShowInfoAndGroup();
		q.WaitPressSay();
	}

	//���������� ������ ����������
	if (number == 3) {
		AddEmployee();
	}

	//�������� ���������� � ����������
	if (number == 4) {
		EditEmployee();
	}

	//��������� ������ �����������
	if (number == 5) {
		EditeEmployeeGroup(0);
	}

	//���������� ������ ���� � ����������
	if (number == 6) {
		AddNewPhoto();
	}

	//������� ����������
	if (number == 7) {
		DeleteEmployee();
	}

	//����� �� ����
	if (number == 8) 
		return -1;
	return 0;
}

void employee_menu::ShowOne(db_employee employee)
{
	
	cout << "id:" << employee.GetId() << " ";
	cout << "���: " << employee.GetFirstName() << " "
		<< employee.GetLastName() << " " << employee.GetMidleName() << endl;
	if (employee.GetDescrInfo() != "") {
		cout << "��������:" << employee.GetDescrInfo() << "\n";
	}
	if (employee.GetOtherId() != -1)
		cout << "id � ������ �������: " << employee.GetOtherId() << "\n";
	
}

void employee_menu::ShowOneGroup(db_employee employee)
{
	//�������� ���� ����� ��� ����������
	list<db_group> l = db_group::GetSnapGoup(employee.GetId());
	//����� ����� ������
	for (auto iter = l.begin(); iter != l.end(); iter++) {
		cout << "id ������:" << iter->GetId() << " ��������:" << iter->GetName() << "; ";
	}
	cout << "\n";

}

int employee_menu::SelectEmployee()
{

	int id = -1;
	while (true)
	{
		string sid;
		cin >> sid;
		id = atoi(sid.c_str());
		//��������, ���� �� ������ � ����� id
		try {
			db_employee check(id);
		}
		catch (...) {
			cout << "�� ������� ������� ���������� � ����� id!\n";
			cout << "������� id ����������:";
			continue;
		}

		break;
	}
	return id;
}

void employee_menu::ShowInfo()
{
	questions_user q;
	q.ClearConsole();
	std::vector<db_employee> *v = db_employee::GetEmployeeWithCondition(db_group::GetAllGroup());

	for (auto iter = v->begin(); iter != v->end(); iter++) {
		ShowOne(*iter);
		cout << "-------------------------------\n\n";
	}
	
}

void employee_menu::ShowInfoAndGroup()
{
	questions_user q;
	q.ClearConsole();
	std::vector<db_employee>* v = db_employee::GetEmployeeWithCondition(db_group::GetAllGroup());

	for (auto iter = v->begin(); iter != v->end(); iter++) {
		ShowOne(*iter);
		ShowOneGroup(*iter);
		cout << "-------------------------------\n\n";
	}
}

void employee_menu::AddEmployee()
{
	questions_user q;
	q.ClearConsole();
	string f, l, m, desc;
	int other_id = -1, id_group = -1;
	cout << "������� ���������� ��� ���������� ������ ����������\n";

	f = q.GetParametr("���");
	l = q.GetParametr("�������");
	m = q.GetParametr("��������");
	other_id = atoi(q.GetParametr("id � ������ ���������� ��� -1").c_str());

	desc = q.GetParametr("�������� ����������");

	//������
	cout << "����� ���������� ������ ������, � ������� ������ ���� ������ ������������.\n";
	int res = q.SendQuestInt("�������� ������ ��������� �����?", { "��", "���" });

	if (res == 1) {
		group_menu g;

		g.ShowGroup(_user);
	}

	id_group = atoi(q.GetParametr("id ������").c_str());

	try {
		db_group group(id_group);
		db_employee *e = db_employee::AddNewEmployee(f, l, m, desc, other_id);
		group.SnapEmployee(e->GetId());
		delete e;
	}
	catch (...) {
		cout << "�� ������� �������� ������ ����������!\n";
		q.WaitPressSay();
	}

	cout << "��������� ��� ������� ��� ��������!\n";
	q.WaitPressSay();
}

void employee_menu::AddNewPhoto()
{
	questions_user q;
	q.ClearConsole();
	ShowInfo();
	cout << "������� id ���������� ��� ���������� ����:";
	int id = SelectEmployee();
	db_employee emp(id);

	cout << "������� ���� � ���� �����, ������� �� ������ ��������:";
	string path;
	cin >> path;

	try {
		face_manager fm;
		fm.AddNewFace(1, "", "", "");
		try {
			fm.AddNewPhoto(1, path);
		}
		catch (std::exception e) {
			cout << e.what();
			throw e;
		}

		face f = fm.GetFaceForId(1);
		db_face::AddNewFace(f.GetFloatDescript(0), emp.GetId());
	}
	catch (...) {
		cout << "�� ������� �������� ����!\n";
		q.WaitPressSay();
		return;
	}
	cout << "���� ���� ������� ���������\n";
	q.WaitPressSay();
}

void employee_menu::EditEmployee()
{
	questions_user q;
	//����� ����������
	q.ClearConsole();
	ShowInfo();
	cout << "������� id ���������� ��� ���������:";
	int id = SelectEmployee();
	db_employee emp(id);

	q.ClearConsole();
	ShowOne(emp);

	string f, l, m, desc;
	int other_id = -1;

	f = q.GetParametr("����� ���");
	l = q.GetParametr("����� �������");
	m = q.GetParametr("����� ��������");
	desc = q.GetParametr("����������");
	other_id = atoi(q.GetParametr("id � ������ ������� ��� -1").c_str());

	try {
		
		emp.SetFirstName(f);
		emp.SetLastName(l);
		emp.SetMidName(m);
		emp.SetDescrInfo(desc);
		emp.SetOtherId(other_id);
	}
	catch (...) {
		cout << "�� ������� �������� ���������� � ����������!\n";
		q.WaitPressSay();
		return;
	}

	q.ClearConsole();
	ShowOne(emp);
	cout << "���������� ������� ��������!\n";
	q.WaitPressSay();
}

void employee_menu::EditeEmployeeGroup(int id)
{
	questions_user q;
	q.ClearConsole();

	ShowInfoAndGroup();

	cout << "�������� ���������� ��� ���������:";
	int res =  SelectEmployee();
	db_employee e(res);

	//����, ��� ������� ��������
	while (true) {
		q.ClearConsole();
		ShowOne(e);
		ShowOneGroup(e);

		cout << endl;
		//�����, ������� ��� �������� ������
		int action = q.SendQuestInt("�������� ��������", { "��������", "�������", "�����" });

		//���������� ������
		if (action == 1) {
			AddGroup(e);
		}

		//�������� ������
		if (action == 2) {
			DeletGroup(e);
		}

		//�����
		if (action == 3)
			break;
	}
}

void employee_menu::AddGroup(db_employee emp)
{
	group_menu gm;
	gm.ShowAllGroup();
	questions_user q;
	cout << "������� id ������ ��� ����������:";
	int id_g = gm.SelectGroup();
	db_group g(id_g);
	try {
		g.SnapEmployee(emp.GetId());
	}
	catch (...) {
		cout << "�� ������� �������� ������!\n";
		q.WaitPressSay();
		return;
	}
	
	cout << "������ ���� �������!\n";
	q.WaitPressSay();
	
}

void employee_menu::DeletGroup(db_employee emp)
{
	questions_user q;
	ShowOneGroup(emp);
	cout << "������� id ������ ��� ��������:";
	group_menu gm;
	int id_g = gm.SelectGroup();
	db_group g(id_g);
	try {
		g.UnLinkEmployee(emp.GetId());
	}
	catch (...) {
		cout << "�� ������� ������� ������!\n";
		q.WaitPressSay();
		return;
	}
	cout << "������ ���� ������� �������!\n";
	q.WaitPressSay();
}

void employee_menu::DeleteEmployee()
{
	questions_user q;
	q.ClearConsole();

	ShowInfo();

	cout << "������� id ���������� ��� ��������:";

	int res = SelectEmployee();

	try {
		db_employee emp(res);
		emp.Delete();
	}
	catch (...) {
		cout << "�� ������� ������� ���������� � ����������!\n";
		q.WaitPressSay();
		return;
	}
	cout << "���������� ���� �������\n";
	q.WaitPressSay();
	return;
}
