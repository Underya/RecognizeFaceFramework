
#pragma once
#include "pch.h"
#include "ControlMessage.h"
#include "simple_pipe.h"

//Класс, который выполняется в паррелельном потоке
class RECOGNITIONBB_API thread_obj
{
public:

	thread_obj();

	//Полученеи канала для общения
	simple_pipe<ControlMessage>* GetControlPipe();

	//Метод, с которого начианется работа потока
	void operator()();

protected:

	//Метод, который вызывается, когда поток начинает работать
	virtual void ThreadMethod();

	//Метод, в котором разибраются сообщения для контроля
	virtual void ParseControlMess();

	//Канал, по которому объект получает сообщения
	simple_pipe<ControlMessage>* pipe;
};

