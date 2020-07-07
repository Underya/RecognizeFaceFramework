#include "file_recognition_coder.h"

file_recognition_coder::file_recognition_coder(std::string fileName, int sizeBuff) : file_recognition_result(fileName, NULL, NULL, sizeBuff)
{
	OpenHashFile();
	ReadFileInfo(fileName);
}

file_recognition_coder::~file_recognition_coder()
{
	SaveBuffToFile();
}

void file_recognition_coder::OpenHashFile()
{
	//������� ������� ��� �����
	std::ifstream file(_fileName + "hash");
	if (!file.is_open()) {
		std::ofstream newf(_fileName + "hash");
		newf.close();
	}
	else {
		file.close();
	}
}

int file_recognition_coder::GetId(std::string& line)
{
	std::string nameParam, valueParam;
	//��������� id
	GetValueForString(line, nameParam, valueParam);
	//���� ������� �������� - ��� � ��� ������, ���������� ��������� ����������� ������
	if (nameParam == "hash") {
		//�� ���������� ������� �������� ����
		CheckHash(atoi(valueParam.c_str()));
		//������ ��������� ������ � Id
		if (!std::getline(*_rFile, line)) {
			//���� ��� ��������� ������, �� ������� -123
			return -123;
		}
		GetValueForString(line, nameParam, valueParam);
	}
	else {
		//���������� ���������� ������� ��� ����
		_countBlock++;
	}
	if (nameParam != "id") ThrowFileReadException("faces.text");
	return atoi(valueParam.c_str());
}

void file_recognition_coder::CheckHash(int sizeBuffer)
{
	//������ �� ����� � ������ ���������� �������
	char* buffer = new char[sizeBuffer]();

	//������ �� ����� c �����
	_inputFile.read(buffer, sizeBuffer);
	//�������������
	int sizeOriginalBuffer = 0;
	char* resBuff = _coder.UnCodind(buffer, sizeBuffer, sizeOriginalBuffer);
	//���������
	bool HasResult = EqualHashPart(resBuff);

	//���� �� �����
	if (!HasResult) throw std::exception("Recognition file hash does not match content! The file is compromised!");

	//�������� ����������� ������� � ����������
	buffResult.clear();

	//�������� �������
	delete[sizeBuffer]buffer;
	//�������� ������� �������
	delete[sizeOriginalBuffer]resBuff;

}

bool file_recognition_coder::EqualHashPart(char* encodingBuffer)
{
	//������� � ����� �������� ������
	std::string encodStr = encodingBuffer;
	int position = 0;
	//�������� � ���, ��� ����� � �������
	for (auto iter = buffResult.begin(); iter != buffResult.end(); iter++) {
		std::string currentRecord = GetNextRecord(encodStr, position);
		if (*iter != currentRecord) {
			return false;
		}
	}
	return true;
}

void file_recognition_coder::ReadFileInfo(std::string fileName)
{
	//������� ����� �����)))))
	std::string old_text = this->_fileName;
	_fileName = fileName;
	//������ �����
	OpenFileForRead();
	//�������� ����� ��� ������ ����
	OpenHashForRead();
	std::string line, nameParam, valueParam;

	int last_id = 0;
	int cur_id;
	//����������� ������ �����
	while (std::getline(*_rFile, line)) {
		//��� �������� �����, ���������� ��������� ������ � ������
		std::string currentOrder;
		//��������� � �������� id
		//��������� id
		cur_id = GetId(line);
		//���� id = -123, �� ��� ����� �����
		if (cur_id == -123) break;
		last_id = cur_id;
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
	//�������� ����� ��� ������ ����
	_inputFile.close();
	//�������� ������
	buffResult.clear();
	//����������� ����� �����
	_fileName = old_text;
}

std::string file_recognition_coder::GetNextRecord(std::string FullRecord, int& currentPosition)
{
	//���������� ������ ������
	int begin = currentPosition;


	//����� �������� ������ time
	int time_position = FullRecord.find("time:", begin);
	//����� �����, � ���� ������� ����� � ������ ������
	currentPosition = FullRecord.find(";", time_position);
	currentPosition++;

	//���� � ����� ���������
	std::string CurrentRecord ="";
	CurrentRecord = FullRecord.substr(begin, currentPosition - begin);
	CurrentRecord += "\n";
	currentPosition++;

	return CurrentRecord;
}

void file_recognition_coder::SaveBuffToFile()
{
	if (buffResult.size() == 0) return;
	CloseFile();
	//�������� ����� ��� ������
	OpenWriteToContinue();
	//������ ���� �������� � ����
	for (int i = 0; i < buffResult.size(); i++) {
		*_wFile << buffResult[i];
	}
	//���������� ������������� �����
	std::string text="";
	//��������� �� �������������� ������ ��� ���������� � ����
	char *coderBuff = NULL;
	text = "hash:";
	int newSize = 0;
	GetCoderInfo(coderBuff, newSize);
	//���������� � ���� ���������� � ������� �������������� �����
	text += std::to_string(newSize) + ";\n";
	*_wFile << text;
	//������ ���� � �������� ����
	WriteHashToFile(coderBuff, newSize);
	//������� �������
	buffResult.clear();
	//�������� �����
	CloseFile();
}

void file_recognition_coder::WriteHashToFile(char* buff, int size)
{
	//�������� ����� ��� ������ � ���� ����
	OpenHasForWrite();
	//������ � ����
	_outputFile.write(buff, size);
	//�������� �����, ����� ������
	_outputFile.close();
}

void file_recognition_coder::OpenHashForRead()
{
	//�������� ����� ��� ������
	_outputFile.close();
	//�������� ��� ������
	_inputFile.open(_fileName + "hash", std::ios::in | std::ios::binary);
}

void file_recognition_coder::OpenHasForWrite()
{
	//�������� ����� ��� ������
	//_inputFile.close();
	//�������� ����� ��� ������
	_outputFile.open(_fileName + "hash", std::ios::app | std::ios::binary);
}

void file_recognition_coder::GetCoderInfo(char * &outStr, int& newSize)
{
	//��������� �������� ������� � ���� ������
	std::string buffer = "";
	for (int i = 0; i < buffResult.size(); i++) {
		buffer += buffResult[i];
	}
	//����� ������
	int size = buffer.size();
	
	//����������� ������ � ���������� ���������� ��� ��������
	outStr = _coder.Coding(buffer.c_str(), size, newSize);
	
}
