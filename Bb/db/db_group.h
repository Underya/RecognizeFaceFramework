#pragma once
#include "db_row.h"
#include "db_connect.h"

#include <vector>

//Группа, в которых состоят пользователи
class DB_API db_group :
	public db_row
{
public:

	//Создание одинчного объекта по id
	db_group(int id);

	//Смерть одинчного объекта
	~db_group();

	//Установить новое имя
	void SetName(std::string name);

	//Установить новое описаение
	void SetDescript(std::string description);

	//Привязать сотрудника к группе
	void SnapEmployee(int id_employee);

	//Уничтожить связь
	void UnLinkEmployee(int id_employee);

	//Загрузка всех групп, соотвествующих условию
	static void LoadedAllGroup(int id_user);

	//Поиск группы для сотрудника среди всех групп
	static std::list<db_group> GetSnapGoup(int id_employee);

	//Получение указателей на все загруженные группы, что свяазаны с сотрудником
	static std::list<db_group*> GetLinkGroup(int id_employee);

	//Добавление новой группы
	static db_group AddNewGroup(std::string name, std::string descriptor);

	//Получить все загруженные в приложении группы
	static  std::vector<db_group> GetAllGroup();

	//Получить все группы из БД
	static std::vector<db_group> GetAllGroupToDB();

	//Уадлить группу из списка
	void Delete() override;

	//Поиск группы среди всех групп по имени 
	static int SerachGroup(std::string name);

	//Получение ID группы
	int GetId();

	//Получение имени группы
	std::string GetName();

	//Получение описания группы
	std::string GetDesc();

private:

	//Проверка, привязан ли сотрудник с указанным id к группе
	bool CheckEmployeeId(int id_employee);

	//Список id сотрудников, которые привязаны к группе
	std::list<int> id_employee;

	//Название объекта группы
	std::string _name;

	//Описание объекта группы
	std::string _descript;

	//Метод, вызываемый при изменении информации об объектах группы
	void _db_update();

	//Все объекты групп, которые связаны с данным пользователем
	static std::list<db_group> all_group;

	//Константы имён разных объектов из БД
	//Название таблицы с информацией
	const static std::string db_table_name;
	const static std::string add_proc_name;
	const static std::string edit_proc_name;
	const static std::string delete_proc_name;
};

