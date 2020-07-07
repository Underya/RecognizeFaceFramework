#pragma once
#include "file_parametr.h"
#include <vector>
#include <map>


//���������� ������ �����, � ������� ������������� ���������
class FILEMANAGER_API file_group :
	public file_parametr
{
public:

	//������������ ���� ��� �������� ���������� � ��������� �������
	file_group(std::string file_name);

	//������� ������ � ������� ��� � ������ �� ����������� �������
	file_group();

	~file_group();

	//��������� ID ���� ����� � �����
	std::vector<int> GetAllId();

	//��������� ID ���� �����������, ��������� � ���������� �������
	std::vector<int> GetEmployeeId(int id_group);

	//��������� ���� ��������������� ������ �� id ����������
	std::vector<int> GetGroupFromId(int id_employee);

	//�������� ��� ��������� ������
	std::string GetName(int id_group);

	//�������� �������� ��������� ������
	std::string GetDesc(int id_group);

	//���������� ����� ������ � ������
	int AddNewGroup(std::string group_name, std::string group_desc, int id = -1);

	//���������� ����� �����
	void AddNewSnap(int id_group, int id_employee);

	//������� ����� ����� ������� � �����������	
	void DeleteSnap(int id_group, int id_employee);

	//������������� ���������� � ������
	void EditGroupInfo(int id, std::string new_name, std::string new_desc);

private:

	//������������� ������, ��� ������ �������� id ������
	//� ��� ��������� - ������ ��������� � ��� �����������
	std::map<int, std::vector<int>> groups_info;
	//������������� ������ �������� �����
	std::map<int, std::string> groups_desc;
	//������������� ������ �������� �����
	std::map<int, std::string> groups_names;

	//������ � ��������� ���������� �� �����
	void ParseFile();

	std::string GetContentList() override;

};

//������ �����
//group
//id:value;
//name:value;
//desc:value;
//employe:-;
//id_employe0
//id_employe1
//id_employe2
//....
//id_employeN
//end

//id_employe - ����� �� ����