//
//
//  �� ����� 03.02.2020
//
//



#pragma once
#include <list>
#include <iostream>
using namespace std;
#include "Condition.h"
#include "db_vcam.h"

#ifdef DB_EXPORTS
#define DB_API __declspec(dllexport)
#else
#define DB_API __declspec(dllimport)
#endif


class DB_API cameraCollect_db
{
	//��������� �� ������ �� ����� ���������� ���������
	list<db_vcam>* cammCollection;

	static cameraCollect_db* GetCollectionCamera(Condition c);

private:

	//�������� ������������ �� ���������, ��� ����
	//��� �� ����� ���� �������� ��������� ������ �� �������
	cameraCollect_db();

	~cameraCollect_db();
}; 

