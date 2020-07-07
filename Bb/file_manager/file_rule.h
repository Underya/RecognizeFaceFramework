#pragma once
#include "file_parametr.h"
#include <list>
#include <vector>
#include <map>

//���������� � �������
struct FILEMANAGER_API rule
{
	//������������� �������
	int id;

	//�������� �������
	std::string name;

	//�������� �������
	std::string description;

};

//������� ��� ����� ����, � ��� ��� ��� ��� �������
class FILEMANAGER_API file_rule :
	public file_parametr
{
public:

	//�������� �������, � ����������� �� ���������� �����
	file_rule(std::string file_name);

	//�������� �������, � ����������� �� �����
	file_rule();

	~file_rule();

	//������ ���� ������
	std::list<rule> GetAllRule();

	//���������� ������ �������
	void AddRule(std::string name, std::string desc = "", int id = -1);

	//������� ������� � ���������� ������
	void LinkWithCamera(int id_rule, int id_camera);

	//������� ����� ����� �������� � �������
	void UnLinkWithCamera(int id_rule, int id_camera);

	//������� ����� ����� �������� � ��������� ���������� (��� ����� ������� � ��������)
	void LinkWithPremise(int id_rule, int id_premise);

	//������� ����� ����� �������� � ���������� ����������
	void UnLinkWithPremise(int id_rule, int id_premise);

	//�������� ��� �������, ��������� � ������� ��� ����� ���������
	std::vector<rule> GetRuleWithCamera(int id_camera);

	//�������� ��� �������, ��������� � ����������, ��� ����� �������� � �������
	std::vector<rule> GetRuleWirhPremuse(int id_primese);

	//��������� ������� � �������� id
	rule GetRule(int id);

	//��������, ���������� �� ������� � ����� �� ���������������
	bool CheckRuleExist(int id_rule);

protected:

	

	//�������� �������� � ������
	void AddIdToVector(std::vector<int> &vector, int id);

	//������ id �� �������
	void DeleteIdInVector(std::vector<int>& vector, int id);

	std::vector<rule> GetRulleFromMap(std::map<int, std::vector<int>> map, int id);

	//������ ���� ������
	std::list<rule> rules;

	//����: ������������� �������, � ������ ��������� � ��� �����
	std::map<int, std::vector<int>> _camera;

	//����: ������������� �������, � ������ ��������� � ��� ���������
	std::map<int, std::vector<int>> _premise;

	//��������� ����� ����������� ����� � ���� ������
	std::string GetContentList() override;

	//������ ����������� ����� � ������������� �������
	void ReciveInfo();

};

