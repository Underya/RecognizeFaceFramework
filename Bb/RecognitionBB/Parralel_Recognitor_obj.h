
#pragma once
#include "limited_pipe.h"
#include "..//face_detection/OneFrame.h"
#include <face_manager.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/ocl.hpp>
#include "thread_obj.h"
#include "IRecognitionHandler.h"
#include "db_manager_parralel.h"
#include <map>

typedef std::vector<OneFrame> Frames;

//Парралельное распознование лиц
class RECOGNITIONBB_API Parralel_Recognitor_obj:
	public thread_obj
{
public:
	
	Parralel_Recognitor_obj(face_manager * faceManager);

	~Parralel_Recognitor_obj();

	//Указатель на канал, с помощью которого передача объекту кадров для распознования
	simple_pipe<std::pair<Frames, information_camera>>* GetMyPipe();

	//Указатель на канал, с помощью которого происходит управление над объектом
	simple_pipe<ControlMessage> *GetControlPipe();

	void SetName(std::string name);

	//Распознование лиц, переданных в параметре frames
	void Recognition(Frames frames, information_camera inform);

	//Установка объекта, для поиска в базе данных лица, если не найдено среди известных
	void SetFaceDb(db_manager_parralel* dbmp);

	//Установка указателя на вектор с обработчиками
	void SetHandler(std::vector<IRecognitionHandler*>* handlers);

private:

	//Единый для всех объектов мьютекс, что бы не вызывать ошибку при получении матрицы
	static std::mutex* _Umat_mutex;

	int num = 0;
	//Вектор со всеми обработчкиами распознования
	std::vector<IRecognitionHandler*>* handlers = NULL;

	//Функция, с которой начинает работу поток
	virtual void ThreadMethod() override;

	//Метод разбирающий сообщения от управления
	//Возвращает -1 - конец работы патока
	int ControlMessParser(ControlMessage mess);

	//Флаг, указывающий, что надо выводить изображение
	bool showImage = false;

	//Объект, в котором происходит поиск при не распознании
	db_manager_parralel * _dbmp = NULL;

	face_manager *_faceManager;

	//Канал, который используется для передачи кадров для распознования
	simple_pipe<std::pair<Frames, information_camera>>* pipe;

	//Передачу объекту сообщений управления (Конец, начать показ, конец показа)
	simple_pipe<ControlMessage>* pipeControl;

	//Время, которое объект будет существовать без вызовов  (в секундах)
	float timeLife = 10.0;
	
	//Имя для отображения окна
	string _name;

	//Текущее время существования без вызовов
	float currTime = 0;

	static bool _showTime_recognit;
};

