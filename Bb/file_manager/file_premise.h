#pragma once
#include "file_parametr.h"
#include <vector>

//�������� ������ ���������
struct FILEMANAGER_API premise {

	//������������� ������ ���������
	int id = -1;

	//�������� ���������
	std::string name = "";

	//�������� 
	std::string description = "";

	//�� �������� ���������
	int id_parent = -1;
};

//���������� ������ � �����������
class FILEMANAGER_API file_premise :
	public file_parametr
{
public:

	file_premise(std::string file_name);

	file_premise();

	~file_premise();

	//�������� ����� ��������� � ���������� ���������� � ��� � ����
	void AddNewPremise(std::string name, std::string desc = "", int id = -1, int id_parent = -1);

	//��������� ���������� ��� ���� ����������
	std::vector<premise> GetAllPremise();

	//��������� ��������� �� ��� id
	premise GetPremise(int id);

	void EditPremisse(int id, std::string name, std::string desc = "", int id_parent = -1);

	//�������� ������ �� ����� �������� ��� ������� ���������
	std::vector<premise> GetAllParent(int id_premise);
	//�������� ������ �� ����� �������� ��� ������� ���������
	std::vector<premise> GetAllParent(premise premis);

	//�������� ������� ��������� � ��� ��� ������
	std::vector<premise> GetPremiseWithParrent(int id_premise);

	void DeletePremise(int id);
	
protected:

	std::string GetContentList() override;

	//�������, ������� ��������� ���������� �� ����
	void ReceiveInfo();

	//����� � �����������
	std::vector<premise> _premises;
};

