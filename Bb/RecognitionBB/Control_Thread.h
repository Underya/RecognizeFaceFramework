
#pragma once
#include "thread_obj.h"
#include <thread>

#ifdef RECOGNITIONBB_EXPORTS
#define RECOGNITIONBB_API __declspec(dllexport)
#else
#define RECOGNITIONBB_API __declspec(dllimport)
#endif


//����� ��� ���������� �� �������� ������ �������������� � ��� �������
class RECOGNITIONBB_API Control_Thread
{
public:

protected:

	//��������� ������ ������� ������
	//���������� ����������
	virtual thread_obj* CreateNewObj();

	//�������� ������ ������ ��� �������������
	virtual void OpenNewThread();

	//�������� ��������� ������ ��� �������������
	virtual void CloseOldThread();

	//��������, �������� �� ����� � ������� ������
	virtual bool CheckWorkThread();

	//���������� �� ����� ��� �������� ��������� ������� 
	simple_pipe<ControlMessage>* pipeControlObj = NULL;
};

