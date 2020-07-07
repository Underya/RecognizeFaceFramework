
#include "pch.h"
#include "file_premise.h"
using namespace std;

file_premise::file_premise(std::string file_name) : file_parametr(file_name)
{
	ReceiveInfo();
}

file_premise::file_premise() : file_parametr("promise_info.txt")
{
	ReceiveInfo();
}

file_premise::~file_premise()
{
	
}

void file_premise::AddNewPremise(string name, string desc, int id, int id_parent)
{
	//�������� ����� ���������
	premise p;
	//� ���������� ���������� � ���
	p.name = name;
	p.description = desc;
	p.id = id;
	//���� �� ������ id
	if (id == -1) {
		p.id = GetNewId();
	}
	//�������� ��������
	p.id_parent = id_parent;
	
	//���������� ��������� � ������
	_premises.push_back(p);
}

std::vector<premise> file_premise::GetAllPremise()
{
	return _premises;
}

premise file_premise::GetPremise(int id)
{
	for (auto iter = _premises.begin(); iter != _premises.end(); iter++) {
		if (iter->id == id) {
			return *iter;
		}
	}

	//���� �� ������� ����� ���������
	throw std::exception("Exception! There is no such room");
}

void file_premise::EditPremisse(int id, std::string name, std::string desc, int id_parent)
{
	//����� ������ � �����������
	vector<premise> new_vector;
	//������� ����� ������� � �����������, ���� �� �������� �� ������
	for (auto iter = _premises.begin(); iter != _premises.end(); iter++) {
		//�������� ����������� � ����� ������
		if (iter->id != id) {
			new_vector.push_back(*iter);
		}
		else {
			//���� ���������� �� ������, �� ���������� ������� ����� ������� � ������� ����������
			premise new_premise;
			new_premise.id = id;
			new_premise.name = name;
			new_premise.description = desc;
			new_premise.id_parent = id_parent;
			new_vector.push_back(new_premise);
		}
	}
	
	//������ �������
	_premises = new_vector;
}

std::vector<premise> file_premise::GetAllParent(int id_premise)
{
	//������ �� ����� ��������
	vector<premise> parent;
	premise current = GetPremise(id_premise);
	while (current.id_parent != -1) {
		current = GetPremise(current.id_parent);
		parent.push_back(current);
	}

	return parent;
}

std::vector<premise> file_premise::GetAllParent(premise premis)
{
	return GetAllParent(premis.id);
}

std::vector<premise> file_premise::GetPremiseWithParrent(int id_premise)
{
	//��� ���������
	vector<premise> premises;
	//���������� �������� ���������
	premises.push_back(GetPremise(id_premise));
	//��������� ���� �������
	vector<premise> parent = GetAllParent(id_premise);
	for (auto iter = parent.begin(); iter != parent.end(); iter++) {
		premises.push_back(*iter);
	}

	return premises;
}

void file_premise::DeletePremise(int id)
{
	//����� ������ � �����������
	vector<premise> new_vector;
	//������� ����� ������� � �����������, ���� �� �������� �� ������
	for (auto iter = _premises.begin(); iter != _premises.end(); iter++) {
		//��� ����� ����������� � �������
		if (iter->id != id) {
			new_vector.push_back(*iter);
		}
	}

	//������ �������
	_premises = new_vector;
}

string file_premise::GetContentList()
{
	//���������� ��� ���������� ��������
	string result = "";

	//���� �� ���� ���������
	//� ���������� ���������� � ��� � ����
	for (auto iter = _premises.begin(); iter != _premises.end(); iter++) {
		result += "id:" + to_string(iter->id) + ";\n";
		result += "name:" + iter->name + ";\n";
		result += "desc:" +  iter->description + ";\n";
		result += "id_parent:" + to_string(iter->id_parent) + ";\n";
	}

	return result;
}

void file_premise::ReceiveInfo()
{
	//������ ���������� �� �����
	this->OpenFileForRead();
	//���������� ��� ������ ����������� �����
	string line, name, value;
	while (std::getline(*_rFile, line)) {
		premise pr;
		//������ ������
		//�������� ���������
		//���������� � ����������
		GetValueForString(line, name, value);
		if (name != "id") throw new exception("Exception! File Corrupted! Location: file_promuse/ReciveInfo\n");
		pr.id = atoi(value.c_str());
		//name
		std::getline(*_rFile, line);
		GetValueForString(line, name, value);
		if (name != "name") throw new exception("Exception! File Corrupted! Location: file_promuse/ReciveInfo\n");
		pr.name = value;
		//desc
		std::getline(*_rFile, line);
		GetValueForString(line, name, value);
		if (name != "desc") throw new exception("Exception! File Corrupted! Location: file_promuse/ReciveInfo\n");
		pr.description = value;
		//id_parent
		std::getline(*_rFile, line);
		GetValueForString(line, name, value);
		if (name != "id_parent") throw new exception("Exception! File Corrupted! Location: file_promuse/ReciveInfo\n");
		pr.id_parent = atoi(value.c_str());

		//���������� ���������� � ���������
		_premises.push_back(pr);
		SetLastUsId(pr.id);
	}

	CloseFile();
}

//������ ���������� � �����
//id:value;
//name:value;
//desc:value;
//id_parent:value;