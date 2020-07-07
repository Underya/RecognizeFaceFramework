#pragma once
#include "db_connect.h"
#include <string>
#include <vector>

//Объект, асоциирущийся с информацией о помещении из БД
class DB_API db_premise :
	public db_row
{
public:

	//Создание одиночног объекта
	db_premise(int id);

	//декструктор по умолчанию
	~db_premise();

	//ID данного объекта
	int GetId();

	//Добавить помещение 
	//Значение -1 убирает родителя
	void SetParrent(int id_premise);

	//Название объекта
	std::string GetName();

	//Указать новое наименование объекта
	void SetName(std::string new_name);

	//Описание объекта
	std::string GetDesc();

	//Указать новое описание объекта
	void SetDesc(std::string new_description);
	
	//Получение ID предка
	int GetIdParent();

	//Добавить дочернее для текущего объекта помещение
	db_premise AddNewChlidren(std::string Name, std::string Desc = "");

	//Полученеи вектора со всеми предками для текущего помещения
	std::vector<db_premise> GetAllParent();

	//Получить все имеющиеся в БД помещения
	static std::vector<db_premise> GetAllPremise();

	//Создание новой записи о помещении
	static db_premise AddNewPremise(std::string Name, std::string Desc = "", int id_parent = -1);

	//Удаление текущего объекта
	void Delete() override;

protected:

	//Обновление информации об объекте в БД
	void _db_update();

	//Идентификатор строки из БД
	int _id = -1;
	//Наименование
	std::string _name;
	//Описание
	std::string _descrtipt;
	//Идентификатор родительского помещения
	int _id_parent = -1;

	//Указатель на соеденение с БД
	db_connect _connect;

	//Информация о таблице, с которой связан объект
	const static std::string table_name;
	const static std::string add_proc_name;
	const static std::string edit_proc_name;
	const static std::string delete_proc_name;
};

