#include "pch.h"
#include "CppUnitTest.h"
#include "..//face_recognition/face_manager.h"
#include "..//include/opencv2/opencv.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using std::vector;

namespace recognitiontest
{
	TEST_CLASS(faces_manager_test)
	{
	public:

		TEST_METHOD(create)
		{
			face_manager f;
		}


		TEST_METHOD(set_vector_face) 
		{
			face_manager fm;
			face f(1, "", "", ""), f2(2, "", "", "");
			std::vector<face> vec = { f, f2 };
			fm.SetListFace(vec);
		}


		TEST_METHOD(check_vector_face) 
		{
			face_manager fm;
			face f(1, "", "", ""), f2(2, "", "", "");
			std::vector<face> vec = { f, f2 };
			fm.SetListFace(vec);
			Assert::AreEqual(2, (int)(*fm.GetAllFace()).size());
		}

		TEST_METHOD(add_new_face)
		{
			int id = -2;
			face_manager f;
			f.AddNewFace(id, "1", "1", "1");
		}

		TEST_METHOD(check_add_new_face)
		{
			int id = -2;
			face_manager f;
			f.AddNewFace(id, "1", "1", "1");
			face retF =  (*f.GetAllFace())[0];
			Assert::AreEqual(id, retF.GetId());
		}

		TEST_METHOD(get_face_for_i)
		{
			int id = -2, id2 = -3;
			face f1(id, "1", "1", "1"), f2(id2, "2", "2", "2");
			face_manager f;
			std::vector<face> vf = { f1, f2 };
			f.SetListFace(vf);
			face rf1 = f.GetFaceForId(id);
			face rf2 = f.GetFaceForId(id2);
			Assert::AreEqual(id, f1.GetId());
		}


		TEST_METHOD(check_error_for_get_i)
		{
			bool exec = false;

			try {
				int id = -2, id2 = -3;
				face f1(id, "1", "1", "1"), f2(id2, "2", "2", "2");
				face_manager f;
				std::vector<face> vf = { f1};
				f.SetListFace(vf);
				face rf1 = f.GetFaceForId(id2);
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
				int id = -2, id2 = -3;
				face f1(id, "1", "1", "1"), f2(id2, "2", "2", "2");
				face_manager f;
				std::vector<face> vf = { f2 };
				f.SetListFace(vf);
				face rf1 = f.GetFaceForId(id);
			}
			catch (...) {
				exec = true;
			}

			Assert::AreEqual(true, exec);
		}

		TEST_METHOD(add_load) 
		{
			int id = -2;
			face f(id, "1", "2", "1");
			face_manager fm;
			fm.SetListFace({ f });

			add_load_face* alf = new add_load_face();
			fm.AddLoad(id, alf);
		}

		TEST_METHOD(add_desc_float) 
		{
			float* desc = new float[128]();
			for (int i = 0; i < 128; i++) desc[i] = 0;

			int id = -2;
			face f(id, "1", "2", "1");
			face_manager fm;
			fm.SetListFace({ f });
			fm.AddDescriptor(id, desc);
		}

		TEST_METHOD(check_add_desc_float) 
		{
			float* desc = new float[128]();
			for (int i = 0; i < 128; i++) desc[i] = 0;

			int id = -2;
			face f(id, "1", "2", "1");
			face_manager fm;
			fm.SetListFace({ f });
			fm.AddDescriptor(id, desc);

			face ref = fm.GetFaceForId(id);

			float *desc2 = ref.GetFloatDescript(0);
			for (int i = 0; i < 128; i++) {
				Assert::AreEqual(0, (int)desc2[i]);
			}
		}


		TEST_METHOD(add_desc_string)
		{
			float* desc = new float[128]();
			string sm1 = "";
			for (int i = 0; i < 128; i++) {
				desc[i] = 0;
				sm1 += "0 ";
			}

			int id = -2;
			face f(id, "1", "2", "1");
			face_manager fm;
			fm.SetListFace({ f });
			fm.AddDescriptor(id, sm1);

		}

		TEST_METHOD(check_add_desc_str)
		{
			float* desc = new float[128]();
			string sm1 = "";
			for (int i = 0; i < 128; i++) {
				desc[i] = 0;
				sm1 += "0 ";
			}

			int id = -2;
			face f(id, "1", "2", "1");
			face_manager fm;
			fm.SetListFace({ f });
			fm.AddDescriptor(id, sm1);

			face ref = fm.GetFaceForId(id);

			float* desc2 = ref.GetFloatDescript(0);
			for (int i = 0; i < 128; i++) {
				Assert::AreEqual(0.0, (double)desc2[i]);
			}
		}

		TEST_METHOD(check_add_load) 
		{
			int id = -2;
			face f(id, "1", "2", "1");
			face_manager fm;
			fm.SetListFace({ f });

			add_load_face* alf = new add_load_face();
			fm.AddLoad(id, alf);
			face retf = fm.GetFaceForId(id);
			Assert::AreEqual(alf->GetType(), retf.GetLoad()->GetType());
		}


		TEST_METHOD(add_photo)
		{
			int id = -2;
			face f(id, "1", "2", "1");
			face_manager fm;
			fm.SetListFace({ f });
			fm.AddNewPhoto(id, "test.jpg");
		}

		TEST_METHOD(add_photo_2_face)
		{
			bool exec = false;

			try {
				int id = -2;
				face f(id, "1", "2", "1");
				face_manager fm;
				//fm.SetListFace({ f });
				fm.AddNewPhoto(id, "test.jpg");
			}
			catch (...) {
				exec = true;
			}

			Assert::AreEqual(true, exec);
		}

		TEST_METHOD(search_1_v_1)
		{
			int id = 2;
			face_manager f;
			face nf(id, "1", "1", "1");
			nf.AddNewPhoto("test.jpg");
			f.SetListFace({ nf });


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

		TEST_METHOD(search_1_v_0)
		{
			int id = 2;
			int id_not_fount = -1;
			face_manager f;


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
			face_manager f;
			face nf(id, "1", "1", "1");
			nf.AddNewPhoto("test.jpg");
			face nf2(id2, "2", "2", "2");
			nf.AddNewPhoto("test2.jpg");
			f.SetListFace({ nf, nf2 });

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
			face_manager f;
			face nf(id, "1", "1", "1");
			nf.AddNewPhoto("test.jpg");
			face nf2(id2, "2", "2", "2");
			nf.AddNewPhoto("test2.jpg");
			f.SetListFace({ nf, nf2 });

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
			face_manager f;
			face nf(id, "1", "1", "1");
			nf.AddNewPhoto("test.jpg");
			face nf2(id2, "2", "2", "2");
			nf.AddNewPhoto("test2.jpg");
			f.SetListFace({ nf, nf2 });

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

		TEST_METHOD(clear_list) 
		{
			int id = 2, id2 = 3;
			face_manager f;
			face nf(id, "1", "1", "1");
			nf.AddNewPhoto("test.jpg");
			face nf2(id2, "2", "2", "2");
			nf.AddNewPhoto("test2.jpg");
			f.SetListFace({ nf, nf2 });
			f.ClearList();
		}

		TEST_METHOD(check_clear_list)
		{
			int id = 2, id2 = 3;
			face_manager f;
			face nf(id, "1", "1", "1");
			nf.AddNewPhoto("test.jpg");
			face nf2(id2, "2", "2", "2");
			nf.AddNewPhoto("test2.jpg");
			f.SetListFace({ nf, nf2 });
			f.ClearList();
			Assert::AreEqual(0, (int)f.GetAllFace()->size());
		}

		TEST_METHOD(getfloat)
		{
			face_matrix m(128, 1);
			for (auto iter = m.begin(); iter != m.end(); iter++) (*iter) = 0;
			face_manager f;
			float *fl = f.GetFloat(m); 
			for (int i = 0; i < 128; i++) Assert::AreEqual(0.0, (double)fl[i]);
		}

		TEST_METHOD(transformation)
		{
			string d = "";
			for (int i = 0; i < 128; i++) d += "0 ";

			face_manager fm;
			face_matrix mat = fm.Transformation(d);

			for (auto iter = mat.begin(); iter != mat.end(); iter++) {
				Assert::AreEqual(0.0, (double)* iter);
			}
		}
	};
}