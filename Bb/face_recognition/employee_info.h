#pragma once

#ifdef FACERECOGNITION_EXPORTS
#define  FACERECOGNITION_API __declspec(dllexport)
#else
#define FACERECOGNITION_API __declspec(dllimport)
#endif


#include <string>
using  std::string;

//���������� � ����������
class FACERECOGNITION_API employee_info
{
public:

	//�������� ����������
	employee_info(int id, string name, string family, string mid_name, string db_description = "");

	//�������� ������������� ����������
	int GetId();

	//���������� ������������� ����������
	void SetId(int id);

	//�������� ������������� ���������� �� ������ �������
	int GetOtherId();

	//���������� ������������� ���������� �� ������ �������
	void SetOtherId(int other_id);

	//�������� ��� ����������
	string GetFirstName();

	//���������� ��� ����������
	void SetFisrtName(string name);

	//�������� ������� ����������
	string GetLastName();

	//���������� ������� ����������
	void SetLastName(string family);

	//�������� �������� ����������
	string GetMidName();

	//���������� �������� ����������
	void SetMidName(string mid_name);

	//��������� ������� ���������� �� ��
	string GetDBDescriptor();

	//���������� ���������� �� ��
	void SetDBDescriptor(string db_descriptor);

protected:

	//���
	string _first_name;

	//�������
	string _last_name;

	//��������
	string _mid_name;

	//�������� ���������� �� ��
	string _db_description = "";

	//������������� �������� �� ��
	int _id = -1;

	//������������� �� �� ������ �������
	int _other_id = -1;
};

