
#include "extendetFace.h"

extendetFace::extendetFace(face f) : face(f)
{
	std::cout << "new_object!!!";
}

void extendetFace::AddGroup(int id_group)
{
	my_group.push_back(id_group);
}
