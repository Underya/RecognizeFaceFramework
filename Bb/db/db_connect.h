#pragma once
//Класс, создающий соеденение с базой данной
//И предоставляющий интерфейс, который выполняет основные виды действий с бД
//Не для экспорта
#include <iostream>
#include <list>
#include "./..//libpq/include/libpq-fe.h"
#include "db_row.h"

#ifdef DB_EXPORTS
#define DB_API __declspec(dllexport)
#else
#define DB_API __declspec(dllimport)
#endif

//Класс, предоставляющий методы для работы с БД
//Перед созданием объектов необходимо вызвать метод setInfoConnect с правильными параметрами
class DB_API db_connect {

public:

	//Получение всех строчек из таблицы, название которой передано в параметре
	PGresult* GetAllRowTable2(std::string nameTables);

	//Получение полной информации об одной строчке с выбарнным id (у такой таблицы должна быть колонка id)
	PGresult* GetOneRowById(std::string nameTables, int id);

	//Выполнение запроса SELECT с любым текстом
	PGresult* GetRowWithQuerry(std::string query);

	//Выполнение процедуры без возвращаяемых значений
	//Если процедура выполнена успешно, вернёт true, иначе - false
	//Сначала передаётся список типов параметров, затем сами типы. Количество элементов должно быть одинаковым
	void ExecuteProcedure(std::string name, std::list<std::string>* parametrsProcedure);

	//Выполнение функции с указаным списком параметров
	//Сначала передаются типы параметров
	//Затем сами параметры
	//Количество элеметов в списках должно быть одинаковым
	//Не надо передавать последний параметр, с возвращающим значением
	//Типы парамаетров бывают следующие: string, number
	int  ExecuteAddProcedure(std::string name, std::list<std::string> * parametrsProcedure);


	//Конструктор по умолчанию
	db_connect();

	//Деструктор по умолчанию
	~db_connect();

	//Указание информацию для подключения
	//show_info - флаг, указывающий, надо ли выводить в консоль информацию о действиях. Используется для тестов
	static void SetInfoConnect(std::string host, std::string port, std::string user_name, std::string password, std::string adress_db, bool show_info = false);

	//Установка, надо ли выводить информацию о соедении
	static void SetInfo(bool inf);

protected:

	//Текущее количество активных объектов db_connect
	static int db_connect_count_active;

	//Указатель на общее для всех и запущенное соеденение
	static PGconn * static_connect;

	//Информация для создания соеденения
	static std::string user_name;
	static std::string password;
	static std::string address_db;
	static std::string host_db;
	static std::string port_db;

	//Флаг, использующийся для того, что бы выводить или не выводить тестовую информацию
	static bool show_info;

	//Окружение Oracle. Сохраняется, что бы закрыть его корректно после выполнения


	PGconn* my_connect2;
	//Указатель на соедение данного экземпляра класса
	
	//Создаёт соедение с бд с помощью occi
	//И вызвается, если до этого не было соеденений
	static void InitialConnect();

	//Закрывает связь с соеденением
	//Вызывается, когда не осталось больше объектов, использующий соеденение
	static void EndConnect();

	//Проверка, есть ли активные соедненения
	static bool CheckUsedConnect();

	//Возвращает текущему экземпляру класса db_connect объект Connect
	static PGconn* GetMyConnect2();

	//С его помощью текущий экземпляр класса db_connect указывает, что он закончил работу
	static void CloseConnect();
};

