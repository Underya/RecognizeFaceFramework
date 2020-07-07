
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifdef FILEMANAGER_EXPORTS
#define FILEMANAGER_API __declspec(dllexport)
#else
#define FILEMANAGER_API __declspec(dllimport)
#endif


//Абстрактный класс, который реализует многие функции для работы классов, которые записывают свои данные как параметры
class FILEMANAGER_API file_parametr
{
public:

	//Сохранение текущей информации в файл
	virtual void Save();

	//Метод показывает всю информацию, что содержиться в файле
	void ShowInfo();

	//Минимальный конструктор, для работы с файлами
	//fileName - название файла, с которым работает класс
	file_parametr(std::string fileName);

	virtual ~file_parametr();

	//Очищение файла
	virtual void ClearFile();

protected:

	//Функция возвращает bool, если такой элемент уже есть в векторе
	bool HasIdInVec(std::vector<int> _vector, int id);

	//Получение название параметра и его значения из строки
	//Строка должна иметь следующий вид nameParametr:valueParametr;
	//str - строка указанного вида, nameParam - выходной параметр название параметра
	//vauleParam - значение параметра
	void GetValueForString(std::string str, std::string& nameParam, std::string& valueParam);

	//Закрытие файла
	void CloseFile();

	void OpenFileForRead();

	void OpenFileForWrite();

	//Метод возвращает всё содержимое списка в виде строкового текста
	virtual std::string GetContentList();

	//Создание нового ПУСТОГО файла
	void CreateNewFile();

	//Дескриптор файла для чтения
	std::ifstream* _rFile = NULL;

	//Десриптор файла для записи
	std::ofstream* _wFile = NULL;

	//Имя файла, в котором храниться информация
	std::string _fileName;

	//Получить новый id для записи
	int GetNewId();

	//Установить последний использованный ID
	//Вызывается при синхронизации работы файловой системы и БД
	void SetLastUsId(int outer_id);

	//Проверка, существует ли файл
	bool CheckFileExist();

	//Если для сохранения информации об объектах не используется БД
	//То файл сам создаёт ID
	int id_not_db = 0;

};

