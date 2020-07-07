#include "export_menu.h"
//������
#include "../db/db_group.h"
#include "..//file_manager/file_group.h"
//������������
#include "..//db///db_employee.h"
#include "..//file_manager/file_faces.h"
//������
#include "..//db/db_vcam.h"
#include "..//file_manager/vcam_file_manager.h"
//���������
#include "..//db/db_premise.h"
#include "..///file_manager/file_premise.h"
//�������
#include "..//db/rules_collection.h"
#include "..//file_manager/rule_link.h"
#include "..//file_manager/file_rule.h"

using std::vector;
using std::pair;
using std::string;
using std::list;
using std::cout;

void export_menu::Export(db_user* user)
{
	//���������� ����������
	_user = user;
	
	//����� ����������
	questions_user qu;
	qu.ClearConsole();
	
	cout << "������� �����;\n";
	try {
		//�������� ���������� � ������
		Clear_Info();

		//������� ������������
		Export_employee();
		cout << "�������������� ������;\n";
		//������� �����
		Export_group();
		cout << "�������������� ���������� � ����;\n";
		//������� �����
		Export_camera();
		cout << "�������������� ������;\n";
		//������� ���������
		Export_premise();
		cout << "�������������� ���������;\n";
		//������� ������
		Export_rules();
		cout << "��������������� �������;\n";

		qu.WaitPressSay();
	}
	catch (...) {
		cout << "��������� ����������� ������!";
	}
}

void export_menu::Export_employee()
{
	//�������� ���� �����
	db_group::LoadedAllGroup(_user->GetId());
	//�������� ���� ��������� ������������
	vector<db_employee>* vector_emp = db_employee::GetEmployeeWithCondition(db_group::GetAllGroup());
	
	file_faces ff;

	//�������� ���� ����������
	for (auto iter = vector_emp->begin(); iter != vector_emp->end(); iter++) {

		//������ ��������
		list<db_face> vector_face = iter->GetListDescr();
		//������� � id � ������������������ ���������
		vector<string> vec_desc;
		vector<int> vec_id;
		for (auto desc = vector_face.begin(); desc != vector_face.end(); desc++) {
			vec_desc.push_back(Transform_vector_to_string(desc->GetDescriptor()));
			vec_id.push_back(desc->GetId());
		}


		ff.AddFace(iter->GetId(), iter->GetFirstName(), iter->GetLastName(), iter->GetMidleName(), iter->GetDescrInfo(), vec_desc, vec_id, iter->GetOtherId());
	}
	//���������� ���������� � ���������
	ff.Save();
}

void export_menu::Export_group()
{
	file_group fg;
	//�������� �����
	db_group::LoadedAllGroup(_user->GetId());
	//��������� �� ����
	vector<db_group> vector_group = db_group::GetAllGroup();

	//���������� ���� ����� � �����
	for (auto iter = vector_group.begin(); iter != vector_group.end(); iter++) {
		fg.AddNewGroup(iter->GetName(), iter->GetDesc(), iter->GetId());

		//��� ������ ������ ���������� ����� ���� �����������
		vector<db_employee> *vec_emp = db_employee::GetEmployeeWithCondition(*iter);

		//���������� ������ � ������������
		for (auto employee = vec_emp->begin(); employee != vec_emp->end(); employee++) {
			fg.AddNewSnap(iter->GetId(), employee->GetId());
		}
	}
	//���������� ����������
	fg.Save();

}

void export_menu::Export_camera()
{
	//�������� ���� �����
	vector<db_vcam> vector_camera = db_vcam::GetAllLinkVcam(*_user);
	//����� ��� ���������� ���������� � �����
	vcam_file_manager vfm;

	//���������� ����������
	for (auto iter = vector_camera.begin(); iter != vector_camera.end(); iter++) {
		vfm.AddNewCamera(iter->GetAddress(), iter->GetDescription(), iter->GetPremise().GetId(), iter->GetPosition(), iter->GetId());
	}

	vfm.Save();
}

void export_menu::Export_premise()
{
	//�������� ����� ��� ���������� ���������
	file_premise fp;

	//��������� ������� � ������������� ����� ������
	vector<db_vcam> vector_camera = db_vcam::GetAllLinkVcam(*_user);

	//��� ������ ����� ���������� ��������, ���� �� ���������
	for (auto camera = vector_camera.begin(); camera != vector_camera.end(); camera++) {
		//���� � ������ ��� ��������� - ����������
		if (camera->GetPremise().GetId() == -1) continue;

		//���� ���� ���������, �� � �� ����������� ����������
		db_premise premise = camera->GetPremise();
		fp.AddNewPremise(premise.GetName(), premise.GetDesc(), premise.GetId(), premise.GetIdParent());
		
		vector<db_premise> vec_premise = premise.GetAllParent();
		//���������� �������
		for (auto premise = vec_premise.begin(); premise != vec_premise.end(); premise++) {
			fp.AddNewPremise(premise->GetName(), premise->GetDesc(), premise->GetId(), premise->GetIdParent());
		}
	}

	fp.Save();
}

void export_menu::Export_rules()
{
	file_rule fr;
	rule_link rl;
	rules_collection rc;

	//��������� ���� �����
	vector<db_vcam> vector_camera = db_vcam::GetAllLinkVcam(*_user);

	//������ ���� ����������
	for (auto camera = vector_camera.begin(); camera != vector_camera.end(); camera++) {
		//������������� ������ �������
		rc = rules_collection();
		//��������� ���� ����������, ��������� ������ � �������
		rc.AppendRule(*camera);

		//���������� ������ � ���������� � ���
		list<db_rule> list_rule = rc.GetAllRuleFull();
		for (auto rule = list_rule.begin(); rule != list_rule.end(); rule++) {

			//���� ������ ������� �� ����
			if (!fr.CheckRuleExist(rule->GetId())) {
				//�� ��� ���������� ��������
				fr.AddRule(rule->GetName(), rule->GetDesc(), rule->GetId());
			}

			//���������� �����
			rl.AddCameraLink(camera->GetId(), rule->GetId());
		}

		//��������� ���� ���������, ��������� � ������ �������
		vector<db_premise> list_premise = camera->GetPremise().GetAllParent();
		//���������� ������ ���������
		list_premise.push_back(camera->GetPremise());

		//��� ������� ��������� ����������� ������� � ����� � ����� ����������
		for (auto premise = list_premise.begin(); premise != list_premise.end(); premise++) {
			//�������� ���������� ��� ���� ���������� ��������
			rc = rules_collection();
			//��������� ������, ��������� � ������ ����������
			rc.AppendRuleForOnePremmis(*premise);

			//��������� ������
			list<db_rule> list_rule_prem = rc.GetAllRuleFull();
			for (auto rule = list_rule_prem.begin(); rule != list_rule_prem.end(); rule++) {
				//���� ��� ������ �������, �� ��� �����������
				if (!fr.CheckRuleExist(rule->GetId())) {
					fr.AddRule(rule->GetName(), rule->GetDesc(), rule->GetId());
				}

				//�������� �����
				rl.AddPremiseLink(premise->GetId(), rule->GetId());
			}

		}

		//���������� ���������� � ��������
		rl.Save();
		//� � ������
		fr.Save();
	}
}

void export_menu::Clear_Info()
{
	file_faces ff;
	ff.ClearFile();
	ff.Save();
	file_rule fr;
	fr.ClearFile();
	fr.Save();
	file_group fg;
	fg.ClearFile();
	fg.Save();
	vcam_file_manager vfm;
	vfm.ClearFile();
	vfm.Save();
	file_premise fp;
	fp.ClearFile();
	fp.Save();
}

std::string export_menu::Transform_vector_to_string(float* desc)
{
	string sdesc = "";

	for (int i = 0; i < 128; i++) {
		sdesc += std::to_string(desc[i]) + " ";
	}

	return sdesc;
}
