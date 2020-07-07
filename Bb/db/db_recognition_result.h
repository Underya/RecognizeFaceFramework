#pragma once
#include "db_connect.h"
#include <string>
#include <vector>
#include <list>
#include "oneRecognit.h"

//���������� � ������ ����������� ������������� ��������
class DB_API db_recognition_result
{
public:

	//���������� ������ ���������� �������������
	void addNewRecognitionResult(int id_employee, int id_camera);

	//��������� ���� ����������� �������������
	//� �������� id \n id_employee \n id_camera \n time_rec\n
	std::vector<std::string> GetRecogntionAll();

	//��������� ������ �� �������, ������ � ����������
	//�������� -100 ��������, ��� ������ �������� �� �����������
	std::vector<oneRecognit> GetRecognitionResult(int id_cam = -100, int id_employee = -100, time_t start_time = -100, time_t end_time = -100);


private:
	
	oneRecognit GetOneRecognit(int id_row, PGresult* res);

	//�������������� ������� �� ���������� ������� �� � ������ time_t
	time_t GetTime(std::string time);

	//�������������� ������� �� ����������� ������� � ��������� ������ ��
	std::string GetTime(time_t time);

	//���������� � ��
	db_connect conn;
};

