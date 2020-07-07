#include "camera_information.h"

using namespace std;

camera_information::camera_information(bool use_db)
{
	_use_db = use_db;
	//���� �����, �� �������� ���������� � ��
	if (_use_db)
		initializeDB();
	//������������� �������� �������
	initializeFile();
}

camera_information::~camera_information()
{
}

void camera_information::InitialInfoFile(string path)
{
	//�������� ����� ��� ������
	std::ifstream file(path);
	//������ ������ - ����� ������
	std::string address;

	//���������� ��� ���������� ���������� � ������� ������ � ��
	db_vcam _db_cam = NULL;

	//���� �� ������� ������� ����
	if (!file.is_open()) throw new exception();

	//������ ����� �����
	while (std::getline(file, address)) {

		if (address == "") continue;

		//������� ������, ���� �� ��� ���������� � ������� � ��
		if (_use_db) {
			//�������� ����� ������
			_db_cam = db_vcam::addNewCamera(address, "n", 7, 1);
			
		}

		////���� ���� ������ � �������� ��������
		////���� �� ������� ���������� � ���� ������
		//if (_db_cam == NULL) {
		//	//���������� � ������ ����������� � ����
		//	file_cam->AddNewCamera(address);
		//} else
		//	//���� ���������� � ������ ���� � ��
		//	//�� ��� ����������� � ����
		//{
		//	file_cam->AddNewCamera(
		//		_db_cam->GetAddress(),
		//		_db_cam->GetDescription(),
		//		//����� ������ ������� ���������� ��� ID
		//		_db_cam->GetPremise().GetId(),
		//		_db_cam->GetPosition(),
		//		_db_cam->GetId());

		//}
		
	}
	
	//���������� ���������� � ������� � �������� �������
	file_cam->Save();
}



int camera_information::UpdateToFile(string path)
{
	//�������� ����� ��� ������
	std::ifstream file(path);
	//������ ������ - ����� ������
	std::string address;

	int count_camera = 0;

	//���������� ��� ���������� ���������� � ������� ������ � ��
	//���������� ��� ���������� ���������� � ������ � �������� �������
	vcam_file* _file_cam = NULL;

	//������ ����� �����
	while (std::getline(file, address)) {

		if (address == "") continue;

		//��������, ��� �� ������� � �������� �������
		if (file_cam->SearchCamera(address) != -1) {
			//������� �������������� � ���, ��� ����� ������ ��� ��� � �������
			std::cout << "��������! ������ '" << address << "' ��� ���� � �������!\n";
			//������� � ���������� ������
			continue;
		}

		////���� ���� ����� � ��
		////�� ������� ���� ���������� ����������
		//if (_use_db) {
		//	//�������� ����� ������
		//	_db_cam = db_vcam::addNewCamera(address, "n", 7);
		//}

		////��������� ���������� �����
		//count_camera++;
		////���� �� ������� ���������� � ���� ������
		//if (_db_cam == NULL) {
		//	//���������� � ������ ����������� � ����
		//	file_cam->AddNewCamera(address);
		//} else
		//	//���� ���������� � ������ ���� � ��
		//	//�� ���������� ��������, �� 
		//{
		//	file_cam->AddNewCamera(
		//		_db_cam->GetAddress(),
		//		_db_cam->GetDescription(),
		//		//����� ������ ������� ���������� ��� ID
		//		_db_cam->GetPremise().GetId(),
		//		_db_cam->GetPosition(),
		//		_db_cam->GetId());

		//}

	}

	//���������� ���������� � �����
	file_cam->Save();
	return count_camera;
}

bool camera_information::ListCameraExist()
{
	//���� ��� ����� � ������, ������ ������ �� ����������
	if(file_cam->GetList()->size() == 0) return false;
	return true;
}

void camera_information::AddNewCamera()
{
}

void camera_information::EditCamInfo()
{
}

void camera_information::initializeDB()
{
	//�������� ������� ��� ������ � ��
}

void camera_information::initializeFile()
{
	//�������� ������� ��� ������ � �������� ��������
	file_cam = new vcam_file_manager();
}
