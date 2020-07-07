#pragma once
#include "OneFrame.h"
#include <vector>



class FACEDETECTION_API  Detecter 
{
public:
	//�������, � ������� ������� ������������� ��������� ���� �����
	virtual std::vector<OneFrame> ScanFrame(OneFrame oneFrame);

	//����������� ������� �� ��������
	Detecter();
	
	virtual ~Detecter();


protected:

	dlib::frontal_face_detector detector;

	//
	dlib::shape_predictor sp;

	//�������������, � ������� �������� � ���������� ����������� ���
};

