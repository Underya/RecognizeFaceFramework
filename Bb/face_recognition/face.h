#pragma once

//����������� ���������� � ���������
#include "..//include/dlib/image_processing/frontal_face_detector.h"
#include <vector>

#include "add_load_face.h"
#include "neironWeb.h"
#include "employee_info.h"


//���� �������, ������� ��������� ���������� 
class FACERECOGNITION_API face :
	public employee_info
{
public:

	face(int id, string name, string family, string mid_name, string db_description = "");

	~face();

	//��������� ����������� �������� 
	double GetDistance(face_matrix faceMatrix);

	//���������� ����� ���������� � ������������ ���� � ������ ����������
	void AddNewDescript(face_matrix faceMatrix);

	//��������� � ���������� ����� ����������
	void AddNewPhoto(cv::String path);

	//��������� ����������� � ���� ������ 
	std::string GetStringContent();
	
	//��� ����������� � ������� �����
	std::vector<std::string> GetAllDescriptor();

	//��������� ����������� ������� � ���� ������
	std::string GetDescriptor(int i);

	//��������� ����������� � ���� �������
	face_matrix GetMatrixDescriptor(int i);

	//��������� ����������� ���� ������� ���� float
	float* GetFloatDescript(int i);

	//��������� ����� ������������
	int GetDescriptorCount();

	//�������� ��� �������� ��� ������� �������
	void SetAddLoad(add_load_face* addLoadFace);

	//�������� �������������� ���������� � �������, ���� ����� ����
	add_load_face* GetLoad();

protected:

	//��������, ���� �� ������� � ����� ��������
	//���� ��� - �� ������������ ������
	void CheckCountFaces(int i );

	//������ � ����������� ��������
	std::vector<face_matrix> _descriptors;

	//��������� ����������� ���� �� �����������
	//face_matrix GetDescriptForPhoto(string path);

	add_load_face *_addLoadFace = NULL;
};

