#pragma once
#include <iostream>
#include <list>
#include <string>

#ifdef DB_EXPORTS
#define DB_API __declspec(dllexport)
#else
#define DB_API __declspec(dllimport)
#endif

//�������, ������� ��������� � ���������� 
//��� ��������� ���������� ��������� �������� � ����������� �� ��
//(�������� - ������, ������������� �� ����� ������)
class DB_API Condition
{
public:

	Condition();

	//�������� �������� ������, ������� ���������� ������ 
	void AddGroup(int id_group);

	//��� ������, ������� ���������� ��������
	std::list<int> GetGroup();

	//�������� ������ ����
	void ClearGroup();

	//���������� ���������, ���������� � ������� ���������� ��������
	void AddPremise(int id_premise);

	std::list<int> GetPremise();

	void ClearPremise();



private:
	//������ �����, ������� ���� ��������
	std::list<int> _group;

	std::list<int> _premise;
};

