#include "pch.h"
#include "CppUnitTest.h"
#include "..//face_recognition/neironWeb.h"
#include "..//face_detection/Camera_file.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace recognitiontest
{
	TEST_CLASS(neironWeb_test)
	{
	public:

		TEST_METHOD(create)
		{
			neironWeb web;
		}

		TEST_METHOD(create_3)
		{
			neironWeb web;
			neironWeb web1;
			neironWeb web2;
		}

		TEST_METHOD(transform)
		{
			//Получение картинки
			cv::VideoCapture cap;
			cap.open("test.jpg");
			Assert::AreEqual(true, cap.isOpened());
			cv::Mat img;
			cap.read(img);
			cv_image<rgb_pixel> dimg (img);
			neironWeb web;
			web.Transform(img);
		}

		TEST_METHOD(get_desc) 
		{
			//Получение картинки
			cv::VideoCapture cap;
			cap.open("test.jpg");
			Assert::AreEqual(true, cap.isOpened());
			cv::Mat img;
			cap.read(img);
			cv_image<rgb_pixel> dimg(img);
			neironWeb web;
			color_image desc = web.Transform(img);
			//Получение дескриптора
			web.GetDescription(desc);
		}

		TEST_METHOD(check_desc)
		{
			//Получение картинки
			cv::VideoCapture cap;
			cap.open("test.jpg");
			Assert::AreEqual(true, cap.isOpened());
			cv::Mat img;
			cap.read(img);
			cv_image<rgb_pixel> dimg(img);
			neironWeb web;
			color_image desc = web.Transform(img);
			//Получение дескриптора
			face_matrix m = web.GetDescription(desc);
		}
		
		TEST_METHOD(get_spec_desc) 
		{
			//Получение картинки
			cv::VideoCapture cap;
			cap.open("test.jpg");
			Assert::AreEqual(true, cap.isOpened());
			cv::Mat img;
			cap.read(img);
			cv_image<rgb_pixel> dimg(img);
			neironWeb web;
			color_image desc = web.Transform(img);
			//Получение дескриптора
			face_matrix m = web.GetAccurateDescrip(desc);
		}
	};
}
