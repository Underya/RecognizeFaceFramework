#pragma once
#include <iostream>

#ifdef FACERECOGNITION_EXPORTS
#define FACERECOGNITION_API __declspec(dllexport)
#else
#define FACERECOGNITION_API __declspec(dllimport)
#endif

//Дополнительная информация, которая прикрепляется с лицом
//Класс наследуется для того, что бы передавать информацию вместе с распознонанным лицом
class FACERECOGNITION_API add_load_face
{
public:

	add_load_face();

	virtual std::string GetType();

protected:
	std::string _this_type;
};