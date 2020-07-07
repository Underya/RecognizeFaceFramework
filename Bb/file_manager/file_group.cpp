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
	//Если такого ключа не в массиве, необходимо выкинуть ошибку
	if (!groups_info.count(id_group))
		throw std::exception("Exception! No such group");
	return groups_info[id_group];
}

std::vector<int> file_group::GetGroupFromId(int id_employee)
{
	//В этом векторе находятся все группы, в которых состоит данный сотрудник
	std::vector<int> id_group;

	//Цикл по всем группам
	for (auto iter = groups_info.begin(); iter != groups_info.end(); iter++) {
		//Каждый элемент - это пара из id списка, и вектора идентификаторов сотрудников
		//Если в этом векторе есть искомый идентификатор сотрудника - то надо добавить id элемента в список id_group
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
	//Добавление новой группы
	//Если не был передан параметр id
	if (id == -1) {
		//Ипользование нового
		id = this->GetNewId();
	}
	vector<int> v;
	//Добавление информации в карты
	groups_info[id] = v;
	groups_names[id] = group_name;
	groups_desc[id] = group_desc;
	return id;
}

void file_group::AddNewSnap(int id_group, int id_employee)
{
	//Проверка, нет ли уже информации о том, что такой сотрудник привязан к такой группе
	if (HasIdInVec(groups_info[id_group], id_employee)) {
		//Если есть, то необходимо вернуть ошибку
		throw std::exception("Exception! This employee is already associated with the group");
	}
	vector<int> v;
	v = groups_info[id_group];
	v.push_back(id_employee);
	groups_info[id_group] = v;
}

void file_group::DeleteSnap(int id_group, int id_employee)
{
	//Для того, что бы удалить элемент из вектора, просто собираем новый вектор
	//Добавляя все элементы из старого, кроме того, который надо удалить
	vector<int> new_id_employee_vector;
	vector<int> old_vector = groups_info[id_group];

	for (auto iter = old_vector.begin(); iter != old_vector.end(); iter++) {
		//Заполнение вектора, всеми элементами, кроме того, который надо удалить
		if (*iter != id_employee) {
			new_id_employee_vector.push_back(*iter);
		}
	}

	//Замена старого вектора новым
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
	//Переменные для чтения содержимого файла
	string line, name, value;
	while (std::getline(*_rFile, line)) {
		//Проверка на слово group
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
		//Добавление нового объекта
		groups_names[id] = name_obj;
		groups_desc[id] = desc_obj;
		std::vector<int> v;
		groups_info[id] = v;
		//Проверка на слово employee:-;
		std::getline(*_rFile, line);
		GetValueForString(line, name, value);
		if (name != "employee" || value != "-") throw new exception("Error! Corrupted File! file_group/ParseFile!\n");
		std::getline(*_rFile, line);
		while (line != "end") {
			//Значит здесь id employee, который надо добавить
			v.push_back(atoi(line.c_str()));
			std::getline(*_rFile, line);
		}
		//Добавление вектора с сотрудниками
		groups_info[id] = v;
		this->SetLastUsId(id);
	}
	CloseFile();
}

string file_group::GetContentList()
{
	//Создание суммарного представления
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

