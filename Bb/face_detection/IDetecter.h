#pragma once
#include "OneFrame.h"
#include "opencv2/opencv.hpp"

//���������� ��� �������
//� ������� �������� ���������� ����������� �� ����������� ���
class FACEDETECTION_API IDetecter
{
public:
	//������������ �����������
	//OneFrame of - �����������, �� ������� � ���������� ������������
	virtual OneFrame ScanFrame(OneFrame of) = 0;
		
};
