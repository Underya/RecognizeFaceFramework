
#pragma once
#include <face_manager.h>
#include <file_faces.h>

#ifdef RECOGNITIONBB_EXPORTS
#define RECOGNITIONBB_API __declspec(dllexport)
#else
#define RECOGNITIONBB_API __declspec(dllimport)
#endif

RECOGNITIONBB_API void inFileSys();

//�������� ������ �� ������� ������������� � �������� �������
void inFileSys(face_manager faceManager, file_faces fileFaces) {

	std::vector<face> * vectorFace =  faceManager.GetAllFace();

	fileFaces.StartSave();

	//��� ������� ������� ����
	for (auto iter = vectorFace->begin(); iter != vectorFace->end(); iter++) {
		//���������� � ������
		std::vector<string> faces = iter->GetAllDescriptor();
		//�������� ������� ������� � ����������� id
		std::vector<int>  vectorId;
		fileFaces.AddFace(iter->GetId(), iter->GetName(), "", faces, vectorId);
	}

	//���������� ����������
	fileFaces.Save();

}
