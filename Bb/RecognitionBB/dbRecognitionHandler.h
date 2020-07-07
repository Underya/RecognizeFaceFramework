
#pragma once
#include "pch.h"
#include "IRecognitionHandler.h"
#include "db_manager_parralel.h"
#include "timer_list.h"

//��������� ����������� ������������� ���������� ���������� � ��
class RECOGNITIONBB_API  dbRecognitionHandler:
	public IRecognitionHandler
{
public:

	dbRecognitionHandler(int id_camera, double second = 60.0);

	~dbRecognitionHandler();

	//��� ������������� ���� ��������� ��������� � ��
	void HandlerFace(int cam_id, std::vector<std::string> premise_name, face face, list_rules rules, list_group group, information_camera camera_info) override;

	//��������� ������ ������, ���������� � ������� �������
	void SetRulesList(list_rules listRules);

private:

	//��� �� �� ������������ ����������� �� ������������� ����� � ���� �� ��������
	//���������� � ��� ���������� ������������ � ������� ����� ������

	//������ ���, ��� ���������� � ��� ���� ������ ��� ���������
	//std::list<std::pair<int, clock_t>> timeList;

	timer_list<int> *timeList;

	//��� ���������� ���������� � ��
	db_manager_parralel dbrr;

	//�� ������, � ������� ���������� ����������
	int id_camera;
};

