#include "..//RecognitionBB/RecognitionBB.h"
#include "..//file_manager/Configuration.h"
#include "..//file_manager/vcam_file_manager.h"
#include "test_scenaria.h"

using namespace std;

void test_scenaria::Start()
{
	//����������� �����, ������� ������������ ��� ������������ � ��������� ���������� ��������
	int thread_count = 0;

	std::string thread_count_name = "thread_count";

	std::string win_show_name = "show_window";
	int show_window = 0;

	Configuration c;

	//���� ������� ����������� �� � 1 ���, � ���� ����� ������� 
	if (c.HasParamert(thread_count_name)) {
		thread_count = atoi(c.GetParametr(thread_count_name).c_str());
	}
	if (thread_count == 8) {
		thread_count = 0;
	}
	//���� ������� ����������� � ������ ���, ���������, ��� � �� 0 �������
	if (thread_count == 4) {
		thread_count = 8;
	}
	//���� ������� ����������� � ������ ���, ���������, ��� � �� 0 �������
	if (thread_count == 2) {
		thread_count = 4;
	}
	//���� ������� ����������� � ������ ���, ���������, ��� � �� 0 �������
	if (thread_count == 1) {
		thread_count = 2;
	}
	//���� ������� ����������� � ������ ���, ���������, ��� � �� 0 �������
	if (thread_count == 0) {
		thread_count = 1;
	}
	//���������� ����� ������� ������� ��������
	std::cout << "thread_count:" << thread_count << "\n";
	c.SetParametr(thread_count_name, std::to_string(thread_count).c_str());
	c.ClearFile();
	c.Save();

	//��������� ���������� � ���, ���� �� ������� �����������
	if (!c.HasParamert(win_show_name)) {
		//���� ���, �� ��� ���� ���������
		c.SetParametr(win_show_name, std::to_string(show_window));
		c.Save();
	}
	else {
		//���� ����, �� ���������� ��������� �������������� ��������
		show_window = atoi(c.GetParametr(win_show_name).c_str());
	}


	//��������� ���������� �������
	vcam_file_manager vf("camers.txt");

	//���� ��� ���������� � �������
	if (vf.GetList()->size() == 0) {
		//�� �������� ����� � ������������ ��� �� �����������
		vf.AddNewCamera("0", "cam1");
		vf.Save();
	}


	face_manager fm;
	distribute_recognitor rr1(&fm, thread_count);
	distribute_recognitor rr2(&fm, thread_count);
	Detecter d;

	//�������� �������� �����
	information_camera* ic1 = NULL;
	information_camera* ic2 = NULL;
	list<vcam_file> list = *vf.GetList();
	vcam_file cam = list.front();

	ic1 = new information_camera(cam.address, "win1");
	if (list.size() == 2) {
		list.pop_front();
		cam = list.front();
		ic2 = new information_camera(cam.address, "win2");
	}

	//��������� ����� �������� ������
	Parralel_Scaner_camera psc1(ic1->GetPath(), *ic1);
	psc1.SetDetecter(&d);
	psc1.SetRecognitor(&rr1);

	//���� ���� ������ ������
	if (ic2 != NULL) {
		Parralel_Scaner_camera psc2(ic2->GetPath(), *ic2);
		psc2.SetDetecter(&d);
		psc2.SetRecognitor(&rr2);
		psc2.StartWork();
		//���� ����, ������ ����
		if (show_window) {
			psc2.StartShow();
		}
	}

	psc1.StartWork();
	if (show_window) {
		psc1.StartShow();
	}

	//psc.StartShow();
	std::this_thread::sleep_for(40s);
	return;
}
