
#pragma once
#include <file_faces.h>
#include <db_employee.h>


#ifdef RECOGNITIONBB_EXPORTS
#define RECOGNITIONBB_API __declspec(dllexport)
#else
#define RECOGNITIONBB_API __declspec(dllimport)
#endif


RECOGNITIONBB_API float* GetFloatRes(std::string s);
RECOGNITIONBB_API void LoadToDBWithFile();

//�������� ���� �������� �� �������� ������� � ���� ������
void LoadToDBWithFile() {
	file_faces ff;
	std::list<face_info> fi = ff.GetFaceInfo();
	int i = 0;

	//���� �� ���� �������� �����
	for (auto iter = fi.begin(), end = fi.end(); iter != end; iter++) {
		try {
			i++;
			//�������� �����������
			std::string s = (*iter).name;
			db_employee* new_emp = db_employee::AddNewEmployee(s);
			//��� ������� ���������� ����������� ����
			for (auto iter2 = iter->desc.begin(), end2 = iter->desc.end(); iter2 != end2; iter2++) {
				new_emp->AddNewDescriptor(GetFloatRes(*iter2));
			}
			delete new_emp;
		}
		catch (...) {

		}
	}


}

//������� �� ������ � ��� float
float* GetFloatRes(std::string s) {
	float* res = new float[128]();
	int iarr = 0;
	int is = 0;
	int ibuff = 0;
	char buff[50];
	//���� �� ���� ��������
	for (; iarr < 128; iarr++) {
		ibuff = 0;
		while (s[is] != ' ' && is < s.size()) {
			buff[ibuff++] = s[is++];
		}
		buff[ibuff] = 0;
		res[iarr] = atof(buff);
		is++;
	}

	return res;
}
