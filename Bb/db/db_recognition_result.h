#pragma once
#include "db_connect.h"
#include <string>
#include <vector>
#include <list>
#include "oneRecognit.h"

//Добавление и чтение результатов распознования объектов
class DB_API db_recognition_result
{
public:

	//Добавление нового результата распознования
	void addNewRecognitionResult(int id_employee, int id_camera);

	//Получение всех результатов распознования
	//В форматае id \n id_employee \n id_camera \n time_rec\n
	std::vector<std::string> GetRecogntionAll();

	//Получение данных по времени, камере и сотруднике
	//значение -100 означает, что данный параметр не проверяется
	std::vector<oneRecognit> GetRecognitionResult(int id_cam = -100, int id_employee = -100, time_t start_time = -100, time_t end_time = -100);


private:
	
	oneRecognit GetOneRecognit(int id_row, PGresult* res);

	//Преобразование времени из строкового формата БД в формат time_t
	time_t GetTime(std::string time);

	//Преобразование времени из внутреннего формата в строковый формат БД
	std::string GetTime(time_t time);

	//Соеденение с БД
	db_connect conn;
};

