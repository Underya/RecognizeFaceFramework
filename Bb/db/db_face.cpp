#include "pch.h"
#include "db_face.h"
#include <string>
#include <list>
using namespace std;

//Указание общих переменных
const string db_face::db_table_name = "face";
const string db_face::add_proc_name = "addface";
const string db_face::edit_proc_name = "editface";
const string db_face::delete_proc_name = "deleteface";
int db_face::descriptSize = 128;

db_face::db_face(int id)
{
	//Создание нового соеднения с бд
	connect = new db_connect();
	//Выделение памяти под массив из чисел
	descript = new float[128]();
	//Установка значения id
	this->_id = id;

	//Получение информации из БД
	PGresult* res = connect->GetOneRowById(db_table_name, id);

	//Вставка полученной информации в объект
	this->id_employee = atoi(PQgetvalue(res, 0, 2));
	//Дескриптор преобразуется из строки
	SetDescriptFromChar(PQgetvalue(res, 0, 1));
}

db_face::~db_face()
{
	//Очищение выделенной памяти
}

int db_face::GetId()
{
	return _id;
}

int db_face::GetIdEmployee()
{
	return id_employee;
}

float* db_face::GetDescriptor()
{
	return descript;
}

int db_face::GetDescriptorSize()
{
	return descriptSize;
}

void db_face::ShowInfo()
{
	cout << "Face. id:" << _id;
	cout << " id_empl:" << id_employee << endl;
}

void db_face::Delete()
{
	//Формирование параметров для запроса
	list<string> l;
	l.push_back(to_string(_id));
	//Вызов процедуры
	connect->ExecuteProcedure(delete_proc_name, &l);
}

db_face* db_face::AddNewFace(float* descriptor, int id_employe)
{
	//Создание нового соеденения с БД
	db_connect c;
	//Создание параметров
	//Дескриптор нового изображения
	string desc = db_face::TransformToString(descriptor);
	//Идентификатор сотрудника
	string id_e = to_string(id_employe);
	//Вектор для передачи параметров в функцию
	list<string> params;
	params.push_back(desc);
	params.push_back(id_e);

	//Вызов операции добавления и получение id новой записи
	int new_id =  c.ExecuteAddProcedure(db_face::add_proc_name, &params);

	//Создание нового объекта
	db_face *nf = new db_face(new_id);
	//Возвращение объекта
	return nf;
}

int db_face::SearchFace(float* descriptor)
{
	//Создание нового соеденения с БД
	db_connect c;
	//Создание параметров
	//Дескриптор нового изображения
	string desc = db_face::TransformToString(descriptor);
	//Создание списка с параметрами
	list<string> params;
	params.push_back(desc);
	int search_id = -1;
	//Вызов операции по поиску лиц
	try {
		search_id = c.ExecuteAddProcedure("searchface", &params);
	}
	catch (...) {
		return -1;
	}
	//Возвращение результата
	return search_id;
}

int db_face::SearchFace(string descriptor)
{
	//Создание нового соеденения с БД
	db_connect c;

	descriptor = "{" + descriptor;

	//Все пробелы должны быть заменены на ,
	for (int i = 0; i < descriptor.size(); i++) {
		if (descriptor[i] == ' ') descriptor[i] = ',';
	}

	descriptor[descriptor.size() - 1] = '}';

	//Создание списка с параметрами
	list<string> params;
	params.push_back(descriptor);

	//Вызов операции по поиску лиц
	int search_id = c.ExecuteAddProcedure("searchface", &params);

	//Возвращение результата
	return search_id;

}

void db_face::SetDescriptFromChar(char* descr)
{
	//Получеамая строка имеет следующий формат
	//{1.0,2.0,10e-8,...}
	//Всего - descriptorSize чисел
	//Индекс, указываюший на то, какой элемент сейчас заполняется
	int indexFloat = 0;
	//Индекс, с помощью которого производится разбор строки
	int indexStr = 1;

	//Буффер, куда записываются символы из разбираемой строки
	char buff[30];
	//Индекс для буффера
	int indexBuff = 0;

	//Циклически извлекаются все элементы
	for (int size = descriptSize; indexFloat < size; indexFloat++) {
		//Заполнение буффера
		indexBuff = 0;
		while (descr[indexStr] != ',' && descr[indexStr] != '}') {
			buff[indexBuff++] = descr[indexStr++];
		}
		//Указание на конец строки в буффере
		buff[indexBuff] = 0;
		//Конвертация строки буффера в число
		descript[indexFloat] = atof(buff);
		//Заполнение буффера останавливается, когда descr[indexStr] == ','
		//Переход к следующему символу, являющимуся цифрой
		indexStr++;
	}

}

string db_face::TransformToString(float* desc)
{
	//Переменная для сохранения результата
	string result = "{";
	//Разбор всех переменных

	for (int i = 0; i < descriptSize; i++) {
		result += std::to_string(desc[i]) + ",";
	}

	//Последний символ "," заменяется на "}"
	result[result.size() - 1] = '}';

	return result;
}

void db_face::_db_update()
{

}
