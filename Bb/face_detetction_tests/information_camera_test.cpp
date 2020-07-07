#include "pch.h"
#include "CppUnitTest.h"
#include "..//face_detection/information_camera.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace facedetetctiontests
{
	TEST_CLASS(information_camera_test)
	{
	public:

		TEST_METHOD(create_path)
		{
			information_camera ic("path");
		}

		TEST_METHOD(crete_number) 
		{
			information_camera ic(0);
		}

		TEST_METHOD(check_path) 
		{
			std::string path = "path";
			information_camera ic(path);
			Assert::AreEqual(true, ic.IsWebCam());
			Assert::AreEqual(path, ic.GetPath());
		}

		TEST_METHOD(check_number)
		{
			int num = 0;
			information_camera ic(num);
			Assert::AreEqual(num, ic.GetNumber());
		}

		TEST_METHOD(check_name_path)
		{
			std::string path = "path", name = "name";
			information_camera ic(path, name);
			Assert::AreEqual(name, ic.GetName());
		}

		TEST_METHOD(check_name_number)
		{
			int num = 0;
			std::string path = "path", name = "name";
			information_camera ic(num, name);
			Assert::AreEqual(name, ic.GetName());
		}

		TEST_METHOD(id) 
		{
			int id = 1;
			std::string desc = "description";
			int num = 0;
			std::string path = "path", name = "name";
			information_camera ic(num);
			ic.SetCameraInfo(id, desc);
			Assert::AreEqual(id, ic.GetId());
		}

		TEST_METHOD(check_premisses) 
		{
			std::pair<int, std::string> p1 = { 1, "prem1" };
			std::pair<int, std::string> p2 = { 2, "prem2" };
			std::vector< std::pair<int, std::string>> premises = { p1, p2 };
			int num = 0;
			information_camera ic(num);
			ic.SetPremises(premises);
			Assert::AreEqual(premises.size(), ic.GetPremises().size());
		}

		TEST_METHOD(check_get_info) 
		{
			int id = 1;
			std::string desc = "description";
			int num = 0;
			std::string path = "path", name = "name";
			information_camera orig(num, name);
			orig.SetCameraInfo(id, desc);
			information_camera copy = orig.GetInformationCamera();
			Assert::AreEqual(orig.GetNumber(), copy.GetNumber());
			Assert::AreEqual(orig.GetName(), copy.GetName());
			Assert::AreEqual(orig.GetId(), copy.GetId());
			Assert::AreEqual(orig.GetDescrtiption(), copy.GetDescrtiption());
		}

		TEST_METHOD(create_number_is_string) 
		{
			information_camera ic("0");
		}

		TEST_METHOD(check_usb_cam_is_string) 
		{
			information_camera ic("0");
			Assert::IsTrue(ic.IsUsbCam());
		}

		TEST_METHOD(check_num_is_string) 
		{
			std::string num = "0";
			information_camera ic(num);
			Assert::AreEqual(atoi(num.c_str()), ic.GetNumber());
		}

		TEST_METHOD(check_is_not_USB) {
			std::string num = "0";
			information_camera ic(num);
			Assert::IsFalse(ic.IsWebCam());
		}

		TEST_METHOD(check_window_name_default) 
		{
			std::string num = "0";
			information_camera ic(num);
			Assert::AreNotEqual(num, ic.GetName());
		}

		TEST_METHOD(set_window_set_name) 
		{
			std::string num = "0", name = "window_name";
			information_camera ic(num, name);
		}

		TEST_METHOD(check_window_set_name) 
		{
			std::string num = "0", name = "window_name";
			information_camera ic(num, name);
			Assert::AreEqual(name, ic.GetName());
		}

		TEST_METHOD(create_number_error) 
		{
			std::string num_error = "err";
			information_camera ic(num_error);
		}
	};

}
