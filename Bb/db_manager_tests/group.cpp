#include "pch.h"
#include "CppUnitTest.h"
#include "..//db/db_group.h"
#include "..//db/db_user.h"
#include "..//db/db_employee.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace dbmanagertests
{
	int db_group_id1 = -101, db_group_id2 = -102, db_group_id3 = -103;

	std::string db_group_name = "db_group_name_test", db_group_new_name = "db_group_name_test_name";
	std::string db_group_desc = "decription_test", db_group_new_desc = "db_group_new_description";

	std::string db_group_name2 = "db_group_name2", db_group_name3 = "db_group_name3";

	int db_group_id_user = -1;

	std::string db_group_user_name = "test_user_name";
	std::string db_group_user_desc = "";


	int db_group_emp1 = -2, db_group_emp2 = -3;

	std::string db_group_emp = "emp";

	TEST_CLASS(group_test)
	{
	public:

		TEST_METHOD_INITIALIZE(initialMethod)
		{
			// method initialization code
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", false);
		}

		TEST_METHOD(s1p01_create) 
		{
			db_group g = db_group::AddNewGroup(db_group_name, db_group_desc);
			db_group_id1 = g.GetId();
		}

		

		//ѕопытка получить тестового сотрудника
		TEST_METHOD(s1p02_load)
		{
			db_group g(db_group_id1);
		}

		TEST_METHOD(s1p03_check_name) 
		{
			db_group g(db_group_id1);
			Assert::AreEqual(db_group_name, g.GetName());
		}
		
		TEST_METHOD(s1p04_edit_name)
		{
			db_group g(db_group_id1);
			g.SetName(db_group_new_name);
		}


		TEST_METHOD(s1p05_check_edit) 
		{
			db_group g(db_group_id1);
			g.SetName(db_group_new_name);
			Assert::AreEqual(db_group_new_name, g.GetName());
		}

		TEST_METHOD(s1p06_check_desc) 
		{
			db_group g(db_group_id1);
			Assert::AreEqual(db_group_desc,g.GetDesc());
		}
		
		TEST_METHOD(s1p07_edit_desc) 
		{
			db_group g1(db_group_id1);
			g1.SetDescript(db_group_new_desc);
			Assert::AreEqual(db_group_new_desc, g1.GetDesc());
		}

		TEST_METHOD(s1p08_check_edit_desc) 
		{
			db_group g1(db_group_id1);
			Assert::AreEqual(db_group_new_desc, g1.GetDesc());
		}

		TEST_METHOD(s1p09_search_group) 
		{
			db_group::SerachGroup(db_group_new_name);
		}

		TEST_METHOD(s1p10_link_user) 
		{
			db_user user = db_user::AddNewUser(db_group_user_name, db_group_user_desc);
			user.LinkGroup(db_group_id1);
			db_group_id_user = user.GetId();
		}

		TEST_METHOD(s1p11_get_link) 
		{
			db_group::LoadedAllGroup(db_group_id_user);
		}

		TEST_METHOD(s1p12_check_link) 
		{
			db_group::LoadedAllGroup(db_group_id_user);
			std::vector<db_group> vec = db_group::GetAllGroup();
			db_group g = vec[0];
			Assert::AreEqual(db_group_id1, g.GetId());
		}

		TEST_METHOD(s1p13_link_3) 
		{
		   db_group_id2 = db_group::AddNewGroup(db_group_name2, "").GetId();
		   db_group_id3 = db_group::AddNewGroup(db_group_name3, "").GetId();
		   db_user *user = db_user::LoginToUser(db_group_user_name);
		   user->LinkGroup(db_group_id2);
		   user->LinkGroup(db_group_id3);
		}
		
		TEST_METHOD(s1p14_check_link) 
		{
			db_group::LoadedAllGroup(db_group_id_user);
			std::vector<db_group> vec = db_group::GetAllGroup();
			Assert::AreEqual(3, (int)vec.size());
		}

		TEST_METHOD(s1p15_unlink) 
		{
			db_user* user = db_user::LoginToUser(db_group_user_name);
			user->UnLinkGroup(db_group_id2);
			user->UnLinkGroup(db_group_id3);
		}

		TEST_METHOD(s1p16_check_link) 
		{
			db_group::LoadedAllGroup(db_group_id_user);
			std::vector<db_group> vec = db_group::GetAllGroup();
			Assert::AreEqual(1, (int)vec.size());
		}
		
		TEST_METHOD(s1p17_delete_new_group) 
		{
			db_group g2(db_group_id2);
			g2.Delete();
			db_group g3(db_group_id3);
			g3.Delete();
		}

		TEST_METHOD(s1p18_link_emp) 
		{
			db_group_emp1 = db_employee::AddNewEmployee(db_group_emp, db_group_emp, db_group_emp)->GetId();
			db_group_emp2 = db_employee::AddNewEmployee(db_group_emp, db_group_emp, db_group_emp)->GetId();
			db_group g(db_group_id1);
			g.SnapEmployee(db_group_emp1);
			g.SnapEmployee(db_group_emp2);
		}

		TEST_METHOD(s1p19_check_link_1) 
		{
			std::list<db_group> vec= db_group::GetSnapGoup(db_group_emp1);
			db_group g = vec.front();

			Assert::AreEqual(db_group_id1, g.GetId());
		}

		TEST_METHOD(s1p19_check_link_2)
		{
			std::list<db_group> vec = db_group::GetSnapGoup(db_group_emp2);
			db_group g = vec.front();

			Assert::AreEqual(db_group_id1, g.GetId());
		}

		TEST_METHOD(s1p20_check_get_link) 
		{
			db_group::LoadedAllGroup(db_group_id_user);
			std::list<db_group*> vec = db_group::GetLinkGroup(db_group_emp1);
			db_group *g = vec.front();

			Assert::AreEqual(db_group_id1, g->GetId());
		}

		TEST_METHOD(s1p21_check_load_all) 
		{
			std::vector<db_group> vec= db_group::GetAllGroupToDB();
			Assert::AreNotEqual(0, (int)vec.size());
		}

		TEST_METHOD(s1p22_create_erro_group) 
		{
			try {
				db_group g(-3);
			}
			catch (...) {
				return;
			}

			Assert::Fail();
		}


		TEST_METHOD(s1p97_delete_user) 
		{
			db_user::LoginToUser(db_group_user_name)->Delete();
		}

		TEST_METHOD(s1p98_delete)
		{
			db_group g(db_group_id1);
			g.Delete();
		}

		TEST_METHOD(s1p99_check_delete)
		{
			try {
				db_group g(db_group_id1);
			}
			catch (...) {
				return;
			}

			Assert::Fail();
		}
		
	};
}
