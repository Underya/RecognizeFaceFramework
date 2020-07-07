#include "camera_menu.h"
#include "questions_user.h"

using std::cout;
using std::cin;

void camera_menu::Switch(db_user* user)
{
	//���������� ���������� � ������������
	_user = user;

	questions_user q;

	//���� ��� ������ � ��

	try {
		while (true) {
			q.ClearConsole();
			//����� ���������� � �������
			ShowInformation();

			//������ ��������� ��������
			int res = q.SendQuestInt("�������� ��������", { "�������� �����", "��������", "�������", "�����" });

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


void camera_menu::ShowOneCamera(db_vcam cam)
{
	cout << "id:" << cam.GetId() << " �����:" << cam.GetAddress() << "\n";
	cout << "      ���������:" << cam.GetPremise().GetName() << " �������: " << cam.GetPosition() << "\n";
	if (cam.GetDescription() != "") {
		cout << "      ��������:" << cam.GetDescription() << "\n";
	}
	cout << "-------------------------------------------------------\n\n";
}


void camera_menu::AddNewCamera()
{
	questions_user q;
	string address;
	string position;
	string description;
	//������ � ������������ ����������
	int id_premise;
	address = q.GetParametr("����� ������");
	cout << "������� ������: i - �� �����, o - �� ������, n - �� �������\n";
	position = q.GetParametr("������� ������");
	id_premise = atoi(q.GetParametr("id ��������� ��� -1").c_str());
	description = q.GetParametr("�������� ������:");

	try {
		db_vcam::addNewCamera(address, position, _user->GetId(), id_premise);
	}
	catch (...) {
		cout << "������! �� ������� �������� ������!\n";
		q.WaitPressSay();
		return;
	}
	cout << "������ ������� ���������!\n";
	q.WaitPressSay();
}

void camera_menu::EditCameraInfo()
{
	questions_user q;
	q.ClearConsole();

	ShowInformation();

	cout << "������� id ������, ������� ���� ��������:";
	
	int id = SelectCamera();

	db_vcam cam(id);

	q.ClearConsole();
	
	//����� ���������� � ������, ������� ��������
	ShowOneCamera(cam);

	string address;
	string position;
	string description;
	//������ � ������������ ����������
	int id_premise;
	address = q.GetParametr("����� ����� ������");
	cout << "������� ������: i - �� �����, o - �� ������, n - �� �������\n";
	position = q.GetParametr("������� ������");
	id_premise = atoi(q.GetParametr("id ��������� ��� -1").c_str());
	description = q.GetParametr("�������� ������:");

	try {
		cam.SetAddress(address);
		cam.SetPosition(position);
		cam.SetDescription(description);
		cam.SetPremise(id_premise);
	}
	catch (...) {
		cout << "�� ������� �������� ��������� � ������!\n";
		q.WaitPressSay();
		return;
	}

	cout << "���������� � ������ ������� ��������\n";
	q.WaitPressSay();
	return;
}

void camera_menu::DeletCamera()
{
	questions_user q;
	q.ClearConsole();

	ShowInformation();

	cout << "������� id ������, ������� ���� �������:";
	int id = SelectCamera();

	db_vcam cam(id);
	cam.Delete();

	cout << "���������� � ������ ���� ������� �������!\n";
	q.WaitPressSay();
}

int camera_menu::ParseAnswer(int number)
{
	//���������� ����� ������
	if (number == 1) {
		AddNewCamera();
	}

	if (number == 2) {
		EditCameraInfo();
	}

	if (number == 3) {
		DeletCamera();
	}

	//�����
	if (number == 4)
		return -1;
}

int camera_menu::SelectCamera()
{
	int id = -1;
	while (true)
	{
		string sid;
		cin >> sid;
		id = atoi(sid.c_str());
		//��������, ���� �� ������ � ����� id
		try {
			db_vcam check(id);
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

void camera_menu::ShowInformation()
{
	//��������� ���� ���������� � �������
	std::vector<db_vcam> camers = db_vcam::GetAllLinkVcam(*_user);
	//����� ���������� � �������
	for (auto iter = camers.begin(); iter != camers.end(); iter++) {
		ShowOneCamera(*iter);
	}
	
}
