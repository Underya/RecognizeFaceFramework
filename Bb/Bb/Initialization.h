#pragma once
#include <string>

//Класс, которые проверяет стартоввую информацию об системе, и если её нет, запрашивает
class Initialization
{
public:

	//Начало проверки
	void Start();

	//Указание, берёться ли информация из файлов
	bool HasImport();

	std::string GetAdress();

	std::string GetPort();

	std::string GetDBName();

	std::string GetUser_Name();

	std::string GetPassword();

protected:

	//Адрес БД
	std::string _db_address;

	//Порт БД
	std::string _port;

	//Название БД
	std::string _db_name;

	//Имя пользовател
	std::string _name;

	//Пароль пользователя
	std::string _password;

	//Сохранить информациию о том, что используется импортирование
	void SetImportInfo();

	//Загрузка информации о ДБ
	void LoadDB();

	//Загрузка информации об импорте
	void LoadImport();

	//Провекра, есть ли параметры 
	bool ConfigEmpty();

	//Стартовый диалог при заупске пустой программы
	void StartDialog();

	//Диалог с пользователем для получения информации о БД
	void DBDialog();

	//Сохранение информации о БД в зашифрованном файле
	void SaveDBInfo();

	//Флаг указывающий, что информация берётся из файлов
	bool _import = false;
};

