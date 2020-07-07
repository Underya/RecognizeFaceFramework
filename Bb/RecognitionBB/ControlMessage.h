
#pragma once

#ifdef RECOGNITIONBB_EXPORTS
#define RECOGNITIONBB_API __declspec(dllexport)
#else
#define RECOGNITIONBB_API __declspec(dllimport)
#endif


//Возможные сообщения, которые передаются потоку для управления
enum RECOGNITIONBB_API ControlMessage {
	endWork,			//Конец работы потока
	startShow,			//Начать вывод изображения
	endShow,			//Закончить вывод изображения
	startMessToConsole,	//Начать вывод сообщений в консоль
	endMessToConsole	//Закончить вывод сообщений в консоль
};