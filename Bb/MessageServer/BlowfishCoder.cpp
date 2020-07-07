#include "pch.h"
#include "BlowfishCoder.h"
using namespace std;

//Размер ключа по умолчанию
#define DEFAULT_KEY_SIZE 56

BlowfishCoder::BlowfishCoder(int blockSize)
{
	if (blockSize % 64 != 0 || blockSize <= 0)
		throw std::exception("Exception! blockSize not % to 64");
	_blockSize = blockSize;
	//Создание ключа по умолчанию
	char defaultKey[DEFAULT_KEY_SIZE] = { 0 };
	//Начально смещение числа
	int start_posit = 101;
	//Цикл, в ходе которого формируется ключ
	for (int i = 0; i < DEFAULT_KEY_SIZE; i++) {
		defaultKey[i] = start_posit + (pow(-1, i % 2) * (i + 3));
	}
	//Вызов функции для инициализации ключа
	InitialKey(defaultKey);
}

BlowfishCoder::BlowfishCoder(char* key, int blockSize)
{
	if (blockSize % 64 != 0 || blockSize <= 0)
		throw std::exception("Exception! blockSize not % to 64");
	_blockSize = blockSize;
	//Вызов функции для инициализации ключа
	InitialKey(key);

}

char* BlowfishCoder::Coding(const char* message, int size, int& newSize)
{
	//Колиечество блоков
	int blockCount = 0;

	//Рассчёт нового размера для массива
	GetNewSize(size, _blockSize, newSize, blockCount);

	//Создание нового буффера, куда будет помещено закодированное сообщение
	char* encodingMess = new char[newSize]();

	//Временный буффер, где будет расширенный исходный текст
	char* Message = new char[newSize]();
	//Копирование в буффер исходного сообщения
	memcpy(Message, message, size);

	//Дополнение исходного сообщения текстом
	AddingMessage(Message, size, newSize);

	//Указатель на текущий блок для кодирования
	char* currentBlock = Message;
	//Указатель на текущий блок буффера
	char* currentBufferBlock = encodingMess;

	//Кодирование всех блоков
	for (int i = 0; i < blockCount; i++) {
		CodingBlock(currentBlock, currentBufferBlock, _blockSize);
		//Переход к следующим блокам для кодирования
		currentBlock += _blockSize;
		currentBufferBlock += _blockSize;
	}

	//Удаление вспомогательного буффера
	delete [newSize] Message;

	//Возвращение буффера сообщением
	return encodingMess;
}

char* BlowfishCoder::UnCodind(const char* encodeMessage, int size, int& newSize)
{
	//Рассчёт количества блоков для разкадирования
	int blockCount = size / _blockSize;
	
	//Буффер для раскадированного сообщения
	char* orignMessage = new char[size]();
	//Указатели на текущие блоки
	const char* currEncodeBlock = encodeMessage;
	char* orignMessBlock = orignMessage;
	
	//Блочное разкодирование
	for (int i = 0; i < blockCount; i++) {
		UnCodingBlock(currEncodeBlock, orignMessBlock, _blockSize);
		//Переход к следующим блокам
		currEncodeBlock += _blockSize;
		orignMessBlock += _blockSize;
	}

	//Рассчёт новой длины
	newSize = strlen(orignMessage);

	//Создание массива точной длины, во избежания утечек памяти
	char* originalMessage = new char[newSize];
	//Копировние сюда информации
	memcpy(originalMessage, orignMessage, newSize);
	
	//Удаление памяти из под оригинального массиа
	delete[size]orignMessage;

	//Возвращание декодированного сообщения
	return originalMessage;
}

void BlowfishCoder::GetNewSize(int oldSize, int blokSize, int& newSize, int& blockCount)
{
	//Как минимум один блок понадобится
	blockCount = 1;
	//Новая длина не может быть меньше размера блока
	newSize = blokSize;
	//До тех пор, пока новый буффер под новое сообщение не вмещает старое сообщение
	while (newSize < oldSize) {
		//Увеличивается количество блоков
		blockCount++;
		//Увеличивается размер буффера
		newSize += blokSize;
	}
}

void BlowfishCoder::UnCodingBlock(const char* encodingMess, char* decodeMess, int blockSize)
{
	bf.Decode((unsigned char*)encodingMess, (unsigned char*)decodeMess, blockSize);
}

void BlowfishCoder::CodingBlock(const char* mess, char* buff, int blockSize)
{
	//Кодирование блока
	bf.Encode((unsigned char*)mess, (unsigned char*)buff, blockSize);
}

void BlowfishCoder::AddingMessage(char* message, int oldSize, int newSize)
{
	//Индекс последнего заполненго символа
	int currSymb = oldSize;
	//В конце сообщения один или два 0, что бы отделить нагрузку при обратном переводе
	if (currSymb < newSize) {
		//Первый 0
		message[currSymb] = 0;
	}
	//Переход к следующему символу
	currSymb++;
	if (currSymb < newSize) {
		message[currSymb] = 0;
	}
	currSymb++;

	//Текст, которым дополняется массив
	char text[] = { "Программирование в Oracle APEX является декларативным. То есть пользователь работает с результатом выполнения кода, и нет необходимости в компиляции или генерации этого кода. Таким образом, разработка приложе-ния на декларативном языке APEX выглядит как работа с конструктором, со-стоящим из множества используемых в том или ином случае блоков." };
	int text_size = sizeof(text);

	//Дополнение текстом
	for (; currSymb < newSize; currSymb++) {
		message[currSymb] = text[textIndex];
		//Переход к следующему символу
		textIndex = ++textIndex % text_size;
	}
}

void BlowfishCoder::InitialKey(char* key)
{
	//Инициализация класса шифровщика ключом
	bf.Initialize((unsigned char*)key, 56);
}
