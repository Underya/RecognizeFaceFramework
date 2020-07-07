
#include "pch.h"  
// ���������� ������ Camera_file
#include "Camera_file.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/ocl.hpp>

void CameraD::Start() {
    //std::cout << "Camera \"" << _path << "\" start\n";
    //cv::ocl::setUseOpenCL(true);

    //��������� ����� ������ ������
    this->_work = true;

    //����, �����������, ���� �� ��������������
    int hasRec = 0;

    //����, �����������, ���� �� � ���� ������������ ��������
    int hasRetValue = 0;

    if (recogn != NULL) hasRec = 1;

    //������ ����������� �����
    //���������� ��� ��������� �����������
	cv::Mat out;
	cv::UMat img;
	
    //����, �����������, ���� �� ��������� ����
    //���� ��� - ����� ������� �����
    bool there_is_next_frame;

    //������� ����, ������ �������� � ���������� ����������
    while(_work){
		
        try {

			there_is_next_frame = video_file->read(img);
      
			if (!there_is_next_frame) break;

			//����� ���� ���������� ������� � ����������
			ControlStep();


			if (myDetecter != NULL) {
				//�������������
				std::time_t start = clock();
				std::vector<OneFrame> res = myDetecter->ScanFrame(img);
				std::time_t finish = clock();
				double dur = (double)(finish - start) / CLOCKS_PER_SEC;
				//std::cout << "d:" << dur << " \n";

				//���� ���� ���������� ����
				if (res.size() != 0) {
					if (hasRec) recogn->Recognition(res, this->GetInformationCamera());
				}
			}

			//result_detect = myDetecter->ScanFrame(img);
			//else result_detect = img;

			if (_show) {

				resize(img, out, cv::Size(500, 500), 0, 0, 0);
				imshow(_name, out);
				cv::waitKey(1);
			}
        }
		catch (cv::Exception err) {
			std::cout << "Error Text:" << err.what() << "\n\n";
		}
        catch (std::exception err1) {
            std::cout << "Error Text:" << err1.what() << "\n\n";
        }
        catch (...) {
            std::cout << "Lol, kek, exception accept!\n\n";
        }
    }
}

void CameraD::End() {
    _work = false;
}

//�����������
CameraD::CameraD(std::string path, std::string window_name) : information_camera(path, window_name) {
    
    //�������� ����� � ���� ������ OpenCV
    this->video_file = new cv::VideoCapture();
    video_file->open(_path);
    //���� �� ������� ������� ���� ��� ������ - ������� ������, �� �������� ������
    if (!video_file->isOpened()) {
		ThrowOpenError();
    }
    //�� ��������� - ��� ���������
    myDetecter = NULL;
    //�� �������� - ������ ���������
    this->_work = false;
    //� �� ����������
    _show = false;
	this->_name = window_name;
    recogn = NULL;
}

CameraD::CameraD(int num, std::string window_name) : information_camera(num, window_name)
{
    //cv::ocl::setUseOpenCL(true);
    //�������� ����� � ���� ������ OpenCV
    this->video_file = new cv::VideoCapture();
    video_file->open(_num_cam);
    //���� �� ������� ������� ���� ��� ������ - ������� ������, �� �������� ������
    if (!video_file->isOpened()) {
		ThrowOpenError();
    }
    //�� ��������� - ��� ���������
    myDetecter = NULL;
    //�� �������� - ������ ���������
    this->_work = false;
	this->_name = window_name;
    //� �� ����������
    _show = false;
	this->_name = window_name;
    recogn = NULL;
}

void CameraD::StartShow() {
    this->_show = true;
}

void CameraD::EndShow() {
    this->_show = false;
}

void CameraD::ThrowOpenError()
{
	std::string error_text = "Error: Camera \"";
	error_text += _name;
	error_text += "\" not open\n";
	throw std::exception(error_text.c_str());
}

void CameraD::ControlStep()
{
}

void CameraD::SetDetecter(Detecter* Detect) {
    this->myDetecter = Detect;
}

void CameraD::SetRecognition(IRecognitor* r)
{
	r->_id_cam = _id_cam;
    this->recogn = r;
}


Detecter* CameraD::GetDetecter() {
    return this->myDetecter;
}


CameraD::~CameraD() {
    //delete this->myDetecter;
    delete this->video_file;
    //if (Detecter != NULL) delete Detecter;
    //std::cout << "Camera \"" << this->_path << "\" is delete\n";
}


