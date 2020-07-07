
#include "pch.h"
#include "rule_link.h"

rule_link::rule_link()
{
	rule_camera = *(new rule_link_obj::rule_link_obj("link_camera.txt"));
	rule_premise = *(new rule_link_obj::rule_link_obj("link_premise.txt"));
}

rule_link::~rule_link()
{
	Save();
}

void rule_link::Save()
{
	rule_camera.Save();
	rule_premise.Save();
}

void rule_link::AddCameraLink(int id_rule, int id_camera)
{
	rule_camera.AddNewLink(id_rule, id_camera);
}

void rule_link::AddPremiseLink(int id_rule, int id_premise)
{
	rule_premise.AddNewLink(id_rule, id_premise);
}

void rule_link::DeleteCameraLink(int id_rule, int id_camera)
{
	rule_camera.DeletLink(id_rule, id_camera);
}

void rule_link::DeletePremiseLink(int id_rule, int id_premise)
{
	rule_premise.DeletLink(id_rule, id_premise);
}

std::vector<int> rule_link::GetAllRule(int id_camera, int id_premise, file_premise* all_premise)
{
	std::vector<int> allRuleId;

	//все id с камеры
	allRuleId = rule_camera.GetLinkedId(id_camera);

	//Если камера привязана к помещению
	while (id_premise != -1) {
		//Поиск в списке указанного помещения
		premise p;
		p = all_premise->GetPremise(id_premise);
		//Поиск связанных с ним правил
		std::vector<int> premiseid = rule_premise.GetLinkedId(p.id);
		//Сложение двух векторов без повторений
		allRuleId = SummVectorNotRepet(allRuleId, premiseid);
		//Переход к родителю помещения
		id_premise = p.id_parent;
	}

	return allRuleId;
}

std::vector<int> rule_link::SummVectorNotRepet(std::vector<int> v1, std::vector<int> v2)
{
	//Результатирующий вектор
	std::vector<int> result;

	//Первый вектор копируется полностью
	for (auto iter = v1.begin(); iter != v1.end(); iter++) result.push_back(*iter);

	//Из второго вектора выибраются только те элементы, которых нет в первом векторе
	for (auto obj2 = v2.begin(); obj2 != v2.end(); obj2++) {
		//Флаг, указывающий, что значение из второго вектора не повторилось в первом
		bool Repeat = false;
		for (auto obj1 = v1.begin(); obj1 != v1.end(); obj1++) {
			if (*obj1 == *obj2) {
				Repeat = true;
				break;
			}
		}
		//Если не было повтора
		if (!Repeat) result.push_back(*obj2);
	}

	return result;
}

/*
std::vector<int> rule_link::GetAllRuleLink(int id_rule)
{
	std::vector<int> allRuleId;

	//все id с камеры
	allRuleId = rule_camera.GetLinkedId(id_rule);

	//Добавление id со всех помещений, но без повторов
	std::vector<int> RulePremiseId = rule_premise.GetLinkedId(id_rule);

	bool repeatid = false;

	//Проход по всем id связей с помещением
	for (auto id_premise = RulePremiseId.begin(); id_premise != RulePremiseId.end(); id_premise++) {
		//Указание, что для данного id нет повтора
		repeatid = false;
		//Поиск повторяющихся id с правилами камеры
		for (auto id_cam = allRuleId.begin(); id_cam != allRuleId.end(); id_cam++) {
			//Если повтор 
			if (*id_cam == *id_premise) {
				//Указание, что найден повтор
				repeatid = true;
				//Конце этого цикла
				break;
			}
		}

		//Если не найден повтор
		if (!repeatid) {
			//Добавление id в список всех id
			allRuleId.push_back(*id_premise);
		}
	}

	return allRuleId;
}
*/
