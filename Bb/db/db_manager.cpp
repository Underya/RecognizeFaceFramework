// db.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "db_manager.h"
#include "db_connect.h"
using namespace std;

// This is the constructor of a class that has been exported.
db_manager::db_manager()
{
}

void db_manager::SetConnectInfo(string host, string port, string user_name, string password, string address_db, bool show_info) {
    db_connect::SetInfoConnect(host, port, user_name, password, address_db, show_info);
}

//��������� ������ �����
list<db_vcam> &db_manager::GetVcamList(string condition) {
    //�������� ������� ��� ������ � ��
    db_connect* db = new db_connect();

    //������������ ������� � �� �� ��������� ����������
    string query = "SELECT t.id FROM bb_camera t ";
    query += condition;

    //���������� ��� ���������� �������� �������
    PGresult *rs = NULL;

    //���������� �������
    try {

        rs = db->GetRowWithQuerry(query);

    }
    catch (exception exp1) {
        
        cout << "\nEXCEPTION\nLOCATION: db_manager/GetVcamList\n";
        throw exp1;
    }

    //������ � ���������� ���������
    list<db_vcam> *list = (new std::list<db_vcam>());

    //������ ����������� � ���������� ������
    for (int i = 0, max = PQntuples(rs); i < max; i++) {
        int id = atoi(PQgetvalue(rs, i, 0));
        list->push_front(*(new db_vcam(id)));
    }

    delete db;

    //������� ����������� ������
    return *(list);
}



int db_manager::SearchFace(float * desc)
{
    //����� ��������������� ������
	return db_face::SearchFace(desc);
}

int db_manager::SearchFace(string desc)
{
    //����� ��������������� ������
    return db_face::SearchFace(desc);
}

void db_manager::AddResultRecognit(int id_face, int id_camera)
{
    //�������� ������ �������, � ���������� � ���� ������
    db_recognition_result dbrr;
    dbrr.addNewRecognitionResult(id_face, id_camera);
}
