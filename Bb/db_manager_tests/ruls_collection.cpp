#include "pch.h"
#include "CppUnitTest.h"
#include "..//db/rules_collection.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace dbmanagertests
{
	TEST_CLASS(rules_collection_test)
	{
	public:

		TEST_METHOD_INITIALIZE(initialMethod)
		{
			// method initialization code
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", false);
		}

		//ѕопытка получить тестового сотрудника
		TEST_METHOD(create_empty)
		{
			rules_collection rulCol;

		}

		TEST_METHOD(load_premise) 
		{
			rules_collection rc;
			db_premise p(-11);
			rc.AppendRule(p);
		}

		TEST_METHOD(check_premise_full)
		{
			rules_collection rc;
			db_premise p(-11);
			rc.AppendRule(p);
			std::list<db_rule> lr =rc.GetAllRuleFull();
			Assert::AreEqual( -11, lr.front().GetId());
		}

		TEST_METHOD(check_premise_short)
		{
			rules_collection rc;
			db_premise p(-11);
			rc.AppendRule(p);
			auto lr = rc.GetAllRule();
			Assert::AreEqual(-11, lr[0].first);
		}

		TEST_METHOD(check_premise_parent)
		{
			rules_collection rc;
			db_premise p(-12);
			rc.AppendRule(p);
			auto lr = rc.GetAllRule();
			Assert::AreEqual((int)lr.size(), 2);
		}

		TEST_METHOD(check_camera_premise) 
		{
			rules_collection rc;
			db_vcam vcam(-10);
			rc.LoadAlRuleLinkCam(vcam);
			auto lr = rc.GetAllRuleFull();
			Assert::AreEqual(3, (int)lr.size());
		}
	};
}
