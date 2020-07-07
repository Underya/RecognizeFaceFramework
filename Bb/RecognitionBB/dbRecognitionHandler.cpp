
#include "dbRecognitionHandler.h"

dbRecognitionHandler::dbRecognitionHandler(int id_camera, double second)
{
	this->id_camera = id_camera;
	timeList = new timer_list<int>(second);
}

dbRecognitionHandler::~dbRecognitionHandler()
{
	delete timeList;
}

void dbRecognitionHandler::HandlerFace(int cam_id, std::vector<std::string> premise_name, face face, list_rules rules, list_group group, information_camera camera_info)
{
	//Проврека, не закончилось ли время для объекта в списк
	if (!timeList->EndTimeToObj(face.GetId())) return;
	//Если закончилось - добавление информации в БД
	dbrr.SaveResetch(face.GetId(), id_camera);
	
}

void dbRecognitionHandler::SetRulesList(list_rules listRules)
{
	_listRules = listRules;
}

