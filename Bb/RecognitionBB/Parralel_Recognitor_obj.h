
#pragma once
#include "limited_pipe.h"
#include "..//face_detection/OneFrame.h"
#include <face_manager.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/ocl.hpp>
#include "thread_obj.h"
#include "IRecognitionHandler.h"
#include "db_manager_parralel.h"
#include <map>

typedef std::vector<OneFrame> Frames;

//������������ ������������� ���
class RECOGNITIONBB_API Parralel_Recognitor_obj:
	public thread_obj
{
public:
	
	Parralel_Recognitor_obj(face_manager * faceManager);

	~Parralel_Recognitor_obj();

	//��������� �� �����, � ������� �������� �������� ������� ������ ��� �������������
	simple_pipe<std::pair<Frames, information_camera>>* GetMyPipe();

	//��������� �� �����, � ������� �������� ���������� ���������� ��� ��������
	simple_pipe<ControlMessage> *GetControlPipe();

	void SetName(std::string name);

	//������������� ���, ���������� � ��������� frames
	void Recognition(Frames frames, information_camera inform);

	//��������� �������, ��� ������ � ���� ������ ����, ���� �� ������� ����� ���������
	void SetFaceDb(db_manager_parralel* dbmp);

	//��������� ��������� �� ������ � �������������
	void SetHandler(std::vector<IRecognitionHandler*>* handlers);

private:

	//������ ��� ���� �������� �������, ��� �� �� �������� ������ ��� ��������� �������
	static std::mutex* _Umat_mutex;

	int num = 0;
	//������ �� ����� ������������� �������������
	std::vector<IRecognitionHandler*>* handlers = NULL;

	//�������, � ������� �������� ������ �����
	virtual void ThreadMethod() override;

	//����� ����������� ��������� �� ����������
	//���������� -1 - ����� ������ ������
	int ControlMessParser(ControlMessage mess);

	//����, �����������, ��� ���� �������� �����������
	bool showImage = false;

	//������, � ������� ���������� ����� ��� �� �����������
	db_manager_parralel * _dbmp = NULL;

	face_manager *_faceManager;

	//�����, ������� ������������ ��� �������� ������ ��� �������������
	simple_pipe<std::pair<Frames, information_camera>>* pipe;

	//�������� ������� ��������� ���������� (�����, ������ �����, ����� ������)
	simple_pipe<ControlMessage>* pipeControl;

	//�����, ������� ������ ����� ������������ ��� �������  (� ��������)
	float timeLife = 10.0;
	
	//��� ��� ����������� ����
	string _name;

	//������� ����� ������������� ��� �������
	float currTime = 0;

	static bool _showTime_recognit;
};

