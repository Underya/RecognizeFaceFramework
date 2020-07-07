
#include "Parralel_Recognitor_obj.h"

#include <time.h>

int number_proc = 0;

bool Parralel_Recognitor_obj::_showTime_recognit = true;

std::mutex* Parralel_Recognitor_obj::_Umat_mutex = NULL;

Parralel_Recognitor_obj::Parralel_Recognitor_obj(face_manager * faceManager) : thread_obj()
{
	//cv::ocl::setUseOpenCL(true);
	limited_pipe<std::pair<Frames, information_camera>>* p = new limited_pipe<std::pair<Frames, information_camera>>();
	if (_Umat_mutex == NULL) {
		_Umat_mutex = new std::mutex();
	}
	p->SetMaxMess(2);
	pipe = p;
	pipeControl = new simple_pipe<ControlMessage>();
	_faceManager = faceManager;
	//_name = "Recognit";
	num = number_proc++;
	//cout << "proc start:" << num << "\n";
}

Parralel_Recognitor_obj::~Parralel_Recognitor_obj()
{
	//cout << "proc dead:" << num << "\n";
}

simple_pipe<std::pair<Frames, information_camera>>* Parralel_Recognitor_obj::GetMyPipe()
{
	return (this->pipe);
}

simple_pipe<ControlMessage>* Parralel_Recognitor_obj::GetControlPipe()
{
	return pipeControl;
}

void Parralel_Recognitor_obj::SetName(std::string name)
{
	_name = name;
}

int resCount = 0;

int id_face = 100;

void Parralel_Recognitor_obj::Recognition(Frames frames, information_camera inform)
{
	string res = "";
	for (auto iter = frames.begin(); iter != frames.end(); iter++) {
		cv_image<rgb_pixel> image;
		while (true) {
			try {
				_Umat_mutex->lock();
				//image = iter->dlib_frame;
				_Umat_mutex->unlock();
			}
			catch (...) {
				cout << "exception catch\n";
				_Umat_mutex->unlock();
				continue;
			}
			break;
		}
		clock_t start = clock();
		face* f = _faceManager->Recongit(iter->dlib_frame);
		clock_t finish = clock();
		double dur = (double)(finish - start) / CLOCKS_PER_SEC;
		//if(_showTime_recognit)
			//cout << "r:" << dur << " \n";
		//resCount++;
 
		if (f == NULL) {
			//��������, ��� �� ������� ����������� ����
			f = new face(-1, "Unrecognized", "Unrecognized", "Unrecognized");
		}
		
		

		//���� �� ������� ���������� ����
		if (f->GetId() == -1) {
			//������� ����� ��� � ��
			if (_dbmp != NULL && f->GetDescriptorCount() != 0) {
				float* res = _faceManager->GetFloat(f->GetMatrixDescriptor(0));
				//���� ���� ����� ����������� - ����� � ��
				db_employee db_face = _dbmp->SearchFace(res);
				//���� ������� ���� � ����
				if (db_face.GetId() != -1) {
					//�� ���������� ���������� � ����
					face* newFace = new face(db_face.GetId(), db_face.GetFirstName(), db_face.GetLastName(), db_face.GetMidleName(), db_face.GetDescrInfo());

					//����� �����, ��������� � �����������
					//������ ����������� � ������
					group_load_face *glf =  new group_load_face( _dbmp->SearchGroup(db_face.GetId()));

					//cout << "Search group for " << glf->GetCount() << "\n";

					//���� ���� ���������� ������, ��� ����������� � ������� ����
					if (glf->GetCount()) {
						newFace->SetAddLoad(glf);
					}
					else {
						//����� - ������������ �������
						delete glf;
					}

					//���� �� ���� ������ ����������
					if (!_faceManager->CheckId(db_face.GetId())) {
						//���������� ���� � ���� ��� ������
						_faceManager->AddNewFace(db_face.GetId(), db_face.GetFirstName(), db_face.GetLastName(), db_face.GetMidleName(), db_face.GetDescrInfo());
					}
					//_faceManager->AddDescriptor(db_face.first, f->GetDescriptor(0));
					//�������� ���������� � �� �������� ����
					delete f;
					//� ������ �������� ����
					f = newFace;
				}
			}
		}
		//cout << "recognit:" << f->GetFirstName() << "\n";
		
		//�������� ���������� ���� ������������
		for (auto iter = handlers->begin(); iter != handlers->end(); iter++) {
			if (f->GetId() == -1) {
				group_load_face* glf = new group_load_face();
				glf->AddGroup(-1, "undefined");
				f->SetAddLoad(glf);
			}

			(*iter)->RecognitionFace(*f, inform);
		}


		//���� �� ������� ����� ����, ��������� ��� ��� ����� � ���� ������ ���
		/*if (f->GetId() == -1) {
			this->_Umat_mutex->lock();
			_faceManager->AddNewFace(id_face, "new_face:" + to_string(id_face));
			_faceManager->AddDescriptor(id_face++, f->GetDescriptor(0));
			this->_Umat_mutex->unlock();
		}*/

		if (false) {
			try {
				//cv::ocl::setUseOpenCL(true);
				cv::Mat img = iter->frame.getMat(cv::ACCESS_READ);
				cv::Mat out;
				cv::resize(img, out, cv::Size(500, 500));
				cv::putText(out, res, cv::Point(30, 450), cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(255, 255, 255));
				cv::imshow(_name, out);
				cv::waitKey(1);
			}
			catch (...) {
				cout << "out put exception\n";
			}
		}
		//cout << "all recog:" << resCount << endl;
		//�������� �� ������������ ���� �� ������
		//if (f->GetId() == -1) delete f;
	}
	
}

void Parralel_Recognitor_obj::SetFaceDb(db_manager_parralel* dbmp)
{
	_dbmp = dbmp;
}

void Parralel_Recognitor_obj::SetHandler(std::vector<IRecognitionHandler*>* handlers)
{
	this->handlers = handlers;
}

void Parralel_Recognitor_obj::ThreadMethod()
{
//	cv::ocl::setUseOpenCL(true);
	//���� ��������, ����� �������� - ������� �����������
	while (currTime < timeLife) {
		if (pipeControl->GetCountMess() != 0) {
			//���� ������� ������� ��������� ���������� ������� -1 - ����� ������ �����
			if (ControlMessParser(pipeControl->GetMessag()) == -1) { 
				//������� ��� ���� ������������ ����� END
				for (auto iter = handlers->begin(); iter != handlers->end(); iter++) {
					(*iter)->EndWork();
				}
				break; 
			}
		}
		if (pipe->GetCountMess() == 0) {
			//���� �� ���� ���������, �� ��� �� ��������� �����
			currTime += 0.1;
			this_thread::sleep_for(0.1s);
		}
		else {
			//����� - ��������� ��������
			currTime = 0;
			std::pair<Frames, information_camera> message = pipe->GetMessag();
			Recognition(message.first, message.second);
		}
	}

	//std::cout << "Thread work closse\n";
	//�������, ��� ����� �������� ������
	this->pipeControl->SetThreadIsEnd();
}

int Parralel_Recognitor_obj::ControlMessParser(ControlMessage mess)
{
	if (mess == ControlMessage::endShow) {
		showImage = false;
	}
	if (mess == ControlMessage::startShow) {
		showImage = true;
	}
	if (mess == ControlMessage::endWork) {
		//std::cout << "Thread End Work\n";
		return -1;
	}

	return 0;
}

