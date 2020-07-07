#pragma once
#include "..//file_manager/file_recognition_result.h"
#include "..//MessageServer/BlowfishCoder.h"

#ifdef RECOGNITIONBB_EXPORTS
#define RECOGNITIONBB_API __declspec(dllexport)
#else
#define RECOGNITIONBB_API __declspec(dllimport)
#endif


//�����, �������������, ������� ������ ������ � ������������� ����
class RECOGNITIONBB_API file_recognition_coder :
	public file_recognition_result
{
public:

	//������� ����, ���� ����� ������������ ����������
	file_recognition_coder(std::string fileName, int sizeBuff = 15);

	~file_recognition_coder();

protected:

	//�������� ��� �������� ����� ����
	void OpenHashFile();

	//������ �������� ID ����� ���������� �������� ������� ���� �������
	virtual int GetId(std::string& line) override;
	
	//�������� �������������� �����
	//sizeBuffer - ������ �������������� �����, ������� � �����
	void CheckHash(int sizeBuffer);

	//���������, ��������� �� 
	bool EqualHashPart(char* encodingBuffer);

	//����������, ������ ������ ��� �� ��� ����� ����������
	void ReadFileInfo(std::string fileName) override;

	//��������� ��������� ������ �� �������� ������
	std::string GetNextRecord(std::string FullRecord, int& currentPosition);

	//���������� �������� ������� � ����
	void SaveBuffToFile() override;

	//������� ���������� ���� ������ � ����
	void WriteHashToFile(char *buff, int size);

	//����� ��� ���������� � ����������� ������
	BlowfishCoder _coder;

	//�������� ����� ��� ��� ������
	void OpenHashForRead();

	//��������� �� ����, � ������� �������� ��� ������ ��� ������
	std::ifstream _inputFile;

	//�������� ���� ��� ��� ������
	void OpenHasForWrite();

	//��������� �� ����, � ������� �������� ��� ������ ��� ������
	std::ofstream _outputFile;

	//�������� �������� ������� � ���� ��������������� ������
	void GetCoderInfo(char* &outStr, int& newSize);

	int _countBlock = 0;
};

