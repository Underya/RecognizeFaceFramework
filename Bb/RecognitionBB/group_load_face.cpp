
#include "group_load_face.h"

group_load_face::group_load_face()
{
	_this_type = "group type";
}

group_load_face::group_load_face(std::vector<std::pair<int, std::string>> vect)
{
	_this_type = "group type";
	//Разбор вектора, и добалвения его в список групп
	for (auto iter = vect.begin(); iter != vect.end(); iter++) {
		AddGroup(iter->first, iter->second);
	}
}

int group_load_face::GetCount()
{
	return groups.size();
}


void group_load_face::AddGroup(int id, std::string name)
{
	//Добавление нового элемента
	groups.push_back(std::pair<int, std::string>(id, name));
}

std::vector<std::pair<int, std::string>> group_load_face::GetGroups()
{
	return groups;
}

