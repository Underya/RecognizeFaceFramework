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

//Получение списка камер
list<db_vcam> &db_manager::GetVcamList(string condition) {
    //Создание объекта для работа с БД
    db_connect* db = new db_connect();

    //Формирование запроса к бд на получении информации
    string query = "SELECT t.id FROM bb_camera t ";
    query += condition;

    //Переменная для сохранения результа запроса
    PGresult *rs = NULL;

    //Выполнение запроса
    try {

        rs = db->GetRowWithQuerry(query);

    }
    catch (exception exp1) {
        
        cout << "\nEXCEPTION\nLOCATION: db_manager/GetVcamList\n";
        throw exp1;
    }

    //Список с созданными объектами
    list<db_vcam> *list = (new std::list<db_vcam>());

    //Разбор результатов и заполнение списка
    for (int i = 0, max = PQntuples(rs); i < max; i++) {
        int id = atoi(PQgetvalue(rs, i, 0));
        list->push_front(*(new db_vcam(id)));
    }

    delete db;

    //Возврат полученного списка
    return *(list);
}



int db_manager::SearchFace(float * desc)
{
    //Вызов соотвествующего метода
	return db_face::SearchFace(desc);
}

int db_manager::SearchFace(string desc)
{
    //Вызов соотвествующего метода
    return db_face::SearchFace(desc);
}

void db_manager::AddResultRecognit(int id_face, int id_camera)
{
    //Создание нового объекта, и доабвление в него вызова
    db_recognition_result dbrr;
    dbrr.addNewRecognitionResult(id_face, id_camera);
}
