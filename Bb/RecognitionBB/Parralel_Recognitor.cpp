
#include "Parralel_Recognitor.h"

Parralel_Recognitor::Parralel_Recognitor(face_manager* faceManager)
{
	_faceManager = faceManager;
}

Parralel_Recognitor::~Parralel_Recognitor()
{
	//Если Есть активный поток
	if (CheckWorkThread()) {
		//Указать потоку, что необходимо завершить работу
		pipeControlObj->SendMessag(ControlMessage::endWork);
		CloseOldThread();
	}
}

void Parralel_Recognitor::StartShow()
{
	if (CheckWorkThread())
		pipeControlObj->SendMessag(ControlMessage::startShow);
	else
		throw new std::exception("Error! Thred not work! Location:Parralel_Recognition/StartShow\n");
}

void Parralel_Recognitor::EndShow()
{
	if (CheckWorkThread()) 
		pipeControlObj->SendMessag(ControlMessage::endShow);
	else
		throw new std::exception("Error! Thred not work! Location:Parralel_Recognition/EndShow\n");
}

void Parralel_Recognitor::EndWork()
{
	pipeControlObj->SendMessag(ControlMessage::endWork);
}

void Parralel_Recognitor::SetName(std::string name)
{
	_name = name;
}

thread_obj* Parralel_Recognitor::CreateNewObj()
{
	Parralel_Recognitor_obj *pro = new Parralel_Recognitor_obj(_faceManager);
	pipeToObj = pro->GetMyPipe();
	pro->SetName(_name);
	pro->SetHandler(&Handlers);
	pro->SetFaceDb(_dbmp);
	thread_obj* tobj = pro;
	return tobj;
}

void Parralel_Recognitor::SetDbFaceSource(db_manager_parralel* dbmp)
{
	_dbmp = dbmp;
}

void Parralel_Recognitor::AddHandler(IRecognitionHandler* handler)
{
	handler->SetId(_id_cam);
	Handlers.push_back(handler);
}

void Parralel_Recognitor::OpenNewThread()
{
	//cv::ocl::setUseOpenCL(true);
	if (this->pipeControlObj != NULL) CloseOldThread();
	Parralel_Recognitor_obj* obj = (Parralel_Recognitor_obj*)CreateNewObj();
	this->pipeControlObj = obj->GetControlPipe();
	std::thread t(*obj);
	t.detach();
}


void Parralel_Recognitor::Recognition(std::vector<OneFrame> faces, information_camera cam) {


	if (!CheckWorkThread()) {

		OpenNewThread();
	}
	//Передача сообщения потоку
	pipeToObj->SendMessag({ (Frames)faces, cam});
	StartShow();
	/*
	Parralel_Recognitor_obj obj;
	pipeToObj = obj.GetMyPipe();
	thread t(obj, faces);
	this_thread::sleep_for(2.5s);
	pipeToObj->SendMessage(faces);
	std::cout << "Trying to join\n";
	t.join();
	std::cout << "Success join to thread!" << "\n";
	*/
}

