
#pragma once
#include "Parralel_Recognitor_obj.h"
#include "IRecognitor.h"
#include "Control_Thread.h"
#include "IRecognitionHandler.h"

//�����, ����� ������ �������� �������������� ������������ �������������
class RECOGNITIONBB_API Parralel_Recognitor: 
	public IRecognitor, 
	public Control_Thread
{
public:
	
	Parralel_Recognitor(face_manager *faceManager);

	~Parralel_Recognitor();

	void StartShow();

	void EndShow();

	void EndWork() override;

	//������� ��� ��� ������������ ����(������ ���� ���������)
	void SetName(std::string name);

	//�������� ������ ������� ��� �������������
	thread_obj* CreateNewObj() override;

	//������������� ���������� ������ ���
	void IRecognitor::Recognition(std::vector<OneFrame> faces, information_camera cam) override;

	void SetDbFaceSource(db_manager_parralel *dbmp);

	//�������� ����� ���������� � ������
	void AddHandler(IRecognitionHandler* handler);

private:

	

	db_manager_parralel* _dbmp = NULL;

	//������ �� ����� �������������, ��� ���������� ��� �������������
	std::vector<IRecognitionHandler*> Handlers;

	void OpenNewThread() override;

	//��������� �� ����� ��� �������� ������ ������� �������� ��� �������������
	simple_pipe<std::pair<Frames, information_camera>>* pipeToObj;

	std::string _name;

	//���� � ������
	face_manager* _faceManager;
};

