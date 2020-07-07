
#pragma once
#include <add_load_face.h>
#include <vector>

#ifdef RECOGNITIONBB_EXPORTS
#define RECOGNITIONBB_API __declspec(dllexport)
#else
#define RECOGNITIONBB_API __declspec(dllimport)
#endif



//Иноформация о том, к каким группам принадлежит лицо
class RECOGNITIONBB_API group_load_face :
	public add_load_face
{
public:

	group_load_face();

	group_load_face(std::vector<std::pair<int, std::string>>);

	int GetCount();

	//Добавить новую группу в список
	void AddGroup(int id, std::string name);

	//Получить весь список групп
	std::vector< std::pair<int, std::string>> GetGroups();

private:
	//Информация о группах, к которым принадлежит пользователь
	//int - Это id группы, string - название
	std::vector< std::pair<int, std::string> > groups;
};

