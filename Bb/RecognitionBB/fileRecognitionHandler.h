
#pragma once
#include "IRecognitionHandler.h"
#include "timer_list.h"
#include "file_recognition_coder.h"

class RECOGNITIONBB_API fileRecognitionHandler :
	public IRecognitionHandler
{
public:

	//Конструктор по умолчанию
	fileRecognitionHandler(std::string fileName, int id_camera, double second);

	~fileRecognitionHandler();

	//Обработка распознанных лиц
	void HandlerFace(int cam_id, std::vector<std::string> premise_name, face face, list_rules rules, list_group group, information_camera camera_info) override;

	//Список правил, которые связаны с текущей камерой
	void SetRulesList(list_rules listRules);

	void EndWork() override;

private:
	
	//Список, который отслеживат частосту сообщений о распозновании
	timer_list<int> *tlist;

	//Через этот объект осуществуляется работа с файлом
	file_recognition_coder *frr = NULL;

	//Сохрание информации о камере
	int _id_camera = -1;
};

