#include "pch.h"
#include "faces.h"
#include <opencv2/opencv.hpp>

using namespace std;

faces::faces()
{
}

faces::faces(std::vector<face> v)
{
	vectorFaces = v;
}

faces::~faces()
{
}

face *faces::CreateNewFace(int id, string name, string family, string mid_name, string db_description)
{
	//�������� ������ �������
	face * f = new face(id, name, family, mid_name, db_description);
	//����������� ������ ���� ����������� ����������
	return f;
}

void faces::AddFace(face f)
{
	while (true) {
		try {
			vectorFaces.push_back(f);
		}
		catch (...) {
			continue;
		}

		break;
	} 
}

std::vector<face>* faces::GetFaces()
{
	return &vectorFaces;
}

face* faces::GetFace(int id)
{
	int last_id;
	//����� ����� ���� ��� - �����������, � ����� �� id
	for (auto iter = vectorFaces.begin(), end = vectorFaces.end(); iter != end; iter++) {
		last_id = iter->GetId();
		if (iter->GetId() == id)
			return &(*iter);
	}

	//	cout << "last id:" << last_id;

	//���� �� ������� - �������� ����������
	throw new exception(("Error! Not found face in id:" + to_string(id) + "\n").c_str());
	return nullptr;
}

void faces::DeletFace(face f)
{
	//����� ������� �������� �������
	for (auto iter = vectorFaces.begin(); iter != vectorFaces.end(); iter++) {
		//�������� �� ID
		if (iter->GetId() == f.GetId()) {
			//�������� ������� �� ���������
			vectorFaces.erase(iter);
			//����� ������ � �������
			return;
		}
	}
}

void faces::ClearList()
{
	vectorFaces.clear();
}

int i = 0;

int z = 1;


face* faces::Recongit(dlib::matrix<rgb_pixel> descr) {
	neironWeb web;

	face_matrix sface;

	//time_t start = clock();
	
	sface = web.GetDescription(descr);
	//time_t finish = clock();
	//double dur = (double)(finish - start) / CLOCKS_PER_SEC;


	face* ret_face = NULL;

	double min_dist = 0.6;

	//����� ������������ ��������
	for (auto iter = vectorFaces.begin(), end = vectorFaces.end(); iter != end; iter++) {
		//���� ����� ����������, �� ��� ������������ ��������� �� ����
		face* f = &(*(iter));
		double dist = f->GetDistance(sface);
		if (dist < min_dist) {
			//���� ����� ����� ����������� ��������
			//�� ������������ ��������� �� ����
			ret_face = &(*(iter));
			//� ����� ����������� ��������
			min_dist = dist;
		}
	}

	//���� ���� ������� ����������� ��������
	if (ret_face != NULL)
		return ret_face;

	//���� �� ���� ������� ����, ����������� ��������� �� �������� ������
	face* not_find = new face(-1, "unrecognized", "unrecognized", "unrecognized");
	//� ������������� ���� ����������� ��� ����������
	not_find->AddNewDescript(sface);

	//���� �� ���� ������� ��������
	//����������� ������� �������
	return not_find;
}

face* faces::Recongit(cv_image<rgb_pixel> descr)
{
	
	neironWeb web;
	face* not_find = new face(-1, "unrecognized", "unrecognized", "unrecognized");
	face_matrix sface;

	try {
		clock_t startt = clock();
		//sface = GetFaceMatrix(descr);
		dlib::shape_predictor sp;
		dlib::deserialize("shape_predictor_5_face_landmarks.dat") >> sp;

		//��������� ����� ������� ��� � ����������
		dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
		std::vector <color_image> facesVec;

		for (auto face : detector(descr)) {
			auto shape = sp(descr, face);
			color_image face_chip;
			extract_image_chip(descr, get_face_chip_details(shape, 150, 0.25), face_chip);
			clock_t finischt = clock();
			double dur = (double)(finischt - startt) / CLOCKS_PER_SEC;
			cout << "time ship find:" << dur << "\n";
			sface =  web.GetDescription(face_chip);
		}
		
		

	}
	catch (...) {
		return NULL;
	}

	//����� ������������ ��������
	for (auto iter = vectorFaces.begin(), end = vectorFaces.end(); iter != end; iter++) {
		//���� ����� ����������, �� ��� ������������ ��������� �� ����
		face* f = &(*(iter));
		float dist = f->GetDistance(sface);
		if (dist < 0.6) {
			return &(*iter);
		}
	}

	//� ������������� ���� ����������� ��� ����������
	not_find->AddNewDescript(sface);

	//���� �� ���� ������� ��������
	//����������� ������� �������
	return not_find;
}

face_matrix faces::GetFaceMatrix(cv_image<rgb_pixel> descr)
{
	//��������� ����������� ����
	neironWeb web;

	face_matrix sface;
	try {
		//matrix<rgb_pixel> n = matrix<rgb_pixel>(descr);
		//��������� �����������
		color_image face_chip;
		chip_details cd;
		cd.rows = 150;
		cd.cols = 150;
		cd.angle = 0.25;
		extract_image_chip(descr, cd, face_chip);
		//cv::imshow("reco", face_chip);
		//cv_image<rgb_pixel> ci(face_chip);
		//cv::Mat(face_chip);
		//color_image ci = web.Transform(descr);
		//cout << "\nSecond transf time:" << durable << "\n";

		sface = web.GetDescription(face_chip);

		//sface = web.GetDescription(face_chip);
		//cout << "new desc:\n";

		//for (auto iter = sface.begin(); iter != sface.end(); iter++) {
			//cout << to_string(*iter);
		//}

		//cout << endl;
	}
	catch (...) {
		cout << "Not face Transform\n";
		throw "Not face Transform\n";
	}

	return sface;
}

void faces::CheckCountFace(int i)
{
	if (i >= vectorFaces.size()) throw std::exception("Exception! Index is greater than the number of elements");
}

