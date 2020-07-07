#pragma once
#include "..//RecognitionBB/RecognitionBB.h"
//Класс, который отвечает за работу приложения
class work_class
{
public:

	//Запуск работы обнаружени и распознавания, 
	void Start(db_user  *user);

	//Покзать список помещений, и всхе сотрудников в нём
	void ShowPremiseEmployee();

	//Показать список сотрудников, и где они находятся
	void ShowEmployeePremise();

protected:

	void Menu();

	db_user *_user = NULL;

	//Запуск системы
	void StartWork();

	RecognitionBB bb;
};

