#pragma once
#include "..//file_manager/file_recognition_result.h"
#include "..//MessageServer/BlowfishCoder.h"

#ifdef RECOGNITIONBB_EXPORTS
#define RECOGNITIONBB_API __declspec(dllexport)
#else
#define RECOGNITIONBB_API __declspec(dllimport)
#endif


//Класс, распознавания, который хранит данные в защифрованном виде
class RECOGNITIONBB_API file_recognition_coder :
	public file_recognition_result
{
public:

	//Создать файл, куда будут записываться результаты
	file_recognition_coder(std::string fileName, int sizeBuff = 15);

	~file_recognition_coder();

protected:

	//Откыртие или создание файла хеша
	void OpenHashFile();

	//Вместо проверки ID может возникнуть проблема проерки кода буффера
	virtual int GetId(std::string& line) override;
	
	//Проверка закодированной части
	//sizeBuffer - размер закодированной части, записан в файле
	void CheckHash(int sizeBuffer);

	//Пороверка, совпадает ли 
	bool EqualHashPart(char* encodingBuffer);

	//Перегрузка, только потому что не тот метод вызывается
	void ReadFileInfo(std::string fileName) override;

	//Получение следующей записи из большого списка
	std::string GetNextRecord(std::string FullRecord, int& currentPosition);

	//Сохранение текущего буффера в файл
	void SaveBuffToFile() override;

	//Функция записывает весь буффер в файл
	void WriteHashToFile(char *buff, int size);

	//Класс для широфвания и расшифровки файлов
	BlowfishCoder _coder;

	//Открытие файла хеш для чтения
	void OpenHashForRead();

	//Указатель на файл, в котором хранится кеш файлов для чтения
	std::ifstream _inputFile;

	//Октрытие файл хеш для записи
	void OpenHasForWrite();

	//Указателя на файл, в котором хранится кеш файлов для записи
	std::ofstream _outputFile;

	//Полчение текущего буффера в виде закодированного текста
	void GetCoderInfo(char* &outStr, int& newSize);

	int _countBlock = 0;
};

