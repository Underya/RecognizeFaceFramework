
#include "db_manager_parralel.h"
using namespace std;

//������������ ��������� NULL
db_thread_obj *db_manager_parralel::db_thread = NULL;
int db_manager_parralel::countObject = 0;

db_manager_parralel::db_manager_parralel()
{
	countObject++;
	//������������� ���� ������
	db_manager db;
	//��� �������� �������, ���������� ������� ������� ������
	OpenNewThread();
}

db_manager_parralel::~db_manager_parralel()
{
	countObject--;
	//���� ������ �� �������� ���������� �������� - ������� �����
	if (countObject == 0) {
		CloseThread();
	}
}

db_employee db_manager_parralel::SearchFace(float* desc)
{
	//����������� ���������
	pipe_find->SendMess(desc, this->myNumSearch);
	//�������� ������
	while (!pipe_find->CheckCountMyAnswer(myNumSearch));
	//��������� ������
	return pipe_find->GetMyAnswer(myNumSearch);
}

void db_manager_parralel::SaveResetch(int id_employee, int id_camera)
{
	//�������� ��������������� ���������
	pipe_recognit->SendMess(id_camera, id_employee);
}

std::vector<std::pair<int, std::string>> db_manager_parralel::SearchGroup(int id_employee)
{
	//�������� ���������
	pipe_group->SendMess(id_employee, myNumGroup);
	//��������� ������
	while (!pipe_group->CheckCountMyAnswer(myNumGroup));
	//��������� ������
	return pipe_group->GetMyAnswer(myNumGroup);
}

bool db_manager_parralel::CheckWorkThread()
{
	if (db_thread != NULL) return true;
	return false;
}

thread_obj* db_manager_parralel::CreateNewObj()
{
	db_thread = new db_thread_obj();
	//������ ������ 
	thread t(*db_thread);
	t.detach();
	return nullptr;
}

void db_manager_parralel::OpenNewThread()
{
	//��������, ���� �� ��� ���������� �����
	if (!CheckWorkThread())
		//���� ��� ����������� ������, ���������� ������� ��� �������� ������
		CreateNewObj();
	//������ ������ �������� ������ �� ������, ��� ������ � �������
	pipeControlObj = db_thread->GetControlPipe();
	pipe_find = db_thread->GetSearchPipe();
	pipe_recognit = db_thread->GetRecognitionResultPipe();
	pipe_group = db_thread->GetGroupSearchPipe();
	//��������� ������� ��� ������ � ��������
	myNumRecoginition = pipe_recognit->GetMyNumber();
	myNumSearch = pipe_find->GetMyNumber();
	myNumGroup = pipe_group->GetMyNumber();
}

void db_manager_parralel::CloseThread()
{
	//��������� ������ � ��������
	pipeControlObj->SendMessag(ControlMessage::endWork);
	//�������� ��������
	while (!pipeControlObj->CheckThreadIsEnd());
	//�������� ������ ����������
	CloseOldThread();
	//�������� ������� 
	delete pipe_find;
	delete pipe_recognit;
	db_thread = NULL;
}
