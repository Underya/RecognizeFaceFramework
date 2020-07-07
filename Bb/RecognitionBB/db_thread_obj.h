
#pragma once
#include "thread_obj.h"
#include <db_manager.h>
#include <db_group.h>
#include "Two_Way_Pipe.h"

//Объект потока, который работает с БД
class RECOGNITIONBB_API db_thread_obj :
	public thread_obj
{
public:

	db_thread_obj();

	~db_thread_obj();

	//Получение указателя на канал, через который передаются запросы на поиск лица в БД
	Two_Way_Pipe<float*, db_employee>* GetSearchPipe();

	//Получение указателя на кнала, через которые предаются результаты распознования в БД
	Two_Way_Pipe<int, int>* GetRecognitionResultPipe();

	//Получение указатель на канал, через который предаётся информация о сотрудниках
	Two_Way_Pipe<int, std::vector<std::pair<int, std::string>>>* GetGroupSearchPipe();

private:

	//Главный метод потока
	void ThreadMethod() override;

	//Разбор сообщений управления
	void ParseControlMess() override;

	//Разбор сообщений о добавлении результата
	void RecognitionMess();

	//Разбор сообщений о поиске лиц
	void SearchMess();

	//Разбор сообщений о поиске группы
	void GroupSearchMess();

	//Канал для двусторонней передачи сообщений о поиске лиц в БД
	Two_Way_Pipe<float*, db_employee>* search_pipe;

	//Канал для передачи сообщений о распозновании
	Two_Way_Pipe<int, int>* recognition_result;

	//Вектор для обмена информацией о пиоске групп
	Two_Way_Pipe<int, std::vector<std::pair<int, std::string>>> * group_search_pipe;

	//Переменная, обозначающая, что поток поток должен продолжить выполнять работу
	bool work = true;
};

