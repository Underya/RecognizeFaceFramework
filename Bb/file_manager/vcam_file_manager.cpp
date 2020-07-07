#include "pch.h"
#include "vcam_file_manager.h"
using namespace std;

vcam_file_manager::vcam_file_manager(std::string file_name) : file_parametr(file_name)
{
	//Создание списка
	this->list = new std::list<vcam_file>();

	//Чтение файла и получение информации из него
	ReadVcamInfo();
}

vcam_file_manager::vcam_file_manager() : file_parametr("vcam_date.txt")
{

	//Создание списка
	this->list = new std::list<vcam_file>();

	//Чтение файла и получение информации из него
	ReadVcamInfo();
}

vcam_file_manager::~vcam_file_manager()
{
}

void vcam_file_manager::AddNewCamera(string address, string description, int id_premise, string position, int id)
{
	vcam_file* vf = new vcam_file();
	vf->address = address;
	vf->position = position;
	vf->description = description;
	vf->id_premise = id_premise;
	//Если id не указано, то используется послденне
	vf->id = id;
	if (id == -1) {
		vf->id = GetNewId(); 
	}
	list->push_back(*vf);
}

list<vcam_file>* vcam_file_manager::GetList()
{
	//Возвращается УКАЗАТЕЛЬ на лист
	return list;
}

vcam_file vcam_file_manager::GetCamera(int id)
{
	//Поиск среди всех камер, камер с таким же id
	for (auto cam = list->begin(); cam != list->end(); cam++) {
		if (cam->id == id) return *cam;
	}

	//Если камера не найдена, вернуть исключение
	throw new exception(("Not camera with id, where id = " + to_string(id)).c_str());
}

int vcam_file_manager::SearchCamera(string address)
{
	//Поиск среди всех объектов камеры с таким же адрессом
	for (auto cam = list->begin(); cam != list->end(); cam++) {
		if (cam->address == address) return cam->id;
	}
	return -1;
}

string vcam_file_manager::GetContentList()
{
	//Содержимое всех элементов
	string content = "";

	for (auto iter = list->begin(); iter != list->end(); iter++) {
		content += "cam\n";
		content += "address:" + iter->address + ";\n";
		content += "position:" + iter->position + ";\n";
		content += "id:" + iter->id_str() + ";\n";
		content += "description:" + iter->description + ";\n";
		content += "id_premise:" + to_string(iter->id_premise) + ";\n";
	}

	//Вовзращение содрежимого файла
	return content;
}

void vcam_file_manager::ReadVcamInfo()
{
	//Откртыие файла для чтения
	OpenFileForRead();
	string line, nameParam, valueParam;
	//Чтение всего файла
	while (getline(*_rFile, line)) {
		//Создание новой структуры информации об камере из файла
		vcam_file* vf = new vcam_file();
		//Проверка, на корректность
		//Строка cam
		if (line != "cam") throw new exception("Error! File is not correct!");

		//address
		//Разбор строк со значенеим параметров
		getline(*_rFile, line);
		//Получение параметра address из строки
		GetValueForString(line, nameParam, valueParam);
		//Провека, правильный ли это параметр
		if(nameParam != "address") throw new exception("Error! File is not correct!");
		//добавление параметра в переменную
		vf->address = valueParam;

		//postion
		//Разбор строк со значенеим параметров
		getline(*_rFile, line);
		//Получение параметра address из строки
		GetValueForString(line, nameParam, valueParam);
		//Провека, правильный ли это параметр
		if (nameParam != "position") throw new exception("Error! File is not correct!");
		//добавление параметра в переменную
		vf->position = valueParam;

		//id
		//Разбор строк со значенеим параметров
		getline(*_rFile, line);
		//Получение параметра address из строки
		GetValueForString(line, nameParam, valueParam);
		//Провека, правильный ли это параметр
		if (nameParam != "id") throw new exception("Error! File is not correct!");
		//добавление параметра в переменную
		vf->id = atoi(valueParam.c_str());

		//description
		//Разбор строк со значенеим параметров
		getline(*_rFile, line);
		//Получение параметра address из строки
		GetValueForString(line, nameParam, valueParam);
		//Провека, правильный ли это параметр
		if (nameParam != "description") throw new exception("Error! File is not correct!");
		//добавление параметра в переменную
		vf->description = valueParam;

		//id_premise
		getline(*_rFile, line);
		//Получение параметра address из строки
		GetValueForString(line, nameParam, valueParam);
		//Провека, правильный ли это параметр
		if (nameParam != "id_premise") throw new exception("Error! File is not correct!");
		//добавление параметра в переменную
		vf->id_premise = atoi(valueParam.c_str());

		//Добавление камеры в список
		list->push_back(*vf);

		//Указание последнего id
		SetLastUsId(vf->id);
	}

}
