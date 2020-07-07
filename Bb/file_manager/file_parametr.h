
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifdef FILEMANAGER_EXPORTS
#define FILEMANAGER_API __declspec(dllexport)
#else
#define FILEMANAGER_API __declspec(dllimport)
#endif


//����������� �����, ������� ��������� ������ ������� ��� ������ �������, ������� ���������� ���� ������ ��� ���������
class FILEMANAGER_API file_parametr
{
public:

	//���������� ������� ���������� � ����
	virtual void Save();

	//����� ���������� ��� ����������, ��� ����������� � �����
	void ShowInfo();

	//����������� �����������, ��� ������ � �������
	//fileName - �������� �����, � ������� �������� �����
	file_parametr(std::string fileName);

	virtual ~file_parametr();

	//�������� �����
	virtual void ClearFile();

protected:

	//������� ���������� bool, ���� ����� ������� ��� ���� � �������
	bool HasIdInVec(std::vector<int> _vector, int id);

	//��������� �������� ��������� � ��� �������� �� ������
	//������ ������ ����� ��������� ��� nameParametr:valueParametr;
	//str - ������ ���������� ����, nameParam - �������� �������� �������� ���������
	//vauleParam - �������� ���������
	void GetValueForString(std::string str, std::string& nameParam, std::string& valueParam);

	//�������� �����
	void CloseFile();

	void OpenFileForRead();

	void OpenFileForWrite();

	//����� ���������� �� ���������� ������ � ���� ���������� ������
	virtual std::string GetContentList();

	//�������� ������ ������� �����
	void CreateNewFile();

	//���������� ����� ��� ������
	std::ifstream* _rFile = NULL;

	//��������� ����� ��� ������
	std::ofstream* _wFile = NULL;

	//��� �����, � ������� ��������� ����������
	std::string _fileName;

	//�������� ����� id ��� ������
	int GetNewId();

	//���������� ��������� �������������� ID
	//���������� ��� ������������� ������ �������� ������� � ��
	void SetLastUsId(int outer_id);

	//��������, ���������� �� ����
	bool CheckFileExist();

	//���� ��� ���������� ���������� �� �������� �� ������������ ��
	//�� ���� ��� ������ ID
	int id_not_db = 0;

};

