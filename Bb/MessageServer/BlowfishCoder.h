#pragma once

#include <iostream>
#include "blowfish.h"

#ifdef MESSAGESERVER_EXPORTS
#define MESSAGESERVER_API __declspec(dllexport)
#else
#define MESSAGESERVER_API __declspec(dllimport)
#endif


//����� ������������� ��������� ������� ��� ����������  � ������������ � ������� ��������� Blowfish
class MESSAGESERVER_API BlowfishCoder
{
public:

	//�������� ������ � ��������� ������� �����
	//������ ����� ������ ���� ������ 64 !
	BlowfishCoder(int blockSize = 256);

	//�������� ������ � ��������� ������ � �������� �����
	//������ ����� - 56 ����!
	//������ ����� ������ ���� ������ 64 !
	BlowfishCoder(char *key, int blockSize = 128);

	//����������� ���������
	//message - ���������
	//size - ��� ����������� �����
	//newSize - �������������� ��������� �����
	//���������� ��������� �� ����������� ���������
	char* Coding(const char* message, int size, int &newSize);

	//�������������� ��������������� ���������
	//message - ��������������� ���������
	//size - ��� ������
	//newSize - ������ ���������������� ���������
	char* UnCodind(const char* encodeMessage, int size, int& newSize);

protected:

	//������� ������ ������ ���������, � ���������� ��� ������
	void GetNewSize(int oldSize, int blokSize, int& newSize, int& blockCount);

	//�������������� ����� ��������� �����
	void UnCodingBlock(const char* encodingMess, char* decodeMess, int blockSize);

	//����������� ����� ��������� �����
	void CodingBlock(const char* mess, char* buff, int blockSize);

	//���������� ��������� ��������� �������
	void AddingMessage(char* message, int oldSize, int newSize);

	//������ ������ ����� ����������� � ������
	int _blockSize = 64;

	int textIndex = 0;

	//������������� ����� ��� �����������
	//key - ���� ������ ���� ������ 56 ����!
	void InitialKey(char* key);

	//����� ������ ������ ���������������
	CBlowFish bf;
};

