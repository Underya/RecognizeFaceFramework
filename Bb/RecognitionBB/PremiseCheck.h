#pragma once
#include <mutex>
#include "IRecognitionHandler.h"
#include "../db/db_premise.h"
#include "../db/db_employee.h"

class RECOGNITIONBB_API PremiseCheck :
	public IRecognitionHandler
{
public:

	PremiseCheck();

	//�����, ������� ���������� �����������
	//���� �������� ��� ���������� � ���������
	virtual void HandlerFace(int cam_id, std::vector<std::string> premise_name, face face, list_rules rules, list_group group, information_camera camera_info);

	//���������� ���������� ������ ������, ��������� � �������
	virtual void SetRulesList(list_rules listRules);

	//�������� ���������� � ���, ��� ��� ���������
	void EmployeeRecognitImPremise(face employee, std::string premise);
	
	void SetCurrIdCam(int id_cam);

	virtual void SetPremisesList(std::vector<std::string> listPremise) override;

	//��������� ������� ��� � ��������� �������:
	//�������� ���������, ��� ����������
	static std::vector<std::pair<std::string, std::vector<std::string>>> GetPremiseEmplyee();

	//�������� ������ ��� � �������:
	//��� ����������, �������� ���������
	static std::vector<std::pair<db_employee, std::string>> GetEmployeePremise();

protected:

	//id ������, ��� ������� ������ ����������� ���������
	int _last_id_cam = -1;

	static std::string GetNameEmp(int id);

	//��� ��������� ���� �����, ��� ������� ���������� ��������������
	static std::map<int, std::vector<std::string>> _all_camera_premise;

	//��������� id ��������� �� �����. ���� ������ ��������� ���
	//�� ������������ -1
	int SearchPremise(std::string premise_name);

	void CheckEmployee(face f);

	//���������� ������ ���������
	int AddPremise(std::string premise_name);

	//������ id �����������
	static std::vector<int> _id_employee;

	//��������� ���������, � ������� �� ����� ��������� ���������
	int GetIdOldPremise(int id_employee);

	void DeleteEmployeeInPremise(int id_premise, int id_employee);

	//������ ��� �����������
	static std::vector <std::pair <int, std::string>> _name_employee;

	//�������, ��� ��������� ��������� � ����� ���������
	void AddEmployeeInPremise(int id_employee, int id_premise);

	//������������� ������ �������� ���������
	static std::vector<std::string> _name_premise;

	//��������, ��� ��������� ��������� � ���� ���������
	static std::map<int, int> _employee_in_premise;

	//������ ����� � ����������
	static std::map<int, std::list<int>> _list_employee_in_premise;

	static std::mutex* _my_mutex;
};

