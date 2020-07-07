#pragma once
#include <vector>
#include "db_face.h"
#include "db_group.h"

//Сотрудник или другой объект, у которого есть лицо в базе данных
class DB_API db_employee :
	public db_row
{
public:

	//Объект созданный по информации в БД, с таким же id
	db_employee(int id);

	db_employee();

	~db_employee();

	//Методы для получения информации о сотруднике

	//Имя сотрудника
	std::string GetFirstName();
	//Фамилия сотрудника
	std::string GetLastName();
	//Отчество сотрудника
	std::string GetMidleName();
	//Получить id в другой системе
	//-1 - отсуствие id
	int GetOtherId();

	//Получение описания сотрудника
	std::string GetDescrInfo();
	//Полученеи списка всех лиц сотрудника
	std::list<db_face> GetListDescr();
	//Получение id записи
	int GetId();
	//Методы для изменения информации

	//Задать имя
	void SetFirstName(std::string F_Name);
	//Задать фамилию
	void SetLastName(std::string L_Name);
	//Задать отчество
	void SetMidName(std::string M_Name);
	//Задать идентификатор в другой системе
	void SetOtherId(int other_id);

	//Указание описания сотрудника
	void SetDescrInfo(std::string info);

	//Добавление к сотруднику нового дескриптора, информация о котором сохранится в бд
	void AddNewDescriptor(float* desc);
	
	//Добавление к сотруднику нового дескриптора, информация о котором сохранится в бд
	void AddNewDescriptor(std::string desc);

	//Создание нового сотрудника и информации о нём в БД
	static db_employee* AddNewEmployee(std::string first_name, std::string last_name, std::string midle_name, std::string descInfo = "", int other_id = -1);
	
	//Удаление объекта и информации о его лицах из БД
	void Delete() override;

	//Получение списка всех сотрудников, подходящих под условия
	static std::vector<db_employee >* GetEmployeeWithCondition(db_group group);

	//Получение списка все сотрудников, из списка всех групп
	static std::vector<db_employee >* GetEmployeeWithCondition(std::vector<db_group> groups);

	//Перегрузка оператора сравнения
	//Для того, что бы его можно передавать через каналы
	friend bool DB_API operator== (const db_employee& c1, const db_employee& c2);

private:

	//Список групп, к которым привязан данный сотрудник
	std::list<db_group*> _my_groups;

	//Наименование сотрудника

	//Имя
	std::string _f_name;
	//Фамилия
	std::string _l_name;
	//Отчество
	std::string _m_name;

	//Описание сотрудника
	std::string _descr;

	//Идентификатор 
	int _other_id = -1; 


	//Список со всеми лицами сотрудника
	std::list<db_face> _faceList;

	//Соеденение с БД
	db_connect *_connect;

	//Получение всех связанных с объектом дескрипторов из БД
	void _ReviewAllDesc();

	//Сохранение информации об изменениях в БД
	void _db_update() override;

	//Константы имён разных объектов из БД
	//Название таблицы с информацией
	const static std::string db_table_name;
	const static std::string add_proc_name;
	const static std::string edit_proc_name;
	const static std::string delete_proc_name;
};

