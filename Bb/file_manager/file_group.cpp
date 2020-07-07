#include "pch.h"
#include "file_group.h"
using namespace std;

file_group::file_group(std::string file_name) : file_parametr(file_name)
{
	ParseFile();
}

file_group::file_group() : file_parametr("group_inf.txt")
{
	ParseFile();
}

file_group::~file_group()
{
}

std::vector<int> file_group::GetAllId()
{
	vector<int> v;
	for (auto iter = groups_info.begin(); iter != groups_info.end(); iter++) {
		v.push_back(iter->first);
	}
	return v;
}

std::vector<int> file_group::GetEmployeeId(int id_group)
{
	//���� ������ ����� �� � �������, ���������� �������� ������
	if (!groups_info.count(id_group))
		throw std::exception("Exception! No such group");
	return groups_info[id_group];
}

std::vector<int> file_group::GetGroupFromId(int id_employee)
{
	//� ���� ������� ��������� ��� ������, � ������� ������� ������ ���������
	std::vector<int> id_group;

	//���� �� ���� �������
	for (auto iter = groups_info.begin(); iter != groups_info.end(); iter++) {
		//������ ������� - ��� ���� �� id ������, � ������� ��������������� �����������
		//���� � ���� ������� ���� ������� ������������� ���������� - �� ���� �������� id �������� � ������ id_group
		std::vector<int> id_employes = iter->second;
		if (HasIdInVec(iter->second, id_employee)) {
			id_group.push_back(iter->first);
		}
	}

	return id_group;
}

string file_group::GetName(int id_group)
{
	return groups_names[id_group];
}

string file_group::GetDesc(int id_group)
{
	return groups_desc[id_group];
}

int file_group::AddNewGroup(std::string group_name, std::string group_desc, int id)
{
	//���������� ����� ������
	//���� �� ��� ������� �������� id
	if (id == -1) {
		//������������ ������
		id = this->GetNewId();
	}
	vector<int> v;
	//���������� ���������� � �����
	groups_info[id] = v;
	groups_names[id] = group_name;
	groups_desc[id] = group_desc;
	return id;
}

void file_group::AddNewSnap(int id_group, int id_employee)
{
	//��������, ��� �� ��� ���������� � ���, ��� ����� ��������� �������� � ����� ������
	if (HasIdInVec(groups_info[id_group], id_employee)) {
		//���� ����, �� ���������� ������� ������
		throw std::exception("Exception! This employee is already associated with the group");
	}
	vector<int> v;
	v = groups_info[id_group];
	v.push_back(id_employee);
	groups_info[id_group] = v;
}

void file_group::DeleteSnap(int id_group, int id_employee)
{
	//��� ����, ��� �� ������� ������� �� �������, ������ �������� ����� ������
	//�������� ��� �������� �� �������, ����� ����, ������� ���� �������
	vector<int> new_id_employee_vector;
	vector<int> old_vector = groups_info[id_group];

	for (auto iter = old_vector.begin(); iter != old_vector.end(); iter++) {
		//���������� �������, ����� ����������, ����� ����, ������� ���� �������
		if (*iter != id_employee) {
			new_id_employee_vector.push_back(*iter);
		}
	}

	//������ ������� ������� �����
	groups_info[id_group] = new_id_employee_vector;
}

void file_group::EditGroupInfo(int id, string new_name, string new_desc)
{
	groups_names[id] = new_name;
	groups_desc[id] = new_desc;
}

void file_group::ParseFile()
{
	this->OpenFileForRead();
	//���������� ��� ������ ����������� �����
	string line, name, value;
	while (std::getline(*_rFile, line)) {
		//�������� �� ����� group
		if (line != "group") throw new exception("Error! Corrupted File! file_group/ParseFile!\n");
		//ID
		std::getline(*_rFile, line);
		GetValueForString(line, name, value);
		if(name != "id") throw new exception("Error! Corrupted File! file_group/ParseFile!\n");
		int id = atoi(value.c_str());
		//name
		std::getline(*_rFile, line);
		GetValueForString(line, name, value);
		if (name != "name") throw new exception("Error! Corrupted File! file_group/ParseFile!\n");
		string name_obj = value;
		//description
		std::getline(*_rFile, line);
		GetValueForString(line, name, value);
		if (name != "desc") throw new exception("Error! Corrupted File! file_group/ParseFile!\n");
		string desc_obj = value;
		//���������� ������ �������
		groups_names[id] = name_obj;
		groups_desc[id] = desc_obj;
		std::vector<int> v;
		groups_info[id] = v;
		//�������� �� ����� employee:-;
		std::getline(*_rFile, line);
		GetValueForString(line, name, value);
		if (name != "employee" || value != "-") throw new exception("Error! Corrupted File! file_group/ParseFile!\n");
		std::getline(*_rFile, line);
		while (line != "end") {
			//������ ����� id employee, ������� ���� ��������
			v.push_back(atoi(line.c_str()));
			std::getline(*_rFile, line);
		}
		//���������� ������� � ������������
		groups_info[id] = v;
		this->SetLastUsId(id);
	}
	CloseFile();
}

string file_group::GetContentList()
{
	//�������� ���������� �������������
	string result = "";

	for (auto iter = groups_info.begin(); iter != groups_info.end(); iter++) {
		result += "group\n";
		result += "id:" + to_string(iter->first) + ";\n";
		result += "name:" + groups_names[iter->first] + ";\n";
		result += "desc:" + groups_desc[iter->first] + ";\n";
		result += "employee:-;\n";
		for (auto iter_e = iter->second.begin(); iter_e != iter->second.end(); iter_e++) {
			result += to_string(*iter_e) + "\n";
		}
		result += "end\n";
	}

	return result;
}

