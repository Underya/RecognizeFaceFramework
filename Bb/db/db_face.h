#pragma once
#include "db_connect.h"


//Представление одного дескриптора лица из базы
class DB_API db_face:
	public db_row
{
public:

	//Получение дескриптора с выбранными id
	db_face(int id);

	~db_face();

	//Группа методов, направленных на получение информации от объекта

	//Получение ID дескриптора
	int GetId();
	//Получение id сотрудника
	int GetIdEmployee();
	//Получение дескриптора
	float* GetDescriptor();
	//Получение размера дескриптора
	int GetDescriptorSize();

	//Вывод информации о дискрипторе
	void ShowInfo();

	void Delete() override;

	//Создание нового объекта в БД 
	//И получение на него указателя
	static db_face* AddNewFace(float* descriptor, int id_employe);

	//Поиск человека с указанным дескриптором в БД
	static int SearchFace(float* descriptor);
	static int SearchFace(std::string descriptor);

private:

	//Идентификатор сотрудника, к которому привязано лицо
	int id_employee;

	//Заполнение числового дескриптора из строки
	void SetDescriptFromChar(char* descr);

	//Трансформация из числивого дескриптора
	//В строку для PostgreSQL
	static std::string TransformToString(float* desc);

	//Размер массива дескриптора
	//По умолчанию - 128 элементов
	static int descriptSize;
	//Массив из 128 элементов, который непосредственно содержит дескриптор
	float* descript = NULL;

	//Соеденение с БД
	db_connect *connect = NULL;

	//Изменяет информацию о дескрипторе в БД
	//Вызывается при любом изменении
	void _db_update();

	//Константы имён разных объектов из БД
	//Название таблицы с информацией
	const static std::string db_table_name;
	const static std::string add_proc_name;
	const static std::string edit_proc_name;
	const static std::string delete_proc_name;

};

