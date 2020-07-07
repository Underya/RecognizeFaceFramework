
#pragma once
#include "file_faces.h"
#include "face_manager.h"

#ifdef RECOGNITIONBB_EXPORTS
#define RECOGNITIONBB_API __declspec(dllexport)
#else
#define RECOGNITIONBB_API __declspec(dllimport)
#endif

RECOGNITIONBB_API void LoadFacesInFile(face_manager* f, file_faces* fileFaces);

//Загрузка файлов из текста в объект для распознователя
void LoadFacesInFile(face_manager* f, file_faces* fileFaces) {
	//Кусок кода, который отвечает за загрузку и инициализацию информации о людях

	std::list<face_info> fs_inf = fileFaces->GetFaceInfo();

	for (auto iter = fs_inf.begin(), end = fs_inf.end(); iter != end; iter++) {
		f->AddNewFace(iter->id, iter->name);
		for (auto i1 = iter->desc.begin(), e1 = iter->desc.end(); i1 != e1; i1++) {
			f->AddDescriptor(iter->id, *i1);
		}
	}

	//fileFaces->ClearFaceInfo();
}
