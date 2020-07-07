
#pragma once
#include "thread_obj.h"
#include <db_manager.h>
#include <db_group.h>
#include "Two_Way_Pipe.h"

//������ ������, ������� �������� � ��
class RECOGNITIONBB_API db_thread_obj :
	public thread_obj
{
public:

	db_thread_obj();

	~db_thread_obj();

	//��������� ��������� �� �����, ����� ������� ���������� ������� �� ����� ���� � ��
	Two_Way_Pipe<float*, db_employee>* GetSearchPipe();

	//��������� ��������� �� �����, ����� ������� ��������� ���������� ������������� � ��
	Two_Way_Pipe<int, int>* GetRecognitionResultPipe();

	//��������� ��������� �� �����, ����� ������� �������� ���������� � �����������
	Two_Way_Pipe<int, std::vector<std::pair<int, std::string>>>* GetGroupSearchPipe();

private:

	//������� ����� ������
	void ThreadMethod() override;

	//������ ��������� ����������
	void ParseControlMess() override;

	//������ ��������� � ���������� ����������
	void RecognitionMess();

	//������ ��������� � ������ ���
	void SearchMess();

	//������ ��������� � ������ ������
	void GroupSearchMess();

	//����� ��� ������������ �������� ��������� � ������ ��� � ��
	Two_Way_Pipe<float*, db_employee>* search_pipe;

	//����� ��� �������� ��������� � �������������
	Two_Way_Pipe<int, int>* recognition_result;

	//������ ��� ������ ����������� � ������ �����
	Two_Way_Pipe<int, std::vector<std::pair<int, std::string>>> * group_search_pipe;

	//����������, ������������, ��� ����� ����� ������ ���������� ��������� ������
	bool work = true;
};

