
#include "fileRecognitionHandler.h"
using namespace std;

fileRecognitionHandler::fileRecognitionHandler(std::string fileName, int id_camera, double second)
{
	frr = new file_recognition_coder(fileName);
	_id_camera = id_camera;
	//Новый список 
	tlist = new timer_list<int>(second);
}

fileRecognitionHandler::~fileRecognitionHandler()
{
	frr->Save();
	delete frr;
}

void fileRecognitionHandler::HandlerFace(int cam_id, std::vector<std::string> premise_name, face face, list_rules rules, list_group group, information_camera camera_info)
{
	//Для теста, проверяем, есть ли у объекта - группа
	//Для теста 
	/*if (rules.size() != 0) {
		for (auto iter = rules.begin(); iter != rules.end(); iter++) {
			cout << "\n";
			cout << iter->second << "\n";
		}
	} else {
		cout << "rules == NULL";
	}*/
	//Для теста
	//Если время объект в списке ещё не истекло - закончить выполнение
	if (!tlist->EndTimeToObj(face.GetId())) return;
	//cout << "			face:" << face.GetId() << " access to file\n";
	//Запись информации в файл
	frr->AddRecognition(face.GetId(), _id_camera);
}

void fileRecognitionHandler::SetRulesList(list_rules listRules)
{
	this->_listRules = listRules;
}

void fileRecognitionHandler::EndWork()
{
	std::cout << "File Recogniton EndWorkCalled\n";
	frr->Save();
}
