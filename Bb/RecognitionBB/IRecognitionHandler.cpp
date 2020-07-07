#include "IRecognitionHandler.h"

void IRecognitionHandler::RecognitionFace(face face, information_camera camera_info)
{
	//Формирование параметров в более удобном для пользователя виде
	//И передача их в перегружаемую функцию
	list_group groups;
	if (face.GetLoad() != NULL) {
		if (face.GetLoad()->GetType() == "group type") {
			group_load_face* glf = (group_load_face*)face.GetLoad();
			groups = glf->GetGroups();
		} else {
		}
	} else {
	}
	HandlerFace(_id_cam, premieses, face, _listRules, groups, camera_info);
}

void IRecognitionHandler::EndWork()
{

}



void IRecognitionHandler::SetId(int id_cam) {
	_id_cam = id_cam;
}

void IRecognitionHandler::SetPremisesList(std::vector<std::string> listPremise)
{
	premieses = listPremise;
}
