#pragma once
#include "face.h"

//Управление объектами лиц
class FACERECOGNITION_API faces
{
public:

	faces();

	faces(std::vector<face> v);

	~faces();

	//Создать новый объект человека и вернуть на него ссылку
	//Объект надо добавить через AddFace
	face *CreateNewFace(int id, string name, string family, string mid_name, string db_description = "");

	//Добавление нового лица в список
	void AddFace(face f);

	//Получение всего списка существующих лиц
	std::vector<face> *GetFaces();

	//Возвращение указателя на конркретное лицо
	face* GetFace(int id);

	//Удаление указанного лица из массива, НО НЕ ИЗ ПАМЯТИ
	void DeletFace(face f);

	//Очищение списка лиц
	void ClearList();

	//Распознование лиц
	//Старый вариант, который вообще хз, используется ли
	face *Recongit(cv_image<rgb_pixel> descr);

	//Главный метод для распознавания лиц
	face* Recongit(dlib::matrix<rgb_pixel> descr);

	//Выленение и преобразование лица из картинки в матрицу
	static face_matrix GetFaceMatrix(cv_image<rgb_pixel> descr);

private:
	
	//Проверка количества элементов в векторе для возврата
	//Если нет такого элемента, выкидывается ошибка
	void CheckCountFace(int i);

	//Переменная, указывающая порог распознования
	static const float recongit;

	//Вектор всех объектов лиц
	std::vector <face> vectorFaces;
};

