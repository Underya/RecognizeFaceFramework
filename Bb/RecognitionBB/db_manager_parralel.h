
#pragma once
#include "Control_Thread.h"
#include "db_thread_obj.h"

//�����, ��������������� ������ ��� ������ � �� �� ������ ������
//����� ������ ����� ������ �������������� ������ � ��
class RECOGNITIONBB_API db_manager_parralel :
	public Control_Thread
{
public:

	db_manager_parralel();

	~db_manager_parralel();

	//����� ���� �� �����������
	db_employee SearchFace(float* desc);

	//���������� ����������� �������������
	void SaveResetch(int id_employee, int id_camera);

	//����� ����� ��� ���������� ����������
	std::vector<std::pair<int, std::string>> SearchGroup(int id_employee);

private:

	//����� � ������� ������� ���������� ������ ��� ������
	int myNumSearch;

	//����� � ������� ������� ���������� ������ ��� �������������
	int myNumRecoginition;

	//����� � ������� ��� �����
	int myNumGroup;

	//����� ������ ����������� ��� ������
	Two_Way_Pipe<float*, db_employee>* pipe_find;

	//����� ������ ����������� ��� ���������� ����������� �������������
	Two_Way_Pipe<int, int>* pipe_recognit;

	//����� ������ ��������� ��� ������ �����
	Two_Way_Pipe<int, std::vector<std::pair<int, std::string>>>* pipe_group;

	//��������, ���� �� ��� ���������� �����
	bool CheckWorkThread() override;

	//�������� ������� ������
	thread_obj* CreateNewObj() override;

	//�������� � ������ ������
	void OpenNewThread() override;

	//�������� ��������� ������ ������
	void CloseThread();

	//��������� �� ����� ��� ���� �������� ����� ��� ������ � ��
	static db_thread_obj* db_thread;

	//���������� ����������� ��������. ������������ ��� ����, ��� �� �������� ���������� ����� � ��
	static int countObject;
};

