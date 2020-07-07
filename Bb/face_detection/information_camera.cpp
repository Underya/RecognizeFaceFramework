#include "information_camera.h"

information_camera::information_camera() {

}

information_camera::information_camera(std::string path, std::string window_name)
{
	//Проверка, не является ли путь номером
	//Если номер, то обрабатывается как камера
	if (CheckIsNum(path)) {
		_num_cam = atoi(path.c_str());
		//Указание названия
		if (window_name == "") {
			SetName("camera number:" + path);
		}
		else {
			SetName(window_name);
		}
	}
	//Если нет, то работа как с окном
	else {
		this->_path = path;
		if (window_name == "") {
			SetName(path);
		}
		else {
			SetName(window_name);
		}
	}
	
}

information_camera::information_camera(int number, std::string window_name)
{
	_num_cam = number;
	if (window_name == "") {
		SetName("camera number:" + std::to_string(number));
	}
	else {
		SetName(window_name);
	}


}

bool information_camera::IsWebCam()
{
	if (_path == "") return false;
	return true;
}

bool information_camera::IsUsbCam()
{
	if (_num_cam == -1) return false;
	return true;
}

void information_camera::SetCameraInfo(int id, std::string description)
{
	_id_cam = id;
	_description = description;
}

int information_camera::GetId()
{
	return _id_cam;
}

std::string information_camera::GetDescrtiption()
{
	return _description;
}

void information_camera::SetName(std::string window_name)
{
	_name = window_name;
}

void information_camera::SetPremises(std::vector<std::pair<int, std::string>> stack_premises)
{
	_premises = stack_premises;
}

std::vector<std::pair<int, std::string>> information_camera::GetPremises()
{
	return _premises;
}

std::string information_camera::GetName()
{
	return _name;
}

information_camera information_camera::GetInformationCamera()
{
	return *this;
}

std::string information_camera::GetPath()
{
	return _path;
}

int information_camera::GetNumber()
{
	return _num_cam;
}

bool information_camera::CheckIsNum(std::string path)
{
	for (int i = 0; i < path.length(); i++) {
		if (!isdigit(path[i])) return false;
	}

	return true;
}
