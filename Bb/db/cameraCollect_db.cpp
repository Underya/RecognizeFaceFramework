//
//
//  НЕ НУЖЕН 03.02.2020
//
//

#include "pch.h"
#include "cameraCollect_db.h"
#include "db_connect.h"

cameraCollect_db::cameraCollect_db() {
	cammCollection = NULL;
}

cameraCollect_db::~cameraCollect_db() {
	if (cammCollection != NULL) delete cammCollection;
}


cameraCollect_db *cameraCollect_db::GetCollectionCamera(Condition c) {
	//Разборка блока условий
	
	//Выборка всех объектов, которые подходят условию
	//db->GetAllRowTable("bb_camera");

	//Разбор полученной информации и создание объектов
	//Созданые объекта камеры добавлятся в коллекцию

	return nullptr;
}
