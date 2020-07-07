
#include "db_thread_obj.h"
using namespace std;

db_thread_obj::db_thread_obj() : thread_obj()
{
	search_pipe = new Two_Way_Pipe<float*, db_employee>();
	recognition_result = new Two_Way_Pipe<int, int>();
	this->group_search_pipe = new Two_Way_Pipe<int, std::vector<std::pair<int, string>>>();
}

db_thread_obj::~db_thread_obj() 
{
	//�������� ����, ��� ����� �������� ������
	this->pipe->SetThreadIsEnd();
}

Two_Way_Pipe<float*, db_employee >* db_thread_obj::GetSearchPipe()
{
	return search_pipe;
}

Two_Way_Pipe<int, int>* db_thread_obj::GetRecognitionResultPipe()
{
	return recognition_result;
}

Two_Way_Pipe<int, std::vector<std::pair<int, string>>>* db_thread_obj::GetGroupSearchPipe()
{
	return group_search_pipe;
}

void db_thread_obj::ThreadMethod()
{
	while (true) {
		//������ ����������� ���������
		ParseControlMess();
		if (!work) return;
		//������ ��������� �� �������������
		RecognitionMess();
		//������ ��������� �� ����������� ���
		SearchMess();
		//������ ��������� � ������ ������
		GroupSearchMess();
	}
}

void db_thread_obj::ParseControlMess()
{
	if (pipe->GetCountMess() == 0) return;
	ControlMessage mess = this->pipe->GetMessag();
	if (mess == ControlMessage::endWork) {
		work = false;
	}
}

void db_thread_obj::RecognitionMess()
{
	//���� ���� ��������� �� ���, ��� ���� �������������
	//� ���������� �� ���� ���� �������� � ��
	if(recognition_result->CountMess() == 0) return;

	//��������� ���������
	std::pair<int, int> p = recognition_result->GetMess();

	//�������� ���������� ��� ���������� ����������� � ��
	db_recognition_result drr;

	//���������� ���������� � ��
	try {
		drr.addNewRecognitionResult(p.first, p.second);
	}
	catch (std::exception err) {
		cout << "Exceprtion! Not add inform to db! Text_error:" << err.what() << "\n";
	}
	catch (...) {

	}
}

void db_thread_obj::SearchMess()
{
	//���� ���� ������ �� �����, ��� ���������� ���������
	if (search_pipe->CountMess() == 0) return;

	//��������� ���������
	std::pair<int, float*> p = search_pipe->GetMess();

	//����� ������� ��� �������������
	int id_obj =  db_face::SearchFace(p.second);
	
	//���������� ��� ������ � ����������� �� ����������
	//���� ��������� -1, �� ��� ������, ��� �� ������� ����� ������������ � ��
	if (id_obj == -1) {
		
		//�������� ������ � ����������� � � ��������������� ����������
		db_employee emp;
		search_pipe->SendAnswer(p.first, emp);
	}
	else {
		//���� ������� �����������, �� ������������ ����� � �����������
		//��������� ����������
		db_employee empl(id_obj);
		//�������� ������
		search_pipe->SendAnswer(p.first, empl);
	}

	
}

void db_thread_obj::GroupSearchMess()
{
	//���� ������ �� ����� �����
	if (group_search_pipe->CountMess() == 0) return;

	//��������� ���������
	std::pair<int, int> p = group_search_pipe->GetMess();
	//���������� id �����������
	int id_addr = p.first;
	//�������� ������
	std::vector<std::pair<int, std::string>>  answer;
	list<db_group> snapGroup =	db_group::GetSnapGoup(p.second);

	//������ ����� � ���������� ���� � �����
	for (auto iter = snapGroup.begin(); iter != snapGroup.end(); iter++) {
		pair<int, std::string> p;
		p.first = iter->GetId();
		p.second = iter->GetName();
		answer.push_back(p);
	}
	//����������� ������ ������������
	group_search_pipe->SendAnswer(id_addr, answer);
}
