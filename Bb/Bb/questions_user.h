#pragma once

#include <string>
using std::string;
#include <vector>


//Класс для того, что бы задавать вопросы пользователю 
class questions_user
{
public:

	//Очищение экрана консоли
	void ClearConsole();

	//Метод задаёт вопрос, и возвращает номер выбранного ответа
	int SendQuestInt(string quest_text, std::vector<string> varinats);

	//Метод, который предлагает пользователю отвтетить на вопрос путём выбора ответа из указаных вариантов
	string SendQuest(string quest_text, std::vector<string> varinats);

	//Метод предлагает пользователю ввести значение для параметра
	//И возвращает значение параметра
	string GetParametr(string name_params);

	//Написать, что для продожения надо ждать клавишу
	//И ожидание клавишы
	void WaitPressSay();

	//Ожидание, пока пользователб не нажмёт клавишу
	void WaitPress();
};

