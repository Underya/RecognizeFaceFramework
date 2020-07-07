#include "..//RecognitionBB/RecognitionBB.h"
#include "..//file_manager/Configuration.h"
#include "..//file_manager/vcam_file_manager.h"
#include "test_scenaria.h"

using namespace std;

void test_scenaria::Start()
{
	//Специальный кусок, который используется для тестирования и получения количества объектов
	int thread_count = 0;

	std::string thread_count_name = "thread_count";

	std::string win_show_name = "show_window";
	int show_window = 0;

	Configuration c;

	//Если система запускается не в 1 раз, и есть число потоков 
	if (c.HasParamert(thread_count_name)) {
		thread_count = atoi(c.GetParametr(thread_count_name).c_str());
	}
	if (thread_count == 8) {
		thread_count = 0;
	}
	//Если система запускается в первый раз, считается, что у неё 0 потоков
	if (thread_count == 4) {
		thread_count = 8;
	}
	//Если система запускается в первый раз, считается, что у неё 0 потоков
	if (thread_count == 2) {
		thread_count = 4;
	}
	//Если система запускается в первый раз, считается, что у неё 0 потоков
	if (thread_count == 1) {
		thread_count = 2;
	}
	//Если система запускается в первый раз, считается, что у неё 0 потоков
	if (thread_count == 0) {
		thread_count = 1;
	}
	//Сохранение числа потоков текущей итерации
	std::cout << "thread_count:" << thread_count << "\n";
	c.SetParametr(thread_count_name, std::to_string(thread_count).c_str());
	c.ClearFile();
	c.Save();

	//Получение информации о том, надо ли выодить изображение
	if (!c.HasParamert(win_show_name)) {
		//Если нет, то его надо поместить
		c.SetParametr(win_show_name, std::to_string(show_window));
		c.Save();
	}
	else {
		//Если есть, то необходимо поставить соотвествующее значение
		show_window = atoi(c.GetParametr(win_show_name).c_str());
	}


	//Получение информации камерах
	vcam_file_manager vf("camers.txt");

	//Если нет информации о камерах
	if (vf.GetList()->size() == 0) {
		//То создаётся камер с сопуствующей для неё информацией
		vf.AddNewCamera("0", "cam1");
		vf.Save();
	}


	face_manager fm;
	distribute_recognitor rr1(&fm, thread_count);
	distribute_recognitor rr2(&fm, thread_count);
	Detecter d;

	//Создание объектов камер
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

	//Созданние самих объектов камеры
	Parralel_Scaner_camera psc1(ic1->GetPath(), *ic1);
	psc1.SetDetecter(&d);
	psc1.SetRecognitor(&rr1);

	//Если есть вторая камера
	if (ic2 != NULL) {
		Parralel_Scaner_camera psc2(ic2->GetPath(), *ic2);
		psc2.SetDetecter(&d);
		psc2.SetRecognitor(&rr2);
		psc2.StartWork();
		//Если надо, запуск окна
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
