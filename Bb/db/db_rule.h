#pragma once
#include "db_connect.h"
#include "db_premise.h"

class DB_API db_rule :
	public db_row
{
public:

	db_rule(int id);

	~db_rule();

	//�������� ID ������, �������������� � ������� ��������
	int GetId();

	//�������� �������� �������
	std::string GetName();

	//������� ����� ���
	void SetName(std::string new_name);

	//�������� �������� �������
	std::string GetDesc();
	
	//������� ����� ��������
	void SetDesc(std::string new_desc);

	//��������� ���� ������ �� ��
	static std::vector<db_rule> GetAllRule();

	//���������� ������ �������
	static db_rule AddNewRule(std::string name, std::string desc);

	//�������� ������� �� ������
	void Delete() override;

	//��������� ������ � �������
	void LinkCamera(int camera);

	//��������� ��������� � �������
	void LinkPremise(db_premise premise);
	void LinkPremise(int premise);

	//������� ����� ����� ������ � �������
	static void LinkedWithRuleCamer(int cam, int rule);

	//������� ����� ����� ��������� � �������
	static void LinkedWithRule(db_premise premise, db_rule rule);
	static void LinkedWitRulePremise(int premise, int rule);


protected:

	//������������� ������ � ��
	int _id;
	//�������� �������
	std::string _name;
	//�������� �������
	std::string _desc;

	//���������� � ����� ������
	db_connect _connect;
	
	//���������� ���������� � ��
	void _db_update();

	//���������� � �������, � ������� ������ ������
	const static std::string table_name;
	const static std::string add_proc_name;
	const static std::string edit_proc_name;
	const static std::string delete_proc_name;
};

