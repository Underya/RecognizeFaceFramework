#include "pch.h"
#include "db_vcam.h"
#include <iostream>
using namespace std;
#include "db_connect.h"

//Обозначение имени таблицы
const string db_vcam::db_table_name = "camera";
const string db_vcam::add_proc_name = "addnewcamera";
const string db_vcam::edit_proc_name = "editcamera";
const string db_vcam::delete_proc_name = "deletecamera";

string db_vcam::GetAddress() {
	return address;
}

string db_vcam::GetPosition() {
	return position;
}

std::string db_vcam::GetDescription()
{
	return this->description;
}

db_premise db_vcam::GetPremise()
{
	if (premise == NULL) {
		return *(new db_premise(-1));
	}
	return *premise;
}

int db_vcam::GetUserId()
{
	return _user_id;
}

db_vcam db_vcam::addNewCamera(std::string address, std::string position, db_user user, int id_premisse)
{
	return addNewCamera(address, position, user.GetId(), id_premisse);
}

db_vcam db_vcam::addNewCamera(std::string address, std::string position, int id_user, int id_premisse) {
	CheckPosition(position);
	//Вызов соотвествующей процедуры
	//Формирование спика параметров для этого
	list<string>* params = new list<string>();
	params->push_back(address);
	params->push_back(position);
	//Описание
	params->push_back("");
	//Ид пользователя
	params->push_back(to_string(id_user));
	params->push_back(to_string(id_premisse));
	//Вызов процедуры
	db_connect* d = new db_connect();
	//id новой камеры
	int new_cam_id = 0;
	//Попытка вызова процедуры
	try {
		new_cam_id = d->ExecuteAddProcedure(add_proc_name, params);
	}
	catch (std::exception error) {
		cout << "Error! Not Creature new Camera. Text error: " << error.what()<< "\n Error code:" << -1 << "\n";
		throw error;
	}

	//Создание записи о камере прошло успешно - создание объекта камеры
	db_vcam vc(new_cam_id);
	delete d;
	//Возвращение объекта
	return vc;
}

int db_vcam::GetId()
{
	return _id;
}

void db_vcam::Delete()
{
	list<string> params = { to_string(_id) };
	connect.ExecuteProcedure(delete_proc_name, &params);
}

std::vector<db_vcam> db_vcam::GetAllLinkVcam(int id_user)
{
	//Запрос
	std::string query = "Select c.id from camera c where c.id_user=";
	query += to_string(id_user);
	db_connect conn;
	PGresult *res = conn.GetRowWithQuerry(query);
	//Получение количества камер
	int rowCount = PQntuples(res);
	//Буффер для сохранения результатов
	std::vector<db_vcam> buff;

	//Разбор результатов
	for (int i = 0; i < rowCount; i++) {
		int id = atoi(PQgetvalue(res, i, 0));
		buff.push_back(db_vcam(id));
	}

	return buff;
}

std::vector<db_vcam> db_vcam::GetAllLinkVcam(db_user user)
{
	return GetAllLinkVcam(user.GetId());
}

db_vcam::db_vcam(int id) {
	//Сохранение значений
	this->_id = id;
	//Запрос, для получения полной информации об объекте

	PGresult *db_inf = connect.GetOneRowById(db_table_name, id);
	this->address = PQgetvalue(db_inf, 0, 1);
	this->position = PQgetvalue(db_inf, 0, 2);
	this->description = PQgetvalue(db_inf, 0, 3);
	string id_premise = PQgetvalue(db_inf, 0, 4);
	_user_id = atoi(PQgetvalue(db_inf, 0, 5));
	//Если камера связана с помещением
	if (id_premise != "") {
		//То она сохраняет в себе указательн на помещение
		premise = new db_premise(atoi(id_premise.c_str()));
	} else {
		//Иначе - указать, что нет связанного помещения
		premise = NULL;
	}
	return;
}

db_vcam::~db_vcam() {
	try {
		//Если было привязано помещение, то оно тоже удаляется
		//if (premise != NULL)
			//delete premise;
	}
	catch (exception exp_b) {
		cout << "\nEXCEPTION\nLOCATION: db_vcam/~db_vcam\n";
		cout << exp_b.what();
	}
	catch (...) {
		cout << "\nEXCEPTION\nLOCATION: db_vcam/~db_vcam\n";
		cout << "Undefine Error\n";
	}
}

string db_vcam::GetInfo()
{
	return "id:" + to_string(_id) + " ;path:" + address + ";position:" + position + ";description:" + description + ";";
}

int db_vcam::SearchCam(string address)
{
	db_connect c;
	//Формирование запроса
	string query = "select c.id from camera c where c.address ='" + address + "'";
	//Выполнение запроса
	PGresult *res = c.GetRowWithQuerry(query);
	//Проверка, есть ли ответ
	if (PQntuples(res) == 1) {
		//Если есть камера с таким адрессом, то возвращается её id
		return atoi(PQgetvalue(res, 0, 0));
	} else {
		//Если не нашлось камеры с таким же адрессом
		return -1;
	}
		return 0;
}


void db_vcam::SetAddress(string address) {
	this->address = address;
	_db_update();
}

void db_vcam::SetPosition(string position) {
	
	CheckPosition(position);
	this->position = position;
	_db_update();
}

void db_vcam::SetDescription(string description){
	this->description = description;
	_db_update();
}

void db_vcam::SetPremise(int id_premise)
{
	//Проверка, а есть ли такое првещение
	db_premise *prem = new db_premise(id_premise);
	//Установка информации
	if (this->premise != NULL) {
		delete premise;
	}
	this->premise = prem;
	_db_update();
}

void db_vcam::CheckPosition(std::string position)
{
	if (position != "n" && position != "i" && position != "o")
		throw exception("Execption! Incorrect value . Allowed values: n, i, o");
}

void db_vcam::_db_update() {
	//Формирование парамтеров
	list<string> parametrs = { to_string(_id), address, position, description };
	//Вызов процедуры
	if (premise != NULL) {
		parametrs.push_back(to_string(premise->GetId()));
	}
	this->connect.ExecuteProcedure(edit_proc_name, &parametrs);
}
