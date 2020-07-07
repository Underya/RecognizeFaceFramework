
#pragma once
#include "thread_obj.h"
#include <thread>

#ifdef RECOGNITIONBB_EXPORTS
#define RECOGNITIONBB_API __declspec(dllexport)
#else
#define RECOGNITIONBB_API __declspec(dllimport)
#endif


//Класс для управления из главного потока ассоциированым с ним потоком
class RECOGNITIONBB_API Control_Thread
{
public:

protected:

	//Создаение нового объекта потока
	//НЕОБХОДИМО пергружать
	virtual thread_obj* CreateNewObj();

	//Открытие нового потока для распознования
	virtual void OpenNewThread();

	//Закрытие ЗАКРЫТОГО потока для распознования
	virtual void CloseOldThread();

	//Проверка, работает ли поток в текущий момент
	virtual bool CheckWorkThread();

	//Указаткель на канал для передачи сообщений объекту 
	simple_pipe<ControlMessage>* pipeControlObj = NULL;
};

