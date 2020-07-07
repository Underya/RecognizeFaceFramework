#include "pch.h"
#include "BlowfishCoder.h"
using namespace std;

//������ ����� �� ���������
#define DEFAULT_KEY_SIZE 56

BlowfishCoder::BlowfishCoder(int blockSize)
{
	if (blockSize % 64 != 0 || blockSize <= 0)
		throw std::exception("Exception! blockSize not % to 64");
	_blockSize = blockSize;
	//�������� ����� �� ���������
	char defaultKey[DEFAULT_KEY_SIZE] = { 0 };
	//�������� �������� �����
	int start_posit = 101;
	//����, � ���� �������� ����������� ����
	for (int i = 0; i < DEFAULT_KEY_SIZE; i++) {
		defaultKey[i] = start_posit + (pow(-1, i % 2) * (i + 3));
	}
	//����� ������� ��� ������������� �����
	InitialKey(defaultKey);
}

BlowfishCoder::BlowfishCoder(char* key, int blockSize)
{
	if (blockSize % 64 != 0 || blockSize <= 0)
		throw std::exception("Exception! blockSize not % to 64");
	_blockSize = blockSize;
	//����� ������� ��� ������������� �����
	InitialKey(key);

}

char* BlowfishCoder::Coding(const char* message, int size, int& newSize)
{
	//����������� ������
	int blockCount = 0;

	//������� ������ ������� ��� �������
	GetNewSize(size, _blockSize, newSize, blockCount);

	//�������� ������ �������, ���� ����� �������� �������������� ���������
	char* encodingMess = new char[newSize]();

	//��������� ������, ��� ����� ����������� �������� �����
	char* Message = new char[newSize]();
	//����������� � ������ ��������� ���������
	memcpy(Message, message, size);

	//���������� ��������� ��������� �������
	AddingMessage(Message, size, newSize);

	//��������� �� ������� ���� ��� �����������
	char* currentBlock = Message;
	//��������� �� ������� ���� �������
	char* currentBufferBlock = encodingMess;

	//����������� ���� ������
	for (int i = 0; i < blockCount; i++) {
		CodingBlock(currentBlock, currentBufferBlock, _blockSize);
		//������� � ��������� ������ ��� �����������
		currentBlock += _blockSize;
		currentBufferBlock += _blockSize;
	}

	//�������� ���������������� �������
	delete [newSize] Message;

	//����������� ������� ����������
	return encodingMess;
}

char* BlowfishCoder::UnCodind(const char* encodeMessage, int size, int& newSize)
{
	//������� ���������� ������ ��� ��������������
	int blockCount = size / _blockSize;
	
	//������ ��� ���������������� ���������
	char* orignMessage = new char[size]();
	//��������� �� ������� �����
	const char* currEncodeBlock = encodeMessage;
	char* orignMessBlock = orignMessage;
	
	//������� ��������������
	for (int i = 0; i < blockCount; i++) {
		UnCodingBlock(currEncodeBlock, orignMessBlock, _blockSize);
		//������� � ��������� ������
		currEncodeBlock += _blockSize;
		orignMessBlock += _blockSize;
	}

	//������� ����� �����
	newSize = strlen(orignMessage);

	//�������� ������� ������ �����, �� ��������� ������ ������
	char* originalMessage = new char[newSize];
	//���������� ���� ����������
	memcpy(originalMessage, orignMessage, newSize);
	
	//�������� ������ �� ��� ������������� ������
	delete[size]orignMessage;

	//����������� ��������������� ���������
	return originalMessage;
}

void BlowfishCoder::GetNewSize(int oldSize, int blokSize, int& newSize, int& blockCount)
{
	//��� ������� ���� ���� �����������
	blockCount = 1;
	//����� ����� �� ����� ���� ������ ������� �����
	newSize = blokSize;
	//�� ��� ���, ���� ����� ������ ��� ����� ��������� �� ������� ������ ���������
	while (newSize < oldSize) {
		//������������� ���������� ������
		blockCount++;
		//������������� ������ �������
		newSize += blokSize;
	}
}

void BlowfishCoder::UnCodingBlock(const char* encodingMess, char* decodeMess, int blockSize)
{
	bf.Decode((unsigned char*)encodingMess, (unsigned char*)decodeMess, blockSize);
}

void BlowfishCoder::CodingBlock(const char* mess, char* buff, int blockSize)
{
	//����������� �����
	bf.Encode((unsigned char*)mess, (unsigned char*)buff, blockSize);
}

void BlowfishCoder::AddingMessage(char* message, int oldSize, int newSize)
{
	//������ ���������� ���������� �������
	int currSymb = oldSize;
	//� ����� ��������� ���� ��� ��� 0, ��� �� �������� �������� ��� �������� ��������
	if (currSymb < newSize) {
		//������ 0
		message[currSymb] = 0;
	}
	//������� � ���������� �������
	currSymb++;
	if (currSymb < newSize) {
		message[currSymb] = 0;
	}
	currSymb++;

	//�����, ������� ����������� ������
	char text[] = { "���������������� � Oracle APEX �������� �������������. �� ���� ������������ �������� � ����������� ���������� ����, � ��� ������������� � ���������� ��� ��������� ����� ����. ����� �������, ���������� �������-��� �� ������������� ����� APEX �������� ��� ������ � �������������, ��-������� �� ��������� ������������ � ��� ��� ���� ������ ������." };
	int text_size = sizeof(text);

	//���������� �������
	for (; currSymb < newSize; currSymb++) {
		message[currSymb] = text[textIndex];
		//������� � ���������� �������
		textIndex = ++textIndex % text_size;
	}
}

void BlowfishCoder::InitialKey(char* key)
{
	//������������� ������ ���������� ������
	bf.Initialize((unsigned char*)key, 56);
}
