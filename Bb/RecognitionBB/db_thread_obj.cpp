
#include "db_thread_obj.h"
using namespace std;

db_thread_obj::db_thread_obj() : thread_obj()
{
	search_pipe = new Two_Way_Pipe<float*, db_employee>();
	recognition_result = new Two_Way_Pipe<int, int>();
	this->group_search_pipe = new Two_Way_Pipe<int, std::vector<std::pair<int, string>>>();
}

db_thread_obj::~db_thread_obj() 
{
	//Указание того, что поток завершил работу
	this->pipe->SetThreadIsEnd();
}

Two_Way_Pipe<float*, db_employee >* db_thread_obj::GetSearchPipe()
{
	return search_pipe;
}

Two_Way_Pipe<int, int>* db_thread_obj::GetRecognitionResultPipe()
{
	return recognition_result;
}

Two_Way_Pipe<int, std::vector<std::pair<int, string>>>* db_thread_obj::GetGroupSearchPipe()
{
	return group_search_pipe;
}

void db_thread_obj::ThreadMethod()
{
	while (true) {
		//Разбор контрольных сообщений
		ParseControlMess();
		if (!work) return;
		//Разбор сообщений об распозновании
		RecognitionMess();
		//Разбор сообщений об обнаружении лиц
		SearchMess();
		//Разбор сообщений о поиске группы
		GroupSearchMess();
	}
}

void db_thread_obj::ParseControlMess()
{
	if (pipe->GetCountMess() == 0) return;
	ControlMessage mess = this->pipe->GetMessag();
	if (mess == ControlMessage::endWork) {
		work = false;
	}
}

void db_thread_obj::RecognitionMess()
{
	//Если есть сообщение об том, что было распознование
	//И информацию об этом надо добавить в БД
	if(recognition_result->CountMess() == 0) return;

	//Получение сообщения
	std::pair<int, int> p = recognition_result->GetMess();

	//Создание переменной для добавления резултьтата в БД
	db_recognition_result drr;

	//Добавление результата в БД
	try {
		drr.addNewRecognitionResult(p.first, p.second);
	}
	catch (std::exception err) {
		cout << "Exceprtion! Not add inform to db! Text_error:" << err.what() << "\n";
	}
	catch (...) {

	}
}

void db_thread_obj::SearchMess()
{
	//Если есть запрос на поиск, его необходимо выполнить
	if (search_pipe->CountMess() == 0) return;

	//Получение сообщения
	std::pair<int, float*> p = search_pipe->GetMess();

	//Вызов функции для распознования
	int id_obj =  db_face::SearchFace(p.second);
	
	//Переменная для ответа с информацией об сотруднике
	//Если вернулось -1, то это значит, что не удалось найти пользователя в БД
	if (id_obj == -1) {
		
		//Создаётся объект с информацией с о нераспознаноном сотруднике
		db_employee emp;
		search_pipe->SendAnswer(p.first, emp);
	}
	else {
		//Если удалось распозноать, то отпарвляется ответ с информацией
		//Получение информации
		db_employee empl(id_obj);
		//Отправка ответа
		search_pipe->SendAnswer(p.first, empl);
	}

	
}

void db_thread_obj::GroupSearchMess()
{
	//Если запрос на поиск групп
	if (group_search_pipe->CountMess() == 0) return;

	//Получение сообщения
	std::pair<int, int> p = group_search_pipe->GetMess();
	//Сохранения id отправителя
	int id_addr = p.first;
	//Создание ответа
	std::vector<std::pair<int, std::string>>  answer;
	list<db_group> snapGroup =	db_group::GetSnapGoup(p.second);

	//Разбор групп и добавление инфы в ответ
	for (auto iter = snapGroup.begin(); iter != snapGroup.end(); iter++) {
		pair<int, std::string> p;
		p.first = iter->GetId();
		p.second = iter->GetName();
		answer.push_back(p);
	}
	//Отправление ответа пользователя
	group_search_pipe->SendAnswer(id_addr, answer);
}
