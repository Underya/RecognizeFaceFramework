
#pragma once
#include "Parralel_Recognitor.h"

//�����, ������� � �������� ������������� ������ ������ ����������� �� n ������� ���������������
class RECOGNITIONBB_API distribute_recognitor :
	public IRecognitor
{
public:

	//��������, ������� ����� ����� ������������� ��� ������������� ����������� � ����� �����
	distribute_recognitor(face_manager * fm,  int count_thread = 1);

	~distribute_recognitor();

	//�������� ������ ������ ��� �������������
	//����� �������������� ����� ��������
	virtual void Recognition(std::vector<OneFrame> vector_frame, information_camera cam);

	void SetDBSource(db_manager_parralel* dbmp);

	//��������� ������ ������, ����������� ��� �������������
	virtual void AddRecognitionHandler(IRecognitionHandler *recognitionHandler);

	//������� id_������
	void SetId(int id_cam);

	//�������� ���� �������
	virtual void EndWork();

protected:

	face_manager* _fm = NULL;

	int my_num;

	static int numm;

	db_manager_parralel* _dbmp = NULL;

	//���������� ����� � ������� �������
	int _count_thread = 0;

	//����� ���������� ��������������� ������
	int _last_use_thread = 0;

	//������ �� ����� ������ ��� �������������
	std::vector<Parralel_Recognitor*> _recognitors;

};

