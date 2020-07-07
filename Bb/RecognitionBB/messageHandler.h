#pragma once
#include "messageHandler_obj.h"
#include "IRecognitionHandler.h"
#include "Control_Thread.h"


#ifdef RECOGNITIONBB_EXPORTS
#define RECOGNITIONBB_API __declspec(dllexport)
#else
#define RECOGNITIONBB_API __declspec(dllimport)
#endif

//Отправления сообщения об распозновании всем, кто должен был слушать
class RECOGNITIONBB_API messageHandler :
	public IRecognitionHandler, 
	public Control_Thread
{
public:

	messageHandler(std::string addressIPV4, std::string port, double time_pause = 15.0);

	virtual void HandlerFace(int cam_id, std::vector<std::string> premise_name, face face, list_rules rules, list_group group, information_camera camera_info) override;

	virtual void SetRulesList(list_rules listRules) override;

	virtual void AddRecepient(Recipient recepient);

	void AddNewRecipient(std::string fileName);

	void AddNewRecipient(std::vector<std::string> filesPath);

protected:

	//Список, который указывает, через какие промежутки времени необхимо отправлять информацию
	//Где int - это Id сотрудника
	timer_list<int> *_timerList = NULL;

	//Единый для всех поток общения с потоком информаирования
	static simple_pipe<Message>* _messPipe;

	//Создание нового объекта
	thread_obj* CreateNewObj() override;

	//Открытие нового потока для распознования
	virtual void OpenNewThread() override;

	//Адрес сокета отправщика
	std::string _address = "";

	//Адрес порта отправщика
	std::string _port = "";

	std::vector<std::string> _recepientFileName;

	std::vector<Recipient> _list_recepient;

	//Передача сообщения в поток, который отправляет сообщения
	void MessTranserToThread(Message mess);

};

