#pragma once
#include "db_connect.h"


//������������� ������ ����������� ���� �� ����
class DB_API db_face:
	public db_row
{
public:

	//��������� ����������� � ���������� id
	db_face(int id);

	~db_face();

	//������ �������, ������������ �� ��������� ���������� �� �������

	//��������� ID �����������
	int GetId();
	//��������� id ����������
	int GetIdEmployee();
	//��������� �����������
	float* GetDescriptor();
	//��������� ������� �����������
	int GetDescriptorSize();

	//����� ���������� � �����������
	void ShowInfo();

	void Delete() override;

	//�������� ������ ������� � �� 
	//� ��������� �� ���� ���������
	static db_face* AddNewFace(float* descriptor, int id_employe);

	//����� �������� � ��������� ������������ � ��
	static int SearchFace(float* descriptor);
	static int SearchFace(std::string descriptor);

private:

	//������������� ����������, � �������� ��������� ����
	int id_employee;

	//���������� ��������� ����������� �� ������
	void SetDescriptFromChar(char* descr);

	//������������� �� ��������� �����������
	//� ������ ��� PostgreSQL
	static std::string TransformToString(float* desc);

	//������ ������� �����������
	//�� ��������� - 128 ���������
	static int descriptSize;
	//������ �� 128 ���������, ������� ��������������� �������� ����������
	float* descript = NULL;

	//���������� � ��
	db_connect *connect = NULL;

	//�������� ���������� � ����������� � ��
	//���������� ��� ����� ���������
	void _db_update();

	//��������� ��� ������ �������� �� ��
	//�������� ������� � �����������
	const static std::string db_table_name;
	const static std::string add_proc_name;
	const static std::string edit_proc_name;
	const static std::string delete_proc_name;

};

