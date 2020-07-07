#pragma once
#include "OneFrame.h"
#include "information_camera.h"
#include <vector>

//���������, � ������� ������� ������ ����������� ������ ��� �������������
class FACEDETECTION_API IRecognitor
{
public:
	//������ ����� �������� �� ������ �������� ������ � ������������� ������
	virtual void Recognition(std::vector<OneFrame> vector_frame, information_camera cam) = 0;

	//�����, ���������� ��� ��������� ������
	virtual void EndWork() = 0;

	//������������� ������
	int _id_cam = -1;

};



