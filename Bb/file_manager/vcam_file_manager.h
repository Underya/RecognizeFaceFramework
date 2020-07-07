#include "pch.h"
#include <iostream>
#include <list>
#include "vcam_file.h"
#include <fstream>
#include "file_parametr.h"

//����� ��������� ������ ��� ��������� � ���������� ���������� � ������� �� �����
class FILEMANAGER_API vcam_file_manager : public file_parametr
{
public:

	//�������� ����� � ��������� ������
	vcam_file_manager(std::string file_name);

	//�������� ����� �� �����������
	vcam_file_manager();

	~vcam_file_manager();

	//���������� ����� ������ � ������ ������������ ����� � ��������
	void AddNewCamera(std::string address, std::string description = "", int id_premise = -1, std::string position = "n", int id = -1);

	//��������� ������ ���� ����� �� �����
	//������������ ��������� �� ������ ������
	std::list<vcam_file>* GetList();

	//�������� ������ �� � id
	vcam_file GetCamera(int id);

	//����� ������ � ����� �� �������
	int SearchCamera(std::string address);

private:

	//����� ���������� �� ���������� ������ � ���� ���������� ������
	std::string GetContentList() override;

	//������ ���������� �� ����� � �������� ������ � ������
	void ReadVcamInfo();

	//������ ����� �� ���������� �����
	std::list<vcam_file> *list;

};

//���������� ����� �������� ��������� �������
//cam
//address:value1;
//position:value2;
//id:value3;
//description:value4;
//id_premise:value5;
//������� ���� �������� ����������, ����� - �� ��������
//� �������� ���������� ������ ����������� ������ - ; � ������ \n
