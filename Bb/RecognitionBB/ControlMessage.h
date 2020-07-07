
#pragma once

#ifdef RECOGNITIONBB_EXPORTS
#define RECOGNITIONBB_API __declspec(dllexport)
#else
#define RECOGNITIONBB_API __declspec(dllimport)
#endif


//��������� ���������, ������� ���������� ������ ��� ����������
enum RECOGNITIONBB_API ControlMessage {
	endWork,			//����� ������ ������
	startShow,			//������ ����� �����������
	endShow,			//��������� ����� �����������
	startMessToConsole,	//������ ����� ��������� � �������
	endMessToConsole	//��������� ����� ��������� � �������
};