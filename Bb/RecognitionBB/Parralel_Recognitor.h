
#pragma once
#include "Parralel_Recognitor_obj.h"
#include "IRecognitor.h"
#include "Control_Thread.h"
#include "IRecognitionHandler.h"

//Класс, через методы которого осуществляется парралельное распознование
class RECOGNITIONBB_API Parralel_Recognitor: 
	public IRecognitor, 
	public Control_Thread
{
public:
	
	Parralel_Recognitor(face_manager *faceManager);

	~Parralel_Recognitor();

	void StartShow();

	void EndShow();

	void EndWork() override;

	//Указать имя для графического окна(должно быть уникально)
	void SetName(std::string name);

	//Создание нового объекта для распознования
	thread_obj* CreateNewObj() override;

	//Распознование указанного списка лиц
	void IRecognitor::Recognition(std::vector<OneFrame> faces, information_camera cam) override;

	void SetDbFaceSource(db_manager_parralel *dbmp);

	//Добавить новый обработчки в список
	void AddHandler(IRecognitionHandler* handler);

private:

	

	db_manager_parralel* _dbmp = NULL;

	//Вектор со всеми обработчиками, что вызываются при распозновании
	std::vector<IRecognitionHandler*> Handlers;

	void OpenNewThread() override;

	//Указетель на канал для передачи кадров объекту объектом для распознования
	simple_pipe<std::pair<Frames, information_camera>>* pipeToObj;

	std::string _name;

	//База с лицами
	face_manager* _faceManager;
};

