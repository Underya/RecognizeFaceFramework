
#include "pch.h"
#include "rule_link.h"

rule_link::rule_link()
{
	rule_camera = *(new rule_link_obj::rule_link_obj("link_camera.txt"));
	rule_premise = *(new rule_link_obj::rule_link_obj("link_premise.txt"));
}

rule_link::~rule_link()
{
	Save();
}

void rule_link::Save()
{
	rule_camera.Save();
	rule_premise.Save();
}

void rule_link::AddCameraLink(int id_rule, int id_camera)
{
	rule_camera.AddNewLink(id_rule, id_camera);
}

void rule_link::AddPremiseLink(int id_rule, int id_premise)
{
	rule_premise.AddNewLink(id_rule, id_premise);
}

void rule_link::DeleteCameraLink(int id_rule, int id_camera)
{
	rule_camera.DeletLink(id_rule, id_camera);
}

void rule_link::DeletePremiseLink(int id_rule, int id_premise)
{
	rule_premise.DeletLink(id_rule, id_premise);
}

std::vector<int> rule_link::GetAllRule(int id_camera, int id_premise, file_premise* all_premise)
{
	std::vector<int> allRuleId;

	//��� id � ������
	allRuleId = rule_camera.GetLinkedId(id_camera);

	//���� ������ ��������� � ���������
	while (id_premise != -1) {
		//����� � ������ ���������� ���������
		premise p;
		p = all_premise->GetPremise(id_premise);
		//����� ��������� � ��� ������
		std::vector<int> premiseid = rule_premise.GetLinkedId(p.id);
		//�������� ���� �������� ��� ����������
		allRuleId = SummVectorNotRepet(allRuleId, premiseid);
		//������� � �������� ���������
		id_premise = p.id_parent;
	}

	return allRuleId;
}

std::vector<int> rule_link::SummVectorNotRepet(std::vector<int> v1, std::vector<int> v2)
{
	//���������������� ������
	std::vector<int> result;

	//������ ������ ���������� ���������
	for (auto iter = v1.begin(); iter != v1.end(); iter++) result.push_back(*iter);

	//�� ������� ������� ���������� ������ �� ��������, ������� ��� � ������ �������
	for (auto obj2 = v2.begin(); obj2 != v2.end(); obj2++) {
		//����, �����������, ��� �������� �� ������� ������� �� ����������� � ������
		bool Repeat = false;
		for (auto obj1 = v1.begin(); obj1 != v1.end(); obj1++) {
			if (*obj1 == *obj2) {
				Repeat = true;
				break;
			}
		}
		//���� �� ���� �������
		if (!Repeat) result.push_back(*obj2);
	}

	return result;
}

/*
std::vector<int> rule_link::GetAllRuleLink(int id_rule)
{
	std::vector<int> allRuleId;

	//��� id � ������
	allRuleId = rule_camera.GetLinkedId(id_rule);

	//���������� id �� ���� ���������, �� ��� ��������
	std::vector<int> RulePremiseId = rule_premise.GetLinkedId(id_rule);

	bool repeatid = false;

	//������ �� ���� id ������ � ����������
	for (auto id_premise = RulePremiseId.begin(); id_premise != RulePremiseId.end(); id_premise++) {
		//��������, ��� ��� ������� id ��� �������
		repeatid = false;
		//����� ������������� id � ��������� ������
		for (auto id_cam = allRuleId.begin(); id_cam != allRuleId.end(); id_cam++) {
			//���� ������ 
			if (*id_cam == *id_premise) {
				//��������, ��� ������ ������
				repeatid = true;
				//����� ����� �����
				break;
			}
		}

		//���� �� ������ ������
		if (!repeatid) {
			//���������� id � ������ ���� id
			allRuleId.push_back(*id_premise);
		}
	}

	return allRuleId;
}
*/
