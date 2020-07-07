#pragma once

#include <iostream>
#include "db_premise.h"
#include "db_user.h"

//Объект, работающей с информацией о камере в базе данных
class DB_API db_vcam:
	public db_row
{
public:

	//Получение адреса камеры
	std::string GetAddress();
	//Получение позиции камеры
	std::string GetPosition();
	//Получение описания камеры
	std::string GetDescription();
	//Получение связанного с камерой помещения
	db_premise GetPremise();
	//Получить id юзера, связанного с этой камерой
	int GetUserId();

	//Изменение адрес в базе данных
	void SetAddress(std::string newAddr);
	//Изменение позиции в базе данных
	void SetPosition(std::string Position);
	//Изменение описания камеры
	void SetDescription(std::string description);
	//Установить помещения для камеры
	void SetPremise(int id_premise);

	//Конструктор по умолчанию
	db_vcam(int id);
	//Деструктор по умолчанию
	~db_vcam();

	//Получение общей информации в виде единой строки
	std::string GetInfo();

	//Проверка, есть ли в БД камера с таким же адресом
	static int SearchCam(std::string addrress);

	//Создание новой камеры в БАЗЕ ДАННЫХ
	static db_vcam addNewCamera(std::string address, std::string position, db_user user, int id_premisse = -1);
	//Создание новой камеры в БАЗЕ ДАННЫХ
	static db_vcam addNewCamera(std::string address, std::string position, int id_user, int id_premisse = -1);

	//Получение ID камеры из бд
	int GetId();

	//Удаление информации о камере
	void Delete();

	//Получение всех связанных с пользователем камер
	static std::vector<db_vcam> GetAllLinkVcam(int id_user);

	//Получение всех связанных с пользователем камер
	static std::vector<db_vcam> GetAllLinkVcam(db_user user);

private:
	//Адрес камеры (IP или Web)
	std::string address;
	//Идентификатор камеры в Базе данных
	int _id;
	//Идентификатор пользователя
	int _user_id;
	//Расположение камеры относительно помещения
	std::string position;
	//Описание камеры
	std::string description;

	//Проверка, имеет ли позиция допустимое значение. Если не имеет, выбросить ошибку
	static void CheckPosition(std::string position);

	//Соеденение с базой данных, через которое проходят все запросы
	db_connect connect;

	//Помещение, с которым связана камера
	db_premise *premise;

	//Обновление информации о объекте в базе данных
	//Вызывается, когда вызываются другие функции, изменяющие объект
	void _db_update();

	//Константы имён разных объектов из БД
	//Название таблицы с информацией
	const static std::string db_table_name;
	const static std::string add_proc_name;
	const static std::string edit_proc_name;
	const static std::string delete_proc_name;
};

