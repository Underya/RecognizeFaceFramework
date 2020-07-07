#pragma once 

#include "Detecter.h"
#include "IRecognitor.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include "information_camera.h"


//���������� ���������� ��� ������ � ����� �������
//��� ���������� ������������ ���������� OpenCV
class FACEDETECTION_API CameraD:
	public information_camera
{

public:
	//����� ��������� ��������� �����
	virtual void Start();
	//����� ������������ ��������� �����, ���� ����� ������
	virtual void End();

	//�����������, ������� � �������� ��������� ��������� ���� � �����
	CameraD(std::string path, std::string window_name = "");
	
	//�����������, ������� � �������� ��������� ��������� ����� ������
	CameraD(int num, std::string window_name = "");

	//���������� ������
	~CameraD();

	//��������� ��������� ��� ����������� ���
	void SetDetecter(Detecter *Detect);

	//��������� ��������������
	void SetRecognition(IRecognitor *r);

	//�������� ������� ������������� �������� ��� ����������� ���
	Detecter* GetDetecter();

	//������ ������ ����������� �� �����
	virtual void StartShow();

	//����� ������ ����������� �� �����
	virtual void EndShow();

protected:

	//�������� ������ � ���, ��� �� ������� ������� ����/������
	void ThrowOpenError();

	//������ ����� ���������� � ������ ������� ����� ������ ��������� 
	virtual void ControlStep();

	//��������, � ������� �������� ��������� �������������
	Detecter *myDetecter;

	//��������������, � ������� �������� ���������� �������������
	IRecognitor* recogn;

	//��������� �� ����� ����
	cv::VideoCapture *video_file;

	//����, �����������, ���� �� ��������� ���� � ������������ ������
	bool _show = false;

	//����, �����������, ���� �� ������ �����������
	bool _work = false;
};

