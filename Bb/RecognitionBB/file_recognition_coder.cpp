#include "file_recognition_coder.h"

file_recognition_coder::file_recognition_coder(std::string fileName, int sizeBuff) : file_recognition_result(fileName, NULL, NULL, sizeBuff)
{
	OpenHashFile();
	ReadFileInfo(fileName);
}

file_recognition_coder::~file_recognition_coder()
{
	SaveBuffToFile();
}

void file_recognition_coder::OpenHashFile()
{
	//Попытка откртия хеш файла
	std::ifstream file(_fileName + "hash");
	if (!file.is_open()) {
		std::ofstream newf(_fileName + "hash");
		newf.close();
	}
	else {
		file.close();
	}
}

int file_recognition_coder::GetId(std::string& line)
{
	std::string nameParam, valueParam;
	//Получение id
	GetValueForString(line, nameParam, valueParam);
	//Если текущий параметр - хеш и его размер, необходимо проверить целостность данных
	if (nameParam == "hash") {
		//То вызывается функция проверки хеша
		CheckHash(atoi(valueParam.c_str()));
		//Взятие следующей строки с Id
		if (!std::getline(*_rFile, line)) {
			//Если нет следующей строки, то вернуть -123
			return -123;
		}
		GetValueForString(line, nameParam, valueParam);
	}
	else {
		//Увеличение количества записей без хеша
		_countBlock++;
	}
	if (nameParam != "id") ThrowFileReadException("faces.text");
	return atoi(valueParam.c_str());
}

void file_recognition_coder::CheckHash(int sizeBuffer)
{
	//Чтения из файла в буффер указанного размера
	char* buffer = new char[sizeBuffer]();

	//Чтение из файла c хешом
	_inputFile.read(buffer, sizeBuffer);
	//Декодирование
	int sizeOriginalBuffer = 0;
	char* resBuff = _coder.UnCodind(buffer, sizeBuffer, sizeOriginalBuffer);
	//Сравнение
	bool HasResult = EqualHashPart(resBuff);

	//Если не вышло
	if (!HasResult) throw std::exception("Recognition file hash does not match content! The file is compromised!");

	//Очищение внутреннего буффера с содержимым
	buffResult.clear();

	//Очищение буффера
	delete[sizeBuffer]buffer;
	//Очищение второго буффера
	delete[sizeOriginalBuffer]resBuff;

}

bool file_recognition_coder::EqualHashPart(char* encodingBuffer)
{
	//Перевод в более удобаный формат
	std::string encodStr = encodingBuffer;
	int position = 0;
	//Проверка с тем, что лежит в векторе
	for (auto iter = buffResult.begin(); iter != buffResult.end(); iter++) {
		std::string currentRecord = GetNextRecord(encodStr, position);
		if (*iter != currentRecord) {
			return false;
		}
	}
	return true;
}

void file_recognition_coder::ReadFileInfo(std::string fileName)
{
	//Подмена имени файла)))))
	std::string old_text = this->_fileName;
	_fileName = fileName;
	//Чтение файла
	OpenFileForRead();
	//Открытие файла для чтения кеша
	OpenHashForRead();
	std::string line, nameParam, valueParam;

	int last_id = 0;
	int cur_id;
	//Построковое чтение файла
	while (std::getline(*_rFile, line)) {
		//Для проверки хешей, необходимо сохранять записи в классе
		std::string currentOrder;
		//Получение и проверка id
		//Получение id
		cur_id = GetId(line);
		//Если id = -123, то это конец файла
		if (cur_id == -123) break;
		last_id = cur_id;
		currentOrder += line + "\n";
		//Проверка на id_face
		getline(*_rFile, line);
		currentOrder += line + "\n";
		CheckIdFace(line);
		//Проверка на id_camera
		getline(*_rFile, line);
		currentOrder += line + "\n";
		CheckIdCamera(line);
		//Проверка на time
		getline(*_rFile, line);
		currentOrder += line + "\n";
		CheckTime(line);
		//Добавление во внутренний класс
		buffResult.push_back(currentOrder);
	}

	//Сохранение последнего id
	id_not_db = last_id;
	//Закрытие файла
	CloseFile();
	//Закрытие файла для чтения хеша
	_inputFile.close();
	//Очищение буфера
	buffResult.clear();
	//Возвращение имени назад
	_fileName = old_text;
}

std::string file_recognition_coder::GetNextRecord(std::string FullRecord, int& currentPosition)
{
	//Сохранение начала выреза
	int begin = currentPosition;


	//Поиск следущей записи time
	int time_position = FullRecord.find("time:", begin);
	//После этого, с этой позиции поиск с коноцм записи
	currentPosition = FullRecord.find(";", time_position);
	currentPosition++;

	//Срез в новую подстроку
	std::string CurrentRecord ="";
	CurrentRecord = FullRecord.substr(begin, currentPosition - begin);
	CurrentRecord += "\n";
	currentPosition++;

	return CurrentRecord;
}

void file_recognition_coder::SaveBuffToFile()
{
	if (buffResult.size() == 0) return;
	CloseFile();
	//Открытие файла для записи
	OpenWriteToContinue();
	//Запись всех объектов в файл
	for (int i = 0; i < buffResult.size(); i++) {
		*_wFile << buffResult[i];
	}
	//Добавление зашифрованной части
	std::string text="";
	//Указатель на закодированную строку для сохранения в файл
	char *coderBuff = NULL;
	text = "hash:";
	int newSize = 0;
	GetCoderInfo(coderBuff, newSize);
	//Добавление в файл информации о размере зашифрованного блока
	text += std::to_string(newSize) + ";\n";
	*_wFile << text;
	//Запись хеша в отделный файл
	WriteHashToFile(coderBuff, newSize);
	//Очистка буффера
	buffResult.clear();
	//Закрытие файла
	CloseFile();
}

void file_recognition_coder::WriteHashToFile(char* buff, int size)
{
	//Открытие файла для записи в него хеша
	OpenHasForWrite();
	//Запись в файл
	_outputFile.write(buff, size);
	//Закрытие файла, конец записи
	_outputFile.close();
}

void file_recognition_coder::OpenHashForRead()
{
	//Закрытие файла для записи
	_outputFile.close();
	//Открытие для записи
	_inputFile.open(_fileName + "hash", std::ios::in | std::ios::binary);
}

void file_recognition_coder::OpenHasForWrite()
{
	//Закрытие файла для чтения
	//_inputFile.close();
	//Открытие файла для записи
	_outputFile.open(_fileName + "hash", std::ios::app | std::ios::binary);
}

void file_recognition_coder::GetCoderInfo(char * &outStr, int& newSize)
{
	//Получение текущего буффера в виде строки
	std::string buffer = "";
	for (int i = 0; i < buffResult.size(); i++) {
		buffer += buffResult[i];
	}
	//Длина строки
	int size = buffer.size();
	
	//Кодирование строки и сохранение результата для возврата
	outStr = _coder.Coding(buffer.c_str(), size, newSize);
	
}
