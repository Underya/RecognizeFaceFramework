
#pragma once
#include "thread_obj.h"
#include <db_recognition_result.h>

class RECOGNITIONBB_API dbRecognitionObj :
	public thread_obj
{
public:

	//������ ��� ������ � ������� �������
	simple_pipe<std::pair<int, int>> GetInfoPipe;



private:
	//�����, ���������� ��� ������� �������
	void ThreadMethod() override;

	//����� ��� �������� ���������� � ���, ��� ���� � �� ��������
	//� ������� id ����������, id ������
	simple_pipe<std::pair<int, int>> id_pipe;

	//��������� �� ������ ��� ������ � ��
	db_recognition_result* db_result;
};

