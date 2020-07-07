#include "pch.h"
#include "CppUnitTest.h"
#include "..//db/db_user.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace dbmanagertests
{
	TEST_CLASS(user_test)
	{
	public:

		TEST_METHOD_INITIALIZE(initialMethod)
		{
			// method initialization code
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", false);
		}

		//ѕопытка получить тестового сотрудника
		TEST_METHOD(authoris)
		{
			std::string name = "test_user";
			db_user user = *db_user::LoginToUser(name);
		}

		TEST_METHOD(check_name)
		{
			std::string name = "test_user";
			db_user user = *db_user::LoginToUser(name);
			Assert::AreEqual(user.GetName(), name);
		}

		TEST_METHOD(check_id)
		{
			std::string name = "test_user";
			int id = -2;
			db_user user = *db_user::LoginToUser(name);
			Assert::AreEqual(id, user.GetId());
		}

		TEST_METHOD(check_desc)
		{
			std::string name = "test_user", desc = "descript_test";
			int id = -2;
			db_user user = *db_user::LoginToUser(name);
			Assert::AreEqual(desc, user.GetDescription());
		}

		TEST_METHOD(s1p1_edit_name)
		{
			std::string name = "test_user", desc = "descript_test";
			std::string nname = "new_test_user", ndesc = "new_descript_test";
			db_user user = *db_user::LoginToUser(name);
			user.SetName(nname);
			Assert::AreEqual(nname, user.GetName());
		}

		TEST_METHOD(s1p2_check_edit_name) 
		{
			std::string name = "test_user", desc = "descript_test";
			std::string nname = "new_test_user", ndesc = "new_descript_test";
			db_user user = *db_user::LoginToUser(nname);
			Assert::AreEqual(nname, user.GetName());
		}


		TEST_METHOD(s1p3_edit_description)
		{
			std::string name = "test_user", desc = "descript_test";
			std::string nname = "new_test_user", ndesc = "new_descript_test";
			db_user user = *db_user::LoginToUser(nname);
			user.SetDescription(ndesc);
			Assert::AreEqual(ndesc, user.GetDescription());
		}

		TEST_METHOD(s1p4_check_edit_description)
		{
			std::string name = "test_user", desc = "descript_test";
			std::string nname = "new_test_user", ndesc = "new_descript_test";
			db_user user = *db_user::LoginToUser(nname);
			Assert::AreEqual(ndesc, user.GetDescription());
		}

		TEST_METHOD(s1p5_return) 
		{
			std::string name = "test_user", desc = "descript_test";
			std::string nname = "new_test_user", ndesc = "new_descript_test";
			db_user user = *db_user::LoginToUser(nname);
			user.SetName(name);
			user.SetDescription(desc);
			Assert::AreEqual(desc, user.GetDescription());
			Assert::AreEqual(name, user.GetName());
		}

		TEST_METHOD(s1p6_check_return)
		{
			std::string name = "test_user", desc = "descript_test";
			db_user user = *db_user::LoginToUser(name);
			Assert::AreEqual(desc, user.GetDescription());
			Assert::AreEqual(name, user.GetName());
		}

		TEST_METHOD(wrong_user) 
		{
			std::string wrong_name = "very very vrong name";
			bool exec = false;

			try {
				db_user user = *db_user::LoginToUser(wrong_name);
			}
			catch (...) {
				exec = true;
			}

			if (!exec) {
				Assert::Fail();
			}

		}
	};
}