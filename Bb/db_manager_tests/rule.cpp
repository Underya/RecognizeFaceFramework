#include "pch.h"
#include "CppUnitTest.h"
#include "..//db/db_rule.h"
#include "..//db/rules_collection.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace dbmanagertests
{
	TEST_CLASS(rule_test)
	{
	public:

		TEST_METHOD_INITIALIZE(initialMethod)
		{
			// method initialization code
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", false);
		}

		//ѕопытка получить тестового сотрудника
		TEST_METHOD(load_rule)
		{
			db_rule r(-3);
			db_rule r2(-4);
		}

		TEST_METHOD(check_id)
		{
			int id = -3;
			db_rule r(id);
			Assert::AreEqual(r.GetId(), id);
		}


		TEST_METHOD(check_name)
		{
			std::string name = "rule1", desc = "desc_rule1";
			db_rule r(-3);
			Assert::AreEqual(r.GetName(), name);
		}

		TEST_METHOD(check_desc)
		{
			std::string name = "rule1", desc = "desc_rule1";
			db_rule r(-3);
			Assert::AreEqual(r.GetDesc(), desc);
		}

		TEST_METHOD(s1p1_edit_name)
		{
			std::string name = "rule1", desc = "desc_rule1", n_name = "rule11";
			db_rule r(-3);
			r.SetName(n_name);
		}

		TEST_METHOD(s1p2_check_edit_name)
		{
			std::string name = "rule1", desc = "desc_rule1", n_name = "rule11";
			db_rule r(-3);
			Assert::AreEqual(r.GetName(), n_name);
			r.SetName(name);
		}

		TEST_METHOD(s1p3_edit_desc)
		{
			std::string name = "rule1", desc = "desc_rule1", n_name = "rule11", n_desc = "desc_desc_rules";
			db_rule r(-3);
			r.SetDesc(n_desc);
		}

		TEST_METHOD(s1p4_check_edit_desc)
		{
			std::string name = "rule1", desc = "desc_rule1", n_name = "rule11", n_desc = "desc_desc_rules";
			db_rule r(-3);
			Assert::AreEqual(n_desc, r.GetDesc());
			r.SetDesc(desc);
		}

		TEST_METHOD(add_delete)
		{
			std::string t = "name1_test", b = "desc_test";
			db_rule r = db_rule::AddNewRule(t, b);
			int id = r.GetId();

			Assert::AreEqual(r.GetName(), t);
			Assert::AreEqual(r.GetDesc(), b);

			db_rule r2 = db_rule(id);
			Assert::AreEqual(r2.GetName(), t);
			Assert::AreEqual(r2.GetDesc(), b);

			r2.Delete();

			bool exec = false;
			try {
				db_rule r3 = db_rule(id);
			}
			catch (...) {
				exec = true;
			}

			if (!exec) {
				Assert::Fail();
			}
		}

		TEST_METHOD(s2p1_link_rule)
		{
			db_rule r = db_rule::AddNewRule("rule_test_l", "");
			int id = r.GetId();
			db_premise p(-2);
			r.LinkedWithRule(p, r);

			rules_collection rc;
			rc.AppendRule(p);
			db_rule rules(-4);
			auto list = rc.GetAllRuleFull();
			for (auto iter = list.begin(); iter != list.end(); iter++) {
				if (iter->GetName() == "rule_test_l") {
					rules = *iter;
					break;
				}
			}
			Assert::AreEqual(id, rules.GetId());
		}

		TEST_METHOD(s2p2_unlink_rule)
		{
			db_premise p(-2);
			rules_collection rc;
			rc.AppendRule(p);

			rc.GetAllRuleFull().front().Delete();
			rules_collection rc2;
			Assert::AreEqual((int)rc2.GetAllRuleFull().size(), 0);
		}
	};
}