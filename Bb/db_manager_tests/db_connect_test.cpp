#include "pch.h"
#include "CppUnitTest.h"
#include "..//db/db_connect.h"
#include "..//db/db_group.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace dbmanagertests
{
	int db_connect_add_res = -1;

	TEST_CLASS(db_connect_test)
	{
	public:

		//Успешное соеденение
		TEST_METHOD(SetConnect)
		{
			try {
				db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", false);
				db_connect c;
			}
			catch (...) {
				Assert::Fail();
			}

		}

		TEST_METHOD(show_true) 
		{
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", true);
		}


		TEST_METHOD(create_connect) 
		{
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", true);
			db_connect connect;
		}

		TEST_METHOD(edit_info) 
		{
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", true);
			db_connect c;
			c.SetInfo(true);
			
		}
			
		TEST_METHOD(get_all_info_for_table) 
		{
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", true);
			db_connect c;
			c.GetAllRowTable2("camera");
		}

		TEST_METHOD(check_all_info_for_table) 
		{
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", true);
			db_connect c;
			PGresult* res = c.GetAllRowTable2("camera");
			Assert::IsNotNull(res);
		}

		TEST_METHOD(error_check_all_info_for_table) 
		{
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", true);
			db_connect c;
			try {
				PGresult* res = c.GetAllRowTable2("camerarasdawd");
			}
			catch (...) {
				return;
			}
			Assert::Fail();
		}

		TEST_METHOD(get_row_by_id) 
		{
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", true);
			db_connect c;
			c.GetOneRowById("employee", - 1);
		}

		TEST_METHOD(check_row_by_id) 
		{
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", true);
			db_connect c;
			PGresult *res = c.GetOneRowById("employee", -1);
			Assert::IsNotNull(res);
		}

		TEST_METHOD(error_row_by_id) 
		{
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", true);
			db_connect c;
			try {
				PGresult* res = c.GetOneRowById("employeeeeeeeee", -1);
			}
			catch (...) {
				return;
			}
			Assert::Fail();
		}

		TEST_METHOD(get_row_with_query) 
		{
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", true);
			db_connect c;
			c.GetRowWithQuerry("select * from camera");
		}

		TEST_METHOD(check_row_with_query) 
		{
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", true);
			db_connect c;
			PGresult *res= c.GetRowWithQuerry("select * from camera");
			Assert::IsNotNull(res);
		}

		TEST_METHOD(error_row_in_query) 
		{
			try {
				db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", true);
				db_connect c;
				PGresult* res = c.GetRowWithQuerry("selectdwa * from cameradadadwa");
			} catch(...) {
				return;
			}

			Assert::Fail();
		}

		TEST_METHOD(caller_meth_in_row_in_query) 
		{
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", true);
			db_connect c;
			PGresult* res = c.GetRowWithQuerry("select loginuser('users')");
			char *res_v = PQgetvalue(res, 0, 0);
			char* true_result = "-1";
			std::string a = true_result;
			std::string b = res_v;
			Assert::AreEqual(a, b);
		}

		TEST_METHOD(called_error_method) 
		{
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", true);
			db_connect c;
			try {
				c.GetRowWithQuerry("select unrealFunction('dad')");
			}
			catch (...) {
				return;
			}
			Assert::Fail();
		}

		TEST_METHOD(execute_proc_funct) 
		{
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", true);
			db_connect c;
			std::list<std::string> s = { "127.0.0.1" };
			c.ExecuteProcedure("loginuser", &s);
		}

		TEST_METHOD(execute_error_func) 
		{
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", true);
			db_connect c;
			std::list<std::string> s = { "127.0.0.1" };
			try {
				c.ExecuteProcedure("loginuserdawdawd", &s);
			}
			catch (...) {
				return;
			}
			Assert::Fail();
		}

		TEST_METHOD(s1p1_add_func) 
		{
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", true);
			db_connect c;
			std::list<std::string> list = { "db_connect_test_name", "db_connect_test_desc" };
			db_connect_add_res = c.ExecuteAddProcedure("addgroup", &list);
		}

		TEST_METHOD(s1p2_add_check) 
		{
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", true);
			db_connect c;
			db_group g(db_connect_add_res);
		}

		TEST_METHOD(s1p3_delete_exec) 
		{
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", true);
			db_connect c;
			std::list<std::string> list = { std::to_string(db_connect_add_res) };
			c.ExecuteProcedure("deletegroup", &list);
		}

		TEST_METHOD(s1p4_check_delete) 
		{
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", true);
			try {
				db_group g(db_connect_add_res);
			}
			catch (...) {
				return;
			}

			Assert::Fail();
		}

		TEST_METHOD(error_add_func) 
		{
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", true);
			db_connect c;
			std::list<std::string> list = { "db_connect_test_name", "db_connect_test_desc" };
			try {
				db_connect_add_res = c.ExecuteAddProcedure("addbcdefgroup", &list);
			}
			catch (...) {
				return;
			}

			Assert::Fail();
		}

		//Попытка вызвать не успешное соеденнеие
		TEST_METHOD(SetNotSucccessConnect) 
		{
			//Было ли исключение
			bool execpt = false;
			try {
				//Указание в качестве данных не правильных данных
				db_connect::SetInfoConnect("localhost", "5432", "", "", "postgres", false);
				//Подключение с данными
				db_connect c;
			}
			catch (...) {
				//Указать, что было вызвано исключение
				execpt = true;
			}

			if (!execpt) {
				//Если не было искилючения, выбросить ошибку
				Assert::Fail();
			}
		}

	};
}
