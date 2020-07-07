
#include "pch.h"
#include "file_parametr.h"
using namespace std;

void file_parametr::Save()
{
    CloseFile();
    OpenFileForWrite();
    string content = GetContentList();
    _wFile->clear();
    *_wFile << content;
    CloseFile();
}

void file_parametr::ShowInfo()
{
    cout << GetContentList();
}

file_parametr::file_parametr(string fileName)
{
    this->_fileName = fileName;
    //Проверка, существует ли файл
    if (!CheckFileExist()) {
        //cout << "File " << fileName << "not exist. Creature new file\n";
        CreateNewFile();
    }
    
}

file_parametr::~file_parametr()
{
    CloseFile();
}

void FILEMANAGER_API file_parametr::ClearFile()
{
    OpenFileForWrite();
    _wFile->clear();
    CloseFile();
}

bool file_parametr::HasIdInVec(std::vector<int> _vector, int id)
{
	for (auto iter = _vector.begin(); iter != _vector.end(); iter++) {
		if (*iter == id) return true;
	}
	return false;
}

void file_parametr::GetValueForString(string str, string& nameParam, string& valueParam)
{
    //Проверка, правильно ли сформирована строка
    //Она должна оканчиваться символов ; и содержать символ :
    if (str[str.size() - 1] != ';' || str.find(':', 0) == -1) throw new exception("Error! str not corrected!\n");
    //Получение названия параметра
    int indexDT = str.find(':', 0);
    nameParam = str.substr(0, indexDT);
    //Получение значения параметра
    valueParam = str.substr(indexDT + 1, str.size() - nameParam.size() - 2);
}

void file_parametr::CloseFile()
{
    //Если файл открыт одним из способов - закрыть его
    if (_rFile != NULL) {
        _rFile->close();
        delete _rFile;
        _rFile = NULL;
    }

    if (_wFile != NULL) {
        _wFile->close();
        delete _wFile;
        _wFile = NULL;
    }
}

void file_parametr::OpenFileForRead()
{
    _rFile = new ifstream(_fileName);
}

void file_parametr::OpenFileForWrite()
{
    //Открытие файла
    _wFile = new ofstream(_fileName);
}

std::string file_parametr::GetContentList()
{
	return "";
}

void file_parametr::CreateNewFile()
{
    FILE* newFile = NULL;
    try {
        fopen_s(&newFile, (_fileName).c_str(), "w");
        if (newFile == NULL) throw new exception;
        fclose(newFile);
    }
    catch (exception err) {
        cout << "ERROR! Not create new file" << "\n";
        cout << "LOCATION: file_parametr\CreateNewFile" << "\n";
        cout << err.what() << "\n";
    }
}

int file_parametr::GetNewId()
{
	return ++id_not_db;
}

void file_parametr::SetLastUsId(int outer_id)
{
    id_not_db = outer_id;
}

bool file_parametr::CheckFileExist()
{
    //Вызывается по умолчанию в конструкторах
    OpenFileForRead();

    if (_rFile->is_open()) {
        CloseFile();
        return true;
    }
    else {
        CloseFile();
        return false;
    }

    return false;
}
 
