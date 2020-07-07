#pragma once


//Интерфейс, который облегчает создание объектов, которые являются строчками БД
class db_row
{
public:

	//Удаление строки из БД
	virtual void Delete() = 0;

protected:

	//Идентификатор строки в бд
	int _id;

	//Обновление информации об объекте
	virtual void _db_update() = 0;

};

