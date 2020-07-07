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

	//Метод, который необходимо перегрузить
	//Сюда приходит вся информация о посещении
	virtual void HandlerFace(int cam_id, std::vector<std::string> premise_name, face face, list_rules rules, list_group group, information_camera camera_info);

	//Необходимо установить список правил, связанных с камерой
	virtual void SetRulesList(list_rules listRules);

	//Изменить информации о том, где был сотрудник
	void EmployeeRecognitImPremise(face employee, std::string premise);
	
	void SetCurrIdCam(int id_cam);

	virtual void SetPremisesList(std::vector<std::string> listPremise) override;

	//Получение вектора пар в следующей формате:
	//Название помешения, имя сотрудника
	static std::vector<std::pair<std::string, std::vector<std::string>>> GetPremiseEmplyee();

	//Получить вектор пар в формате:
	//Имя сотрудника, название помещения
	static std::vector<std::pair<db_employee, std::string>> GetEmployeePremise();

protected:

	//id камеры, для которой сейчас добавляются помещения
	int _last_id_cam = -1;

	static std::string GetNameEmp(int id);

	//Все помещения всех камер, для данного экземпляра распознавателя
	static std::map<int, std::vector<std::string>> _all_camera_premise;

	//Получение id помещения по имени. Если такого помещения нет
	//То возвращается -1
	int SearchPremise(std::string premise_name);

	void CheckEmployee(face f);

	//Добавление нового помещения
	int AddPremise(std::string premise_name);

	//Список id сотрудников
	static std::vector<int> _id_employee;

	//Получение помещения, в котором до этого находился сотрудник
	int GetIdOldPremise(int id_employee);

	void DeleteEmployeeInPremise(int id_premise, int id_employee);

	//Список имён сотрудников
	static std::vector <std::pair <int, std::string>> _name_employee;

	//Указние, что сотрудник находится в новом помещении
	void AddEmployeeInPremise(int id_employee, int id_premise);

	//Ассоциативный массив название помещений
	static std::vector<std::string> _name_premise;

	//Указание, что сотрудник находится в этом помещении
	static std::map<int, int> _employee_in_premise;

	//Список людей в помещениях
	static std::map<int, std::list<int>> _list_employee_in_premise;

	static std::mutex* _my_mutex;
};

