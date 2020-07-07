#include "pch.h"
#include "Configuration.h"
using namespace std;

Configuration::Configuration(std::string file_name) : file_parametr(file_name)
{
	//Выделение памяти под карту
	mapConfiguration = new map<string, string>();

	//Заполнение карты
	ReceiveDate();
}

Configuration::Configuration() : file_parametr("Config.txt")
{
	//Выделение памяти под карту
	mapConfiguration = new map<string, string>();

	//Заполнение карты
	ReceiveDate();
}

Configuration::~Configuration()
{
	//Удаление самой карты
	delete mapConfiguration;
}

string Configuration::GetParametr(string Name)
{
	return mapConfiguration->at(Name);
}

bool Configuration::IsEmpty()
{
	//Если количество объектов в словаре нулевое, вернуть истину
	if (mapConfiguration->size() == 0)
		return true;
	else
		return false;
}

bool Configuration::HasParamert(string Name)
{
	auto res = mapConfiguration->find(Name);
	//Если такого объекта нет
	if (res == mapConfiguration->end()) return false;
	//Иначе, такой объект есть
	return true;
}

void Configuration::DeteleParametr(std::string Name)
{
	mapConfiguration->erase(Name);
}

void Configuration::SetParametr(std::string Name, std:: string Value)
{
	//Проверка, есть ли такой объект в словаре
	bool res = HasParamert(Name);
	
	//Если такого объекта нет в словаре, то результат не совпадёт с запросом
	if (!res) {
		//Добавляется новый объект
		//Создание объекта пары для вставки в словарь
		mapConfiguration->insert(make_pair(Name, Value));
	}
	//Иначе - заменяется старый
	else {
		mapConfiguration->operator[](Name) = Value;
	}
}


string Configuration::GetContentList()
{
	string Content = "";

	//Получение всех элементов в привычном виде
	for (auto iter = mapConfiguration->begin(); iter != mapConfiguration->end(); iter++) {
		Content += iter->first + ":" + iter->second + ";\n";
	}

	return Content;
}


void Configuration::ReceiveDate()
{
	CloseFile();
	OpenFileForRead();

	//Строка для сохранение значения из файла
	string line;
	//Название параметра и его значение
	string name, value;
	//Чтение всего файла
	while (getline(*_rFile, line)) {
		if (line == "") continue;
		//Разбор полученной строки
		GetValueForString(line, name, value);
		mapConfiguration->insert(make_pair(name, value));
	}
	
}
