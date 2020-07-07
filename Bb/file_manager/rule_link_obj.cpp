#include "pch.h"
#include "rule_link_obj.h"

using namespace std;

rule_link_obj::rule_link_obj::rule_link_obj(string file_name) : file_parametr(file_name)
{
	ReceivInfo();
}


rule_link_obj::rule_link_obj::rule_link_obj() : file_parametr("empty")
{
}

rule_link_obj::rule_link_obj::~rule_link_obj()
{
	Save();
}

void rule_link_obj::rule_link_obj::AddNewLink(int rule_id, int id)
{
	pair<int, int> p;
	p.first = rule_id;
	p.second = id;
	linked.push_back(p);
}

void rule_link_obj::rule_link_obj::DeletLink(int rule_id, int id)
{
	for (auto iter = linked.begin(); iter != linked.end(); iter++) {
		//Если нашлось такую же связь
		if (iter->first == rule_id && iter->second == id) {
			//То она удаляется из списка
			linked.remove(*iter);
			return;
		}
	}
}

std::vector<int> rule_link_obj::rule_link_obj::GetLinkedId(int id_obj)
{
	//id правил, связанных с объектом
	std::vector<int> id_rule;

	for (auto iter = linked.begin(); iter != linked.end(); iter++) {
		if (iter->second == id_obj) {
			id_rule.push_back(iter->first);
		}
	}

	return id_rule;
}

void rule_link_obj::rule_link_obj::ReceivInfo()
{
	//Чтение информации из файла
	this->OpenFileForRead();
	//Переменные для чтения содержимого файла
	string line, id_rule, id_obj;
	while (std::getline(*_rFile, line)) {
		GetValueForString(line, id_rule, id_obj);
		pair<int, int> p;
		p.first = atoi(id_rule.c_str());
		p.second = atoi(id_obj.c_str());
		//Добавление в список
		linked.push_back(p);
	}
}

string rule_link_obj::rule_link_obj::GetContentList()
{
	string file_text = "";

	for (auto iter = linked.begin(); iter != linked.end(); iter++) {
		file_text += to_string(iter->first) + ":" + to_string(iter->second) + ";\n";
	}

	return file_text;
}

//Формат файла
//id_rule:id_obj;