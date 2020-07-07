
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

//Загрузка информации из бд в файл
void DBinFile_face() {
	Condition c;

	//Создание объекта Бд
	std::list<db_employee*> *db = db_employee::GetEmployeeWithCondition(c);
	//Создание файла
	file_faces ff;
	//Подготовка к сохранению
	ff.StartSave();
	//Заполнение информации
	for (auto employee_lin = db->begin(); employee_lin != db->end(); employee_lin++) {
		db_employee *emp = *employee_lin;
		//Создание векторов для добавления информации
		std::vector<int> id_desc;
		std::vector<std::string> desc;
		//Заполнение векторов
		std::list<db_face*> *lf =  emp->GetListDescr();
		for (auto des = lf->begin(); des != lf->end(); des++) {
			db_face* face = *des;
			id_desc.push_back(face->GetId());
			desc.push_back(ToStringFloat(face->GetDescriptor()));
		}
		ff.AddFace(emp->GetId(), emp->GetInfo(), emp->GetDescrInfo(), desc, id_desc);
	}
	//Сохранение
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