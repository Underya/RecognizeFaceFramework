#include "pch.h"
#include "db_connect.h"
#include <iostream>
using namespace std;
#include <sstream>

//Статические методы и свойства

//Определение статических переменных класса
int db_connect::db_connect_count_active = 0;
string db_connect::user_name = "";
string db_connect::address_db = "";
string db_connect::password = "";
string db_connect::host_db = "";
string db_connect::port_db = "";
PGconn * db_connect::static_connect = NULL;
bool db_connect::show_info = false;

bool db_connect::CheckUsedConnect() {
	if (show_info) cout << "DB_CONNECT: CONNECT COUNT = " << db_connect_count_active << "\n";
	//Если количество больше 0, то значит есть включённое соедененеие
	return db_connect_count_active;
}

PGconn* db_connect::GetMyConnect2()
{
	if (CheckUsedConnect()) {
		if (show_info) cout << "DB_CONNECT: Use existen connnect object\n";
		//Указать, что появился новый объект
		db_connect_count_active++;
		//Вернуть ссылку 
		return static_connect;
	}
	else {
		if (show_info) cout << "DB_CONNECT: Create new connect object\n";
		//Создать соеднение
		InitialConnect();
		db_connect_count_active++;
		return static_connect;
	}
}

//Создание соеденения с нуля
void db_connect::InitialConnect() {
	if (show_info) cout << "DB_CONNECT: Start connecting to data base\n";
	//Создать соеднение
		//oci_connect = envirnomet->createConnection(user_name, password, address_db);
		//Создание строки для подключения
	string connect_info = "host=" + host_db + " ";
	connect_info += "port=" + port_db + " ";
	connect_info += "dbname=";
	connect_info += address_db + " ";
	connect_info += "user=";
	connect_info += user_name + " ";
	connect_info += "password=";
	connect_info += password + " ";
	connect_info += "connect_timeout=10";
	//Подключение
	//static_connect = PQconnectdb("host=localhost port=5432 dbname=face_recognition user=postgres password=1 connect_timeout=10");
	static_connect = PQconnectdb(connect_info.c_str());
	if (PQstatus(static_connect) != CONNECTION_OK) {
		std::cout << "Connect not ok!\n";
		std::cout << "Status:" << PQstatus(static_connect) << "\n";
		string error_code = "ErrorCode:" + to_string(PQstatus(static_connect)) + "\n";
		throw exception(("EXCEPTION\nLOCATION: db_connect/InitialConnect\n" + error_code).c_str());
	}
	//Если в пределах одной сессии было неудачное закрытие
	db_connect_count_active = 0;
	if (show_info) cout << "DB_CONNECT: Success connecting to data base\n";

}
  
//Вызывается, когда один из объектов закачнивает работу
void db_connect::CloseConnect() {
	db_connect_count_active--;
	if (show_info) cout << "DB_CONNECT: survavie " << db_connect_count_active << " object\n";
	if (!CheckUsedConnect()) EndConnect();
}

//Вызывается, когда больше не осталось объектов
void db_connect::EndConnect() {
	if (show_info) cout << "DB_CONNECT: delete all db_connect object and close connect\n";
}

//Указание информации о подключении с базой данных
void db_connect::SetInfoConnect(string host, string port, string user_name, string password, string address_db, bool show_info) {
	db_connect::host_db = host;
	db_connect::user_name = user_name;
	db_connect::password = password;
	db_connect::address_db = address_db;
	db_connect::show_info = show_info;
	db_connect::port_db = port;
}

void db_connect::SetInfo(bool inf)
{
	show_info = inf;
}

//НЕ статические методы
db_connect:: db_connect() {
	//Получение соеденения
	my_connect2 = GetMyConnect2();
}

db_connect:: ~db_connect() {
	CloseConnect();
}

PGresult* db_connect::GetAllRowTable2(std::string nameTables)
{
	//Строка с запросом
	string query = "select * from " + nameTables;
	if (show_info) cout << "DB_CONNECT: Query Text: " << query << "\n";
	//Выполнение запроса 
	//Возвращение указателя на результат
	return GetRowWithQuerry(query);
}

PGresult* db_connect::GetOneRowById(std::string nameTables, int id)
{
	string id_str = to_string(id);

	string query = "select * from " + nameTables + " t where t.id = " + id_str;
	if (show_info) cout << "DB_CONNECT:  Query Text: " << query << "\n";
	//Выполнение запроса
	PGresult * res = GetRowWithQuerry(query);
	//Проверка, что есть хотя бы одна строка
	if (PQntuples(res) < 1) throw exception("Errror! Not rows in query");

	return res;
}

PGresult* db_connect::GetRowWithQuerry(std::string query)
{
	//Выполнение запроса 
	PGresult* res = PQexec(my_connect2, query.c_str());
	//Проверка результата
	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		string error = "Exception! Query Select not success! Error_code:";
		error += to_string(PQresultStatus(res));
		throw exception(error.c_str());
	}
	//Возвращение указателя на результат
	return res;
}


int db_connect::ExecuteAddProcedure(string name, list<string>* parametrsProcedure) {
	
	//Создание строки с вызовом функции
	string query;
	query = "select public." + name + "(";

	for (auto iter = parametrsProcedure->begin(), end = parametrsProcedure->end(); iter != end; iter++) {
		//Если значение параметра = null, то оно не берётся в скбоки
		if (*iter == "null") {
			query += *iter + ", ";
			continue;
		}
		query += "'" + *iter + "', ";
	}
	query[query.size() - 2] = ')';

	if (show_info) cout << "  DB_CONNECT: QUERY_TEXT:" << query << "\n";

	PGresult *res = PQexec(static_connect, query.c_str());
	
	if (PQntuples(res) == 0) throw exception("Error! Not result back!");

	int new_id = atoi(PQgetvalue(res, 0, 0));

	return new_id;
}

void db_connect::ExecuteProcedure(string name, list<string>* parametrsProcedure) {

	string query;
	query = "select public." + name + "(";

	for (auto iter = parametrsProcedure->begin(), end = parametrsProcedure->end(); iter != end; iter++) {
		query += "'" + *iter + "', ";
	}
	query[query.size() - 2] = ')';

	if (show_info) cout << "DB_CONNECT: QUERY_TEXT:" << query << "\n";

	PGresult* res = PQexec(static_connect, query.c_str());

	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		string error = "Exception! Query Select not success! Error_code:";
		error += to_string(PQresultStatus(res));
		throw exception(error.c_str());
	}

	return;
}