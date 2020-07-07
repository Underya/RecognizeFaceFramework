#include "pch.h"
#include "CppUnitTest.h"
#include "..//MessageServer/grPair.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace messagetest
{

	int grpair_rule1 = 10, grpair_rule2 = 11, grpair_rule3 = 12;
	int grpair_group1 = 20, grpair_group2 = 21, grpair_group3 = 22;

	//Тестирование кодирования и декадирования сообщений
	TEST_CLASS(grPair_test)
	{
	public:

		TEST_METHOD(create)
		{
			grPair pair;
		}

		TEST_METHOD(add_rule_one) 
		{
			grPair pair;
			pair.AddRule(grpair_rule1);
		}

		TEST_METHOD(check_rule_one) 
		{
			grPair pair;
			pair.AddRule(grpair_rule1);
			Assert::IsTrue(pair.HasRule(grpair_rule1));
		}

		TEST_METHOD(check_rule_one_error) 
		{
			grPair pair;
			pair.AddRule(grpair_rule1);
			Assert::IsFalse(pair.HasRule(grpair_rule2));
		}

		TEST_METHOD(check_rule_empty)
		{
			grPair pair;
			Assert::IsFalse(pair.HasRule(grpair_rule1));
		}

		TEST_METHOD(add_rule_two) 
		{
			grPair pair;
			pair.AddRule(grpair_rule1);
			pair.AddRule(grpair_rule2);
		}


		TEST_METHOD(check_rule_two_1)
		{
			grPair pair;
			pair.AddRule(grpair_rule1);
			pair.AddRule(grpair_rule2);
			Assert::IsTrue(pair.HasRule(grpair_rule1));
		}


		TEST_METHOD(check_rule_two_2)
		{
			grPair pair;
			pair.AddRule(grpair_rule1);
			pair.AddRule(grpair_rule2);
			Assert::IsTrue(pair.HasRule(grpair_rule2));
		}

		TEST_METHOD(check_rule_two_3_error)
		{
			grPair pair;
			pair.AddRule(grpair_rule1);
			pair.AddRule(grpair_rule2);
			Assert::IsFalse(pair.HasRule(grpair_rule3));
		}

		TEST_METHOD(add_all_rule) 
		{
			grPair pair;
			pair.AddRule(ALL_RULES_CODE);
		}

		TEST_METHOD(check_all_rule_method) 
		{
			grPair pair;
			pair.AddRule(ALL_RULES_CODE);
			Assert::IsTrue(pair.AnyRule());
		}

		TEST_METHOD(check_add_rule) 
		{
			grPair pair;
			pair.AddRule(ALL_RULES_CODE);
			Assert::IsTrue(pair.HasRule(grpair_rule1));
			Assert::IsTrue(pair.HasRule(grpair_rule2));
			Assert::IsTrue(pair.HasRule(grpair_rule3));
		}

		TEST_METHOD(check_add_rule_two)
		{
			grPair pair;
			pair.AddRule(grpair_rule1);
			pair.AddRule(grpair_rule2);
			pair.AddRule(ALL_RULES_CODE);
			Assert::IsTrue(pair.HasRule(grpair_rule1));
			Assert::IsTrue(pair.HasRule(grpair_rule2));
			Assert::IsTrue(pair.HasRule(grpair_rule3));
		}

		TEST_METHOD(add_group_one)
		{
			grPair pair;
			pair.AddGroup(grpair_group1);
		}

		TEST_METHOD(check_group_one)
		{
			grPair pair;
			pair.AddGroup(grpair_group1);
			Assert::IsTrue(pair.HasGroup(grpair_group1));
		}

		TEST_METHOD(check_group_one_error)
		{
			grPair pair;
			pair.AddGroup(grpair_group1);
			Assert::IsFalse(pair.HasGroup(grpair_group2));
		}

		TEST_METHOD(check_group_empty)
		{
			grPair pair;
			Assert::IsFalse(pair.HasGroup(grpair_group1));
		}

		TEST_METHOD(add_group_two)
		{
			grPair pair;
			pair.AddGroup(grpair_group1);
			pair.AddGroup(grpair_group2);
		}


		TEST_METHOD(check_group_two_1)
		{
			grPair pair;
			pair.AddGroup(grpair_group1);
			pair.AddGroup(grpair_group2);
			Assert::IsTrue(pair.HasGroup(grpair_group1));
		}


		TEST_METHOD(check_group_two_2)
		{
			grPair pair;
			pair.AddGroup(grpair_group1);
			pair.AddGroup(grpair_group2);
			Assert::IsTrue(pair.HasGroup(grpair_group2));
		}

		TEST_METHOD(check_group_two_3_error)
		{
			grPair pair;
			pair.AddGroup(grpair_group1);
			pair.AddGroup(grpair_group2);
			Assert::IsFalse(pair.HasGroup(grpair_group3));
		}

		TEST_METHOD(add_all_group)
		{
			grPair pair;
			pair.AddGroup(ALL_GROUP_CODE);
		}

		TEST_METHOD(check_all_group_method) 
		{
			grPair pair;
			pair.AddGroup(ALL_GROUP_CODE);
			Assert::IsTrue(pair.AnyGroup());
		}

		TEST_METHOD(check_add_group)
		{
			grPair pair;
			pair.AddGroup(ALL_GROUP_CODE);
			Assert::IsTrue(pair.HasGroup(grpair_group1));
			Assert::IsTrue(pair.HasGroup(grpair_group2));
			Assert::IsTrue(pair.HasGroup(grpair_group3));
		}

		TEST_METHOD(check_add_group_two)
		{
			grPair pair;
			pair.AddGroup(grpair_group1);
			pair.AddGroup(grpair_group2);
			pair.AddGroup(ALL_GROUP_CODE);
			Assert::IsTrue(pair.HasGroup(grpair_group1));
			Assert::IsTrue(pair.HasGroup(grpair_group2));
			Assert::IsTrue(pair.HasGroup(grpair_group3));
		}

		TEST_METHOD(add_rule_and_group_1) 
		{
			grPair pair;
			pair.AddGroup(grpair_group1);
			pair.AddRule(grpair_rule1);
			
		}

		TEST_METHOD(checK_rule_and_group_1_group) 
		{
			grPair pair;
			pair.AddGroup(grpair_group1);
			pair.AddRule(grpair_rule1);
			Assert::IsTrue(pair.HasGroup(grpair_group1));
		}

		TEST_METHOD(check_rule_and_group_1_rule)
		{
			grPair pair;
			pair.AddGroup(grpair_group1);
			pair.AddRule(grpair_rule1);
			Assert::IsTrue(pair.HasRule(grpair_rule1));
		}

		TEST_METHOD(add_rule_and_group_2) 
		{
			grPair pair;
			pair.AddGroup(grpair_group1);
			pair.AddGroup(grpair_group2);
			pair.AddRule(grpair_rule1);
			pair.AddRule(grpair_rule2);
		}

		TEST_METHOD(check_rule_and_group_2_rule)
		{
			grPair pair;
			pair.AddGroup(grpair_group1);
			pair.AddGroup(grpair_group2);
			pair.AddRule(grpair_rule1);
			pair.AddRule(grpair_rule2);
			Assert::IsTrue(pair.HasRule(grpair_rule1));
			Assert::IsTrue(pair.HasRule(grpair_rule2));
		}


		TEST_METHOD(check_rule_and_group_2_group)
		{
			grPair pair;
			pair.AddGroup(grpair_group1);
			pair.AddGroup(grpair_group2);
			pair.AddRule(grpair_rule1);
			pair.AddRule(grpair_rule2);
			Assert::IsTrue(pair.HasGroup(grpair_group1));
			Assert::IsTrue(pair.HasGroup(grpair_group2));
		}

		TEST_METHOD(check_rule_and_group_2_all) 
		{
			grPair pair;
			pair.AddGroup(grpair_group1);
			pair.AddGroup(grpair_group2);
			pair.AddRule(grpair_rule1);
			pair.AddRule(grpair_rule2);
			Assert::IsTrue(pair.HasGroup(grpair_group1));
			Assert::IsTrue(pair.HasGroup(grpair_group2));
			Assert::IsTrue(pair.HasRule(grpair_rule1));
			Assert::IsTrue(pair.HasRule(grpair_rule2));
		}
		
		TEST_METHOD(check_rule_and_group_2_group_error)
		{
			grPair pair;
			pair.AddGroup(grpair_group1);
			pair.AddGroup(grpair_group2);
			pair.AddRule(grpair_rule1);
			pair.AddRule(grpair_rule2);
			Assert::IsFalse(pair.HasGroup(grpair_group3));
		}


		TEST_METHOD(check_rule_and_group_2_rule_error)
		{
			grPair pair;
			pair.AddGroup(grpair_group1);
			pair.AddGroup(grpair_group2);
			pair.AddRule(grpair_rule1);
			pair.AddRule(grpair_rule2);
			Assert::IsFalse(pair.HasRule(grpair_rule3));
		}

		TEST_METHOD(check_all_rule) 
		{
			grPair pair;
			pair.AddRule(ALL_RULES_CODE);
			pair.AddGroup(ALL_GROUP_CODE);
			Assert::IsTrue(pair.HasGroup(grpair_group1));
			Assert::IsTrue(pair.HasGroup(grpair_group2));
			Assert::IsTrue(pair.HasGroup(grpair_group3));
			Assert::IsTrue(pair.HasRule(grpair_rule1));
			Assert::IsTrue(pair.HasRule(grpair_rule2));
			Assert::IsTrue(pair.HasRule(grpair_rule3));
		}

		TEST_METHOD(check_all_rule_add_groups) 
		{
			grPair pair;
			pair.AddGroup(grpair_group1);
			pair.AddGroup(grpair_group2);
			pair.AddRule(grpair_rule1);
			pair.AddRule(grpair_rule2);
			pair.AddRule(ALL_RULES_CODE);
			pair.AddGroup(ALL_GROUP_CODE);
			Assert::IsTrue(pair.HasGroup(grpair_group1));
			Assert::IsTrue(pair.HasGroup(grpair_group2));
			Assert::IsTrue(pair.HasGroup(grpair_group3));
			Assert::IsTrue(pair.HasRule(grpair_rule1));
			Assert::IsTrue(pair.HasRule(grpair_rule2));
			Assert::IsTrue(pair.HasRule(grpair_rule3));
		}

	};
}
