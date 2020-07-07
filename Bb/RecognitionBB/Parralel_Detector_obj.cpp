
#include "Parralel_Detector_obj.h"

Parralel_Detector_obj::Parralel_Detector_obj(int num, information_camera information): CameraD(num, information.GetName()), thread_obj()
{
	//cv::ocl::setUseOpenCL(true);
	//ВРОДЕ БЫ не нужны, так как thread_obj конструктор вызывается
	//pipe = new simple_pipe<ControlMessage>();
	SetCameraInfromation(information);
	
}

Parralel_Detector_obj::Parralel_Detector_obj(std::string path, information_camera information) : CameraD(path, information.GetName()), thread_obj()
{
	//cv::ocl::setUseOpenCL(true);
	//pipe = new simple_pipe<ControlMessage>();
	SetCameraInfromation(information);
}

void Parralel_Detector_obj::ThreadMethod()
{
	this->Start();
}

void Parralel_Detector_obj::SetCameraInfromation(information_camera infrom)
{
	this->SetCameraInfo(infrom.GetId(), infrom.GetDescrtiption());
	this->SetPremises(infrom.GetPremises());
	this->SetName(infrom.GetName());
}

void Parralel_Detector_obj::ControlStep()
{
	//Передача управления более общему объекту
	ParseControlMess();
}

void Parralel_Detector_obj::ParseControlMess()
{
	//Обработка сообщений 
	while (pipe->GetCountMess() != 0) {
		ControlMessage mess = pipe->GetMessag();
		if (mess == ControlMessage::startShow) {
			StartShow();
		}
		if (mess == ControlMessage::endShow) {
			EndShow();
			//this->recogn->EndWork();
		}
		if (mess == ControlMessage::endWork) {
			End();
		}
	}
}
