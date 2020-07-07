#pragma once
#include <string>
#include <vector>

#ifdef FACEDETECTION_EXPORTS
#define FACEDETECTION_API __declspec(dllexport)
#else
#define FACEDETECTION_API __declspec(dllimport)
#endif


//Класс, который содержит всю информацию о камере, которая может быть в библиотеке
class FACEDETECTION_API information_camera
{
public:

	information_camera();

	//Создание камеры по пути к веб камере или файлу
	//Если не указано имя, то будет использовн путь
	//Происходит проверка, не является ли путь номером
	information_camera(std::string path, std::string window_name = "");

	//Создание камеры по пути к веб камере или файлу
	//Если не указано имя, то будет использовн путь
	information_camera(int number, std::string window_name = "");

	//Если камера создана с помощью адреса
	//То вернёться true
	bool IsWebCam();

	//Если камера USB
	//То вернёться true
	bool IsUsbCam();

	//Указать дополнительную информацию о камере
	void SetCameraInfo(int id, std::string description);

	//Получить id камеры
	int GetId();

	//Получить описание камеры
	std::string GetDescrtiption();

	//Задать имя окна вывода
	void SetName(std::string window_name);

	//Установить для камеры список помещений
	void SetPremises(std::vector<std::pair<int, std::string>> stack_premises);

	//Получить все связанные с данным помещениям помещения
	std::vector<std::pair<int, std::string>> GetPremises();

	//Название окна с видео
	std::string GetName();

	//Возвращание главной информации о камере
	information_camera GetInformationCamera();

	//Получение пути к камере
	std::string GetPath();

	//Получение номера камеры
	int GetNumber();

protected:

	//Провека, не является ли путь чистым номером
	bool CheckIsNum(std::string path);

	//Вектор со всеми помещениями, в которых находиться камера
	std::vector<std::pair<int, std::string>> _premises;

	//Идентификатор камеры в БД
	int _id_cam = -1;

	//Дополнительная информация о камере из БД
	std::string _description = "";

	//Если класс создан по пути к камере или файлу, то здесь храниться имя файла
	std::string _path = "";

	//Если класс создан по номеру усб камеры, то здесь храниться номер камеры
	int _num_cam = -1;

	//Название окна вывода видео
	std::string _name = "defName";
};

