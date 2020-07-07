#pragma once
#include "..//RecognitionBB/RecognitionBB.h"
#include "Initialization.h"

//Основной классс, котуда идёт работа с прилоежниеи
class Main_menu
{
public:

	void Start();

protected:


	//Инициализациия консоли перед использованием
	void Initializate();

	//Разбор ответов
	int ParseAnswer(int result);
	
	void LoadInformation();

	//Указание, надо ли брать информации из файлов
	bool _import = false;

	db_user *_user = NULL;

	Initialization i;
};

