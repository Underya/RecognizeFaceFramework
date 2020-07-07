
#pragma once
#include "..//face_recognition/face_manager.h"
#include <thread>

#ifdef RECOGNITIONBB_EXPORTS
#define RECOGNITIONBB_API __declspec(dllexport)
#else
#define RECOGNITIONBB_API __declspec(dllimport)
#endif


//����������� ���� ������ ���, � ������ �������������� �������������
class RECOGNITIONBB_API sharead_face_manager :
	public face_manager
{
public:

	sharead_face_manager();

	~sharead_face_manager();

	//���������� ����� ���������� � ��� ������������� ������ ����������
	virtual void AddNewPhoto(int id, string path) override;

	//���������� ������ ���� 
	virtual void AddNewFace(int id, string name, string family, string mid_name, string db_description = "") override;

	//��������, ���� �� ������ � ����� id
	virtual bool CheckId(int id) override;

	//���������� ��� ������������� ����������� ��� ����
	virtual void AddDescriptor(int id, string desc) override;

	//���������� ��� ������������� ����������� ��� ����
	virtual void AddDescriptor(int id, float* desc) override;
protected:

	std::mutex* _mutex;
};

