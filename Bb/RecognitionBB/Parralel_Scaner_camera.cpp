
#include "Parralel_Scaner_camera.h"

Parralel_Scaner_camera::Parralel_Scaner_camera(std::string Path, information_camera information)
{
	this->path = Path;
	_information = information;
	SetId(information.GetId());
}

Parralel_Scaner_camera::Parralel_Scaner_camera(int num, information_camera information)
{
	this->_numer_cam = num;
	_information = information;
	SetId(information.GetId());
}

void Parralel_Scaner_camera::SetDetecter(Detecter* detecter)
{
	_detecter = detecter;
}

void Parralel_Scaner_camera::SetRecognitor(IRecognitor* recognitor)
{
	_recognitor = recognitor;
	_recognitor->_id_cam = _id;

}

void Parralel_Scaner_camera::SetId(int id)
{
	_id = id;
}

int Parralel_Scaner_camera::GetId()
{
	return _id;
}

void Parralel_Scaner_camera::SetName(std::string name)
{
	_name = name;
}

std::string Parralel_Scaner_camera::GetName()
{
	return _name;
}

void Parralel_Scaner_camera::StartWork()
{
	OpenNewThread();
}

void Parralel_Scaner_camera::EndWork()
{
	pipeControlObj->SendMessag(ControlMessage::endWork);
}

void Parralel_Scaner_camera::StartShow()
{
	pipeControlObj->SendMessag(ControlMessage::startShow);
}

void Parralel_Scaner_camera::EndShow()
{
	pipeControlObj->SendMessag(ControlMessage::endShow);
}

thread_obj* Parralel_Scaner_camera::CreateNewObj()
{
	Parralel_Detector_obj* pdo;
	if (path != "") {
		pdo = new Parralel_Detector_obj(path, _information);
	} else {
		pdo = new Parralel_Detector_obj(_numer_cam, _information);
	}
	pdo->SetName(_information.GetName());
	pdo->SetDetecter(_detecter);
	pdo->SetRecognition(_recognitor);
	//if (_name == "") {
//		_name = "id:" + std::to_string(_id);
		//pdo->SetName(_name);
	//}

	return pdo;
}

void Parralel_Scaner_camera::OpenNewThread()
{
	if (this->pipeControlObj != NULL) CloseOldThread();
	Parralel_Detector_obj* obj = (Parralel_Detector_obj*)CreateNewObj();
	this->pipeControlObj = obj->GetControlPipe();
	std::thread t(*obj);
	t.detach();
}
