// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the DB_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// DB_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#pragma once
#ifdef DB_EXPORTS
#define DB_API __declspec(dllexport)
#else
#define DB_API __declspec(dllimport)
#endif

#include <list>
//Класс информации о камере в бд
#include "db_vcam.h"
#include "db_face.h"
#include "db_recognition_result.h"
#include "db_employee.h"

// Предоставляет самые необходимые методы для работа с БД
class DB_API db_manager {

public:
	//Коснтруктор по умолчнаию 
	db_manager();

	//Установка информации для соеденения с БД
	static void SetConnectInfo(std::string host, std::string port, std::string user_name, std::string password, std::string address_db, bool show_info);

	//Получение полной коллекции камер
	//condition - Тескстовое условие в виде SQL текста для получения списка камер
	//Пример: "where bb_camera.id in (1, 2, 3)"
	std::list<db_vcam> &GetVcamList(std::string condition = "");

	//Поиск лица в базе данных
	int SearchFace(float * desc);
	int SearchFace(std::string desc);

	//Добавление результата распознования
	void AddResultRecognit(int id_face, int id_camera);
};

