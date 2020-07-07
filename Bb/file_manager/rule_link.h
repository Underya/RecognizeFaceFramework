#pragma once
#include "rule_link_obj.h"
#include "file_premise.h"

//��� ����� ������� � ���������
class FILEMANAGER_API rule_link
{
public:

	rule_link();

	~rule_link();

	//���������� ����������
	void Save();

	//��������� ������ � �������
	void AddCameraLink(int id_rule, int id_camera);

	//��������� ��������� � �������
	void AddPremiseLink(int id_rule, int id_premise);

	//������� ����� ������ � ��������
	void DeleteCameraLink(int id_rule, int id_camera);

	//������� ����� ��������� � ��������
	void DeletePremiseLink(int id_rule, int id_premise);

	//�������� ��� �������, ��������� � ������� � ����������
	std::vector<int> GetAllRule(int id_camera, int id_premise = -1, file_premise *all_premise = NULL);

protected:

	//�������� ���� �������� ��� ����������
	std::vector<int> SummVectorNotRepet(std::vector<int> v1, std::vector<int> v2);

	//������ ������ ������� � ��������
	rule_link_obj::rule_link_obj rule_camera;

	//������ ����� ������ � �����������
	rule_link_obj::rule_link_obj rule_premise;

};

