#include "pch.h"
#include "face.h"
#include "..//include/opencv2/opencv.hpp"


face::face(int id, string name, string family, string mid_name, string db_description) : employee_info(id, name, family, mid_name, db_description)
{

}

face::~face()
{
}

double face::GetDistance(face_matrix faceMatrix)
{
	int size = _descriptors.size();
	//минимальная дистанция
	double minDist = 2;
	//Текущая дистанция
	double currDist = 3;
	//Вычисление дистанций
	for (int i = 0; i < size; i++) {
		currDist = dlib::length(faceMatrix  - _descriptors[i]);
		//Если полученная меньше минимальной - теперь она минимальная
		if (currDist < minDist) minDist = currDist;
	}

	//Вернуть минимальную дистанцию
	return minDist;
}

void face::AddNewDescript(face_matrix faceMatrix)
{
	//Добавление нового дескриптора
	_descriptors.push_back(faceMatrix);
}

void face::AddNewPhoto(cv::String path)
{
	//Получение дескриптора фотографии
	//Захват файла
	cv::VideoCapture cap;

	const cv::String FileName = path;

	cap.open(FileName);
	//Если не удалось открыть файл
	if (!cap.isOpened()) {
		std::string errorText = "Error! Not open file:";
		errorText += path;
		errorText += "; Location:face/AddNewPhoto\n";
		std::cout << errorText;
		throw new std::exception(errorText.c_str());
	}
	cv::Mat imgCV;
	cap.read(imgCV);

	dlib::frontal_face_detector detector;

	//
	dlib::shape_predictor sp;

	detector = dlib::get_frontal_face_detector();
	dlib::deserialize("shape_predictor_5_face_landmarks.dat") >> sp;

	dlib::cv_image<dlib::rgb_pixel> cv_im(imgCV);
	dlib::matrix<dlib::rgb_pixel> face_chip;

	int i = 0;
	for (auto face : detector(cv_im)) {
		//auto shape = sp(cv_im, face);
		
		dlib::chip_dims chd(150, 150);
		dlib::chip_details cd(face, chd, 0.25);
		extract_image_chip(cv_im, cd, face_chip);
		i++;
	}

	if (i != 1) {
		throw std::exception("Exception! In Image faces count != 1!");
	}

	neironWeb web;

	/*
	std::vector<cv::Rect> faces;

	//На полученной фотографии выделяет человек с помощью opencv
	cv::CascadeClassifier *detect = new cv::CascadeClassifier("haarcascade_frontalface_default.xml");
	//Выделение количества лиц на фотографии
	detect->detectMultiScale(imgCV, faces, 1.1, 3, 0, cv::Size(120, 120));

	//Если получилось больше или меньше нужно людей
	if (faces.size() != 1) throw new std::exception("Error! In Image count faces != 1");

	//Выделение человека на изображении
	cv::Mat newFrame(imgCV, faces[0]);

	for (int i = 0; i < faces.size(); i++) {
		cv::Mat test_f(imgCV, faces[i]);
		cv::imshow("test", test_f);
		cv::waitKey(1);
	}

	cv_image<rgb_pixel> img(newFrame);

	//Создание объекта нейронной сети
	

	chip_details cd;
	cd.rows = 150;
	cd.cols = 150;
	cd.angle = 0.25;
	color_image face_chip;
	extract_image_chip(img, cd, face_chip);
	
	*/
	//Получение и сохранение более точного дескриптора
	AddNewDescript(web.GetDescription(face_chip));
}

std::string face::GetStringContent()
{
	//Получение содержимого класса в виде строки
	std::string content = "";
	content += "face\n";
	//Сюда надо ставить строчку про имя, фамилию и ТД	
	throw std::exception("Ne dodelano!");
	//Если указан id - добавление его в строку
	if (_id != -1)
		content += "id:" + std::to_string(_id) + ";\n";
	else
		//Иначе - он не указывается
		content += "id:-;\n";
	//Добалвение информации о всех фотографиях
	for (int i = 0, size = GetDescriptorCount(); i < size; i++) {
		
		//Конвертация массива в строку
		std::string str = "desc:";
		str += GetDescriptor(i);
		str += "\n";
		content += str;
	}

	return content;
}

std::vector<std::string> face::GetAllDescriptor()
{
	std::vector<std::string> vec_str;

	for (int i = 0; i < this->GetDescriptorCount(); i++) {
		vec_str.push_back(GetDescriptor(i));
	}

	return vec_str;
}

std::string face::GetDescriptor(int i)
{
	CheckCountFaces(i);
	//Переменная, куда будет записан дексриптор
	std::string dect = "";
	for (auto iter = _descriptors[i].begin(), end = _descriptors[i].end(); iter != end; iter++) {
		dect+= std::to_string(*iter) + " ";
	}

	return dect;
}

face_matrix face::GetMatrixDescriptor(int i)
{
	CheckCountFaces(i);
	return _descriptors[i];
}

float* face::GetFloatDescript(int i)
{
	float* res = new float[128]();
	face_matrix mat = GetMatrixDescriptor(i);
	
	int k = 0;
	for (auto iter = mat.begin(); iter != mat.end(); iter++) {
		res[k] = *iter;
		k++;
	}

	return res;
}

int face::GetDescriptorCount()
{
	return _descriptors.size();
}

void face::SetAddLoad(add_load_face* addLoadFace)
{
	_addLoadFace = addLoadFace;
}

add_load_face* face::GetLoad()
{
	return _addLoadFace;
}

void face::CheckCountFaces(int i)
{
	if (_descriptors.size() <= i) throw std::exception("Exception! Index is greater than the number of elements");
}

//face_matrix face::GetDescriptForPhoto(string path)
//{
	//return descriptors[0];

//}
