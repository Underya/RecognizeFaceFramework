#include "Initialization.h"
#include "..//file_manager/Configuration.h"
#include "..//MessageServer/BlowfishCoder.h"
#include "questions_user.h"

#define BLOCK_SIZE 256

using namespace std;

void Initialization::Start()
{
	//Если файл пустой, то вызывается диалог инициализация
	if (ConfigEmpty()) {
		StartDialog();
	}
	else {
		//Если файл не пустой, из него необходимо получить информацию
		//Получение информации о БД
		LoadDB();
		//Получение информации об иморте
		LoadImport();
	}
}



bool Initialization::HasImport()
{
	return _import;
}

std::string Initialization::GetAdress()
{
	return _db_address;
}

std::string Initialization::GetPort()
{
	return _port;
}

std::string Initialization::GetDBName()
{
	return _db_name;
}

std::string Initialization::GetUser_Name()
{
	return _name;
}

std::string Initialization::GetPassword()
{
	return _password;
}

void Initialization::SetImportInfo()
{
	Configuration conf;
	if (_import) {
		conf.SetParametr("import", "1");
	}
	else {
		conf.SetParametr("import", "0");
	}
	conf.Save();
}

void Initialization::LoadDB()
{
	//Если нет информациии, ничего загружать не надо
	Configuration c;
	if (!c.HasParamert("has_db")) return;

	//Загрузка информации
	//Загрузка и создание БД
	ifstream file("config.info", std::ios::in | std::ios::binary);
	char* buff = new char[5000], * res = NULL;
	file.read(buff, 5000);
	//Закрытие файла
	file.close();
	//Расшифрование
	BlowfishCoder bc(64);
	//Получение длины закодированной строки
	int size = 0, newSize = 0;
	size = atoi(c.GetParametr("has_db").c_str());
	res = bc.UnCodind(buff, size, newSize);
	string fullStr;
	//Получение настроек и создание БД
	fullStr = res;
	int position = 0, strPosition = 0;
	strPosition = fullStr.find('\n', position);
	_db_address = fullStr.substr(position, strPosition);
	position = strPosition + 1;
	strPosition = fullStr.find('\n', position);
	_port = fullStr.substr(position, strPosition - position);
	position = strPosition + 1;
	strPosition = fullStr.find('\n', position);
	_db_name = fullStr.substr(position, strPosition - position);
	position = strPosition + 1;
	strPosition = fullStr.find('\n', position);
	_name = fullStr.substr(position, strPosition - position);
	position = strPosition + 1;
	strPosition = fullStr.find('\n', position);
	_password = fullStr.substr(position, strPosition - position);
}

void Initialization::LoadImport()
{
	//Если такая информаия
	Configuration c;
	if (c.HasParamert("import")) {
		if (c.GetParametr("import") == "1") {
			_import = true;
		}
		if (c.GetParametr("import") == "0") {
			_import = true;
		}
	}
}

bool Initialization::ConfigEmpty()
{
	Configuration conf;

	//Если файл пустой, он пустой
	if (conf.IsEmpty()) {
		return true;
	}

	return false;
}

void Initialization::StartDialog()
{
	questions_user qu;
	int res = qu.SendQuestInt("Выберите источник информации", { "База данных", "Импорт из файлов" });
	//Обработка ответов
	if (res == 1) {
		//Очищение экрана
		qu.ClearConsole();
		//Вызов диалога для полученияи информации о БД
		DBDialog();
	}

	if (res == 2) {
		//Указание, что испольузется импорт из файлов
		_import = true;
	}

	//При любом раскладе сохраняем информаци о том, используется ли имопрт
	SetImportInfo();
}

void Initialization::DBDialog()
{
	//Получение настроек и создание БД
	cout << "Введите информацию для подключение к БД." << endl;
	cout << "Внимание, данная информация будет храниться в зашифрованном виде." << endl;
	cout << "Введите адрес подключения" << endl << ">> ";
	cin >> _db_address;
	cout << "Введит порт подключения" << endl << ">> ";
	cin >> _port;
	cout << "Введите название базы данных" << endl << ">> ";
	cin >> _db_name;
	cout << "Введите имя пользователя" << endl << ">> ";
	cin >> _name;
	cout << "Введить пароль пользователя" << endl << ">> ";
	cin >> _password;
	system("cls");

	//Сохранение полученной информации
	SaveDBInfo();
}


void Initialization::SaveDBInfo()
{
	BlowfishCoder coder(BLOCK_SIZE);
	//Представление информации в типичном формате
	string res = _db_address + "\n" + _port + "\n" + _db_name + "\n" + _name + "\n" + _password + "\n";
	//Открыть файл для записи
	ofstream file("config.info", std::ios::out | std::ios::binary);
	//Кодирование строки
	int size = 0, newSize = 0;
	char* codingString = NULL;
	codingString = coder.Coding(res.c_str(), res.size(), newSize);
	//Запись в файл
	file.write(codingString, newSize);
	//Указание, что есть информмация о БД
	Configuration conf;
	conf.SetParametr("has_db", std::to_string(newSize));
	conf.Save();
	//Закрытие файла
	file.close();
	//Удаление буффера
	delete[newSize]codingString;
}
