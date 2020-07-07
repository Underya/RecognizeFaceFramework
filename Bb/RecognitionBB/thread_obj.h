
#pragma once
#include "pch.h"
#include "ControlMessage.h"
#include "simple_pipe.h"

//�����, ������� ����������� � ������������ ������
class RECOGNITIONBB_API thread_obj
{
public:

	thread_obj();

	//��������� ������ ��� �������
	simple_pipe<ControlMessage>* GetControlPipe();

	//�����, � �������� ���������� ������ ������
	void operator()();

protected:

	//�����, ������� ����������, ����� ����� �������� ��������
	virtual void ThreadMethod();

	//�����, � ������� ����������� ��������� ��� ��������
	virtual void ParseControlMess();

	//�����, �� �������� ������ �������� ���������
	simple_pipe<ControlMessage>* pipe;
};

