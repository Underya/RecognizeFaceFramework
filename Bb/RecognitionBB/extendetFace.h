
#pragma once
#include <face.h>

#ifdef RECOGNITIONBB_EXPORTS
#define RECOGNITIONBB_API __declspec(dllexport)
#else
#define RECOGNITIONBB_API __declspec(dllimport)
#endif



//Расширенная информация о лице
class RECOGNITIONBB_API extendetFace :
	public face
{
public:

	extendetFace(face f);

	void AddGroup(int id_group);

protected:

	std::vector<int> my_group;
};

