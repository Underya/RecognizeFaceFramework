
#pragma once
#include "simple_pipe.h"

template <typename T>
class RECOGNITIONBB_API limited_pipe :
	public simple_pipe <T>
{
public:
	//ќтправка сообщени€
	void SendMessag(T mess) {
		this->_mutex->lock();
		this->_queue.push(mess);
		//≈сли есть планка на кол-во сообщений
		if (maxMess != -1) {
			//“о выкидываютс€ все лишнии, пока не будет достигнуто нужное число
			while (this->_queue.size() > maxMess) this->_queue.pop();
		}
		this->_mutex->unlock();
	}

	//”становка максимального количества сообщений
	void SetMaxMess(int maxCount) {
		maxMess = maxCount;
	}

private:
	int maxMess = -1;
};

/*
template<typename T>
inline void limited_pipe<T>::SendMessag(T mess)
{
	this->_mutex->lock();
	this->queue.push(mess);
	//≈сли есть планка на кол-во сообщений
	if (maxMess != -1) {
		//“о выкидываютс€ все лишнии, пока не будет достигнуто нужное число
		while (this->queue.size() > maxMess) this->queue.pop();
	}
	this->_mutex->unlock();
}

template<typename T>
inline void limited_pipe<T>::SetMaxMess(int maxCount)
{
	maxMess = maxCount;
}
*/