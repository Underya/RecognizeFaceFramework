#include "pch.h"
#include "CppUnitTest.h"
#include "..//file_manager/file_recognition_result.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace filemanagertest
{
	std::string result_file_name = "file_recognition_result.test";

	std::string result_empty = "";

	//Идентификаторы сотрудников
	int result_emp1 = 1, result_emp2 = 2, result_emp3 = 3;

	int result_cam1 = 1, result_cam2 = 2;

	int result_size_buff = 3;

	int result_id = 1613;

	

	TEST_CLASS(file_result_test)
	{
	public:

		TEST_METHOD(create)
		{
			file_recognition_result frr(result_file_name);

		}

		TEST_METHOD(create_size_buff) 
		{
			file_recognition_result frr(result_file_name, result_size_buff);
		}

		TEST_METHOD(add_recognit) 
		{
			file_recognition_result frr(result_file_name);
			frr.AddRecognition(result_emp1, result_cam1);
		}

		TEST_METHOD(add_recognit_with_id) 
		{
			file_recognition_result frr(result_file_name);
			frr.AddRecognition(result_emp1, result_cam1, result_id);
		}

		TEST_METHOD(add_recognit_save) 
		{
			file_recognition_result frr(result_file_name);
			frr.AddRecognition(result_emp1, result_cam1);
			frr.Save();
		}

		TEST_METHOD(start_with_id) 
		{
			file_recognition_result frr(result_file_name);
			frr.SetStartId(123);
		}

		TEST_METHOD(start_with_id_add) 
		{
			file_recognition_result frr(result_file_name);
			frr.SetStartId(123);
			frr.AddRecognition(result_emp2, result_cam2);
			frr.Save();
		}

		TEST_METHOD(buffer_overflow)
		{
			file_recognition_result frr(result_file_name, result_size_buff);
			for (int i = 0; i < result_size_buff * 2 + 1; i++) {
				frr.AddRecognition(result_emp2, result_cam2);
			}
		}

		TEST_METHOD(check_ram_content) 
		{
			file_recognition_result frr(result_file_name, result_size_buff);
			frr.AddRecognition(result_emp1, result_cam1);
			Assert::AreNotEqual(result_empty, frr.GetContentList());
		}

		TEST_METHOD(face_id) 
		{
			file_recognition_result frr(result_file_name, result_size_buff);
			frr.AddRecognition(result_emp1, result_cam1);
			if (frr.GetContentList().find("id_face:" + std::to_string(result_emp1) + ";") == -1) {
				Assert::Fail();
			}
		}

		TEST_METHOD(cam_id) 
		{
			file_recognition_result frr(result_file_name, result_size_buff);
			frr.AddRecognition(result_emp1, result_cam1);
			if (frr.GetContentList().find("id_camera:" + std::to_string(result_cam1) + ";") == -1) {
				Assert::Fail();
			}
		}

		TEST_METHOD(check_res_id) 
		{
			file_recognition_result frr(result_file_name, result_size_buff);
			frr.AddRecognition(result_emp1, result_cam1, result_id);
			if (frr.GetContentList().find("id:" + std::to_string(result_id) + ";") == -1) {
				Assert::Fail();
			}
		}

		TEST_METHOD(check_start_id) 
		{
			file_recognition_result frr(result_file_name, result_size_buff);
			frr.SetStartId(result_id);
			frr.AddRecognition(result_emp1, result_cam1);
			if (frr.GetContentList().find("id:" + std::to_string(result_id + 1) + ";") == -1) {
				Assert::Fail();
			}
		}

		TEST_METHOD(s1e1_clear) 
		{
			file_recognition_result frr(result_file_name);
			frr.ClearFile();
		}

		TEST_METHOD(s1e2_check_clear) 
		{
			std::fstream file;
			file.open(result_file_name);
			std::string res;
			std::getline(file, res);
			Assert::AreEqual(result_empty, res);
		}

		TEST_METHOD(s1e3_add_save) 
		{
			file_recognition_result frr(result_file_name);
			frr.AddRecognition(result_emp2, result_cam1);
			frr.Save();
		}

		TEST_METHOD(s1e4_check_save) 
		{
			std::fstream file;
			file.open(result_file_name);
			std::string res;
			std::getline(file, res);
			Assert::AreNotEqual(result_empty, res);
		}

		TEST_METHOD(s1e5_buffer_overflow) 
		{
			file_recognition_result frr(result_file_name, result_size_buff);
			frr.ClearFile();
			for (int i = 0; i < result_size_buff + 1; i++) {
				frr.AddRecognition(result_emp2, result_cam2);
			}
		}

		TEST_METHOD(s1e6_check_buffer_overflow) 
		{
			std::fstream file;
			file.open(result_file_name);
			std::string res;
			std::getline(file, res);
			Assert::AreNotEqual(result_empty, res);
		}

		TEST_METHOD(s1e7_desctuctor_save) 
		{
			file_recognition_result frr(result_file_name, result_size_buff);
			frr.ClearFile();
			frr.AddRecognition(result_emp2, result_cam1);
		}

		TEST_METHOD(s1e8_check_descturctor_save) 
		{
			std::fstream file;
			file.open(result_file_name);
			std::string res;
			std::getline(file, res);
			Assert::AreNotEqual(result_empty, res);
		}

	};
}