#pragma once
#include "..//db/db_user.h"
#include "..//db/db_rule.h"
#include "..//db/db_vcam.h"

//����, ����� ������� ���������� �������������� � ���������
class rule_menu
{
public:
	
	//������������� � ��� ����
	void Switch(db_user* user);

protected:

	//������ ������� ������������
	int ParseAnswer(int number);

	//������� ���������� �� ����� �������
	void ShowOne(db_rule rule);

	//�������� ��� ��������� � ������ ������������� �������
	void ShowLink(db_user* _user);

	//�������� ��� ������ ������� ��� ������ 
	void ShowRuleForCamera(db_vcam cam);

	//�������� ��� �������
	void ShowAll();

	//�������� ��� �������, ��������� � ��������
	void ShowLinkCam();

	//����� ����������, ��������� � ���������� ����������
	void ShowLinkPremise();

	//�������� ������
	void AddRule();

	//����� �������, ������������� � ��
	int SelectRule();

	//�������� ���������� � �������
	void EditRule();

	//�������� ���������� �� ����� � �����������
	void EditRulePremise();

	//�������� ���������� � ����� � ������
	void EditRuleCamera();

	//�������� ������� � ��������� ������
	void AppendRuleCamera(int id_cam);

	//������� � ��������� ������ �������
	void DeleteRuleCamera(int id_cam);

	//�������� ������� ������ ��� �������� ���������
	void ShowRulePremiseNotParrent();

	//������� � �������� ������� ��� ����������� ���������
	void AppendRulePremise(db_premise prem);

	//������� � ������ � ���������� ��������� �������
	void DeleteRulePremise(db_premise prem);

	db_user* _user = NULL;
};

