#pragma once
#include "faces.h"
#include <vector>
using namespace std;


//Представляет интерфейс для управления объектами лиц
class FACERECOGNITION_API face_manager
{
public:

	face_manager();

	~face_manager();

	//Добавление новой фотографии к уже существуюшему списку фотографий
	virtual void AddNewPhoto(int id, string path);

	//Добавление нового лица 
	virtual void AddNewFace(int id, string name, string family, string mid_name, string db_description = "");

	//Добавление нагрузочной информации к лицу
	virtual void AddLoad(int id, add_load_face *load);

	//Получение дескриптора лица в виде массива float
	float* GetFloat(face_matrix faceMatrix);

	//Проверка, есть ли объект с таким id
 	virtual bool CheckId(int id);

	//Получение информации сотрудника по его ид
	face GetFaceForId(int id);

	//Добавление уже существующего дескриптора для лица
	virtual void AddDescriptor(int id, string desc);

	//Добавление уже существующего дескриптора для лица
	virtual void AddDescriptor(int id, float* desc);

	//Получение всего списка лиц для сохранения
	std::vector<face>* GetAllFace();

	//Проебразования строкового представления дескриптора в матричное
	face_matrix Transformation(string desc);

	//Распознование лица по изображению
	face* Recongit(cv_image<rgb_pixel> descr);

	face* Recongit(matrix<rgb_pixel> descr);

	//Очищение списка лиц
	void ClearList();

	//Установка списка лиц
	void SetListFace(std::vector<face> faces);

protected:

	float GetFloat(string str, int& index);

	//Коллекция лиц, общая для всех объектов
	static faces* cfases;

};

