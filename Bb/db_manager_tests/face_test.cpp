#include "pch.h"
#include "CppUnitTest.h"
#include "..//db/db_face.h"
#include "..//db/db_employee.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace dbmanagertests
{
	int face_emp1 = -1, face_emp2 = -2;
	int face_id1 = -3, face_id2 = -4;



	TEST_CLASS(face_test)
	{
	public:

		TEST_METHOD_INITIALIZE(initialMethod)
		{
			// method initialization code
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", false);
		}
		
		TEST_METHOD(s1p01_create_emp) 
		{
			face_emp1 = db_employee::AddNewEmployee("face_f", "face_l", "face_m")->GetId();
		}

		TEST_METHOD(s1p02_create_face) 
		{
			float* desc = new float[128]();
			for (int i = 0; i < 128; i++) desc[i] = 0;
			db_face new_face = *db_face::AddNewFace(desc, face_emp1);
			face_id1 = new_face.GetId();
		}

		TEST_METHOD(s1p03_crete_fail_emp) 
		{
			float* desc = new float[128]();
			for (int i = 0; i < 128; i++) desc[i] = 0;
			try {
				db_face new_face = *db_face::AddNewFace(desc, -10);
			}
			catch (...) {
				return;
			}
			Assert::Fail();
		}

		TEST_METHOD(s1p04_load_face) 
		{
			db_face face(face_id1);
		}

		TEST_METHOD(s1p05_error_load)
		{
			try {
				db_face face(-10);
			}
			catch (...) {
				return;
			}
			Assert::Fail();
		}

		TEST_METHOD(s1p06_check_emp) 
		{
			db_face face(face_id1);
			Assert::AreEqual(face_emp1, face.GetIdEmployee());
		}

		TEST_METHOD(s1p07_check_desc) 
		{
			db_face face(face_id1);
			float* desc = face.GetDescriptor();
			for (int i = 0; i < 128; i++) {
				if (desc[i] != 0) Assert::Fail();
			}
		}


		TEST_METHOD(s1p08_desc_size) 
		{
			db_face f(face_id1);
			Assert::AreEqual(f.GetDescriptorSize(), 128);
		}

		TEST_METHOD(s1p09_search) 
		{
			float* desc = new float[128]();
			for (int i = 0; i < 128; i++) desc[i] = 0;
			int id_e = db_face::SearchFace(desc);
			Assert::AreEqual(face_emp1, id_e);
		}

		TEST_METHOD(s1p10_not_exec_search) 
		{
			float* desc = new float[128]();
			for (int i = 0; i < 128; i++) desc[i] = 1 + i;
			int id_e = db_face::SearchFace(desc);
			Assert::AreEqual(-1, id_e);
		}

		TEST_METHOD(s1p11_search_str)
		{
			std::string s = "";
			for (int i = 0; i < 128; i++) s += std::to_string(0) + " ";
			int id_r = db_face::SearchFace(s);
			Assert::AreEqual(face_emp1, id_r);
		}

		TEST_METHOD(s1p12_search_error) 
		{
			std::string s = "";
			for (int i = 0; i < 128; i++) s += std::to_string(i + 2) + " ";
			int id_r = db_face::SearchFace(s);
			Assert::AreEqual(-1, id_r);
		}

		TEST_METHOD(s1p13_add_2_to_emp) 
		{
			float* desc = new float[128]();
			for (int i = 0; i < 128; i++) desc[i] = 1;
			db_face new_face = *db_face::AddNewFace(desc, face_emp1);
			face_id2 = new_face.GetId();

		}

		TEST_METHOD(s1p14_search_1) 
		{
			float* desc = new float[128]();
			for (int i = 0; i < 128; i++) desc[i] = 0;
			int id_e = db_face::SearchFace(desc);
			Assert::AreEqual(face_emp1, id_e);
		}

		TEST_METHOD(s1p15_search_2) 
		{
			float* desc = new float[128]();
			for (int i = 0; i < 128; i++) desc[i] = 1;
			int id_e = db_face::SearchFace(desc);
			Assert::AreEqual(face_emp1, id_e);
		}

		TEST_METHOD(s1p91_delet_face) 
		{
			db_face f1(face_id1);
			f1.Delete();
			db_face f2(face_id2);
			f2.Delete();
		}

		TEST_METHOD(s1p92_check_delet1) 
		{
			try {
				db_face f1(face_id1);
			}
			catch (...) {
				return;
			}

			Assert::Fail();
		}

		TEST_METHOD(s1p92_check_delet2)
		{
			try {
				db_face f1(face_id2);
			}
			catch (...) {
				return;
			}

			Assert::Fail();
		}
		
		TEST_METHOD(s1p93_delete_emp) 
		{
			db_employee emp(face_emp1);
			emp.Delete();
		}

	};
}
