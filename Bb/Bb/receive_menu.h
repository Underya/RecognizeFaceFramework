#pragma once
#include "..//db/db_user.h"

#include <vector>
#include <string>

//Класс, который реализует функции для работы с получателями
class recipients_list
{

public:

	void Switch(db_user* user);

	//Получение всего списка получателей
	std::vector<std::string> GetFileReceiver();

protected:

	//Показ всех получателей
	void ShowAllReceive();

	//Показать информацию об одно получателе
	void ShowInfoOner(std::string path);

	std::string GetNameParams(std::string params, int number);

	//Добавить нового получателя
	void AddReceiver();

	//Получить последний номер использованный 
	int GetNexttNumber();

	//Удалить из списка
	void DeleteRecipient();

	void Menu();

	int ParseAnswer(int munber);

	db_user* _user = NULL;

	static std::string rec_name;
};

