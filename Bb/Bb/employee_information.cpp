#include "employee_information.h"
using namespace std;

employee_information::employee_information(bool use_db, bool _use_file)
{
	_use_db = use_db;
	_use_file = _use_file;
}

void employee_information::LoadToDB(group_information gi)
{
}

void employee_information::LoadToFile(std::list<face_info> faces)
{
}

face_manager* employee_information::GetFaces()
{
	return faces;
}

int employee_information::GetCount()
{
	if (faces == NULL) return 0;
	if(faces->GetAllFace() == NULL) return 0;
	return faces->GetAllFace()->size();
	return 0;
}
