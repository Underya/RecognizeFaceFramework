#include "pch.h"
#include "CppUnitTest.h"
#include "..//db/db_premise.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace dbmanagertests
{
	int id_premise1 = -1, id_premise2 = -2;

	std::string prem_name1 = "premise_name1", prem_name2 = "premise_name2";


	TEST_CLASS(premise_test)
	{
	public:

		TEST_METHOD_INITIALIZE(initialMethod)
		{
			// method initialization code
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", false);
		}

		//ѕопытка получить тестового сотрудника
		TEST_METHOD(load_premise)
		{
			db_premise p(-2);
		}
		
		TEST_METHOD(check_name)
		{
			std::string name = "premise1", desc = "prem1";
			db_premise p(-2);
			Assert::AreEqual(p.GetName(), name);
		}

		TEST_METHOD(check_desc) 
		{
			std::string name = "premise1", desc = "prem1";
			db_premise p(-2);
			Assert::AreEqual(p.GetDesc(), desc);
		}

		TEST_METHOD(id_parrent)
		{
			db_premise p(-3);
			Assert::AreEqual(p.GetIdParent(), -2);
		}

		TEST_METHOD(parrent)
		{
			std::string name = "premise1", desc = "prem1";
			db_premise p(-3);
			std::vector<db_premise> v = p.GetAllParent();
			Assert::AreEqual(v[0].GetId(), -2);
		}

		TEST_METHOD(add_delet)
		{
			std::string name = "prem_test_1", desc = "desc_prem_1";
			db_premise pr = db_premise::AddNewPremise(name, desc);
			Assert::AreEqual(pr.GetName(), name);
			Assert::AreEqual(pr.GetDesc(), desc);
			int id = pr.GetId();
			db_premise pr2(id);
			Assert::AreEqual(pr2.GetName(), name);
			Assert::AreEqual(pr2.GetDesc(), desc);

			pr2.Delete();
			bool exec = false;
			try {
				db_premise p3(id);
			}
			catch (...) {
				exec = true;
			}

			if (!exec) {
				Assert::Fail();
			}
		}

		TEST_METHOD(add_premise) 
		{
			std::string name = "prem_test_2", desc = "desc_prem_2";
			db_premise new_pres = db_premise::AddNewPremise(name, desc, -3);
			std::vector<db_premise> l = new_pres.GetAllParent();
			new_pres.Delete();
			if (l.size() < 2)
				Assert::Fail();

		}

		TEST_METHOD(add_children) 
		{
			std::string name = "prem_test_3", desc = "desc_prem_3";
			db_premise new_pres = db_premise::AddNewPremise(name, desc);
			
			db_premise p2 = new_pres.AddNewChlidren("prem_test_4");
			std::vector<db_premise> l = p2.GetAllParent();

			Assert::AreEqual(l[0].GetName(), name);
			p2.Delete();
			new_pres.Delete();
		}

		TEST_METHOD(s1p01_add_premise) 
		{
			id_premise1 = db_premise::AddNewPremise(prem_name1).GetId();
			id_premise2 = db_premise::AddNewPremise(prem_name2).GetId();
		}

		TEST_METHOD(s1p02_check_null_premise) 
		{
			db_premise p1(id_premise1);
			Assert::AreEqual(-1, p1.GetIdParent());
			db_premise p2(id_premise2);
			Assert::AreEqual(-1, p2.GetIdParent());
		}

		TEST_METHOD(s1p03_set_parrenet_1) 
		{
			db_premise p1(id_premise1);
			db_premise p2(id_premise2);
			p1.SetParrent(p2.GetId());
		}

		TEST_METHOD(s1p04_check_parent) 
		{
			db_premise p1(id_premise1);
			Assert::AreEqual(id_premise2, p1.GetIdParent());
		}

		TEST_METHOD(s1p05_set_not_parrent) 
		{
			db_premise p1(id_premise1);
			p1.SetParrent(-1);
		}

		TEST_METHOD(s1p06_check_null_parent) 
		{
			db_premise p1(id_premise1);
			Assert::AreEqual(-1, p1.GetIdParent());
		}

		TEST_METHOD(s1p07_delete_premise) 
		{
			db_premise p1(id_premise1);
			db_premise p2(id_premise2);
			p1.Delete();
			p2.Delete();
		}

	};
}