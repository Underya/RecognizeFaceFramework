
#pragma once
#include "file_parametr.h"
#include <list>
#include "face_info.h"
#include <string>

#ifdef FILEMANAGER_EXPORTS
#define FILEMANAGER_API __declspec(dllexport)
#else
#define FILEMANAGER_API __declspec(dllimport)
#endif

//Класс, сохраняющий информацию об сотрудниках их их лицах
class FILEMANAGER_API  file_faces :
	public file_parametr
{
public:

	//Связать с файлом со стандартным имененм
	file_faces();

	//Связать с файлом с ненстандантрным именем
	file_faces(std::string file_name);

	~file_faces();

	//Проверка, есть ли лицо с таким же идентификатором
	bool CheckFace(int id);

	//Добавление инофрмации о лице, которого надо сохранить в файл
	void AddFace(int id, std::string first_name, std::string last_name, std::string mid_name, std::string desc_inf,
		std::vector<std::string> descript, std::vector<int> id_desc, int other_id = -1);

	//Метод, удаляющий информацию о лицах
	//Используется для освобождение памяти
	void ClearFaceInfo();

	//Возвращает информацию о количество объектов лиц
	int GetCountFace();

	//Возвращение всей информаици о лицах
	std::list<face_info> GetFaceInfo();

	//Получить информацию о сотруднике с таким же имененм
	face_info GetFace(int id);


private:
	
	//Если нет настоящих id для лиц, используются фейковые
	int id_desc = 0;

	//Очищение списка лиц
	void ClearList();

	std::list<face_info> listFaces;

	//Имя файла, в котором хранятся данные о изображениях;
	static std::string fileName;

	//Возвращение всей информации внутри объекта в виде строки, для записи в файл
	std::string GetContentList();

	//Чтение информации из файла, и заполнение списка
	void ReadInfo();
};

//Формат данных следующий:
//id:id_value;
//name:name_value;
//desc_inf:desc_inf_value;
//id_desc:id_desc_value;
//desc:descriptor_value;
//end;