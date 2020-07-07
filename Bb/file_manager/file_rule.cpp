#include "pch.h"
#include "file_rule.h"
using namespace std;

file_rule::file_rule(std::string file_name) : file_parametr(file_name)
{
	ReciveInfo();
}

file_rule:: file_rule() : file_parametr("file_rule.txt")
{
	//������ �����
	ReciveInfo();
}

file_rule::~file_rule()
{
}

std::list<rule> file_rule::GetAllRule()
{
	return rules;
}

void file_rule::AddRule(string name, string desc, int id)
{
	//����� ������ �������
	rule r;
	r.name = name;
	r.description = desc;
	//���� �� ��� ����� id 
	if (id == -1) {
		//�� ������������ ����������
		r.id = GetNewId();
	} else {
		r.id = id;
	}
	//���������� ������� � ������
	rules.push_back(r);
}

void file_rule::LinkWithCamera(int id_rule, int id_camera)
{
	if (!CheckRuleExist(id_rule))
		throw exception("Exception! Undifined Rule!");
	vector<int> rule = _camera[id_rule];
	AddIdToVector(rule, id_camera);
	_camera[id_rule] = rule;
}

void file_rule::UnLinkWithCamera(int id_rule, int id_camera)
{
	if (!CheckRuleExist(id_rule))
		throw exception("Exception! Undifined Rule!");
	vector<int> rule = _camera[id_rule];
	DeleteIdInVector(rule, id_camera);
	_camera[id_rule] = rule;
}

void file_rule::LinkWithPremise(int id_rule, int id_premise)
{
	if (!CheckRuleExist(id_rule))
		throw exception("Exception! Undifined Rule!");
	vector<int> rule = _premise[id_rule];
	AddIdToVector(rule, id_premise);
	_premise[id_rule] = rule;
}

void file_rule::UnLinkWithPremise(int id_rule, int id_premise)
{
	if (!CheckRuleExist(id_rule))
		throw exception("Exception! Undifined Rule!");
	vector<int> rule = _premise[id_rule];
	DeleteIdInVector(rule, id_premise);
	_premise[id_rule] = rule;
}

std::vector<rule> file_rule::GetRuleWithCamera(int id_camera)
{
	return GetRulleFromMap(_camera, id_camera);
}

std::vector<rule> file_rule::GetRuleWirhPremuse(int id_primese)
{
	return GetRulleFromMap(_premise, id_primese);
}

rule file_rule::GetRule(int id)
{
	for (auto iter = rules.begin(); iter != rules.end(); iter++) {
		if (iter->id == id) return *iter;
	}

	throw new exception(("Not foun fule with id, where id = " + to_string(id)).c_str());
}

bool file_rule::CheckRuleExist(int id_rule)
{
	for (auto iter = rules.begin(); iter != rules.end(); iter++) {
		if (id_rule == iter->id) return true;
	}
	return false;
}

void file_rule::AddIdToVector(std::vector<int>& _vector, int id)
{
	_vector.push_back(id);
}

void file_rule::DeleteIdInVector(std::vector<int>& _vector, int id)
{
	vector<int> new_vector;
	for (auto iter = new_vector.begin(); iter != new_vector.end(); iter++) {
		if (*iter != id) {
			new_vector.push_back(*iter);
		}
	}

	_vector = new_vector;
}

std::vector<rule> file_rule::GetRulleFromMap(std::map<int, std::vector<int>> map, int id)
{
	vector<rule> vec;

	//���� �� ���� �������� � map
	for (auto iter = map.begin(); iter != map.end(); iter++) {
		//���� � ������� ���� ������� ��
		if (HasIdInVec(iter->second, id)) {
			//�� � ������ ����������� ����� ��������
			vec.push_back(GetRule(iter->first));
		}
	}

	return vec;
}

string file_rule::GetContentList()
{
	string text_file;

	//�������� ���� ������, � ���������� ���������� � ��� � ����
	for (auto iter = rules.begin(); iter != rules.end(); iter++) {
		text_file += "id:" + to_string(iter->id) + ";\n";
		text_file += "name:" + iter->name + ";\n";
		text_file += "desc:" + iter->description + ";\n";

		//���������� � ���� ���������� � ���, � ������ �������� ������� �������
		text_file += "camera:-;\n";
		vector<int> id = _camera[iter->id];
		for (auto iter = id.begin(); iter != id.end(); iter++) {
			text_file += to_string(*iter) + "\n";
		}
		text_file += "end\n";

		//���������� � ���� ���������� � ���, � ������ �������� ������� �������
		text_file += "premise:-;\n";
		vector<int> id_v = _premise[iter->id];
		for (auto iter2 = id_v.begin(); iter2 != id_v.end(); iter2++) {
			text_file += to_string(*iter2) + "\n";
		}
		text_file += "end\n";
	}

	return text_file;
}

void file_rule::ReciveInfo()
{
	//������ ���������� �� �����
	this->OpenFileForRead();
	//���������� ��� ������ ����������� �����
	string line, name, value;
	while (std::getline(*_rFile, line)) {
		rule rul;
		//id
		GetValueForString(line, name, value);
		if (name != "id") throw new exception("EXCEPTION! File corrupted! Location: file_rule/ReciveInfo\n");
		rul.id = atoi(value.c_str());
		//name
		std::getline(*_rFile, line);
		GetValueForString(line, name, value);
		if (name != "name") throw new exception("EXCEPTION! File corrupted! Location: file_rule/ReciveInfo\n");
		rul.name = value;
		//desc
		std::getline(*_rFile, line);
		GetValueForString(line, name, value);
		if (name != "desc") throw new exception("EXCEPTION! File corrupted! Location: file_rule/ReciveInfo\n");
		rul.description = value;

		//��������� �����
		std::getline(*_rFile, line);
		GetValueForString(line, name, value);
		if (name != "camera") throw new exception("EXCEPTION! File corrupted! Location: file_rule/ReciveInfo\n");

		vector<int> camera;
		//������ id �����, ��������� � ���������
		std::getline(*_rFile, line);
		while (line != "end") 
		{
			camera.push_back(atoi(line.c_str()));
			std::getline(*_rFile, line);
		}
		_camera[rul.id] = camera;

		vector<int> premise;
		//������ id �����, ��������� � ���������
		std::getline(*_rFile, line);
		while (line != "end")
		{
			premise.push_back(atoi(line.c_str()));
			std::getline(*_rFile, line);
		}
		_premise[rul.id] = premise;

		//���������� ������� � ������
		rules.push_back(rul);
		//�������� ���������� id
		SetLastUsId(rul.id);
	}
}

//������ �����
//id:value;
//name:value;
//desc:value;
//camera:-;
//id
//...
//id
//end
//premise:-;
//id
//id
//..
//id
//end