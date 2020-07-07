#pragma once

#include <face.h>
#include "group_load_face.h"
#include "..///face_detection/information_camera.h"

//������� ������ ������
typedef std::vector<std::pair<int, std::string>> list_rules;
typedef std::vector<std::pair<int, std::string>> list_group;

class RECOGNITIONBB_API IRecognitionHandler {
public:

	//�����, ������� ���������� ��� ������������� �������
	//� ������� ���������� � �����, ������� ���������� ����������� �������
	virtual void RecognitionFace(face face, information_camera camera_info);

	//�����, ������� ���������� �����������
	//���� �������� ��� ���������� � ���������
	virtual void HandlerFace(int cam_id, std::vector<std::string> premise_name, face face, list_rules rules, list_group group, information_camera camera_info) = 0;

	//���������� ���������� ������ ������, ��������� � �������
	virtual void SetRulesList(list_rules listRules) = 0;

	//�����, ����� ������� ������� ����������� ���������� � ���, ��� ����� �������� ������
	virtual void EndWork();

	void SetId(int id_cam);

	virtual void SetPremisesList(std::vector<std::string> listPremise);

protected:

	std::vector<std::string> premieses;

	int _id_cam = -1;

	list_rules _listRules;

};

