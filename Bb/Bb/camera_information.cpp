#include "camera_information.h"

using namespace std;

camera_information::camera_information(bool use_db)
{
	_use_db = use_db;
	//Если можно, то создаётся соеденение с БД
	if (_use_db)
		initializeDB();
	//Инициализация файловый системы
	initializeFile();
}

camera_information::~camera_information()
{
}

void camera_information::InitialInfoFile(string path)
{
	//Открытие файла для чтения
	std::ifstream file(path);
	//Каждая строка - адрес камеры
	std::string address;

	//Переменная для сохранения информации о текущей камере в БД
	db_vcam _db_cam = NULL;

	//Если не удалось открыть файл
	if (!file.is_open()) throw new exception();

	//Чтение всего файла
	while (std::getline(file, address)) {

		if (address == "") continue;

		//Попытка понять, есть ли уже информация о камерах в БД
		if (_use_db) {
			//Создаётся новая запись
			_db_cam = db_vcam::addNewCamera(address, "n", 7, 1);
			
		}

		////Если есть работа с файловой системой
		////Если не найдена информация в базе данных
		//if (_db_cam == NULL) {
		//	//Информация о камере сохраняется в файл
		//	file_cam->AddNewCamera(address);
		//} else
		//	//Если информация о камере была в БД
		//	//То она дублируется в файл
		//{
		//	file_cam->AddNewCamera(
		//		_db_cam->GetAddress(),
		//		_db_cam->GetDescription(),
		//		//Через объект позиции получается его ID
		//		_db_cam->GetPremise().GetId(),
		//		_db_cam->GetPosition(),
		//		_db_cam->GetId());

		//}
		
	}
	
	//Сохранения информации о камерах в файловой системе
	file_cam->Save();
}



int camera_information::UpdateToFile(string path)
{
	//Открытие файла для чтения
	std::ifstream file(path);
	//Каждая строка - адрес камеры
	std::string address;

	int count_camera = 0;

	//Переменная для сохранения информации о текущей камере в БД
	//Переменная для сохранения информации о камере в файловой системе
	vcam_file* _file_cam = NULL;

	//Чтение всего файла
	while (std::getline(file, address)) {

		if (address == "") continue;

		//Проверка, нет ли камерый в файловой системе
		if (file_cam->SearchCamera(address) != -1) {
			//Вывести предупреждение о том, что такая камера уже ест в системе
			std::cout << "Внимание! Камера '" << address << "' Уже есть в системе!\n";
			//Перейти к следующему адресу
			continue;
		}

		////Если есть связь с БД
		////То сначала туда происходит добавление
		//if (_use_db) {
		//	//Создаётся новая запись
		//	_db_cam = db_vcam::addNewCamera(address, "n", 7);
		//}

		////Увеличить количество камер
		//count_camera++;
		////Если не найдена информация в базе данных
		//if (_db_cam == NULL) {
		//	//Информация о камере сохраняется в файл
		//	file_cam->AddNewCamera(address);
		//} else
		//	//Если информация о камере была в БД
		//	//То происходит проверка, не 
		//{
		//	file_cam->AddNewCamera(
		//		_db_cam->GetAddress(),
		//		_db_cam->GetDescription(),
		//		//Через объект позиции получается его ID
		//		_db_cam->GetPremise().GetId(),
		//		_db_cam->GetPosition(),
		//		_db_cam->GetId());

		//}

	}

	//Сохранение информации в файле
	file_cam->Save();
	return count_camera;
}

bool camera_information::ListCameraExist()
{
	//Если нет камер в списке, значит списка не существует
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
	//Создание объекта для работа с БД
}

void camera_information::initializeFile()
{
	//Создание объекта для работы с файловой системой
	file_cam = new vcam_file_manager();
}
