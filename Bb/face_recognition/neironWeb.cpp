#include "pch.h"
#include "neironWeb.h"


//Установка начальных значений нейронной сети
//И количество объектов, которые активно её используют в данный момент
int neironWeb::countNeironUses = 0;

//Инициализация пути к  файлу
std::string neironWeb::dataTrianPath = "dlib_face_recognition_resnet_model_v1.dat";
anet_type* neironWeb::web = NULL;

neironWeb::neironWeb()
{
	//Если нейроная сеть не была создана, вызвать метод, который её создаст
	if (web == NULL) {
		InitialNeironWev();
	}
}

neironWeb::~neironWeb()
{

}

//Функция для получение более точного дескриптора
std::vector<color_image> jitter_image(
	const color_image &img
)
{
	// All this function does is make 100 copies of img, all slightly jittered by being
	// zoomed, rotated, and translated a little bit differently. They are also randomly
	// mirrored left to right.
	thread_local dlib::rand rnd;

	std::vector<color_image> crops;
	for (int i = 0; i < 100; ++i)
		crops.push_back(jitter_image(img, rnd));

	return crops;
}


face_matrix neironWeb::GetAccurateDescrip(color_image img)
{
	//Получение более точного дескриптора
	return mean(mat(web->operator()(jitter_image(img))));
}




color_image neironWeb::Transform(cv_image<rgb_pixel> img)
{
	dlib::shape_predictor sp;
	dlib::deserialize("shape_predictor_5_face_landmarks.dat") >> sp;

	//Получение всего массива лиц с фотографии
	dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
	std::vector <color_image> facesVec;

	for (auto face : detector(img)) {
		auto shape = sp(img, face);
		color_image face_chip;
		extract_image_chip(img, get_face_chip_details(shape, 150, 0.25), face_chip);
		return face_chip;
	}

	throw new std::exception("not face");
}

face_matrix neironWeb::GetDescription(color_image img)
{
	std::vector<color_image> v;
	v.push_back(img);
	std::vector<face_matrix> r;
	r = web->operator()(v);
	return r[0];
}

void neironWeb::InitialNeironWev()
{
	web = new anet_type();
	deserialize(dataTrianPath) >> (* web);
}

