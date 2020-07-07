#pragma once
#include "file_parametr.h"
#include <vector>

//Структра одного помещения
struct FILEMANAGER_API premise {

	//Идентификатор одного помещения
	int id = -1;

	//Название помещения
	std::string name = "";

	//Описание 
	std::string description = "";

	//Ид родителя помещения
	int id_parent = -1;
};

//Управление файлом с помещениями
class FILEMANAGER_API file_premise :
	public file_parametr
{
public:

	file_premise(std::string file_name);

	file_premise();

	~file_premise();

	//Создание новой структуры и добавление информации о ней в файл
	void AddNewPremise(std::string name, std::string desc = "", int id = -1, int id_parent = -1);

	//Получение информации обо всхе помещениях
	std::vector<premise> GetAllPremise();

	//Получение помещения по его id
	premise GetPremise(int id);

	void EditPremisse(int id, std::string name, std::string desc = "", int id_parent = -1);

	//Получить вектор со всеми предками для данного помещения
	std::vector<premise> GetAllParent(int id_premise);
	//Получить вектор со всеми предками для данного помещения
	std::vector<premise> GetAllParent(premise premis);

	//Получить текущее помещение и все его предки
	std::vector<premise> GetPremiseWithParrent(int id_premise);

	void DeletePremise(int id);
	
protected:

	std::string GetContentList() override;

	//Функция, которая извлекает информацию из файл
	void ReceiveInfo();

	//Списо с помещениями
	std::vector<premise> _premises;
};

