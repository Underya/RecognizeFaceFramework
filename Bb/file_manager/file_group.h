#pragma once
#include "file_parametr.h"
#include <vector>
#include <map>


//Управление файлом групп, к которым приписываются сотрудник
class FILEMANAGER_API file_group :
	public file_parametr
{
public:

	//Использовать файл для хранения информации с указанным имененм
	file_group(std::string file_name);

	//Создать объект и связать его с файлом со стандартным имененм
	file_group();

	~file_group();

	//Получение ID всех групп в файле
	std::vector<int> GetAllId();

	//Получение ID всех сотрудников, связанных с переданной группой
	std::vector<int> GetEmployeeId(int id_group);

	//Получение всех идентификаторов группы по id сотрудника
	std::vector<int> GetGroupFromId(int id_employee);

	//Получить имя указанной группы
	std::string GetName(int id_group);

	//Получить описание указанной группы
	std::string GetDesc(int id_group);

	//Добавление новой группы в список
	int AddNewGroup(std::string group_name, std::string group_desc, int id = -1);

	//Добавление новой связи
	void AddNewSnap(int id_group, int id_employee);

	//Удалить связь между группой и сотрудником	
	void DeleteSnap(int id_group, int id_employee);

	//Редактировать информацию о группе
	void EditGroupInfo(int id, std::string new_name, std::string new_desc);

private:

	//Ассоциативный массив, где ключём является id группы
	//А его значением - вектор связанных с ним сотрудников
	std::map<int, std::vector<int>> groups_info;
	//Ассоциативный массив названий групп
	std::map<int, std::string> groups_desc;
	//Ассоциативный массив описаний групп
	std::map<int, std::string> groups_names;

	//Чтение и получение информации из файла
	void ParseFile();

	std::string GetContentList() override;

};

//Формат файла
//group
//id:value;
//name:value;
//desc:value;
//employe:-;
//id_employe0
//id_employe1
//id_employe2
//....
//id_employeN
//end

//id_employe - может не быть