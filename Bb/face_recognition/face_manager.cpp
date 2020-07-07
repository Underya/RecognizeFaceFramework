#include "pch.h"
#include "face_manager.h"

faces* face_manager::cfases = NULL;

face_manager::face_manager()
{
	//�������� ������ �������, �������� ����� ���������� ������ �������
	cfases = new faces();
}

face_manager::~face_manager()
{
}

void face_manager::AddNewPhoto(int id, string path)
{
	//��������� � ������ � ��� � ����������� ��������
	face *f = cfases->GetFace(id);
	//���������� ����
	f->AddNewPhoto(path);
}

void face_manager::AddNewFace(int id, string name, string family, string mid_name, string db_description)
{
	face *f = cfases->CreateNewFace(id, name, family, mid_name, db_description);
	cfases->AddFace(*f);
}

void face_manager::AddLoad(int id, add_load_face *load)
{
	face* f = cfases->GetFace(id);
	f->SetAddLoad(load);
}

void face_manager::AddDescriptor(int id, string desc)
{
	//��������� ��������� �� ����
	face* f = cfases->GetFace(id);
	//�������������� ����������� � ���������� � ������
	f->AddNewDescript(Transformation(desc));
}

void face_manager::AddDescriptor(int id, float* desc)
{
	face_matrix m(128, 1);

	auto iter = m.begin();

	int index = 1;

	for (int i = 0; i < 128; i++) {
		(*iter) = desc[i];
		iter++;
	}

	face* f = cfases->GetFace(id);
	//�������������� ����������� � ���������� � ������
	f->AddNewDescript(m);
}

std::vector<face>* face_manager::GetAllFace()
{
	return cfases->GetFaces();
}

inline string  ms(face_matrix m) {
	string dect = "";
	for (auto iter = m.begin(), end = m.end(); iter != end; iter++) {
		dect += to_string(*iter) + " ";
	}

	return dect;

}

//������� �� face_matrix �� float
float* face_manager::GetFloat(face_matrix fm) {
	float* result = new float[128]();
	int i = 0;
	for (auto iter = fm.begin(); iter != fm.end(); iter++) {
		result[i] = *iter;
		i++;
	}
	return result;
}

bool face_manager::CheckId(int id)
{
	//���� �� ������� ����� ���� - ����������� ����������
	try { 
		cfases->GetFace(id); 
	}
	catch (...) {
		return false;
	}
	return true;
}

face face_manager::GetFaceForId(int id)
{
 	return * cfases->GetFace(id);
}

//��������� �� ������ ����� ���� float, ������� � ������� index
float face_manager::GetFloat(string str, int &index) {
	//������ ��� �����
	string num = "";
	//���� �� ������� ������� ��������� ����� �������
	if (str[index] == ' ' || str[index] == ',') index++;
	for (; index < str.length() && str[index] != ' '; index++) {
		num += str[index];
	}
	//����������� ����������� �����
	return atof(num.c_str());
}

face_matrix face_manager::Transformation(string desc)
{

	face_matrix m(128, 1);
	
	auto iter = m.begin();

	int index = 1;

	for (int i = 0; i < 128; i++) {
		(*iter) = GetFloat(desc, index);
		iter++;
	}

	return m;
}

face* face_manager::Recongit(cv_image<rgb_pixel> descr)
{
	//������ ������ � ��������� ���
	face *ff = cfases->Recongit(descr);
	return ff;
}

face* face_manager::Recongit(dlib::matrix<rgb_pixel> descr)
{
	//������ ������ � ��������� ���
	face* ff = cfases->Recongit(descr);
	return ff;
}

void face_manager::ClearList()
{
	cfases->ClearList();
}

void face_manager::SetListFace(std::vector<face> fac)
{
	cfases = new faces(fac);
}
