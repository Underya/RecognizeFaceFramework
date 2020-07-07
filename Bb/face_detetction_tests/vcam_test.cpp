#include "pch.h"
#include "CppUnitTest.h"
#include "..//face_detection/Camera_file.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace facedetetctiontests
{
	//К сожалению, ХЗ как это сделать по отдельности, поэтоиму надо 
	//полностью тестировать
	TEST_CLASS(cameraD)
	{
	public:

		TEST_METHOD(create_empty)
		{
			CameraD d();
		}

		TEST_METHOD(load_jpg) 
		{
			try {
				CameraD c("test.jpg");
			}
			catch (...) {
				Assert::Fail();
			}

		}

		TEST_METHOD(load_video) 
		{
			CameraD c("test_video.avi");

		}

		TEST_METHOD(start_jpg) 
		{
			CameraD c("test.jpg");
			c.Start();
		}

		TEST_METHOD(start_video)
		{
			CameraD c("test_video.avi");
			c.Start();
		}

		TEST_METHOD(start_show_jpg) 
		{
			CameraD c("test.jpg");
			c.StartShow();
			c.Start();
		}

		TEST_METHOD (start_show_video)
		{
			CameraD c("test_video.avi");
			c.StartShow();
			c.Start();
		}

		TEST_METHOD(create_detector) 
		{
			Detecter d;
		}

		TEST_METHOD(set_detector)
		{
			Detecter* d = new Detecter();
			CameraD c("test_video.avi");
			c.SetDetecter(d);
			delete d;
		}


		TEST_METHOD(check_video_s_detecter)
		{
			Detecter* d = new Detecter();
			CameraD c("test_video.avi");
			c.SetDetecter(d);
			c.Start();
			delete d;
		}


	};
}
