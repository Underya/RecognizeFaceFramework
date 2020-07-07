#include "pch.h"
#include "CppUnitTest.h"
#include "..//face_recognition/face.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;



namespace recognitiontest
{
	TEST_CLASS(face_test)
	{
	public:

		TEST_METHOD(create)
		{
			int id = 10;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			face ei(id, name, famyli, mid_name, dbdesc);
		}


		TEST_METHOD(check_id)
		{
			int id = 10;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			face ei(id, name, famyli, mid_name, dbdesc);
			Assert::AreEqual(id, ei.GetId());
		}

		TEST_METHOD(check_first_name)
		{
			int id = 10;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			face ei(id, name, famyli, mid_name, dbdesc);
			Assert::AreEqual(name, ei.GetFirstName());
		}

		TEST_METHOD(check_last_name)
		{
			int id = 10;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			face ei(id, name, famyli, mid_name, dbdesc);
			Assert::AreEqual(famyli, ei.GetLastName());
		}

		TEST_METHOD(check_mid_name)
		{
			int id = 10;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			face ei(id, name, famyli, mid_name, dbdesc);
			Assert::AreEqual(dbdesc, ei.GetDBDescriptor());
		}


		TEST_METHOD(check_db_desc)
		{
			int id = 10;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			face ei(id, name, famyli, mid_name, dbdesc);
			Assert::AreEqual(mid_name, ei.GetMidName());
		}

		TEST_METHOD(set_other_id)
		{
			int id = 10, other_id = 12;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			face ei(id, name, famyli, mid_name, dbdesc);
			ei.SetOtherId(other_id);
		}

		TEST_METHOD(edit_id)
		{
			int id = 10;
			int nid = 11;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			face ei(id, name, famyli, mid_name, dbdesc);
			ei.SetId(nid);
			Assert::AreEqual(nid, ei.GetId());
		}


		TEST_METHOD(edit_name)
		{
			int id = 10;
			int nid = 11;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			string nname = "name", nfamyli = "famyli", nmid_name = "otechestvo", ndbdesc = "";
			face ei(id, name, famyli, mid_name, dbdesc);
			ei.SetFisrtName(nname);
			Assert::AreEqual(nname, ei.GetFirstName());
		}


		TEST_METHOD(edit_last_name)
		{
			int id = 10;
			int nid = 11;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			string nname = "name", nfamyli = "famyli", nmid_name = "otechestvo", ndbdesc = "";
			face ei(id, name, famyli, mid_name, dbdesc);
			ei.SetLastName(nfamyli);
			Assert::AreEqual(nfamyli, ei.GetLastName());
		}

		TEST_METHOD(edit_mid_name)
		{
			int id = 10;
			int nid = 11;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			string nname = "name", nfamyli = "famyli", nmid_name = "otechestvo", ndbdesc = "";
			face ei(id, name, famyli, mid_name, dbdesc);
			ei.SetMidName(nmid_name);
			Assert::AreEqual(nmid_name, ei.GetMidName());
		}

		TEST_METHOD(edit_db_desc)
		{
			int id = 10;
			int nid = 11;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			string nname = "name", nfamyli = "famyli", nmid_name = "otechestvo", ndbdesc = "";
			face ei(id, name, famyli, mid_name, dbdesc);
			ei.SetDBDescriptor(ndbdesc);
			Assert::AreEqual(ndbdesc, ei.GetDBDescriptor());
		}

		TEST_METHOD(edit_other_id)
		{
			int id = 10, oid = 101;
			int nid = 11, noid = 111;;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			face ei(id, name, famyli, mid_name, dbdesc);
			ei.SetOtherId(oid);
			ei.SetOtherId(noid);
			Assert::AreEqual(noid, ei.GetOtherId());
		}

		TEST_METHOD(s1e1_add_desc) 
		{
			//Инициализация матрицы для проверки
			face_matrix m(128, 1);
			for (auto iter = m.begin(); iter != m.end(); iter++) {
				*iter = 0;
			}

			int id = 10;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			face ei(id, name, famyli, mid_name, dbdesc);
			ei.AddNewDescript(m);
		}

		TEST_METHOD(s1e2_check_count_desc) {
			face_matrix m(128, 1), m2(128, 1);
			for (auto iter = m.begin(); iter != m.end(); iter++) {
				*iter = 0;
			}
			for (auto iter = m2.begin(); iter != m2.end(); iter++) {
				*iter = 1;
			}

			int id = 10;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			face ei(id, name, famyli, mid_name, dbdesc);
			ei.AddNewDescript(m);
			ei.AddNewDescript(m2);
			Assert::AreEqual(2, ei.GetDescriptorCount());
		}

		TEST_METHOD(s1e3_check_string_desc)
		{
			face_matrix m(128, 1), m2(128, 1);
			for (auto iter = m.begin(); iter != m.end(); iter++) {
				*iter = 0;
			}
			for (auto iter = m2.begin(); iter != m2.end(); iter++) {
				*iter = 1;
			}

			//Получение матриц в виде строки
			string sm1 = "", sm2 = "";
			for (auto iter = m.begin(); iter != m.end(); iter++) {
				sm1 += std::to_string(*iter) + " ";
			}
			for (auto iter = m2.begin(); iter != m2.end(); iter++) {
				sm2 += std::to_string(*iter) + " ";
			}


			int id = 10;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			face ei(id, name, famyli, mid_name, dbdesc);
			ei.AddNewDescript(m);
			ei.AddNewDescript(m2);
			std::vector<string> matrixs =  ei.GetAllDescriptor();
			Assert::AreEqual(sm1, matrixs[0]);
			Assert::AreEqual(sm2, matrixs[1]);
		}

		TEST_METHOD(s1e4_check_str_i)
		{
			face_matrix m(128, 1), m2(128, 1);
			for (auto iter = m.begin(); iter != m.end(); iter++) {
				*iter = 0;
			}
			for (auto iter = m2.begin(); iter != m2.end(); iter++) {
				*iter = 1;
			}

			//Получение матриц в виде строки
			string sm1 = "", sm2 = "";
			for (auto iter = m.begin(); iter != m.end(); iter++) {
				sm1 += std::to_string(*iter) + " ";
			}
			for (auto iter = m2.begin(); iter != m2.end(); iter++) {
				sm2 += std::to_string(*iter) + " ";
			}


			int id = 10;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			face ei(id, name, famyli, mid_name, dbdesc);
			ei.AddNewDescript(m);
			ei.AddNewDescript(m2);
			Assert::AreEqual(sm1, ei.GetDescriptor(0));
			Assert::AreEqual(sm2, ei.GetDescriptor(1));
			
		}

		TEST_METHOD(s1e5_check_matrix_i)
		{
			face_matrix m(128, 1), m2(128, 1);
			for (auto iter = m.begin(); iter != m.end(); iter++) {
				*iter = 0;
			}
			for (auto iter = m2.begin(); iter != m2.end(); iter++) {
				*iter = 1;
			}

			int id = 10;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			face ei(id, name, famyli, mid_name, dbdesc);
			ei.AddNewDescript(m);
			ei.AddNewDescript(m2);
			//Assert::AreEqual(m, ei.GetMatrixDescriptor(0));
			//Assert::AreEqual(m2, ei.GetMatrixDescriptor(1));
			face_matrix rm(128, 1), rm2(128, 1);
			rm = ei.GetMatrixDescriptor(0);
			rm2 = ei.GetMatrixDescriptor(1);

			//Проверка первой матрицы через итераторы
			auto main_m = m.begin();
			auto ret_m = rm.begin();

			auto main_m2 = m.begin();
			auto ret_m2 = rm.begin();

			for (int i = 0; i < 128; i++) {
				Assert::AreEqual(*main_m, *ret_m);
				main_m++;
				ret_m++;

				Assert::AreEqual(*main_m2, *ret_m2);
				main_m2++;
				ret_m2++;
			}
		}

		TEST_METHOD(s1e6_check_float_i) 
		{
			float *fm = new float[128], *fm2 = new float[128];
			for(int i = 0; i < 128; i++){
				fm[i] = 0;
				fm2[i] = 1;
			}

			face_matrix m(128, 1), m2(128, 1);
			for (auto iter = m.begin(); iter != m.end(); iter++) {
				*iter = 0;
			}
			for (auto iter = m2.begin(); iter != m2.end(); iter++) {
				*iter = 1;
			}

			int id = 10;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			face ei(id, name, famyli, mid_name, dbdesc);
			ei.AddNewDescript(m);
			ei.AddNewDescript(m2);
			float* retf = ei.GetFloatDescript(0);
			float* retf2 = ei.GetFloatDescript(1);
			for (int i = 0; i < 128; i++) {
				Assert::AreEqual(fm[i], retf[i]);
				Assert::AreEqual(fm2[i], retf2[i]);
			}

			delete[128]fm;
			delete[128]fm2;
			delete[128]retf;
			delete[128]retf2;
		}

		TEST_METHOD(s1e7_get_dist_0)
		{
			face_matrix m(128, 1), m2(128, 1);
			for (auto iter = m.begin(); iter != m.end(); iter++) {
				*iter = 0;
			}
			for (auto iter = m2.begin(); iter != m2.end(); iter++) {
				*iter = 1;
			}

			int id = 10;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			face ei(id, name, famyli, mid_name, dbdesc);
			ei.AddNewDescript(m);
			ei.AddNewDescript(m2);
			
			int dist = 0;
			int real_dist = ei.GetDistance(m);
			Assert::AreEqual(dist, real_dist);
		}

		TEST_METHOD(s1e7_get_dist_1)
		{
			face_matrix m(128, 1), m2(128, 1);
			for (auto iter = m.begin(); iter != m.end(); iter++) {
				*iter = 0;
			}
			for (auto iter = m2.begin(); iter != m2.end(); iter++) {
				*iter = 1;
			}

			int id = 10;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			face ei(id, name, famyli, mid_name, dbdesc);
			ei.AddNewDescript(m);
			ei.AddNewDescript(m2);

			int dist = 0;
			int real_dist = ei.GetDistance(m2);
			Assert::AreEqual(dist, real_dist);
		}


		TEST_METHOD(s1e8_get_dist_0_vs_1)
		{
			face_matrix m(128, 1), m2(128, 1);
			for (auto iter = m.begin(); iter != m.end(); iter++) {
				*iter = 0;
			}
			for (auto iter = m2.begin(); iter != m2.end(); iter++) {
				*iter = 1;
			}

			int id = 10;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			face ei(id, name, famyli, mid_name, dbdesc);
			//ei.AddNewDescript(m);
			ei.AddNewDescript(m2);

			int dist = 0;
			int real_dist = ei.GetDistance(m);
			Assert::AreNotEqual(dist, real_dist);
		}

		TEST_METHOD(s1e8_get_dist_1_vs_0)
		{
			face_matrix m(128, 1), m2(128, 1);
			for (auto iter = m.begin(); iter != m.end(); iter++) {
				*iter = 0;
			}
			for (auto iter = m2.begin(); iter != m2.end(); iter++) {
				*iter = 1;
			}

			int id = 10;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			face ei(id, name, famyli, mid_name, dbdesc);
			ei.AddNewDescript(m);
			//ei.AddNewDescript(m2);

			int dist = 0;
			int real_dist = ei.GetDistance(m2);
			Assert::AreNotEqual(dist, real_dist);
		}

		TEST_METHOD(get_desc_error_str)
		{
			bool exec = false;
			int id = 10;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			
			try {
				face ei(id, name, famyli, mid_name, dbdesc);
				ei.GetDescriptor(0);
			}
			catch (...) {
				exec = true;
			}

			Assert::AreEqual(true, exec);
		}

		TEST_METHOD(get_desc_error_matrix)
		{
			bool exec = false;
			int id = 10;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";

			try {
				face ei(id, name, famyli, mid_name, dbdesc);
				ei.GetMatrixDescriptor(0);
			}
			catch (...) {
				exec = true;
			}

			Assert::AreEqual(true, exec);
		}

		TEST_METHOD(get_desc_error_float)
		{
			bool exec = false;
			int id = 10;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";

			try {
				face ei(id, name, famyli, mid_name, dbdesc);
				ei.GetFloatDescript(0);
			}
			catch (...) {
				exec = true;
			}

			Assert::AreEqual(true, exec);
		}


		TEST_METHOD(add_photo)
		{
			face f(-2, "1", "2", "1");
			f.AddNewPhoto("test.jpg");
		}

		TEST_METHOD(add_photo_2_face)
		{
			bool exec = false;

			try {
				face f(-2, "1", "2", "1");
				f.AddNewPhoto("test2_2.jpg");
			}
			catch (...) {
				exec = true;
			}

			Assert::AreEqual(true, exec);
		}

	};
}