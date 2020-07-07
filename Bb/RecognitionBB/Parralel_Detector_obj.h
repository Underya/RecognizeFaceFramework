
#pragma once 
#include "..//face_detection/Camera_file.h"
#include "limited_pipe.h"
#include "thread_obj.h"
#include <opencv2/core/ocl.hpp>

//������ ������������� ������������� 
class RECOGNITIONBB_API  Parralel_Detector_obj :
	public CameraD,
	public thread_obj
{
public:

	//����������� � ��������� ������ ������
	Parralel_Detector_obj(int num, information_camera information);

	//����������� � ��������� ���� � ������
	Parralel_Detector_obj(std::string path, information_camera information);

protected:

	void SetCameraInfromation(information_camera infrom);

	//����� ���������� ������ ������ Camera_file
	void ControlStep() override;

	//������ ��������� ����������
	void ParseControlMess() override;

	//������� ����� ������
	void ThreadMethod() override;
};

