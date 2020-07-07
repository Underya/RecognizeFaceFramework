#pragma once
#include "file_parametr.h"
#include <vector>
#include <string>
#include <time.h>

//Класс для сохранения результатов распознования в файл
class FILEMANAGER_API file_recognition_result :
	public file_parametr
{
public:

	//Соеденение с указанным файлом
	file_recognition_result(std::string fileName, int sizeBuff = 15);

	~file_recognition_result();

	//Установить начальное значение для id запсией. 
	//По умолчанию оно равно последнему значение из файлов
	void SetStartId(int id_start);

	//добавление новой записи об распозновании
	//rec - id записи. 
	virtual void AddRecognition(int id_face, int id_camera, int rec = -1);

	//Представление ТЕКУЩИХ данных в виде файла
	std::string GetContentList() override;

	//Досрочное сохранение результатов в файл
	void Save() override;

protected:

	//ТУПА КАСТЫЛЬ 
	file_recognition_result(std::string file_name, char* a, int* b, int sizeBuffer = 15);

	//Число сообщений, после которого они автоматически сохраняются в файл
	int _sizeBuff;

	//Ряд методов, которе разбирают параметры из текста, выдавая результат

	//Получение ID
	virtual int GetId(std::string& line);
	//Проверка id_face
	virtual void CheckIdFace(std::string line);
	//Проверка id_camera
	virtual void CheckIdCamera(std::string line);
	//Проверка времени
	virtual void CheckTime(std::string line);

	//Чтение информации из файла
	//Используется для получение последнего Id
	virtual void ReadFileInfo(std::string fileName);

	//Открыть файл для продолжения записи
	void OpenWriteToContinue();

	//Получение текущего времени в формате строки
	std::string GetCurrentTimeStr();

	//Проверка, достаточно ли заполнен буффер для записи его в файл
	bool CheckFullBuff();

	//Метод сохраняет всю информацию, хранящуюся в объекте в файл
	virtual void SaveBuffToFile();

	//Выбор ошибки
	//LOCATION - метод, в котором произошла ошибка
	void ThrowFileReadException(std::string fileName);

	//Буффер для сохранения запсией 
	std::vector<std::string> buffResult;
};

