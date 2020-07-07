
#pragma once
#include <Condition.h>
#include <db_employee.h>
#include <file_faces.h>

#ifdef RECOGNITIONBB_EXPORTS
#define RECOGNITIONBB_API __declspec(dllexport)
#else
#define RECOGNITIONBB_API __declspec(dllimport)
#endif


std::string  RECOGNITIONBB_API ToStringFloat(float* arr);

void RECOGNITIONBB_API DBinFile_face();

//�������� ���������� �� �� � ����
void DBinFile_face() {
	Condition c;

	//�������� ������� ��
	std::list<db_employee*> *db = db_employee::GetEmployeeWithCondition(c);
	//�������� �����
	file_faces ff;
	//���������� � ����������
	ff.StartSave();
	//���������� ����������
	for (auto employee_lin = db->begin(); employee_lin != db->end(); employee_lin++) {
		db_employee *emp = *employee_lin;
		//�������� �������� ��� ���������� ����������
		std::vector<int> id_desc;
		std::vector<std::string> desc;
		//���������� ��������
		std::list<db_face*> *lf =  emp->GetListDescr();
		for (auto des = lf->begin(); des != lf->end(); des++) {
			db_face* face = *des;
			id_desc.push_back(face->GetId());
			desc.push_back(ToStringFloat(face->GetDescriptor()));
		}
		ff.AddFace(emp->GetId(), emp->GetInfo(), emp->GetDescrInfo(), desc, id_desc);
	}
	//����������
	ff.Save();
}

std::string ToStringFloat(float* arr) {
	 std::string res = "{";
	for (int i = 0; i < 128; i++) {
		res += std::to_string(arr[i]) + ",";
	}
	res[res.size() - 1] = '}';
	return res;
}