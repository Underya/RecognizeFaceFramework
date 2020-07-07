
#include "pch.h"
#include "file_recognition_result.h"

using namespace std;

file_recognition_result::file_recognition_result(string fileName, int sizeBuff ) : file_parametr(fileName)
{
	//Чтение всей информации из файла, ради последнего id
	ReadFileInfo(_fileName);
	_sizeBuff = sizeBuff;
}

file_recognition_result::~file_recognition_result()
{
	SaveBuffToFile();
}

void file_recognition_result::SetStartId(int id_start)
{
	this->id_not_db = id_start;
}

void file_recognition_result::AddRecognition(int id_face, int id_camera, int id_rec)
{
	//Формирование записи
	string result;
	//Если передано значение по умолчанию
	if (id_rec == -1) {
		result = "id:" + to_string(this->GetNewId()) + ";\n";
	}
	else {
		result = "id:" + to_string(id_rec) + ";\n";
	}
	result += "id_face:" + to_string(id_face) + ";\n";
	result += "id_camera:" + to_string(id_camera) + ";\n";
	
	//Получение и сохранение текущего времени
	result += "time:";
	result += GetCurrentTimeStr();

	//Добавление записи в буффер
	buffResult.push_back(result);
	//Проверка, достаточно ли заполнен буффер
	if (this->CheckFullBuff())
		//Сохранение информаици в файл
		SaveBuffToFile();
}

string file_recognition_result::GetContentList()
{
	string content = "";

	for (int i = 0; i < buffResult.size(); i++) {
		content += buffResult[i];
	}

	return content;
}

void file_recognition_result::Save()
{
	SaveBuffToFile();
}

file_recognition_result::file_recognition_result(std::string file_name, char* a, int* b, int sizeBuffer) : file_parametr(file_name)
{
	_sizeBuff = sizeBuffer;
}

int file_recognition_result::GetId(std::string &line)
{
	string nameParam, valueParam;
	//Получение id
	GetValueForString(line, nameParam, valueParam);
	if (nameParam != "id") ThrowFileReadException("faces.text");
	return atoi(valueParam.c_str());
}

void file_recognition_result::CheckIdFace(std::string line)
{
	string nameParam, valueParam;
	GetValueForString(line, nameParam, valueParam);
	if (nameParam != "id_face") ThrowFileReadException("faces.txt");
}

void file_recognition_result::CheckIdCamera(std::string line)
{
	string nameParam, valueParam;
	GetValueForString(line, nameParam, valueParam);
	if (nameParam != "id_camera") ThrowFileReadException("faces.txt");
}

void file_recognition_result::CheckTime(std::string line)
{
	string nameParam, valueParam;
	GetValueForString(line, nameParam, valueParam);
	if (nameParam != "time") ThrowFileReadException("faces.txt");
}

void file_recognition_result::ReadFileInfo(std::string fileName)
{
	//Подмена имени файла)))))
	string old_text = this->_fileName;
	_fileName = fileName;
	//Чтение файла
	OpenFileForRead();
	string line, nameParam, valueParam;

	int last_id = 0;

	//Построковое чтение файла
	while (getline(*_rFile, line)) {
		//Для проверки хешей, необходимо сохранять записи в классе
		string currentOrder;
		//Получение и проверка id
		//Получение id
		last_id = GetId(line);
		currentOrder += line + "\n";
		//Проверка на id_face
		getline(*_rFile, line);
		currentOrder += line + "\n";
		CheckIdFace(line);
		//Проверка на id_camera
		getline(*_rFile, line);
		currentOrder += line + "\n";
		CheckIdCamera(line);
		//Проверка на time
		getline(*_rFile, line);
		currentOrder += line + "\n";
		CheckTime(line);
		//Добавление во внутренний класс
		buffResult.push_back(currentOrder);
	}

	//Сохранение последнего id
	id_not_db = last_id;
	//Закрытие файла
	CloseFile();
	//Очищение буфера
	buffResult.clear();
	//Возвращение имени назад
	_fileName = old_text;
}



void file_recognition_result::OpenWriteToContinue()
{
	//Открытие файла для продолжения записи
	_wFile = new ofstream(_fileName, ofstream::app);
}

std::string file_recognition_result::GetCurrentTimeStr()
{
	//Получение текущего времени
	time_t t = time(NULL);
	tm time;
	localtime_s(&time, &t);

	string result = "";

	result += to_string(time.tm_year + 1900) + "-";
	result += to_string(time.tm_mon + 1) + "-";
	result += to_string(time.tm_mday) + " ";
	result += to_string(time.tm_hour) + ".";
	result += to_string(time.tm_min) + ".";
	result += to_string(time.tm_sec) + ";\n";

	return result;
}

bool file_recognition_result::CheckFullBuff()
{
	if (buffResult.size() >= _sizeBuff) return true;
	return false;
}

void file_recognition_result::SaveBuffToFile()
{
	CloseFile();
	//Открытие файла для записи
	OpenWriteToContinue();
	//Запись всех объектов в файл
	for (int i = 0; i < buffResult.size(); i++) {
		*_wFile << buffResult[i];
	}
	//Очистка буффера
	buffResult.clear();
	//Закрытие файла
	CloseFile();
}

void file_recognition_result::ThrowFileReadException(std::string fileName)
{
	string error_text = "Error! File ";
	error_text += fileName;
	error_text += "corrupted or not correctde!location:file_recognition_result / ReadInfo\n";
	throw exception(error_text.c_str());
}
