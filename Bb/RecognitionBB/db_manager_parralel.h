
#pragma once
#include "Control_Thread.h"
#include "db_thread_obj.h"

//Класс, предоставляющий методы для работы с БД из разных потокв
//Через объект этого класса осуществляется работа с БД
class RECOGNITIONBB_API db_manager_parralel :
	public Control_Thread
{
public:

	db_manager_parralel();

	~db_manager_parralel();

	//Поиск лица по дескриптору
	db_employee SearchFace(float* desc);

	//Сохранение результатов распознавания
	void SaveResetch(int id_employee, int id_camera);

	//Поиск групп для указанного сотрудника
	std::vector<std::pair<int, std::string>> SearchGroup(int id_employee);

private:

	//Номер в очереди данного экземпляра класса для поиска
	int myNumSearch;

	//Номер в очереди данного экземпляра класса для распознования
	int myNumRecoginition;

	//Номер в очереди для групп
	int myNumGroup;

	//Поток обмена сообщениями для поиска
	Two_Way_Pipe<float*, db_employee>* pipe_find;

	//Поток обмена сообщениями для сохранения результатов распознования
	Two_Way_Pipe<int, int>* pipe_recognit;

	//Поток обмена сообщения для поиска групп
	Two_Way_Pipe<int, std::vector<std::pair<int, std::string>>>* pipe_group;

	//Проверка, есть ли уже запушенный поток
	bool CheckWorkThread() override;

	//Создание объекта потока
	thread_obj* CreateNewObj() override;

	//Открытие и запуск потока
	void OpenNewThread() override;

	//Передача остановка работы потока
	void CloseThread();

	//Указетель на общий для всех объектов поток для работы с БД
	static db_thread_obj* db_thread;

	//Количество действующих объектов. Используется для того, что бы правилно унчитожить поток с БД
	static int countObject;
};

