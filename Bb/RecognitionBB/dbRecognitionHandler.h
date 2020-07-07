
#pragma once
#include "pch.h"
#include "IRecognitionHandler.h"
#include "db_manager_parralel.h"
#include "timer_list.h"

//Обработка результатов распознования добавленим информации в БД
class RECOGNITIONBB_API  dbRecognitionHandler:
	public IRecognitionHandler
{
public:

	dbRecognitionHandler(int id_camera, double second = 60.0);

	~dbRecognitionHandler();

	//При распозновании лица добавляет результат в БД
	void HandlerFace(int cam_id, std::vector<std::string> premise_name, face face, list_rules rules, list_group group, information_camera camera_info) override;

	//Установка списка правил, свяазанных с текущей камерой
	void SetRulesList(list_rules listRules);

private:

	//Что бы не заспамливать информацией об распозновании одног и того же человека
	//Информация о его добавлении игнорируется в течении одной минуты

	//Список тех, кто информация о ком была только что добавлена
	//std::list<std::pair<int, clock_t>> timeList;

	timer_list<int> *timeList;

	//Для добавления информации в БД
	db_manager_parralel dbrr;

	//Ид камеры, с которой происходит добавление
	int id_camera;
};

