//
//
//  �� ����� 03.02.2020
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
	//�������� ����� �������
	
	//������� ���� ��������, ������� �������� �������
	//db->GetAllRowTable("bb_camera");

	//������ ���������� ���������� � �������� ��������
	//�������� ������� ������ ���������� � ���������

	return nullptr;
}
