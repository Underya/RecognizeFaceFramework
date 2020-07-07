
#pragma once
#include <thread>
#include <mutex>
#include <queue>
#include "iostream"


#ifdef RECOGNITIONBB_EXPORTS
#define RECOGNITIONBB_API __declspec(dllexport)
#else
#define RECOGNITIONBB_API __declspec(dllimport)
#endif


//Канал для передачи объектов через потоки с помощью mutex
 template <typename T> 
class RECOGNITIONBB_API simple_pipe
{
public:
	
	simple_pipe() {
		_mutex = new std::mutex();
		_threadEnd = false;
	}

	~simple_pipe() {

	}

	//Отправление нового сообщения
	 virtual void  SendMessag(T mess) {
		_mutex->lock();
		_queue.push(mess);
		_mutex->unlock();
	}

	//Получение количества сообщений
	int GetCountMess() {
		int count = 0;
		_mutex->lock();
		count = _queue.size();
		_mutex->unlock();
		return count;
	}

	//Получение последнего сообщения
	virtual T   GetMessag() {
		_mutex->lock();
		T ret = _queue.front();
		_queue.pop();
		_mutex->unlock();
		return ret;
	}

	//Проверка, закончил ли работу поток
	bool  CheckThreadIsEnd() {
		_mutex->lock();
		bool ret = _threadEnd;
		_mutex->unlock();
		return ret;
	}

	//Указать, что поток закончил работу
	void  SetThreadIsEnd() {
		_mutex->lock();
		_threadEnd = true;
		_mutex->unlock();
	}

	//Очищение мьютекса
	void  DeletMex() {
		delete _mutex;
	}

protected:

	//Флаг, был ли уничтожен поток.  
	bool _threadEnd;

	//Очередь всех сообщений
	std::queue<T> _queue;

	//Мьютекс, на основании блокировки которого и передаются сообщения
	std::mutex *_mutex;
};

/*
template<typename T> RECOGNITIONBB_API
inline  simple_pipe<T>::simple_pipe()
{
	_mutex = new std::mutex();
}

template<typename T> RECOGNITIONBB_API
inline RECOGNITIONBB_API simple_pipe<T>::~simple_pipe()
{
	//while (!_mutex.try_lock());
	//_mutex.unlock();
	//std::cout << "delete mut\n";
	//delete _mutex;
}

template<typename T> RECOGNITIONBB_API
inline  void RECOGNITIONBB_API simple_pipe<T>:: SendMessag(T mess)
{
	
}

template<typename T> RECOGNITIONBB_API
inline RECOGNITIONBB_API  int RECOGNITIONBB_API simple_pipe<T>::GetCountMess()
{
	return queue.size();
}

template<typename T> RECOGNITIONBB_API
inline RECOGNITIONBB_API  T RECOGNITIONBB_API simple_pipe<T>::GetMessag()
{
	//while (!_mutex->try_lock());
	_mutex->lock();
	T ret = queue.front();
	queue.pop();
	_mutex->unlock();
	return ret;
}

template<typename T> RECOGNITIONBB_API
inline RECOGNITIONBB_API  bool RECOGNITIONBB_API simple_pipe<T>::CheckThreadIsEnd()
{
	_mutex->lock();
	bool ret = threadEnd;
	_mutex->unlock();
	return ret;
}

template<typename T> RECOGNITIONBB_API
inline  RECOGNITIONBB_API void RECOGNITIONBB_API simple_pipe<T>::SetThreadIsEnd()
{
	_mutex->lock();
	threadEnd = true;
	_mutex->unlock();
}

 template<typename T> RECOGNITIONBB_API
inline  RECOGNITIONBB_API void RECOGNITIONBB_API simple_pipe<T>::DeletMex()
{
	delete _mutex;
}

 */