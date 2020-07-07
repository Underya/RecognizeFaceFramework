#pragma once
#include "faces.h"
#include <vector>
using namespace std;


//������������ ��������� ��� ���������� ��������� ���
class FACERECOGNITION_API face_manager
{
public:

	face_manager();

	~face_manager();

	//���������� ����� ���������� � ��� ������������� ������ ����������
	virtual void AddNewPhoto(int id, string path);

	//���������� ������ ���� 
	virtual void AddNewFace(int id, string name, string family, string mid_name, string db_description = "");

	//���������� ����������� ���������� � ����
	virtual void AddLoad(int id, add_load_face *load);

	//��������� ����������� ���� � ���� ������� float
	float* GetFloat(face_matrix faceMatrix);

	//��������, ���� �� ������ � ����� id
 	virtual bool CheckId(int id);

	//��������� ���������� ���������� �� ��� ��
	face GetFaceForId(int id);

	//���������� ��� ������������� ����������� ��� ����
	virtual void AddDescriptor(int id, string desc);

	//���������� ��� ������������� ����������� ��� ����
	virtual void AddDescriptor(int id, float* desc);

	//��������� ����� ������ ��� ��� ����������
	std::vector<face>* GetAllFace();

	//�������������� ���������� ������������� ����������� � ���������
	face_matrix Transformation(string desc);

	//������������� ���� �� �����������
	face* Recongit(cv_image<rgb_pixel> descr);

	face* Recongit(matrix<rgb_pixel> descr);

	//�������� ������ ���
	void ClearList();

	//��������� ������ ���
	void SetListFace(std::vector<face> faces);

protected:

	float GetFloat(string str, int& index);

	//��������� ���, ����� ��� ���� ��������
	static faces* cfases;

};

