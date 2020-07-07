
#include "Control_Thread.h"

thread_obj* Control_Thread::CreateNewObj()
{
	return nullptr;
}

void Control_Thread::OpenNewThread()
{
	if (this->pipeControlObj != NULL) CloseOldThread();
	thread_obj *obj = CreateNewObj();
	this->pipeControlObj = obj->GetControlPipe();
	std::thread t(*obj);
	t.detach();
}

void Control_Thread::CloseOldThread()
{
	this->pipeControlObj->DeletMex();
	delete this->pipeControlObj;
	this->pipeControlObj = NULL;
}

bool Control_Thread::CheckWorkThread()
{
	if (this->pipeControlObj == NULL) return false;
	if (this->pipeControlObj->CheckThreadIsEnd()) return false;
	return true;
}
