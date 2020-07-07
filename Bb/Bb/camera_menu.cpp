#include "camera_menu.h"
#include "questions_user.h"

using std::cout;
using std::cin;

void camera_menu::Switch(db_user* user)
{
	//Сохранение информации о пользователе
	_user = user;

	questions_user q;

	//Цикл для работы в нём

	try {
		while (true) {
			q.ClearConsole();
			//Вывод информации о камерах
			ShowInformation();

			//Выввод возможных действий
			int res = q.SendQuestInt("Выберите действие", { "Добавить новую", "Изменить", "Удалить", "Выход" });

			res = ParseAnswer(res);

			//Если вернулось -1, то конец цикла
			if (res == -1)
				break;
		}
	}
	catch (...) {
		cout << "Произошла неизвестная ошибка!";
	}
}


void camera_menu::ShowOneCamera(db_vcam cam)
{
	cout << "id:" << cam.GetId() << " адрес:" << cam.GetAddress() << "\n";
	cout << "      помещение:" << cam.GetPremise().GetName() << " позиция: " << cam.GetPosition() << "\n";
	if (cam.GetDescription() != "") {
		cout << "      описание:" << cam.GetDescription() << "\n";
	}
	cout << "-------------------------------------------------------\n\n";
}


void camera_menu::AddNewCamera()
{
	questions_user q;
	string address;
	string position;
	string description;
	//Запрос у пользователя информации
	int id_premise;
	address = q.GetParametr("Адрес камеры");
	cout << "Позиция камеры: i - на входе, o - на выходе, n - не указано\n";
	position = q.GetParametr("Позиция камеры");
	id_premise = atoi(q.GetParametr("id помещения или -1").c_str());
	description = q.GetParametr("Описание камеры:");

	try {
		db_vcam::addNewCamera(address, position, _user->GetId(), id_premise);
	}
	catch (...) {
		cout << "Ошибка! не удалось добавить камеру!\n";
		q.WaitPressSay();
		return;
	}
	cout << "Камера успешно добавлена!\n";
	q.WaitPressSay();
}

void camera_menu::EditCameraInfo()
{
	questions_user q;
	q.ClearConsole();

	ShowInformation();

	cout << "Введити id камеры, которую надо изменить:";
	
	int id = SelectCamera();

	db_vcam cam(id);

	q.ClearConsole();
	
	//Вывод информации о камере, которая меняется
	ShowOneCamera(cam);

	string address;
	string position;
	string description;
	//Запрос у пользователя информации
	int id_premise;
	address = q.GetParametr("Новый адрес камеры");
	cout << "Позиция камеры: i - на входе, o - на выходе, n - не указано\n";
	position = q.GetParametr("Позиция камеры");
	id_premise = atoi(q.GetParametr("id помещения или -1").c_str());
	description = q.GetParametr("Описание камеры:");

	try {
		cam.SetAddress(address);
		cam.SetPosition(position);
		cam.SetDescription(description);
		cam.SetPremise(id_premise);
	}
	catch (...) {
		cout << "Не удалось изменить информаию о камере!\n";
		q.WaitPressSay();
		return;
	}

	cout << "Информация о камере успешно изменена\n";
	q.WaitPressSay();
	return;
}

void camera_menu::DeletCamera()
{
	questions_user q;
	q.ClearConsole();

	ShowInformation();

	cout << "Введити id камеры, которую надо удалить:";
	int id = SelectCamera();

	db_vcam cam(id);
	cam.Delete();

	cout << "Информация о камере была успешно удалена!\n";
	q.WaitPressSay();
}

int camera_menu::ParseAnswer(int number)
{
	//Добавление новой камеры
	if (number == 1) {
		AddNewCamera();
	}

	if (number == 2) {
		EditCameraInfo();
	}

	if (number == 3) {
		DeletCamera();
	}

	//Выход
	if (number == 4)
		return -1;
}

int camera_menu::SelectCamera()
{
	int id = -1;
	while (true)
	{
		string sid;
		cin >> sid;
		id = atoi(sid.c_str());
		//Проверка, есть ли камера с таким id
		try {
			db_vcam check(id);
		}
		catch (...) {
			cout << "Не удалось выбрать камеру с таким id!\n";
			cout << "Введите id камеры:";
			continue;
		}

		break;
	}
	return id;
}

void camera_menu::ShowInformation()
{
	//Получение всей информации о камерах
	std::vector<db_vcam> camers = db_vcam::GetAllLinkVcam(*_user);
	//Вывод информации о камерах
	for (auto iter = camers.begin(); iter != camers.end(); iter++) {
		ShowOneCamera(*iter);
	}
	
}
