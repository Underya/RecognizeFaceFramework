#pragma once
#include "file_parametr.h"
#include <list>
#include <vector>

//������� ���������� � ������������ ���, ��� ��������� ������ � �������
namespace rule_link_obj {

	//����� ������� � ��������
	class FILEMANAGER_API rule_link_obj :
		public file_parametr
	{
	public:

		//�������� �������, ������� ��������� � �������� �����
		rule_link_obj(std::string file_name);

		//������ ������
		rule_link_obj();

		~rule_link_obj();

		//���������� ����� ����� ������� � ��� ��
		void AddNewLink(int rule_id, int id);

		//�������� ����� ������� � ��� ��
		void DeletLink(int rule_id, int id);

		//��� �������, ��������� � ��������
		std::vector<int> GetLinkedId(int id_obj);

	protected:

		//����� ������� � ������� �������
		std::list<std::pair<int, int>> linked;

		//������ ����������� ����� � ������������� �������
		void ReceivInfo();

		//��������� ���� ������  ���� ������ ��� ���������� � ����
		std::string GetContentList() override;

	};

}
