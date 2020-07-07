#pragma once

#include "..//include/dlib/dnn.h"
#include "..//include/dlib/gui_widgets.h"
#include "..//include/dlib/clustering.h"
#include "..//include/dlib/string.h"
#include "..//include/dlib/image_io.h"
#include "..//include/dlib/image_processing/frontal_face_detector.h"

using namespace dlib;
#include "..//include/dlib/opencv.h"
#include "..//include/dlib/matrix.h"
#include <iostream>

//Представление матрицы для лица единым типом
typedef dlib::matrix<float, 0, 1 > face_matrix;
//#define dlib::matrix<float, 0, 1 > dlib::matrix<float, 0, 1 >

//Обработанная фотография
typedef dlib::matrix<rgb_pixel> color_image;
//#define dlib::matrix<rgb_pixel> dlib::matrix<rgb_pixel>

template <template <int, template<typename>class, int, typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual = add_prev1<block<N, BN, 1, tag1<SUBNET>>>;

template <template <int, template<typename>class, int, typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual_down = add_prev2<avg_pool<2, 2, 2, 2, skip1<tag2<block<N, BN, 2, tag1<SUBNET>>>>>>;

template <int N, template <typename> class BN, int stride, typename SUBNET>
using block = BN<con<N, 3, 3, 1, 1, relu<BN<con<N, 3, 3, stride, stride, SUBNET>>>>>;

template <int N, typename SUBNET> using ares = relu<residual<block, N, affine, SUBNET>>;
template <int N, typename SUBNET> using ares_down = relu<residual_down<block, N, affine, SUBNET>>;

template <typename SUBNET> using alevel0 = ares_down<256, SUBNET>;
template <typename SUBNET> using alevel1 = ares<256, ares<256, ares_down<256, SUBNET>>>;
template <typename SUBNET> using alevel2 = ares<128, ares<128, ares_down<128, SUBNET>>>;
template <typename SUBNET> using alevel3 = ares<64, ares<64, ares<64, ares_down<64, SUBNET>>>>;
template <typename SUBNET> using alevel4 = ares<32, ares<32, ares<32, SUBNET>>>;

using anet_type = loss_metric<fc_no_bias<128, avg_pool_everything<
    alevel0<
    alevel1<
    alevel2<
    alevel3<
    alevel4<
    max_pool<3, 3, 2, 2, relu<affine<con<32, 7, 7, 2, 2,
    input_rgb_image_sized<150>
    >>>>>>>>>>>>;

#ifdef FACERECOGNITION_EXPORTS
#define FACERECOGNITION_API __declspec(dllexport)
#else
#define FACERECOGNITION_API __declspec(dllimport)
#endif



//Класс, предоставляющий нейронную сеть для РАСПОЗНОВАНИЯ лиц
class FACERECOGNITION_API neironWeb
{
public:
    //Получение указателя на нейронную сеть
    //Время жизни объекта сети совпадает со временм жизни объкта neironWeb
    //anet_type *GetRecogntiorNeiron();

    neironWeb();

    ~neironWeb();

    //Получение ТОЧНОГО дескриптора лица по цветному изображению
    face_matrix GetAccurateDescrip(color_image img);

    //Получение цветной фотографии, и её обработка для того, что бы можно было получить её дескриптор
    color_image Transform(cv_image<rgb_pixel> img);

    //Получение дескриптора фотографии обычным образом
    face_matrix GetDescription(color_image img);

private:

    //Нейросеть для распознования
    static anet_type *web;

	//Создание объекта нейронной сети
	void InitialNeironWev();

    //Путь к файлу, в котором есть результаты тренировки
    static std::string dataTrianPath;

    //Количество использований нейрона
    static int countNeironUses;
};