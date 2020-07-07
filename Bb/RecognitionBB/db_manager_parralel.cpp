
#include "db_manager_parralel.h"
using namespace std;

//Инциализация значением NULL
db_thread_obj *db_manager_parralel::db_thread = NULL;
int db_manager_parralel::countObject = 0;

db_manager_parralel::db_manager_parralel()
{
	countObject++;
	//Инициализация базы данных
	db_manager db;
	//При создании объекта, вызывается функция запуска потока
	OpenNewThread();
}

db_manager_parralel::~db_manager_parralel()
{
	countObject--;
	//Если больше не осталось дейсвующих объектов - закрыть поток
	if (countObject == 0) {
		CloseThread();
	}
}

db_employee db_manager_parralel::SearchFace(float* desc)
{
	//Отправление сообщения
	pipe_find->SendMess(desc, this->myNumSearch);
	//Ожидание ответа
	while (!pipe_find->CheckCountMyAnswer(myNumSearch));
	//Получение ответа
	return pipe_find->GetMyAnswer(myNumSearch);
}

void db_manager_parralel::SaveResetch(int id_employee, int id_camera)
{
	//Передача соотсветсующего сообщения
	pipe_recognit->SendMess(id_camera, id_employee);
}

std::vector<std::pair<int, std::string>> db_manager_parralel::SearchGroup(int id_employee)
{
	//Передача сообщения
	pipe_group->SendMess(id_employee, myNumGroup);
	//Ождинание ответа
	while (!pipe_group->CheckCountMyAnswer(myNumGroup));
	//Получение ответа
	return pipe_group->GetMyAnswer(myNumGroup);
}

bool db_manager_parralel::CheckWorkThread()
{
	if (db_thread != NULL) return true;
	return false;
}

thread_obj* db_manager_parralel::CreateNewObj()
{
	db_thread = new db_thread_obj();
	//Запуск потока 
	thread t(*db_thread);
	t.detach();
	return nullptr;
}

void db_manager_parralel::OpenNewThread()
{
	//Проверка, есть ли уже запущенный поток
	if (!CheckWorkThread())
		//Если нет запущенного потока, вызывается функция для создания нового
		CreateNewObj();
	//Данный объект получает ссылки на каналы, для работы с потоком
	pipeControlObj = db_thread->GetControlPipe();
	pipe_find = db_thread->GetSearchPipe();
	pipe_recognit = db_thread->GetRecognitionResultPipe();
	pipe_group = db_thread->GetGroupSearchPipe();
	//Получение номеров для работы с каналами
	myNumRecoginition = pipe_recognit->GetMyNumber();
	myNumSearch = pipe_find->GetMyNumber();
	myNumGroup = pipe_group->GetMyNumber();
}

void db_manager_parralel::CloseThread()
{
	//Сообщенеи потоку о закрытии
	pipeControlObj->SendMessag(ControlMessage::endWork);
	//Ожидание закрытия
	while (!pipeControlObj->CheckThreadIsEnd());
	//Закрытие канала управление
	CloseOldThread();
	//Удаление каналов 
	delete pipe_find;
	delete pipe_recognit;
	db_thread = NULL;
}
