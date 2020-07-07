#pragma once

#include "..//MessageServer/Ipcofnig.h"
#include "..//RecognitionBB/messageHandler.h"
#include "..//db///db_manager.h"
#include "..//db/rules_collection.h"
#include "..//RecognitionBB/sharead_face_manager.h"
#include "..//RecognitionBB/Parralel_Scaner_camera.h"
#include "..//RecognitionBB/distribute_recognitor.h"
#include "..//RecognitionBB/dbRecognitionHandler.h"
#include "..//RecognitionBB/fileRecognitionHandler.h"
#include "../RecognitionBB/PremiseCheck.h"

#ifdef RECOGNITIONBB_EXPORTS
#define RECOGNITIONBB_API __declspec(dllexport)
#else
#define RECOGNITIONBB_API __declspec(dllimport)
#endif


//Интрукция по использнованию билиотеки
//1.Подулючение к БД
//2. Логин и подтверждение
//3. Получение данных из БД

//Класс предстовляет набор методов для упрощённой работы с библиотекой
class RECOGNITIONBB_API RecognitionBB
{
public:

	RecognitionBB();

	~RecognitionBB();

	void m1_Connect_to_db(std::string host, std::string port, std::string user_name, std::string password, std::string address_db);

	void m2_Authorization(std::string login);

	void m2_Authorization();

	void m3_LoadGroupAndCamera();

	void m4_LoadEmployeeAndFace();

	void m5_CreateRecognizerAndHandler(int countThread, double SecToFile, double SecToDB);

	void m6_AddReceiver(std::vector<std::string> lisfFileName);

	void m7_addHandler(IRecognitionHandler* handler);

	void m8_Start();

	void m10_startShow();

	void m10_endShow();

	std::vector<std::pair<std::string, std::vector<std::string>>> m11_GetPrimeseInEmployee();

	void m9_end();

protected:

	//Объект, связанный с текущим пользователем
	db_user* _user = NULL;

	//Буффер с камерами
	std::vector<db_vcam> _listCamInfo;

	PremiseCheck* pc = NULL;

	//Загрузка всех сотрудников
	std::vector<db_employee> _listEmployee;

	std::vector<Parralel_Scaner_camera> _listCam;

	sharead_face_manager* _faces = NULL;
	
	std::vector<distribute_recognitor*> _listRecognitior;
};
