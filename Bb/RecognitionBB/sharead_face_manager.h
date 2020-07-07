
#pragma once
#include "..//face_recognition/face_manager.h"
#include <thread>

#ifdef RECOGNITIONBB_EXPORTS
#define RECOGNITIONBB_API __declspec(dllexport)
#else
#define RECOGNITIONBB_API __declspec(dllimport)
#endif


//Разделяемая база данных лиц, с учётом многопоточного использования
class RECOGNITIONBB_API sharead_face_manager :
	public face_manager
{
public:

	sharead_face_manager();

	~sharead_face_manager();

	//Добавление новой фотографии к уже существуюшему списку фотографий
	virtual void AddNewPhoto(int id, string path) override;

	//Добавление нового лица 
	virtual void AddNewFace(int id, string name, string family, string mid_name, string db_description = "") override;

	//Проверка, есть ли объект с таким id
	virtual bool CheckId(int id) override;

	//Добавление уже существующего дескриптора для лица
	virtual void AddDescriptor(int id, string desc) override;

	//Добавление уже существующего дескриптора для лица
	virtual void AddDescriptor(int id, float* desc) override;
protected:

	std::mutex* _mutex;
};

