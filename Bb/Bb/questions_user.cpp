#include "questions_user.h"

#include <iostream>
using namespace std;

#include <conio.h>

void questions_user::ClearConsole()
{
	//Очищение экрана
	system("cls");
}

int questions_user::SendQuestInt(string quest_text, std::vector<string> varinats)
{
	//Сохранение количества ответов
	int count = varinats.size();
	//До тех пор, пока не будет дан верный ответ, будет задаваться вопрос
	while (true) {
		//Вывод вопроса
		cout << quest_text << endl;
		//Переменная для указания номера ответа
		int i = 1;
		//Вывод вариантов ответа
		for (auto iter = varinats.begin(); iter != varinats.end(); iter++) {
			cout << i++ << ". " << *iter << endl;
		}
		//Выбор приглашения для ввода
		cout << ">> ";
		//Переменная для получение ответа
		string answer;
		//Ожидание ответа
		cin >> answer;
		//Попытка преобразовать ответ в число
		try {
			int num_res = atoi(answer.c_str());
			//Если ответ в не правильном диапазоне
			//Выбросить ошибку
			if (num_res < 1 || num_res > count) throw new exception();
			//Если выбран правильный вариант, то вернуть его результат
			return num_res;
		}
		catch (...) {
			cout << "Выбран не правильный вариант ответа!" << endl;
			continue;
		}
	}
}

std::string questions_user::SendQuest(string quest_text, vector<std::string> varinats)
{
	//Метод возвращает номер ответа, который на один больше, чем позиция в ответе
	return varinats[SendQuestInt(quest_text, varinats) - 1];
}

string questions_user::GetParametr(string name_params)
{
	char cres[300];
	string res;
	cout << name_params << ": ";
	cin >> res;
	return res;

}

void questions_user::WaitPressSay()
{
	cout << "Для продолжения нажмите любую клавишу...";
	WaitPress();
}

void questions_user::WaitPress()
{
	_getch();
}
