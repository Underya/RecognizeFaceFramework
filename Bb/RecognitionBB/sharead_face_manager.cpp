
#include "sharead_face_manager.h"

sharead_face_manager::sharead_face_manager() : face_manager()
{
	_mutex = new std::mutex();
}

sharead_face_manager::~sharead_face_manager()
{
}

void sharead_face_manager::AddNewPhoto(int id, string path)
{
	_mutex->lock();
	face_manager::AddNewPhoto(id, path);
	_mutex->unlock();
}

void sharead_face_manager::AddNewFace(int id, string name, string family, string mid_name, string db_description)
{
	_mutex->lock();
	face_manager::AddNewFace(id, name, family, mid_name, db_description);
	_mutex->unlock();
}

bool sharead_face_manager::CheckId(int id)
{
	_mutex->lock();
	bool restult = face_manager::CheckId(id);
	_mutex->unlock();
	return restult;
}

void sharead_face_manager::AddDescriptor(int id, string desc)
{
	_mutex->lock();
	face_manager::AddDescriptor(id, desc);
	_mutex->unlock();
}

void sharead_face_manager::AddDescriptor(int id, float* desc)
{
	_mutex->lock();
	face_manager::AddDescriptor(id, desc);
	_mutex->unlock();
}
