#include "work_class.h"
#include "questions_user.h"
#include "..//RecognitionBB/PremiseCheck.h"
#include "receive_menu.h"

void work_class::Start(db_user* user)
{
	questions_user q;
	q.ClearConsole();
	cout << "������ ������ ����������...\n";
	_user = user;
	//������������ � ������ ������
	StartWork();
	//������� � ����
	std::this_thread::sleep_for(std::chrono::seconds(2));
	Menu();

}

void work_class::Menu()
{
	questions_user q;
	try {
		while (true) {
			q.ClearConsole();
			int res = q.SendQuestInt("��������� ��������", { "������ �����", "��������� �����", "���������", "����������"
				, "�����" });
			if (res == 1) {
				bb.m10_startShow();
			}

			if (res == 2) {
				bb.m10_endShow();
			}

			if (res == 3) {
				ShowPremiseEmployee();
				q.WaitPressSay();
			}

			if (res == 4) {
				ShowEmployeePremise();
				q.WaitPressSay();
			}

			//�����
			if (res == 5) {
				exit(1);
			}
		}
	}
	catch (...) {
		std::cout << "��������� ����������� ������!";
	}
}


void work_class::ShowPremiseEmployee()
{
	PremiseCheck pc;

	auto info = pc.GetPremiseEmplyee();

	string space = "   ";

	for (auto premise = info.begin(); premise != info.end(); premise++) {
		cout << "���������:" << premise->first << ":\n";
		auto vec_emp = premise->second;
		for (auto emp = vec_emp.begin(); emp != vec_emp.end(); emp++) {
			cout << space << *emp << "\n";
		}
		cout << "\n";
	}
}

void work_class::ShowEmployeePremise()
{
	PremiseCheck pc;
	std::vector<std::pair< db_employee, std::string>> vector = pc.GetEmployeePremise();

	for (auto iter = vector.begin(); iter != vector.end(); iter++) {
		db_employee employee = iter->first;
		cout << employee.GetFirstName() << " " << employee.GetLastName() << " " << employee.GetMidleName() << ":";
		cout << iter->second << "\n";
	}
}



void work_class::StartWork()
{
	//����������� � ������� ������������
	bb.m2_Authorization(_user->GetName());
	//�������� ����� � �����
	bb.m3_LoadGroupAndCamera();
	//�������� ����������� � ���
	bb.m4_LoadEmployeeAndFace();
	//�������� ��������������� � ������������ 
	bb.m5_CreateRecognizerAndHandler(1, 10.0, 20.0);
	//��������� ����� ������ �����������
	recipients_list rl;
	//���������� �����������
	bb.m6_AddReceiver(rl.GetFileReceiver());
	//������ �������
	bb.m8_Start();
}


