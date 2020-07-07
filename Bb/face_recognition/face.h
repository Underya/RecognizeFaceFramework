#pragma once

//Подключение библиотеки с матрицами
#include "..//include/dlib/image_processing/frontal_face_detector.h"
#include <vector>

#include "add_load_face.h"
#include "neironWeb.h"
#include "employee_info.h"


//Один человек, имеющий несколько фотографий 
class FACERECOGNITION_API face :
	public employee_info
{
public:

	face(int id, string name, string family, string mid_name, string db_description = "");

	~face();

	//Получение наименьшего различия 
	double GetDistance(face_matrix faceMatrix);

	//Добавление новой фотографии с изображением лица в список фотографий
	void AddNewDescript(face_matrix faceMatrix);

	//Обработка и добавление новой фотографии
	void AddNewPhoto(cv::String path);

	//Получение содержимого в виде строки 
	std::string GetStringContent();
	
	//Все дескрипторы в формате строк
	std::vector<std::string> GetAllDescriptor();

	//Получение декрисптора объекта в виде строки
	std::string GetDescriptor(int i);

	//Получение дескриптора в виде матрицы
	face_matrix GetMatrixDescriptor(int i);

	//Получение дескриптора виде массива типа float
	float* GetFloatDescript(int i);

	//Получение числа дескрипторов
	int GetDescriptorCount();

	//Добавить доп нагрузку для данного объекта
	void SetAddLoad(add_load_face* addLoadFace);

	//Получить дополнительную информацию о объекте, если такая есть
	add_load_face* GetLoad();

protected:

	//Проверка, есть ли элемент с таким индексом
	//Если нет - то выкидывается ошибка
	void CheckCountFaces(int i );

	//Массив с фотографими человека
	std::vector<face_matrix> _descriptors;

	//Получение дескриптора лица из изображения
	//face_matrix GetDescriptForPhoto(string path);

	add_load_face *_addLoadFace = NULL;
};

