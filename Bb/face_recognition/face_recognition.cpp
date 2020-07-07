// face_recognition.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "face_recognition.h"

/*
#include "opencv2/opencv.hpp"
#include "dlib/dnn.h"
#include "dlib/gui_widgets.h"
#include "dlib/clustering.h"
#include "dlib/string.h"
#include "dlib/image_io.h"
#include "dlib/image_processing/frontal_face_detector.h"
#include "dlib/opencv.h"
using namespace dlib;
using namespace cv;
*/

// This is an example of an exported function.
FACERECOGNITION_API int fnfacerecognition(void)
{
    /*
    cv::VideoCapture cap("C:/02.jpg");

    anet_type net;
    deserialize("dlib_face_recognition_resnet_model_v1.dat") >> net;

    cv::Mat imgV;
    cap.read(imgV);
    dlib::cv_image<rgb_pixel> img(imgV);
    shape_predictor sp;
    deserialize("shape_predictor_5_face_landmarks.dat") >> sp;
    std::vector<matrix<rgb_pixel>> facesVec;
    frontal_face_detector detector = get_frontal_face_detector();
    for (auto face : detector(img)) {
        auto shape = sp(img, face);
        matrix<rgb_pixel> face_chip;
        extract_image_chip(img, get_face_chip_details(shape, 150, 0.25), face_chip);
        facesVec.push_back(move(face_chip));
    }

    std::vector<dlib::matrix<float, 0, 1 >> face_descriptors = net(facesVec);

    */
    /*
    
    faces fs;
    
    std:: vector<string> res;

    res.push_back("C:/photo/02.jpg");
    res.push_back("C:/photo/03.jpg");
    res.push_back("C:/photo/04.jpg");
    res.push_back("C:/photo/05.jpg");

    for (int i = 0; i < res.size(); i++) {
        face* s = fs.AddNewFaces(res[i]);
        s->AddNewPhoto(res[i]);
        cout << "Add new photo" << endl;
        fs.AddFace(*s);
    }

    //Тест поиска
    cv::VideoCapture vc1("C:/photo/02.jpg");
    cv::VideoCapture vc2("C:/photo/03.jpg");
    cv::VideoCapture vc3("C:/photo/04.jpg");
    cv::VideoCapture vc4("C:/photo/05.jpg");
    cv::VideoCapture vc5("C:/photo/06.jpg");

    std::vector<cv::VideoCapture> vcc;
    vcc.push_back(vc1);
    vcc.push_back(vc2);
    vcc.push_back(vc3);
    vcc.push_back(vc4);
    vcc.push_back(vc5);

    //Чтение в переменную
    for (int i = 0; i < 5; i++) {
        cv::Mat img;
        vcc[i].read(img);
        cv_image<rgb_pixel> cvi(img);
        face* result = fs.Recongit(cvi);
        if( result != nullptr)
            cout << "Find foto:" << res[i] << endl;
    }
    */
    return 1;

}

// This is the constructor of a class that has been exported.
Cfacerecognition::Cfacerecognition()
{
    return;
}
