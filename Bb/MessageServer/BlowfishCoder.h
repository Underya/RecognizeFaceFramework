#pragma once

#include <iostream>
#include "blowfish.h"

#ifdef MESSAGESERVER_EXPORTS
#define MESSAGESERVER_API __declspec(dllexport)
#else
#define MESSAGESERVER_API __declspec(dllimport)
#endif


//Класс предоставляет различные функции для шифрования  и дешифрования с помощью алгоритма Blowfish
class MESSAGESERVER_API BlowfishCoder
{
public:

	//Создание кодера с указанием размера блока
	//Размер блока должен быть кратен 64 !
	BlowfishCoder(int blockSize = 256);

	//Создание кодера с указанным ключём и размером блока
	//Размер ключа - 56 байт!
	//Размер блока должен быть кратен 64 !
	BlowfishCoder(char *key, int blockSize = 128);

	//Кодирование сообщение
	//message - сообщение
	//size - его изначальная длина
	//newSize - зашифрованного сообщения длина
	//Возврвщает указатель на зашифронное сообщение
	char* Coding(const char* message, int size, int &newSize);

	//Разкодирование закадированного сообщения
	//message - заскодированное сообщение
	//size - его размер
	//newSize - размер разкадированного сообщения
	char* UnCodind(const char* encodeMessage, int size, int& newSize);

protected:

	//Рассчёт длинны нового сообщения, и количество его блоков
	void GetNewSize(int oldSize, int blokSize, int& newSize, int& blockCount);

	//Раскодирование блока указанной длины
	void UnCodingBlock(const char* encodingMess, char* decodeMess, int blockSize);

	//Кодирование блока указанной длины
	void CodingBlock(const char* mess, char* buff, int blockSize);

	//Дополнение исходного сообщения текстом
	void AddingMessage(char* message, int oldSize, int newSize);

	//Рамзер одного блока кодирования в байтах
	int _blockSize = 64;

	int textIndex = 0;

	//Инициализация ключа для кодирования
	//key - ключ должен быть длиной 56 байт!
	void InitialKey(char* key);

	//Класс самого кодера непосредственно
	CBlowFish bf;
};

