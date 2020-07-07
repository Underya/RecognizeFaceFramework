
#pragma once
#include <mutex>
#include <iostream>
#include <list>

#ifdef RECOGNITIONBB_EXPORTS
#define RECOGNITIONBB_API __declspec(dllexport)
#else
#define RECOGNITIONBB_API __declspec(dllimport)
#endif


//Дву-стронний канал
//IN - тип сообщений для передачи потоку
//OUT - тип сообщений на выход потоку
template <typename IN_TYPE, typename OUT_TYPE>
class RECOGNITIONBB_API Two_Way_Pipe
{
public:

	Two_Way_Pipe() {
		in_list = new std::list<std::pair<int, IN_TYPE>>();
		out_list = new std::list<std::pair<int, OUT_TYPE>>();
		in_mutex = new std::mutex();
		out_mutex = new std::mutex();
	}

	~Two_Way_Pipe() {

	}

	//Получение номера, для отправки и получения сообщений
	int GetMyNumber() {
		return id_subscriber++;
	}

	//Отправка сообщения
	//mess - сообщение
	//id_subs - номер того, кто отправляет сообщение
	void SendMess(IN_TYPE mess, int id_subs) {
		in_mutex->lock();
		in_list->push_back(std::pair<int, IN_TYPE>(id_subs, mess));
		in_mutex->unlock();
	}

	//Получение количества ответов указанного подписчика
	int CheckCountMyAnswer(int id) {
		int count = 0;
		out_mutex->lock();
		//Подсчёт количества элементов с таким же id
		for (auto iter = out_list->begin(); iter != out_list->end(); iter++) {
			std::pair<int, OUT_TYPE> p;
			p = *iter;
			if (p.first == id) count++;
		}
		out_mutex->unlock();
		return count;
	}

	//Получить ответ на сообщение
	OUT_TYPE GetMyAnswer(int id) {
		std::pair<int, OUT_TYPE> p;
		out_mutex->lock();
		for (auto iter = out_list->begin(); iter != out_list->end(); iter++) {
			if ((*iter).first == id) {
				p = *iter;
				out_list->remove(p);
				break;
			}
		}
		out_mutex->unlock();
		return p.second;
	}

	//Общее количество сообщений
	int CountMess() {
		return in_list->size();
	}

	//Получение сообщения
	std::pair<int, IN_TYPE> GetMess() {
		in_mutex->lock();
		std::pair<int, IN_TYPE> p = in_list->front();
		in_list->pop_front();
		in_mutex->unlock();

		return p;
	}

	void SendAnswer(int id_subs, OUT_TYPE answer) {
		out_mutex->lock();
		out_list->push_back(std::pair<int, OUT_TYPE>(id_subs, answer));
		out_mutex->unlock();
	}

	//Унитчожить поток
	void DeletPipe() {
		delete out_mutex;

	}

protected:

	
	//Список входных сообщений
	std::list<std::pair<int, IN_TYPE>> *in_list;
	//Список выходных сообщений
	std::list<std::pair<int, OUT_TYPE>>* out_list;

	//Мьютекс для входных сообщений
	std::mutex* in_mutex;
	//Мьютекс для выходных сообщений
	std::mutex* out_mutex;

	//Для каждого канала, который хочет получать сообщения, устанвливается свой номер
	//Который выдаётся из этой переменной
	int id_subscriber = 1;

private:
};

/*
template<typename IN_TYPE, typename OUT_TYPE>
inline Two_Way_Pipe<IN_TYPE, OUT_TYPE>::Two_Way_Pipe()
{
	in_list = new std::list<std::pair<int, IN_TYPE>>();
	out_list = new std::list<std::pair<int, OUT_TYPE>>();
	in_mutex = new std::mutex();
	out_mutex = new std::mutex();
}

template<typename IN_TYPE, typename OUT_TYPE>
inline Two_Way_Pipe<IN_TYPE, OUT_TYPE>::~Two_Way_Pipe()
{

}

template <typename IN_TYPE, typename OUT_TYPE>
inline int Two_Way_Pipe<IN_TYPE, OUT_TYPE>::GetMyNumber()
{
	return id_subscriber++;
}

template<typename IN_TYPE, typename OUT_TYPE>
inline void Two_Way_Pipe<IN_TYPE, OUT_TYPE>::SendMess(IN_TYPE mess, int id_subs)
{
	in_mutex->lock();
	in_list->push_back(std::pair<int, IN_TYPE>(id_subs, mess));
	in_mutex->unlock();
}

template<typename IN_TYPE, typename OUT_TYPE>
inline int Two_Way_Pipe<IN_TYPE, OUT_TYPE>::CheckCountMyAnswer(int id)
{
	int count = 0;
	out_mutex->lock();
	//Подсчёт количества элементов с таким же id
	for (auto iter = out_list->begin(); iter != out_list->end(); iter++) {
		pair<int, OUT_TYPE> p;
		p = *iter;
		if (p.first == id) count++;
	}
	out_mutex->unlock();
	return count;
}

template<typename IN_TYPE, typename OUT_TYPE>
inline OUT_TYPE Two_Way_Pipe<IN_TYPE, OUT_TYPE>::GetMyAnswer(int id)
{
	std::pair<int, OUT_TYPE> p;
	out_mutex->lock();
	for (auto iter = out_list->begin(); iter != out_list->end(); iter++) {
		if ((*iter).first == id) {
			p = *iter;
			out_list->remove(p);
			break;
		}
	}
	out_mutex->unlock();
	return p.second;
}

template<typename IN_TYPE, typename OUT_TYPE>
inline void Two_Way_Pipe<IN_TYPE, OUT_TYPE>::DeletPipe()
{
	delete in_list;
	delete in_mutex;
	delete out_list;
	delete out_mutex;
}

template<typename IN_TYPE, typename OUT_TYPE>
inline int Two_Way_Pipe<IN_TYPE, OUT_TYPE>::CountMess()
{
	return in_list->size();
}

template<typename IN_TYPE, typename OUT_TYPE>
inline std::pair<int, IN_TYPE> Two_Way_Pipe<IN_TYPE, OUT_TYPE>::GetMess()
{
	in_mutex->lock();
	std::pair<int, IN_TYPE> p = in_list->front();
	in_list->pop_front();
	in_mutex->unlock();

	return p;
}

template<typename IN_TYPE, typename OUT_TYPE>
inline void Two_Way_Pipe<IN_TYPE, OUT_TYPE>::SendAnswer(int id_subs, OUT_TYPE answer)
{
	out_mutex->lock();
	out_list->push_back(std::pair<int, OUT_TYPE>(id_subs, answer));
	out_mutex->unlock();
}

*/