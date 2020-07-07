#include "pch.h"
#include "file_faces.h"
using namespace std;

string file_faces::fileName = "faces.txt";

file_faces::file_faces() : file_parametr("faces.txt")
{
	//Создание списка для чтения файлов
	//Чтение всех объектов из файла
	ReadInfo();
}

file_faces::file_faces(std::string file_name) : file_parametr(file_name)
{
	//Создание списка для чтения файлов
	//Чтение всех объектов из файла
	ReadInfo();
}

file_faces::~file_faces()
{
	//Очищение выделенной памяти
	CloseFile();
}

bool file_faces::CheckFace(int id)
{
	//Проверка, есть ли пользователь с таким же id
	for (auto iter = listFaces.begin(); iter != listFaces.end(); iter++) {
		if ((*iter).id == id) return true;
	}

	return false;
}

void file_faces::AddFace(int id, std::string first_name, std::string last_name, std::string mid_name, std::string desc_inf,
	std::vector<std::string> descript, std::vector<int> id_desc, int other_id)
{
	face_info fi;
	fi.id = id;
	if (id == -1) {
		fi.id = GetNewId();
	}
	fi.first_name = first_name;
	fi.last_name = last_name;
	fi.mid_name = mid_name;
	fi.other_id = other_id;
	fi.desc = descript;
	fi.descinfo = desc_inf;
	//Если нет id для лиц - использование фейковых
	if (id_desc.size() == 0) {
		for (int i = 0; i < descript.size(); i++) {
			id_desc.push_back(this->id_desc++);
		}
	}
	fi.id_desc = id_desc;
	listFaces.push_back(fi);
}

string file_faces::GetContentList() {
	string res = "";
	for (auto iter = listFaces.begin(), end = listFaces.end(); iter != end; iter++) {
		//id
		res += "id:" + to_string(iter->id) + ";\n";
		//first name
		res += "first_name:" + iter->first_name + ";\n";
		//last name
		res += "last_name:" + iter->last_name + ";\n";
		//mid_name 
		res += "mid_name:" + iter->mid_name + ";\n";
		//desc_inf
		res += "desc_inf:" + iter->descinfo + ";\n";
		//other_id
		res += "other_id:" + to_string(iter->other_id) + ";\n";
		//desc
		vector<string> v = iter->desc;
		//id_desc
		vector<int> v_id = iter->id_desc;
		auto id_des = v_id.begin();
		for (auto sdes = v.begin(); sdes != v.end(); sdes++, id_des++) { 
			res += "id_desc:" + to_string(*id_des) + ";\n";
			res += "desc:" + (*sdes) + ";\n"; 
		}
		res += "end\n";
	}

	return res;
}

void file_faces::ClearFaceInfo()
{
	CloseFile();
	//Удаление всей информации об объектах, для того, что бы не хранить её в памяти
	ClearList();
}

int file_faces::GetCountFace()
{
	return listFaces.size();
}


list<face_info> file_faces::GetFaceInfo()
{
	return listFaces;
}

face_info file_faces::GetFace(int id)
{
	for (auto iter = listFaces.begin(), end = listFaces.end(); iter != end; iter++) {
		if (iter->id == id) return *iter;
	}

	throw new exception(("Not found face with, where id = " + to_string(id)).c_str());
}

void file_faces::ClearList()
{
	listFaces.clear();
}

void file_faces::ReadInfo()
{
	OpenFileForRead();
	string line, nameParam, valueParam;
	
	//Построковое чтение файла
	while (getline(*_rFile, line)) {
		//Создание новой структуры
		face_info ff;

		//Получение id
		GetValueForString(line, nameParam, valueParam);
		if (nameParam != "id") throw new exception("Error! File faces.text corrupted or not correctde! location:file_faces/ReadInfo\n");
		ff.id = atoi(valueParam.c_str());
		//Получение имени
		getline(*_rFile, line);
		GetValueForString(line, nameParam, valueParam);
		if (nameParam != "first_name") throw new exception("Error! File faces.text corrupted or not correctde! location:file_faces/ReadInfo\n");
		ff.first_name = valueParam;
		//Получение фамилии
		getline(*_rFile, line);
		GetValueForString(line, nameParam, valueParam);
		if (nameParam != "last_name") throw new exception("Error! File faces.text corrupted or not correctde! location:file_faces/ReadInfo\n");
		ff.last_name = valueParam;
		//Получение отчества
		getline(*_rFile, line);
		GetValueForString(line, nameParam, valueParam);
		if (nameParam != "mid_name") throw new exception("Error! File faces.text corrupted or not correctde! location:file_faces/ReadInfo\n");
		ff.mid_name = valueParam;
		//Получение описания человека
		getline(*_rFile, line);
		GetValueForString(line, nameParam, valueParam);
		if (nameParam != "desc_inf") throw new exception("Error! File faces.text corrupted or not correctde! location:file_faces/ReadInfo\n");
		ff.descinfo = valueParam;
		//Получение идентификатора из другой системы
		getline(*_rFile, line);
		GetValueForString(line, nameParam, valueParam);
		if (nameParam != "other_id") throw new exception("Error! File faces.text corrupted or not correctde! location:file_faces/ReadInfo\n");
		ff.other_id = atoi(valueParam.c_str());
		//Получение дескрипторов до тех пор, пока не будет встречена строка end
		getline(*_rFile, line);
		while (line != "end") {
			//Получение ид
			GetValueForString(line, nameParam, valueParam);
			ff.id_desc.push_back(atoi(valueParam.c_str()));
			getline(*_rFile, line);
			GetValueForString(line, nameParam, valueParam);
			ff.desc.push_back(valueParam);
			getline(*_rFile, line);
		}

		listFaces.push_back(ff);
	}
}

//Формат данных следующий:
//id:id_value;
//fist_name:name_value;
//last_name:last_name;
//mid_name:mid_name;
//desc_inf:desc_inf_value;
//other_id:other_id;
//id_desc:id_desc_value;
//desc:descriptor_value;
//end