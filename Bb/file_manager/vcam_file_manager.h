#include "pch.h"
#include <iostream>
#include <list>
#include "vcam_file.h"
#include <fstream>
#include "file_parametr.h"

//Класс реализует методы для получения и сохранения информации о камерах из файла
class FILEMANAGER_API vcam_file_manager : public file_parametr
{
public:

	//Создание файла с указанным именем
	vcam_file_manager(std::string file_name);

	//Создание файла со стандартным
	vcam_file_manager();

	~vcam_file_manager();

	//Добавление новой камеры в список используемых камер и объектов
	void AddNewCamera(std::string address, std::string description = "", int id_premise = -1, std::string position = "n", int id = -1);

	//Получение списка всех камер из файла
	//Возвращается указатель на единый список
	std::list<vcam_file>* GetList();

	//Получить камеру по её id
	vcam_file GetCamera(int id);

	//Поиск камеры с таким же адресом
	int SearchCamera(std::string address);

private:

	//Метод возвращает всё содержимое списка в виде строкового текста
	std::string GetContentList() override;

	//Чтение информации из файла и создание списка с камера
	void ReadVcamInfo();

	//Список камер из текстового файла
	std::list<vcam_file> *list;

};

//Содержимое файла выглядит следующим образом
//cam
//address:value1;
//position:value2;
//id:value3;
//description:value4;
//id_premise:value5;
//Сначала идут название параметров, затем - их значения
//в значении параметров нельзя использовть символ - ; и символ \n
