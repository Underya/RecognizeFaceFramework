
#include "Parralel_Detector_obj.h"

Parralel_Detector_obj::Parralel_Detector_obj(int num, information_camera information): CameraD(num, information.GetName()), thread_obj()
{
	//cv::ocl::setUseOpenCL(true);
	//����� �� �� �����, ��� ��� thread_obj ����������� ����������
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
	//�������� ���������� ����� ������ �������
	ParseControlMess();
}

void Parralel_Detector_obj::ParseControlMess()
{
	//��������� ��������� 
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
