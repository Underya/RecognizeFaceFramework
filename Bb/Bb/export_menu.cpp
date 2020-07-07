#include "export_menu.h"
//Группы
#include "../db/db_group.h"
#include "..//file_manager/file_group.h"
//Пользователи
#include "..//db///db_employee.h"
#include "..//file_manager/file_faces.h"
//Камеры
#include "..//db/db_vcam.h"
#include "..//file_manager/vcam_file_manager.h"
//Помещения
#include "..//db/db_premise.h"
#include "..///file_manager/file_premise.h"
//Правила
#include "..//db/rules_collection.h"
#include "..//file_manager/rule_link.h"
#include "..//file_manager/file_rule.h"

using std::vector;
using std::pair;
using std::string;
using std::list;
using std::cout;

void export_menu::Export(db_user* user)
{
	//Сохранение информации
	_user = user;
	
	//Вывод информации
	questions_user qu;
	qu.ClearConsole();
	
	cout << "Экспорт начат;\n";
	try {
		//Очищение информации о файлах
		Clear_Info();

		//Экспорт пользоватлей
		Export_employee();
		cout << "Экспортированы группы;\n";
		//Экспорт групп
		Export_group();
		cout << "Экспортированы сотрудники и лица;\n";
		//Экспорт камер
		Export_camera();
		cout << "Экспортированы камеры;\n";
		//Экспорт помещений
		Export_premise();
		cout << "Экспортированы помещения;\n";
		//Экспорт правил
		Export_rules();
		cout << "Экспортированны правила;\n";

		qu.WaitPressSay();
	}
	catch (...) {
		cout << "Произошла неизвестная ошибка!";
	}
}

void export_menu::Export_employee()
{
	//Загрузка всех групп
	db_group::LoadedAllGroup(_user->GetId());
	//Загрузка всех связанных пользоватлей
	vector<db_employee>* vector_emp = db_employee::GetEmployeeWithCondition(db_group::GetAllGroup());
	
	file_faces ff;

	//Загрузка всей информации
	for (auto iter = vector_emp->begin(); iter != vector_emp->end(); iter++) {

		//Вектор векторов
		list<db_face> vector_face = iter->GetListDescr();
		//Вектора с id и характеристическми векторами
		vector<string> vec_desc;
		vector<int> vec_id;
		for (auto desc = vector_face.begin(); desc != vector_face.end(); desc++) {
			vec_desc.push_back(Transform_vector_to_string(desc->GetDescriptor()));
			vec_id.push_back(desc->GetId());
		}


		ff.AddFace(iter->GetId(), iter->GetFirstName(), iter->GetLastName(), iter->GetMidleName(), iter->GetDescrInfo(), vec_desc, vec_id, iter->GetOtherId());
	}
	//Сохранение информации с векторами
	ff.Save();
}

void export_menu::Export_group()
{
	file_group fg;
	//Загрузка групп
	db_group::LoadedAllGroup(_user->GetId());
	//Получение их всех
	vector<db_group> vector_group = db_group::GetAllGroup();

	//Сохранение всех групп в файле
	for (auto iter = vector_group.begin(); iter != vector_group.end(); iter++) {
		fg.AddNewGroup(iter->GetName(), iter->GetDesc(), iter->GetId());

		//Для каждой группы происходит поиск всех сотрудников
		vector<db_employee> *vec_emp = db_employee::GetEmployeeWithCondition(*iter);

		//Сохранение связей с сотрудниками
		for (auto employee = vec_emp->begin(); employee != vec_emp->end(); employee++) {
			fg.AddNewSnap(iter->GetId(), employee->GetId());
		}
	}
	//Сохранение информации
	fg.Save();

}

void export_menu::Export_camera()
{
	//Загрузка всех камер
	vector<db_vcam> vector_camera = db_vcam::GetAllLinkVcam(*_user);
	//Класс для сохранения информации о камер
	vcam_file_manager vfm;

	//Сохранение информации
	for (auto iter = vector_camera.begin(); iter != vector_camera.end(); iter++) {
		vfm.AddNewCamera(iter->GetAddress(), iter->GetDescription(), iter->GetPremise().GetId(), iter->GetPosition(), iter->GetId());
	}

	vfm.Save();
}

void export_menu::Export_premise()
{
	//Создание файла для сохранения помещений
	file_premise fp;

	//Помещения связаны с пользователем через камеры
	vector<db_vcam> vector_camera = db_vcam::GetAllLinkVcam(*_user);

	//Для каждой камер происходит проверка, есть ли помещения
	for (auto camera = vector_camera.begin(); camera != vector_camera.end(); camera++) {
		//Если у камеры нет помещения - пропустить
		if (camera->GetPremise().GetId() == -1) continue;

		//Если есть помещение, то о нём добавляется информация
		db_premise premise = camera->GetPremise();
		fp.AddNewPremise(premise.GetName(), premise.GetDesc(), premise.GetId(), premise.GetIdParent());
		
		vector<db_premise> vec_premise = premise.GetAllParent();
		//Добавление предков
		for (auto premise = vec_premise.begin(); premise != vec_premise.end(); premise++) {
			fp.AddNewPremise(premise->GetName(), premise->GetDesc(), premise->GetId(), premise->GetIdParent());
		}
	}

	fp.Save();
}

void export_menu::Export_rules()
{
	file_rule fr;
	rule_link rl;
	rules_collection rc;

	//Получение всех камер
	vector<db_vcam> vector_camera = db_vcam::GetAllLinkVcam(*_user);

	//Разбор всей информации
	for (auto camera = vector_camera.begin(); camera != vector_camera.end(); camera++) {
		//Инициализация пустым списком
		rc = rules_collection();
		//Получение всей информации, связанной только с камерой
		rc.AppendRule(*camera);

		//Добавление правил и информации о них
		list<db_rule> list_rule = rc.GetAllRuleFull();
		for (auto rule = list_rule.begin(); rule != list_rule.end(); rule++) {

			//Если такого правила не было
			if (!fr.CheckRuleExist(rule->GetId())) {
				//То его необходимо добавить
				fr.AddRule(rule->GetName(), rule->GetDesc(), rule->GetId());
			}

			//Добавление связи
			rl.AddCameraLink(camera->GetId(), rule->GetId());
		}

		//Получение всех помещений, связанных с данной камерой
		vector<db_premise> list_premise = camera->GetPremise().GetAllParent();
		//Добавление самого помещения
		list_premise.push_back(camera->GetPremise());

		//Для каждого помещения добавляются правила и связь с самим помещением
		for (auto premise = list_premise.begin(); premise != list_premise.end(); premise++) {
			//Удаление информации обо всех предыдущих правилах
			rc = rules_collection();
			//Получение правил, связанных с данным помещением
			rc.AppendRuleForOnePremmis(*premise);

			//Получение списка
			list<db_rule> list_rule_prem = rc.GetAllRuleFull();
			for (auto rule = list_rule_prem.begin(); rule != list_rule_prem.end(); rule++) {
				//Если нет такого правила, то оно добавляется
				if (!fr.CheckRuleExist(rule->GetId())) {
					fr.AddRule(rule->GetName(), rule->GetDesc(), rule->GetId());
				}

				//Создание связи
				rl.AddPremiseLink(premise->GetId(), rule->GetId());
			}

		}

		//Сохранение информации о правилах
		rl.Save();
		//И о связях
		fr.Save();
	}
}

void export_menu::Clear_Info()
{
	file_faces ff;
	ff.ClearFile();
	ff.Save();
	file_rule fr;
	fr.ClearFile();
	fr.Save();
	file_group fg;
	fg.ClearFile();
	fg.Save();
	vcam_file_manager vfm;
	vfm.ClearFile();
	vfm.Save();
	file_premise fp;
	fp.ClearFile();
	fp.Save();
}

std::string export_menu::Transform_vector_to_string(float* desc)
{
	string sdesc = "";

	for (int i = 0; i < 128; i++) {
		sdesc += std::to_string(desc[i]) + " ";
	}

	return sdesc;
}
