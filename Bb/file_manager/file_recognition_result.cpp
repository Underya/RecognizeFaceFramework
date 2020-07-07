
#include "pch.h"
#include "file_recognition_result.h"

using namespace std;

file_recognition_result::file_recognition_result(string fileName, int sizeBuff ) : file_parametr(fileName)
{
	//������ ���� ���������� �� �����, ���� ���������� id
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
	//������������ ������
	string result;
	//���� �������� �������� �� ���������
	if (id_rec == -1) {
		result = "id:" + to_string(this->GetNewId()) + ";\n";
	}
	else {
		result = "id:" + to_string(id_rec) + ";\n";
	}
	result += "id_face:" + to_string(id_face) + ";\n";
	result += "id_camera:" + to_string(id_camera) + ";\n";
	
	//��������� � ���������� �������� �������
	result += "time:";
	result += GetCurrentTimeStr();

	//���������� ������ � ������
	buffResult.push_back(result);
	//��������, ���������� �� �������� ������
	if (this->CheckFullBuff())
		//���������� ���������� � ����
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
	//��������� id
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
	//������� ����� �����)))))
	string old_text = this->_fileName;
	_fileName = fileName;
	//������ �����
	OpenFileForRead();
	string line, nameParam, valueParam;

	int last_id = 0;

	//����������� ������ �����
	while (getline(*_rFile, line)) {
		//��� �������� �����, ���������� ��������� ������ � ������
		string currentOrder;
		//��������� � �������� id
		//��������� id
		last_id = GetId(line);
		currentOrder += line + "\n";
		//�������� �� id_face
		getline(*_rFile, line);
		currentOrder += line + "\n";
		CheckIdFace(line);
		//�������� �� id_camera
		getline(*_rFile, line);
		currentOrder += line + "\n";
		CheckIdCamera(line);
		//�������� �� time
		getline(*_rFile, line);
		currentOrder += line + "\n";
		CheckTime(line);
		//���������� �� ���������� �����
		buffResult.push_back(currentOrder);
	}

	//���������� ���������� id
	id_not_db = last_id;
	//�������� �����
	CloseFile();
	//�������� ������
	buffResult.clear();
	//����������� ����� �����
	_fileName = old_text;
}



void file_recognition_result::OpenWriteToContinue()
{
	//�������� ����� ��� ����������� ������
	_wFile = new ofstream(_fileName, ofstream::app);
}

std::string file_recognition_result::GetCurrentTimeStr()
{
	//��������� �������� �������
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
	//�������� ����� ��� ������
	OpenWriteToContinue();
	//������ ���� �������� � ����
	for (int i = 0; i < buffResult.size(); i++) {
		*_wFile << buffResult[i];
	}
	//������� �������
	buffResult.clear();
	//�������� �����
	CloseFile();
}

void file_recognition_result::ThrowFileReadException(std::string fileName)
{
	string error_text = "Error! File ";
	error_text += fileName;
	error_text += "corrupted or not correctde!location:file_recognition_result / ReadInfo\n";
	throw exception(error_text.c_str());
}
