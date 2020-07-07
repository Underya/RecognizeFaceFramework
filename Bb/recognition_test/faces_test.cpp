#include "pch.h"
#include "CppUnitTest.h"
#include "..//face_recognition/faces.h"
#include "..//include/opencv2/opencv.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using std::vector;

namespace recognitiontest
{
	TEST_CLASS(faces_test)
	{
	public:

		TEST_METHOD(create)
		{
			faces f;
		}

		TEST_METHOD(create_vec)
		{
			std::vector<face> vf;
			face f1(-1, "1", "1", "1"), f2(-2, "2", "2", "2");
			vf.push_back(f1);
			vf.push_back(f2);
			faces f(vf);
		}

		TEST_METHOD(add_face)
		{
			face f1(-1, "1", "1", "1"), f2(-2, "2", "2", "2");
			faces f;
			f.AddFace(f1);
			f.AddFace(f2);
		}

		TEST_METHOD(check_add_face)
		{
			face f1(-1, "1", "1", "1"), f2(-2, "2", "2", "2");
			faces f;
			f.AddFace(f1);
			f.AddFace(f2);
			std::vector<face>* vf = f.GetFaces();
			Assert::AreEqual(f1.GetId(), (*vf)[0].GetId());
			Assert::AreEqual(f2.GetId(), (*vf)[1].GetId());
		}

		TEST_METHOD(add_new_face)
		{
			int id = -2;
			faces f;
			f.CreateNewFace(id, "1", "1", "1");
		}

		TEST_METHOD(check_add_new_face)
		{
			int id = -2;
			faces f;
			face* retF = f.CreateNewFace(id, "1", "1", "1");
			Assert::AreEqual(id, retF->GetId());
		}

		TEST_METHOD(get_face_for_i)
		{
			int id = -2, id2 = -3;
			face f1(id, "1", "1", "1"), f2(id2, "2", "2", "2");
			faces f;
			f.AddFace(f1);
			f.AddFace(f2);
			face* rf1 = f.GetFace(id);
			face* rf2 = f.GetFace(id2);
			Assert::AreEqual(id, f1.GetId());
		}

		TEST_METHOD(check_error_for_get_i)
		{
			bool exec = false;

			try {
				faces f;
				f.GetFace(0);
			}
			catch (...) {
				exec = true;
			}

			Assert::AreEqual(true, exec);
		}

		TEST_METHOD(check_error_for_get_i_2)
		{
			bool exec = false;

			try {
				faces f;
				face f1(10, "1", "1", "1");
				f.AddFace(f1);
				f.GetFace(1);
			}
			catch (...) {
				exec = true;
			}

			Assert::AreEqual(true, exec);
		}

		TEST_METHOD(delete_face)
		{
			face f(-1, "1", "1", "1");
			faces faces;
			faces.AddFace(f);
			faces.DeletFace(f);
			Assert::AreEqual(0, (int)faces.GetFaces()->size());
		}

		TEST_METHOD(transform_to_face_matirx)
		{
			//Получеие изоражения с лицом из файла
			cv::VideoCapture cap;
			const cv::String FileName = "test.jpg";
			cap.open(FileName);
			cv::Mat imgCV;
			cap.read(imgCV);
			dlib::cv_image<dlib::rgb_pixel> cv_im(imgCV);


			faces::GetFaceMatrix(cv_im);
		}

		TEST_METHOD(clear) 
		{
			int id = 2, id2 = 3;
			faces f;
			face nf(id, "1", "1", "1");
			nf.AddNewPhoto("test.jpg");
			face nf2(id2, "2", "2", "2");
			nf.AddNewPhoto("test2.jpg");
			f.AddFace(nf);
			f.AddFace(nf2);
			f.ClearList();
		}

		TEST_METHOD(check_clear)
		{
			int id = 2, id2 = 3;
			faces f;
			face nf(id, "1", "1", "1");
			nf.AddNewPhoto("test.jpg");
			face nf2(id2, "2", "2", "2");
			nf.AddNewPhoto("test2.jpg");
			f.AddFace(nf);
			f.AddFace(nf2);
			f.ClearList();

			Assert::AreEqual(0, (int)f.GetFaces()->size());
		}

		TEST_METHOD(search_1_v_1) 
		{
			int id = 2;
			faces f;
			face nf(id, "1", "1", "1");
			nf.AddNewPhoto("test.jpg");
			f.AddFace(nf);


			//Получеие изоражения с лицом из файла
			cv::VideoCapture cap;
			const cv::String FileName = "test.jpg";
			cap.open(FileName);
			cv::Mat imgCV;
			cap.read(imgCV);
			dlib::cv_image<dlib::rgb_pixel> cv_im(imgCV);

			face *ret = f.Recongit(cv_im);

			Assert::AreEqual(id, ret->GetId());
		}
	
		TEST_METHOD(search_1_v_0)
		{
			int id = 2;
			int id_not_fount = -1;
			faces f;


			//Получеие изоражения с лицом из файла
			cv::VideoCapture cap;
			const cv::String FileName = "test.jpg";
			cap.open(FileName);
			cv::Mat imgCV;
			cap.read(imgCV);
			dlib::cv_image<dlib::rgb_pixel> cv_im(imgCV);

			face* ret = f.Recongit(cv_im);

			Assert::AreEqual(id_not_fount, ret->GetId());
		}

		TEST_METHOD(search_1_v_2) 
		{
			int id = 2, id2 = 3;
			faces f;
			face nf(id, "1", "1", "1");
			nf.AddNewPhoto("test.jpg");
			face nf2(id2, "2", "2", "2");
			nf.AddNewPhoto("test2.jpg");
			f.AddFace(nf);
			f.AddFace(nf2);

			//Получеие изоражения с лицом из файла
			cv::VideoCapture cap;
			const cv::String FileName = "test.jpg";
			cap.open(FileName);
			cv::Mat imgCV;
			cap.read(imgCV);
			dlib::cv_image<dlib::rgb_pixel> cv_im(imgCV);

			face* ret = f.Recongit(cv_im);

			Assert::AreEqual(id, ret->GetId());
		}

		TEST_METHOD(search_2_v_2) 
		{
			int id = 2, id2 = 3;
			faces f;
			face nf(id, "1", "1", "1");
			nf.AddNewPhoto("test.jpg");
			face nf2(id2, "2", "2", "2");
			nf.AddNewPhoto("test2.jpg");
			f.AddFace(nf);
			f.AddFace(nf2);

			//Получеие изоражения с лицом из файла
			cv::VideoCapture cap;
			const cv::String FileName = "test2.jpg";
			cap.open(FileName);
			cv::Mat imgCV;
			cap.read(imgCV);
			dlib::cv_image<dlib::rgb_pixel> cv_im(imgCV);

			face* ret = f.Recongit(cv_im);

			Assert::AreEqual(id, ret->GetId());
		}

		TEST_METHOD(search_3_v_2)
		{
			int id = 2, id2 = 3;
			faces f;
			face nf(id, "1", "1", "1");
			nf.AddNewPhoto("test.jpg");
			face nf2(id2, "2", "2", "2");
			nf.AddNewPhoto("test2.jpg");
			f.AddFace(nf);
			f.AddFace(nf2);

			//Получеие изоражения с лицом из файла
			cv::VideoCapture cap;
			const cv::String FileName = "test3.jpg";
			cap.open(FileName);
			cv::Mat imgCV;
			cap.read(imgCV);
			dlib::cv_image<dlib::rgb_pixel> cv_im(imgCV);

			face* ret = f.Recongit(cv_im);
			int id_not_fount = -1;
			Assert::AreEqual(id_not_fount, ret->GetId());
		}
	};
}