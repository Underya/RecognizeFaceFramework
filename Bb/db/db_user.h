#pragma once

#include <string>

#include "db_connect.h"

//Класс, представляющий объект user бд
class DB_API db_user :
	public db_row
{
public:

	//Получить ID объекта
	int GetId();

	//Получить имя объекта
	std::string GetName();

	//Получить описание объекта
	std::string GetDescription();

	//Изменить имя пользователя
	void SetName(std::string name);

	//Изменить описание пользователя
	void SetDescription(std::string description);

	//Добавление нового пользовтаеля
	static db_user AddNewUser(std::string name, std::string description);

	//Удаление информации о пользователе из БД
	void Delete() override;

	//Авторизация под выбранным пользователем
	//Если такой пользователь есть,  - вернётся ассоцированный с ним объект
	//Иначе - вылетит исключение
	static db_user* LoginToUser(std::string name);

	//Привязать группу к выбранному пользователю
	void LinkGroup(int id_group);

	//Отвязать группу от выбранного пользователя
	void UnLinkGroup(int id_group);

protected:

	//Перекрытие конструктора по умолчнаию
	db_user();

	//Создание пользователя ассоциированнаого с указанным адресом
	db_user(int id);

	//Обновление информации об объекте в вк
	void _db_update();

	//ID записи в БД
	int _id;

	//Имя пользователя
	std::string _name;

	//Описание пользователя
	std::string _description;

	//Соеденение с БД
	db_connect _connect;

	//Название вещей, ассоциированный с таблицей
	const static std::string tableName;
	const static std::string addProcedureName;
	const static std::string editProcedureName;
	const static std::string deleteProcedureName;
};

