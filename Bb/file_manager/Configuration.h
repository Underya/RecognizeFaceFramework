#pragma once

#include <map>
#include <string>
#include <fstream>
#include "file_parametr.h"

#ifdef FILEMANAGER_EXPORTS
#define FILEMANAGER_API __declspec(dllexport)
#else
#define FILEMANAGER_API __declspec(dllimport)
#endif

//Класс, который управляет содержимым файла настроек
 class FILEMANAGER_API Configuration : public file_parametr
{
public:

	//Создание файла с найстройками с указанным именем
	Configuration(std::string file_name);

	//Создание файла с натройсками с именем по умолчанию
	Configuration();

	~Configuration();

	//Получение значения параметра из файла
	std::string GetParametr(std::string Name);

	//Указание, есть ли настройки в объекте
	bool IsEmpty();

	//Имеется ли такой параметр в словаре
	bool HasParamert(std::string Name);

	//удалить указанный параметр
	void DeteleParametr(std::string Name);

	//Установка значения параметра из файла
	void SetParametr(std::string Name, std::string Value);

private:

	//Словарь со всеми созданными параметрами
	std::map<std::string, std::string> *mapConfiguration;

	//Получение всех настроек в текстовом формате
	std::string GetContentList() override;

	//Получение всех данных из текстового файла
	void ReceiveDate();
};

