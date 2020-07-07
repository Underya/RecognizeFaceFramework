#pragma once
//�����, ��������� ���������� � ����� ������
//� ��������������� ���������, ������� ��������� �������� ���� �������� � ��
//�� ��� ��������
#include <iostream>
#include <list>
#include "./..//libpq/include/libpq-fe.h"
#include "db_row.h"

#ifdef DB_EXPORTS
#define DB_API __declspec(dllexport)
#else
#define DB_API __declspec(dllimport)
#endif

//�����, ��������������� ������ ��� ������ � ��
//����� ��������� �������� ���������� ������� ����� setInfoConnect � ����������� �����������
class DB_API db_connect {

public:

	//��������� ���� ������� �� �������, �������� ������� �������� � ���������
	PGresult* GetAllRowTable2(std::string nameTables);

	//��������� ������ ���������� �� ����� ������� � ��������� id (� ����� ������� ������ ���� ������� id)
	PGresult* GetOneRowById(std::string nameTables, int id);

	//���������� ������� SELECT � ����� �������
	PGresult* GetRowWithQuerry(std::string query);

	//���������� ��������� ��� ������������� ��������
	//���� ��������� ��������� �������, ����� true, ����� - false
	//������� ��������� ������ ����� ����������, ����� ���� ����. ���������� ��������� ������ ���� ����������
	void ExecuteProcedure(std::string name, std::list<std::string>* parametrsProcedure);

	//���������� ������� � �������� ������� ����������
	//������� ���������� ���� ����������
	//����� ���� ���������
	//���������� �������� � ������� ������ ���� ����������
	//�� ���� ���������� ��������� ��������, � ������������ ���������
	//���� ����������� ������ ���������: string, number
	int  ExecuteAddProcedure(std::string name, std::list<std::string> * parametrsProcedure);


	//����������� �� ���������
	db_connect();

	//���������� �� ���������
	~db_connect();

	//�������� ���������� ��� �����������
	//show_info - ����, �����������, ���� �� �������� � ������� ���������� � ���������. ������������ ��� ������
	static void SetInfoConnect(std::string host, std::string port, std::string user_name, std::string password, std::string adress_db, bool show_info = false);

	//���������, ���� �� �������� ���������� � ��������
	static void SetInfo(bool inf);

protected:

	//������� ���������� �������� �������� db_connect
	static int db_connect_count_active;

	//��������� �� ����� ��� ���� � ���������� ����������
	static PGconn * static_connect;

	//���������� ��� �������� ����������
	static std::string user_name;
	static std::string password;
	static std::string address_db;
	static std::string host_db;
	static std::string port_db;

	//����, �������������� ��� ����, ��� �� �������� ��� �� �������� �������� ����������
	static bool show_info;

	//��������� Oracle. �����������, ��� �� ������� ��� ��������� ����� ����������


	PGconn* my_connect2;
	//��������� �� �������� ������� ���������� ������
	
	//������ �������� � �� � ������� occi
	//� ���������, ���� �� ����� �� ���� ����������
	static void InitialConnect();

	//��������� ����� � �����������
	//����������, ����� �� �������� ������ ��������, ������������ ����������
	static void EndConnect();

	//��������, ���� �� �������� �����������
	static bool CheckUsedConnect();

	//���������� �������� ���������� ������ db_connect ������ Connect
	static PGconn* GetMyConnect2();

	//� ��� ������� ������� ��������� ������ db_connect ���������, ��� �� �������� ������
	static void CloseConnect();
};

