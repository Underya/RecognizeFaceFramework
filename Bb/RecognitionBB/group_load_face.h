
#pragma once
#include <add_load_face.h>
#include <vector>

#ifdef RECOGNITIONBB_EXPORTS
#define RECOGNITIONBB_API __declspec(dllexport)
#else
#define RECOGNITIONBB_API __declspec(dllimport)
#endif



//����������� � ���, � ����� ������� ����������� ����
class RECOGNITIONBB_API group_load_face :
	public add_load_face
{
public:

	group_load_face();

	group_load_face(std::vector<std::pair<int, std::string>>);

	int GetCount();

	//�������� ����� ������ � ������
	void AddGroup(int id, std::string name);

	//�������� ���� ������ �����
	std::vector< std::pair<int, std::string>> GetGroups();

private:
	//���������� � �������, � ������� ����������� ������������
	//int - ��� id ������, string - ��������
	std::vector< std::pair<int, std::string> > groups;
};

