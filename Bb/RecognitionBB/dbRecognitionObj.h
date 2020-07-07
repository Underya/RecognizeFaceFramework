
#pragma once
#include "thread_obj.h"
#include <db_recognition_result.h>

class RECOGNITIONBB_API dbRecognitionObj :
	public thread_obj
{
public:

	//Объект для работы с текущем потоком
	simple_pipe<std::pair<int, int>> GetInfoPipe;



private:
	//Метод, вызываемый при запуске объекта
	void ThreadMethod() override;

	//Поток для передачи информации о том, что надо в БД добавить
	//В формате id сотрудника, id камеры
	simple_pipe<std::pair<int, int>> id_pipe;

	//Указатель на объект для работы с БД
	db_recognition_result* db_result;
};

