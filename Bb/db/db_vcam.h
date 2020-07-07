#pragma once

#include <iostream>
#include "db_premise.h"
#include "db_user.h"

//������, ���������� � ����������� � ������ � ���� ������
class DB_API db_vcam:
	public db_row
{
public:

	//��������� ������ ������
	std::string GetAddress();
	//��������� ������� ������
	std::string GetPosition();
	//��������� �������� ������
	std::string GetDescription();
	//��������� ���������� � ������� ���������
	db_premise GetPremise();
	//�������� id �����, ���������� � ���� �������
	int GetUserId();

	//��������� ����� � ���� ������
	void SetAddress(std::string newAddr);
	//��������� ������� � ���� ������
	void SetPosition(std::string Position);
	//��������� �������� ������
	void SetDescription(std::string description);
	//���������� ��������� ��� ������
	void SetPremise(int id_premise);

	//����������� �� ���������
	db_vcam(int id);
	//���������� �� ���������
	~db_vcam();

	//��������� ����� ���������� � ���� ������ ������
	std::string GetInfo();

	//��������, ���� �� � �� ������ � ����� �� �������
	static int SearchCam(std::string addrress);

	//�������� ����� ������ � ���� ������
	static db_vcam addNewCamera(std::string address, std::string position, db_user user, int id_premisse = -1);
	//�������� ����� ������ � ���� ������
	static db_vcam addNewCamera(std::string address, std::string position, int id_user, int id_premisse = -1);

	//��������� ID ������ �� ��
	int GetId();

	//�������� ���������� � ������
	void Delete();

	//��������� ���� ��������� � ������������� �����
	static std::vector<db_vcam> GetAllLinkVcam(int id_user);

	//��������� ���� ��������� � ������������� �����
	static std::vector<db_vcam> GetAllLinkVcam(db_user user);

private:
	//����� ������ (IP ��� Web)
	std::string address;
	//������������� ������ � ���� ������
	int _id;
	//������������� ������������
	int _user_id;
	//������������ ������ ������������ ���������
	std::string position;
	//�������� ������
	std::string description;

	//��������, ����� �� ������� ���������� ��������. ���� �� �����, ��������� ������
	static void CheckPosition(std::string position);

	//���������� � ����� ������, ����� ������� �������� ��� �������
	db_connect connect;

	//���������, � ������� ������� ������
	db_premise *premise;

	//���������� ���������� � ������� � ���� ������
	//����������, ����� ���������� ������ �������, ���������� ������
	void _db_update();

	//��������� ��� ������ �������� �� ��
	//�������� ������� � �����������
	const static std::string db_table_name;
	const static std::string add_proc_name;
	const static std::string edit_proc_name;
	const static std::string delete_proc_name;
};

