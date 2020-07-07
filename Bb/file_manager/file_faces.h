
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

//�����, ����������� ���������� �� ����������� �� �� �����
class FILEMANAGER_API  file_faces :
	public file_parametr
{
public:

	//������� � ������ �� ����������� �������
	file_faces();

	//������� � ������ � ��������������� ������
	file_faces(std::string file_name);

	~file_faces();

	//��������, ���� �� ���� � ����� �� ���������������
	bool CheckFace(int id);

	//���������� ���������� � ����, �������� ���� ��������� � ����
	void AddFace(int id, std::string first_name, std::string last_name, std::string mid_name, std::string desc_inf,
		std::vector<std::string> descript, std::vector<int> id_desc, int other_id = -1);

	//�����, ��������� ���������� � �����
	//������������ ��� ������������ ������
	void ClearFaceInfo();

	//���������� ���������� � ���������� �������� ���
	int GetCountFace();

	//����������� ���� ���������� � �����
	std::list<face_info> GetFaceInfo();

	//�������� ���������� � ���������� � ����� �� �������
	face_info GetFace(int id);


private:
	
	//���� ��� ��������� id ��� ���, ������������ ��������
	int id_desc = 0;

	//�������� ������ ���
	void ClearList();

	std::list<face_info> listFaces;

	//��� �����, � ������� �������� ������ � ������������;
	static std::string fileName;

	//����������� ���� ���������� ������ ������� � ���� ������, ��� ������ � ����
	std::string GetContentList();

	//������ ���������� �� �����, � ���������� ������
	void ReadInfo();
};

//������ ������ ���������:
//id:id_value;
//name:name_value;
//desc_inf:desc_inf_value;
//id_desc:id_desc_value;
//desc:descriptor_value;
//end;