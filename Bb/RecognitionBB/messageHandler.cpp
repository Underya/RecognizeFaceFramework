#include "messageHandler.h"

simple_pipe<Message>* messageHandler::_messPipe = NULL;

messageHandler::messageHandler(std::string addressIPV4, std::string port, double time_pause)
{
	_address = addressIPV4;
	_port = port;
	_timerList = new timer_list<int>(time_pause);
}

void messageHandler::HandlerFace(int cam_id, std::vector<std::string> premise_name, face face, list_rules rules, list_group group, information_camera camera_info)
{
	//Если не был создан поток
	if (_messPipe == NULL) OpenNewThread();
	//Проверка, вышел ли сотрудник из списа времени
	if (!_timerList->EndTimeToObj(face.GetId())) return;
	Message message;
	message.SetIdEmployee(face.GetId());
	message.SetFirstName(face.GetFirstName());
	message.SetLastName(face.GetLastName());
	message.SetMidName(face.GetMidName());
	message.SetCurrentTime();
	//Добавление правил и групп
	for (auto iter = rules.begin(); iter != rules.end(); iter++) {
		message.AddRule(iter->first, iter->second);
	}
	for (auto iter = group.begin(); iter != group.end(); iter++) {
		message.AddGroup(iter->first, iter->second);
	}
	//Добавление списка помещений, если он есть
	if (premise_name.size() != 0) {
		message.AddPremiseList(premise_name);
	}
	//Отправка сообщений
	_messPipe->SendMessag(message);
}

void messageHandler::SetRulesList(list_rules listRules)
{
	_listRules = listRules;
}

void messageHandler::AddRecepient(Recipient recepient)
{
	_list_recepient.push_back(recepient);
}

void messageHandler::AddNewRecipient(std::string fileName)
{
	_recepientFileName.push_back(fileName);
}

void messageHandler::AddNewRecipient(std::vector<std::string> filesPath)
{
	for (auto iter = filesPath.begin(); iter != filesPath.end(); iter++) {
		AddNewRecipient(*iter);
	}
}

thread_obj* messageHandler::CreateNewObj()
{
	messageHandler_obj* pro = new messageHandler_obj(_address, _port);
	_messPipe = pro->GetMyPipe();
	pro->AddRecepient(_list_recepient);
	pro->SetListRecepient(_recepientFileName);
	thread_obj* tobj = pro;
	return tobj;
}

void messageHandler::OpenNewThread()
{
	if (_messPipe == NULL) {
		messageHandler_obj* obj = (messageHandler_obj*)CreateNewObj();
		this->pipeControlObj = obj->GetControlPipe();
		std::thread t(*obj);
		t.detach();
	}
}

void messageHandler::MessTranserToThread(Message mess)
{
}
