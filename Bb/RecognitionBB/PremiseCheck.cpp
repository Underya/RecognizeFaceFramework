#include "PremiseCheck.h"

std::mutex* PremiseCheck::_my_mutex = NULL;

 std::map<int, std::vector<std::string>> PremiseCheck::_all_camera_premise;

std::vector<int> PremiseCheck::_id_employee;

std::vector<std::pair<int,std::string>> PremiseCheck::_name_employee;

std::vector<std::string> PremiseCheck::_name_premise;

std::map<int, int> PremiseCheck::_employee_in_premise;

std::map<int, std::list<int>> PremiseCheck::_list_employee_in_premise;


PremiseCheck::PremiseCheck()
{
	_my_mutex = new std::mutex();
}

void PremiseCheck::HandlerFace(int cam_id, std::vector<std::string> premise_name, face face, list_rules rules, list_group group, information_camera camera_info)
{
	//���� ������ �� ��� ��������� � ��������
	if(_all_camera_premise[cam_id].size() > 0)
		EmployeeRecognitImPremise(face, _all_camera_premise[cam_id].front());
}

void PremiseCheck::SetRulesList(list_rules listRules)
{
	_listRules = listRules;
}

void PremiseCheck::EmployeeRecognitImPremise(face employee, std::string premise)
{
	//��������� �� ����������
	int id_employee = employee.GetId();
	//��������� �� ���������
	int id_premise = SearchPremise(premise);
	
	//���� �� ���� ������ ���������, �� ��� ���������� ��������
	if (id_premise == -1) {
		id_premise = AddPremise(premise);
	}

	//��������, ��� �� ���������
	CheckEmployee(employee);

	//��������� id ���������, ��� �� ����� ��� ��������� ���������
	int old_id_premise = GetIdOldPremise(id_employee);
	
	//���� �� ����� �� ��� � ��������, ���������� ������� ��� �� ������� ������ ����
	if (old_id_premise != -1) {
		DeleteEmployeeInPremise(old_id_premise, id_employee);
	}

	//���������� �������� � ����� ���������
	AddEmployeeInPremise(id_employee, id_premise);

}

void PremiseCheck::SetCurrIdCam(int id_cam)
{
	_last_id_cam = id_cam;
}


void PremiseCheck::SetPremisesList(std::vector<std::string> listPremise)
{
	//���������� ���� ��������
	_all_camera_premise[_last_id_cam] = listPremise;
}

std::vector<std::pair<std::string, std::vector<std::string>>> PremiseCheck::GetPremiseEmplyee()
{
	std::vector<std::pair<std::string, std::vector<std::string>>> list;
	//��� ������� ��������� 
	for (auto iter = _list_employee_in_premise.begin(); iter != _list_employee_in_premise.end(); iter++) {
		//��������� �����
		std::string premise_name = "";
		premise_name = _name_premise[iter->first];
		//���������� ��� ���� �����������
		std::vector<std::string> _emp_name;
		std::list<int> temp = iter->second;
		for (auto id_e = temp.begin(); id_e != temp.end(); id_e++) {
			std::string t;
			t = GetNameEmp(*id_e);
			_emp_name.push_back(t);
		}
		//���������� �� ���� ������
		std::pair<std::string, std::vector<std::string>> pair;
		pair.first = premise_name;
		pair.second = _emp_name;

		list.push_back(pair);
	}

	return list;
}

std::vector<std::pair<db_employee, std::string>> PremiseCheck::GetEmployeePremise()
{
	//�������� ������ 
	std::vector<std::pair<db_employee, std::string>> vec;
	
	//������ ���� �����������
	for (auto iter = _id_employee.begin(); iter != _id_employee.end(); iter++) {
		//���� �� ������ - �������
		if (*iter == -1) continue;
		db_employee emp(*iter);
		//��������� ��������� ��� ����������
		int _id_premise_in_array = _employee_in_premise[emp.GetId()];
		//��������� ����������� �����
		string name_premise = _name_premise[_id_premise_in_array];
		//��������� �� �� ������ ���������

		vec.push_back({ emp, name_premise });
	}

	return vec;
}

std::string PremiseCheck::GetNameEmp(int id)
{
	for (auto iter = _name_employee.begin(); iter != _name_employee.end(); iter++) {
		if (iter->first == id)
			return iter->second;
	}
	return std::string();
}

int PremiseCheck::SearchPremise(std::string premise_name)
{
	for (int i = 0; i < _name_premise.size(); i++) {
		if (_name_premise[i] == premise_name) {
			//������� ��������� � ������
			return i;
		}
	}
	//���� ��� � ������, ������ -1
	return -1;
}

void PremiseCheck::CheckEmployee(face f)
{
	//���������� ��
	bool in_vec = false;
	_my_mutex->lock();
	for (auto iter = _id_employee.begin(); iter != _id_employee.end(); iter++) {
		if (*iter == f.GetId()) {
			in_vec = true;
			break;
		}
	}
	//���� ��� � ������
	if (!in_vec) {
		_id_employee.push_back(f.GetId());
	}
	_my_mutex->unlock();
	//���� ���� � ������
	for (auto iter = _name_employee.begin(); iter != _name_employee.end(); iter++) {
		if (iter->first == f.GetId())
			return;
	}
	//�����, ��������
	_name_employee.push_back({ f.GetId(), f.GetFirstName() + " " + f.GetLastName() + " " + f.GetMidName() });
}

int PremiseCheck::AddPremise(std::string premise_name)
{
	_my_mutex->lock();
	int ret_id = -1;
	_name_premise.push_back(premise_name);
	ret_id = _name_premise.size() - 1;
	_my_mutex->unlock();
	return ret_id;
}

int PremiseCheck::GetIdOldPremise(int id_employee)
{
	//��������, ���� �� ������ ������ � ����� ����������
	if (_employee_in_premise.count(id_employee) == 0) return -1;
	return _employee_in_premise[id_employee];
}

void PremiseCheck::DeleteEmployeeInPremise(int id_premise, int id_employee)
{
	_my_mutex->lock();
	//��������� ������
	std::list<int> list_employee = _list_employee_in_premise[id_premise];
	//�������� �������� �� ������
	list_employee.remove(id_employee);
	//������ �������� � ������
	_list_employee_in_premise[id_premise] = list_employee;

	_my_mutex->unlock();

}

void PremiseCheck::AddEmployeeInPremise(int id_employee, int id_premise)
{
	_my_mutex->lock();

	//std::cout << "id_emp:" << id_employee << " id_premise:" << id_premise << "\n";
	//��������, ��� ������ ��������� ��������� � ���� ���������
	_employee_in_premise[id_employee] = id_premise;
	std::list<int> list_employee = _list_employee_in_premise[id_premise];
	//�������� �������� �� ������
	list_employee.push_back(id_employee);
	//������ �������� � ������
	_list_employee_in_premise[id_premise] = list_employee;

	_my_mutex->unlock();
}
