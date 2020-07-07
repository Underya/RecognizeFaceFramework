#include "pch.h"
#include "CppUnitTest.h"
#include "..//db/db_recognition_result.h"
#include "..//db/db_employee.h"
#include "..//db/db_vcam.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace dbmanagertests
{

	int db_rec_emp_id1 = -1;
	int db_rec_cam_id1 = -2, db_rec_cam_id2 = -3;

	TEST_CLASS(recognition_result_test)
	{
	public:

		TEST_METHOD_INITIALIZE(initialMethod)
		{
			// method initialization code
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", false);
		}

		//ѕопытка получить тестового сотрудника
		TEST_METHOD(create_obj)
		{
			db_recognition_result dbrr;
		}

		TEST_METHOD(s1p01_crete_emp_camera) 
		{
			db_rec_emp_id1 =	db_employee::AddNewEmployee("db_vca", "d", "daw")->GetId();
			db_rec_cam_id1 = db_vcam::addNewCamera("db_recognition_vcam_test", "n", -2).GetId();
			db_rec_cam_id2 = db_vcam::addNewCamera("db_recognition_vcam_test2", "n", -2).GetId();
		}

		TEST_METHOD(s1p02_add_rec) 
		{
			db_recognition_result dbrr;
			dbrr.addNewRecognitionResult(db_rec_emp_id1, db_rec_cam_id1);
			dbrr.addNewRecognitionResult(db_rec_emp_id1, db_rec_cam_id2);
		}

		TEST_METHOD(s1p03_add_error_emp) 
		{
			db_recognition_result dbrr;
			try {
				dbrr.addNewRecognitionResult(db_rec_emp_id1 * 3, db_rec_cam_id1);
			}
			catch (...) {
				return;
			}
			Assert::Fail();
		}

		TEST_METHOD(s1p04_add_error_cam)
		{
			try {
				db_recognition_result dbrr;
				dbrr.addNewRecognitionResult(db_rec_emp_id1, db_rec_cam_id1 * 3);
			}
			catch (...) {
				return;
			}
			Assert::Fail();
		}


		TEST_METHOD(s1p05_load_all) 
		{
			db_recognition_result dbrr;
			auto res = dbrr.GetRecognitionResult();
			if (res.size() < 1) {
				Assert::Fail();
			}
		}

		TEST_METHOD(s1p06_load_cam) 
		{
			db_recognition_result dbrr;
			auto res = dbrr.GetRecognitionResult(db_rec_cam_id1);
			Assert::AreNotEqual(0, (int)res.size());
		}

		TEST_METHOD(s1p07_load_cam_error) 
		{
			db_recognition_result dbrr;
			auto res = dbrr.GetRecognitionResult(db_rec_cam_id1 * 3);
			Assert::AreEqual(0, (int)res.size());
		}

		TEST_METHOD(s1p08_load_cam2) 
		{
			db_recognition_result dbrr;
			auto res = dbrr.GetRecognitionResult(db_rec_cam_id2);
			Assert::AreNotEqual(0, (int)res.size());
		}

		TEST_METHOD(s1p09_load_emp) 
		{
			db_recognition_result dbrr;
			auto res = dbrr.GetRecognitionResult(-100, db_rec_emp_id1);
			Assert::AreNotEqual(0, (int)res.size());
		}

		TEST_METHOD(s1p10_load_error_emp) 
		{
			db_recognition_result dbrr;
			auto res = dbrr.GetRecognitionResult(-100, db_rec_emp_id1 * 3);
			Assert::AreEqual(0, (int)res.size());
		}

		TEST_METHOD(s1p11_load_start_data) 
		{
			db_recognition_result dbrr;

			tm times;
			time_t tt1;

			memset(&times, 0, sizeof(times));

			times.tm_year = 2019 - 1900;
			times.tm_mon = 03;
			times.tm_mday = 1;
			times.tm_hour = 0;
			times.tm_min = 59;

			tt1 = mktime(&times);

			auto res = dbrr.GetRecognitionResult(-100, -100, tt1);
			if (res.size() < 1) {
				Assert::Fail();
			}
		}

		TEST_METHOD(s1p12_load_end_data) 
		{

			
				db_recognition_result dbrr;

				tm times;
				time_t tt1;

				memset(&times, 0, sizeof(times));

				times.tm_year = 2080 - 1900;
				times.tm_mon = 03;
				times.tm_mday = 1;
				times.tm_hour = 0;
				times.tm_min = 59;

				tt1 = mktime(&times);

				auto res = dbrr.GetRecognitionResult(-100, -100, -100, tt1);
				if (res.size() < 1) {
					Assert::Fail();
				}
		
		}

		TEST_METHOD(s1p99_delete_emp_camera) 
		{
			db_employee e(db_rec_emp_id1);
			e.Delete();
			db_vcam c(db_rec_cam_id1);
			c.Delete();
			db_vcam c2(db_rec_cam_id2);
			c2.Delete();
		}
						
	};
}