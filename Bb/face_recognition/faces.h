#pragma once
#include "face.h"

//���������� ��������� ���
class FACERECOGNITION_API faces
{
public:

	faces();

	faces(std::vector<face> v);

	~faces();

	//������� ����� ������ �������� � ������� �� ���� ������
	//������ ���� �������� ����� AddFace
	face *CreateNewFace(int id, string name, string family, string mid_name, string db_description = "");

	//���������� ������ ���� � ������
	void AddFace(face f);

	//��������� ����� ������ ������������ ���
	std::vector<face> *GetFaces();

	//����������� ��������� �� ����������� ����
	face* GetFace(int id);

	//�������� ���������� ���� �� �������, �� �� �� ������
	void DeletFace(face f);

	//�������� ������ ���
	void ClearList();

	//������������� ���
	//������ �������, ������� ������ ��, ������������ ��
	face *Recongit(cv_image<rgb_pixel> descr);

	//������� ����� ��� ������������� ���
	face* Recongit(dlib::matrix<rgb_pixel> descr);

	//��������� � �������������� ���� �� �������� � �������
	static face_matrix GetFaceMatrix(cv_image<rgb_pixel> descr);

private:
	
	//�������� ���������� ��������� � ������� ��� ��������
	//���� ��� ������ ��������, ������������ ������
	void CheckCountFace(int i);

	//����������, ����������� ����� �������������
	static const float recongit;

	//������ ���� �������� ���
	std::vector <face> vectorFaces;
};

