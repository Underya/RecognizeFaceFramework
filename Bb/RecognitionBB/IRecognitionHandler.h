#pragma once

#include <face.h>
#include "group_load_face.h"
#include "..///face_detection/information_camera.h"

//Синоним набора правил
typedef std::vector<std::pair<int, std::string>> list_rules;
typedef std::vector<std::pair<int, std::string>> list_group;

class RECOGNITIONBB_API IRecognitionHandler {
public:

	//Метод, который вызывается при распозновании челоека
	//И передаёт управление в метод, который необходимо реализовать клиенту
	virtual void RecognitionFace(face face, information_camera camera_info);

	//Метод, который необходимо перегрузить
	//Сюда приходит вся информация о посещении
	virtual void HandlerFace(int cam_id, std::vector<std::string> premise_name, face face, list_rules rules, list_group group, information_camera camera_info) = 0;

	//Необходимо установить список правил, связанных с камерой
	virtual void SetRulesList(list_rules listRules) = 0;

	//Метод, через который объекту указывается информация о том, что поток закончил работу
	virtual void EndWork();

	void SetId(int id_cam);

	virtual void SetPremisesList(std::vector<std::string> listPremise);

protected:

	std::vector<std::string> premieses;

	int _id_cam = -1;

	list_rules _listRules;

};

