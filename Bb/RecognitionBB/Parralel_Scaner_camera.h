
#pragma once
#include "Parralel_Detector_obj.h"
#include "Control_Thread.h"

//�����, ������� ��������� ����������� � ������ � ��������� ������
//�, ���� ���������� �������� � �������������� - ������������ � ���������
class RECOGNITIONBB_API  Parralel_Scaner_camera :
	public Control_Thread
{
public:

	//�������� ������� ��� ��������� ������
	Parralel_Scaner_camera(std::string Path, information_camera information);

	//�������� ������� ��� ��������� ������
	Parralel_Scaner_camera(int num, information_camera information);

	//��������� ��������� ��� 
	void SetDetecter(Detecter *detecter);

	//��������� �������������� 
	void SetRecognitor(IRecognitor* recognitor);
	
	//������ id ��� ������
	void SetId(int id);

	//��������� id ������
	int GetId();

	//��������� ����� ��� ������
	void SetName(std::string name);

	//��������� ����� ������
	std::string GetName();

	//������ ������ ������
	void StartWork();

	//��������� ������
	void EndWork();

	//������ ����� �����������
	void StartShow();

	//����� ������ �����������
	void EndShow();

private:

	//�� ������
	int _id = -1;

	//�������� ������. ������������ ��� ���� ������
	std::string _name = "";

	//�������� ������ ������� ��� �����������
	thread_obj* CreateNewObj() override;

	//�������� ������ ������� ������
	void OpenNewThread() override;

	//���� � ������
	std::string path = "";
	
	//����� USB ������
	int _numer_cam;

	Detecter* _detecter = NULL;

	IRecognitor* _recognitor = NULL;

	information_camera _information;
};

