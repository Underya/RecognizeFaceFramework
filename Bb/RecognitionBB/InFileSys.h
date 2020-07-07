
#pragma once
#include <face_manager.h>
#include <file_faces.h>

#ifdef RECOGNITIONBB_EXPORTS
#define RECOGNITIONBB_API __declspec(dllexport)
#else
#define RECOGNITIONBB_API __declspec(dllimport)
#endif

RECOGNITIONBB_API void inFileSys();

//Загрузка файлов из объекта распознования в файловую систему
void inFileSys(face_manager faceManager, file_faces fileFaces) {

	std::vector<face> * vectorFace =  faceManager.GetAllFace();

	fileFaces.StartSave();

	//Для каждого объекта лица
	for (auto iter = vectorFace->begin(); iter != vectorFace->end(); iter++) {
		//Дескриптор с лицами
		std::vector<string> faces = iter->GetAllDescriptor();
		//Создание пустого вектора с дескриптами id
		std::vector<int>  vectorId;
		fileFaces.AddFace(iter->GetId(), iter->GetName(), "", faces, vectorId);
	}

	//Сохранение информации
	fileFaces.Save();

}
