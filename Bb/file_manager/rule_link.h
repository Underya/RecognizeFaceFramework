#pragma once
#include "rule_link_obj.h"
#include "file_premise.h"

//Все связи правила с объектами
class FILEMANAGER_API rule_link
{
public:

	rule_link();

	~rule_link();

	//Сохранение информации
	void Save();

	//Привязать камеру к правилу
	void AddCameraLink(int id_rule, int id_camera);

	//Привязать помещение к правилу
	void AddPremiseLink(int id_rule, int id_premise);

	//Удалять связь камеры с правилом
	void DeleteCameraLink(int id_rule, int id_camera);

	//Удалить связь помещения с правилом
	void DeletePremiseLink(int id_rule, int id_premise);

	//Получить все правила, связанные с камерой и помещением
	std::vector<int> GetAllRule(int id_camera, int id_premise = -1, file_premise *all_premise = NULL);

protected:

	//Сложение двух векторов без повторений
	std::vector<int> SummVectorNotRepet(std::vector<int> v1, std::vector<int> v2);

	//Список связей правила с камерами
	rule_link_obj::rule_link_obj rule_camera;

	//Список связи правил с помещениями
	rule_link_obj::rule_link_obj rule_premise;

};

