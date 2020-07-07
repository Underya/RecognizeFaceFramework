#pragma once
#include "file_parametr.h"
#include <list>
#include <vector>
#include <map>

//Информация о правиле
struct FILEMANAGER_API rule
{
	//Идентификатор правила
	int id;

	//Название правила
	std::string name;

	//Описание правила
	std::string description;

};

//Правила без учёта того, с кем или чем они связаны
class FILEMANAGER_API file_rule :
	public file_parametr
{
public:

	//Создание объекта, с информацией из указанного файла
	file_rule(std::string file_name);

	//Создание объекта, с информацией из файла
	file_rule();

	~file_rule();

	//Список всех правил
	std::list<rule> GetAllRule();

	//Добавление нового правила
	void AddRule(std::string name, std::string desc = "", int id = -1);

	//Связать правило и конкретную камеру
	void LinkWithCamera(int id_rule, int id_camera);

	//Удалить связь между правилом и камерой
	void UnLinkWithCamera(int id_rule, int id_camera);

	//Создать связь между правилом и кокретным помещением (без учёта предков и потомков)
	void LinkWithPremise(int id_rule, int id_premise);

	//Удалить связь между правилом и конкретным помещением
	void UnLinkWithPremise(int id_rule, int id_premise);

	//Получить все правила, связанные с камерой БЕЗ учёта помещений
	std::vector<rule> GetRuleWithCamera(int id_camera);

	//Получить все правила, связанные с помещением, БЕЗ учёта потомков и предков
	std::vector<rule> GetRuleWirhPremuse(int id_primese);

	//Получение правила с указаным id
	rule GetRule(int id);

	//Проверка, существует ли правило с таким же идентификатором
	bool CheckRuleExist(int id_rule);

protected:

	

	//Добавить значение в вектор
	void AddIdToVector(std::vector<int> &vector, int id);

	//Убрать id из вектора
	void DeleteIdInVector(std::vector<int>& vector, int id);

	std::vector<rule> GetRulleFromMap(std::map<int, std::vector<int>> map, int id);

	//Список всех правил
	std::list<rule> rules;

	//Пары: идентификатор правила, и список связанных с ним камер
	std::map<int, std::vector<int>> _camera;

	//Пары: идентификатор правила, и список связанных с ним помещений
	std::map<int, std::vector<int>> _premise;

	//Получение всего содержимого файла в виде строки
	std::string GetContentList() override;

	//Чтение содрежимого файла и инициализация объекта
	void ReciveInfo();

};

