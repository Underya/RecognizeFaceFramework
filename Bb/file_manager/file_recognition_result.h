#pragma once
#include "file_parametr.h"
#include <vector>
#include <string>
#include <time.h>

//����� ��� ���������� ����������� ������������� � ����
class FILEMANAGER_API file_recognition_result :
	public file_parametr
{
public:

	//���������� � ��������� ������
	file_recognition_result(std::string fileName, int sizeBuff = 15);

	~file_recognition_result();

	//���������� ��������� �������� ��� id �������. 
	//�� ��������� ��� ����� ���������� �������� �� ������
	void SetStartId(int id_start);

	//���������� ����� ������ �� �������������
	//rec - id ������. 
	virtual void AddRecognition(int id_face, int id_camera, int rec = -1);

	//������������� ������� ������ � ���� �����
	std::string GetContentList() override;

	//��������� ���������� ����������� � ����
	void Save() override;

protected:

	//���� ������� 
	file_recognition_result(std::string file_name, char* a, int* b, int sizeBuffer = 15);

	//����� ���������, ����� �������� ��� ������������� ����������� � ����
	int _sizeBuff;

	//��� �������, ������ ��������� ��������� �� ������, ������� ���������

	//��������� ID
	virtual int GetId(std::string& line);
	//�������� id_face
	virtual void CheckIdFace(std::string line);
	//�������� id_camera
	virtual void CheckIdCamera(std::string line);
	//�������� �������
	virtual void CheckTime(std::string line);

	//������ ���������� �� �����
	//������������ ��� ��������� ���������� Id
	virtual void ReadFileInfo(std::string fileName);

	//������� ���� ��� ����������� ������
	void OpenWriteToContinue();

	//��������� �������� ������� � ������� ������
	std::string GetCurrentTimeStr();

	//��������, ���������� �� �������� ������ ��� ������ ��� � ����
	bool CheckFullBuff();

	//����� ��������� ��� ����������, ���������� � ������� � ����
	virtual void SaveBuffToFile();

	//����� ������
	//LOCATION - �����, � ������� ��������� ������
	void ThrowFileReadException(std::string fileName);

	//������ ��� ���������� ������� 
	std::vector<std::string> buffResult;
};

