#pragma once
#include <iostream>

#ifdef FACERECOGNITION_EXPORTS
#define FACERECOGNITION_API __declspec(dllexport)
#else
#define FACERECOGNITION_API __declspec(dllimport)
#endif

//�������������� ����������, ������� ������������� � �����
//����� ����������� ��� ����, ��� �� ���������� ���������� ������ � �������������� �����
class FACERECOGNITION_API add_load_face
{
public:

	add_load_face();

	virtual std::string GetType();

protected:
	std::string _this_type;
};