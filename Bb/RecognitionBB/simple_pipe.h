
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


//����� ��� �������� �������� ����� ������ � ������� mutex
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

	//����������� ������ ���������
	 virtual void  SendMessag(T mess) {
		_mutex->lock();
		_queue.push(mess);
		_mutex->unlock();
	}

	//��������� ���������� ���������
	int GetCountMess() {
		int count = 0;
		_mutex->lock();
		count = _queue.size();
		_mutex->unlock();
		return count;
	}

	//��������� ���������� ���������
	virtual T   GetMessag() {
		_mutex->lock();
		T ret = _queue.front();
		_queue.pop();
		_mutex->unlock();
		return ret;
	}

	//��������, �������� �� ������ �����
	bool  CheckThreadIsEnd() {
		_mutex->lock();
		bool ret = _threadEnd;
		_mutex->unlock();
		return ret;
	}

	//�������, ��� ����� �������� ������
	void  SetThreadIsEnd() {
		_mutex->lock();
		_threadEnd = true;
		_mutex->unlock();
	}

	//�������� ��������
	void  DeletMex() {
		delete _mutex;
	}

protected:

	//����, ��� �� ��������� �����.  
	bool _threadEnd;

	//������� ���� ���������
	std::queue<T> _queue;

	//�������, �� ��������� ���������� �������� � ���������� ���������
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