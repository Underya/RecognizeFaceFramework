#pragma once
#include "db_connect.h"
#include "db_premise.h"

class DB_API db_rule :
	public db_row
{
public:

	db_rule(int id);

	~db_rule();

	//Получить ID строки, ассоцированной с текущим правилом
	int GetId();

	//Получить название правила
	std::string GetName();

	//Указать новое имя
	void SetName(std::string new_name);

	//Получить описание правила
	std::string GetDesc();
	
	//указать новое описание
	void SetDesc(std::string new_desc);

	//Получение всех правил из БД
	static std::vector<db_rule> GetAllRule();

	//Добавление нового правила
	static db_rule AddNewRule(std::string name, std::string desc);

	//Удаление объекта из памяти
	void Delete() override;

	//Привязать камеру к правелу
	void LinkCamera(int camera);

	//Привязать помещение к правилу
	void LinkPremise(db_premise premise);
	void LinkPremise(int premise);

	//Связать между собой камеру и правило
	static void LinkedWithRuleCamer(int cam, int rule);

	//Связать между собой помещение и правило
	static void LinkedWithRule(db_premise premise, db_rule rule);
	static void LinkedWitRulePremise(int premise, int rule);


protected:

	//Идентификатор строки в БД
	int _id;
	//Название правила
	std::string _name;
	//Описание правила
	std::string _desc;

	//Соеденение с базой данных
	db_connect _connect;
	
	//Обновление информации о БД
	void _db_update();

	//Информация о таблице, с которой связан объект
	const static std::string table_name;
	const static std::string add_proc_name;
	const static std::string edit_proc_name;
	const static std::string delete_proc_name;
};

