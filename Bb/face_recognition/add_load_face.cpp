#include "pch.h"
#include "add_load_face.h"

add_load_face::add_load_face()
{
	_this_type = "based type";
}

std::string add_load_face::GetType()
{
	return this->_this_type;
}
