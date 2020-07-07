
#pragma once
#include "IRecognitionHandler.h"
#include "timer_list.h"
#include "file_recognition_coder.h"

class RECOGNITIONBB_API fileRecognitionHandler :
	public IRecognitionHandler
{
public:

	//����������� �� ���������
	fileRecognitionHandler(std::string fileName, int id_camera, double second);

	~fileRecognitionHandler();

	//��������� ������������ ���
	void HandlerFace(int cam_id, std::vector<std::string> premise_name, face face, list_rules rules, list_group group, information_camera camera_info) override;

	//������ ������, ������� ������� � ������� �������
	void SetRulesList(list_rules listRules);

	void EndWork() override;

private:
	
	//������, ������� ���������� �������� ��������� � �������������
	timer_list<int> *tlist;

	//����� ���� ������ ��������������� ������ � ������
	file_recognition_coder *frr = NULL;

	//�������� ���������� � ������
	int _id_camera = -1;
};

