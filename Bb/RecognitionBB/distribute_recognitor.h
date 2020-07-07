
#pragma once
#include "Parralel_Recognitor.h"

// ласс, который в раздел€т распознование одного потока изображений на n потоков распознователей
class RECOGNITIONBB_API distribute_recognitor :
	public IRecognitor
{
public:

	//”казание, сколько поток будет использоватс€ дл€ распозновани€ изображени€ с одной камер
	distribute_recognitor(face_manager * fm,  int count_thread = 1);

	~distribute_recognitor();

	//ѕередача набора кадров дл€ распозновани€
	// адры распредел€ютс€ между потоками
	virtual void Recognition(std::vector<OneFrame> vector_frame, information_camera cam);

	void SetDBSource(db_manager_parralel* dbmp);

	//”становка нового класса, вызываемого при распозновании
	virtual void AddRecognitionHandler(IRecognitionHandler *recognitionHandler);

	//”казать id_камеры
	void SetId(int id_cam);

	//«акрытие всех потоков
	virtual void EndWork();

protected:

	face_manager* _fm = NULL;

	int my_num;

	static int numm;

	db_manager_parralel* _dbmp = NULL;

	// оличество поток у данного объекта
	int _count_thread = 0;

	//Ќомер последнего использованного потока
	int _last_use_thread = 0;

	//¬ектор со всеми потока дл€ распозновани€
	std::vector<Parralel_Recognitor*> _recognitors;

};

