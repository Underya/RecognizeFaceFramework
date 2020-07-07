
#include "distribute_recognitor.h"

int distribute_recognitor::numm = 1;

distribute_recognitor::distribute_recognitor(face_manager* fm, int count_thread)
{
	my_num = numm++;
	//Сохранение информации
	_fm = fm;
	_count_thread = count_thread;
	//Проверка на ошибку
	if (_count_thread < 1) throw new exception("Count thread must eqal 1 or more");
	//Создание объектов потоков
	for (int i = 0; i < _count_thread; i++) {
		Parralel_Recognitor pr(_fm);
		_recognitors.push_back( new Parralel_Recognitor(_fm));
	}
}

distribute_recognitor::~distribute_recognitor()
{
}

void distribute_recognitor::Recognition(std::vector<OneFrame> vector_fram, information_camera cam)
{

	//Вызов следующего в очереди использования потока для распознования
	_recognitors[_last_use_thread]->Recognition(vector_fram, cam);
	_last_use_thread = (_last_use_thread + 1) % _count_thread;
}

void distribute_recognitor::SetDBSource(db_manager_parralel* dbmp)
{
	_dbmp = dbmp;
	for (auto iter = this->_recognitors.begin(); iter != this->_recognitors.end(); iter++) {
		(*iter)->SetDbFaceSource(_dbmp);
	}
}

void distribute_recognitor::AddRecognitionHandler(IRecognitionHandler *recognitionHandler)
{
	for (auto iter = this->_recognitors.begin(); iter != this->_recognitors.end(); iter++) {
		recognitionHandler->SetId(this->_id_cam);
		(*iter)->AddHandler(recognitionHandler);
	}
}

void distribute_recognitor::SetId(int id_cam)
{
	_id_cam = id_cam;
	for (auto iter = _recognitors.begin(); iter != _recognitors.end(); iter++) {
		(*iter)->_id_cam = _id_cam;
	}
}

void distribute_recognitor::EndWork()
{
	for (auto iter = this->_recognitors.begin(); iter != this->_recognitors.end(); iter++) {
		(*iter)->EndWork();
	}
}
