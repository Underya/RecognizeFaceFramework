#pragma once
#include <string>
#include <vector>

#ifdef FACEDETECTION_EXPORTS
#define FACEDETECTION_API __declspec(dllexport)
#else
#define FACEDETECTION_API __declspec(dllimport)
#endif


//�����, ������� �������� ��� ���������� � ������, ������� ����� ���� � ����������
class FACEDETECTION_API information_camera
{
public:

	information_camera();

	//�������� ������ �� ���� � ��� ������ ��� �����
	//���� �� ������� ���, �� ����� ���������� ����
	//���������� ��������, �� �������� �� ���� �������
	information_camera(std::string path, std::string window_name = "");

	//�������� ������ �� ���� � ��� ������ ��� �����
	//���� �� ������� ���, �� ����� ���������� ����
	information_camera(int number, std::string window_name = "");

	//���� ������ ������� � ������� ������
	//�� �������� true
	bool IsWebCam();

	//���� ������ USB
	//�� �������� true
	bool IsUsbCam();

	//������� �������������� ���������� � ������
	void SetCameraInfo(int id, std::string description);

	//�������� id ������
	int GetId();

	//�������� �������� ������
	std::string GetDescrtiption();

	//������ ��� ���� ������
	void SetName(std::string window_name);

	//���������� ��� ������ ������ ���������
	void SetPremises(std::vector<std::pair<int, std::string>> stack_premises);

	//�������� ��� ��������� � ������ ���������� ���������
	std::vector<std::pair<int, std::string>> GetPremises();

	//�������� ���� � �����
	std::string GetName();

	//����������� ������� ���������� � ������
	information_camera GetInformationCamera();

	//��������� ���� � ������
	std::string GetPath();

	//��������� ������ ������
	int GetNumber();

protected:

	//�������, �� �������� �� ���� ������ �������
	bool CheckIsNum(std::string path);

	//������ �� ����� �����������, � ������� ���������� ������
	std::vector<std::pair<int, std::string>> _premises;

	//������������� ������ � ��
	int _id_cam = -1;

	//�������������� ���������� � ������ �� ��
	std::string _description = "";

	//���� ����� ������ �� ���� � ������ ��� �����, �� ����� ��������� ��� �����
	std::string _path = "";

	//���� ����� ������ �� ������ ��� ������, �� ����� ��������� ����� ������
	int _num_cam = -1;

	//�������� ���� ������ �����
	std::string _name = "defName";
};

