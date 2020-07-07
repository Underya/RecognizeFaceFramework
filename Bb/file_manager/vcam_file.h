#pragma once
#include <iostream>
#include <string>


#ifdef FILEMANAGER_EXPORTS
#define FILEMANAGER_API __declspec(dllexport)
#else
#define FILEMANAGER_API __declspec(dllimport)
#endif


//Информация о камере из файла
struct FILEMANAGER_API vcam_file
{
	//Адрес камеры. IP или Web
	std::string address;

	//Позиция камеры
	std::string position;

	//Расположение камеры
	std::string description;

	//Идентификатор камеры в базе данных
	int id;

	//Ид помещения
	int id_premise;

	//Идентификатор камеры в виде строки
	std::string id_str() { return std::to_string(id); }

	//Проверка, явлвется ли адрес числом
	bool AddressIsNumber() 
	{
		for (int i = 0; i < address.size(); i++) {
			if (!isdigit(address[i])) return false;
		}

		return true;
	}

	//Возвращение адреса в виде числа
	int GetAddressNumber() {
		if (!AddressIsNumber()) {
			throw std::exception("Execption! Address in not number");
		}
		return atoi(address.c_str());
	}
};
