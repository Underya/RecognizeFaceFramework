#include "pch.h"
#include "CppUnitTest.h"
#include "..//MessageServer/Message.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace messagetest
{
	int message_id_emp1 = 1, message_id_emp2 = 2;

	std::string message_first_name1 = "name_emp1", message_first_name2 = "name_emp2";

	std::string message_last_name1 = "last_name_emp1", message_last_name2 = "last_name_emp2";

	std::string message_mid_name1 = "mid_name_emp1", message_mid_name2 = "mid_name_emp2";

	std::string message_add_info1 = "message_add_info1", message_add_info2 = "message_add_info2";

	int message_id_group1 = 3, message_id_group2 = 4, message_id_group3 = 5;
	std::string message_name_group1 = "name_group_test1", message_name_group2 = "name_group_test2", message_name_group3 = "name_group_test3";

	int message_id_rule1 = 6, message_id_rule2 = 7, message_id_rule3 = 8;
	std::string message_name_rule1 = "name_rule_test1", message_name_rule2 = "name_group_rule2", message_name_rule3 = "name_rule_test3";

	typedef std::vector<std::pair<int, std::string>> list_info;

	std::string message_premise1 = "premise_name1", message_premise2 = "premise_name2", message_premise3 = "premise_name3";

	TEST_CLASS(messages_create_test)
	{
	public:

		TEST_METHOD(create) 
		{
			Message mess;
		}

		TEST_METHOD(set_id_emp) 
		{
			Message mess;
			mess.SetIdEmployee(message_id_emp1);
		}
		
		TEST_METHOD(get_id_emp) 
		{
			Message mess;
			mess.SetIdEmployee(message_id_emp1);
			Assert::AreEqual(message_id_emp1, mess.GetId());
		}

		TEST_METHOD(set_f_name) 
		{
			Message mess;
			mess.SetFirstName(message_first_name1);
		}

		TEST_METHOD(get_f_name) 
		{
			Message mess;
			mess.SetFirstName(message_first_name1);
			Assert::AreEqual(message_first_name1, mess.GetFirstName());
		}

		TEST_METHOD(set_l_name) 
		{
			Message mess;
			mess.SetLastName(message_last_name1);
		}

		TEST_METHOD(get_l_name) 
		{
			Message mess;
			mess.SetLastName(message_last_name1);
			Assert::AreEqual(message_last_name1, mess.GetLastName());
		}

		TEST_METHOD(set_m_name) 
		{
			Message mess;
			mess.SetMidName(message_mid_name1);
		}

		TEST_METHOD(get_m_name) 
		{
			Message mess;
			mess.SetMidName(message_mid_name1);
			Assert::AreEqual(message_mid_name1, mess.GetMidName());
		}
		
		TEST_METHOD(add_info) 
		{
			Message mess;
			mess.AddInfo(message_add_info1);
		}

		TEST_METHOD(check_add_info) 
		{
			Message mess;
			mess.AddInfo(message_add_info1);
			Assert::AreEqual(message_add_info1, mess.GetInfo());
		}

		TEST_METHOD(set_time) 
		{
			tm time;
			memset(&time, 0, sizeof(tm));
			time.tm_year = 2020-1900;
			time.tm_mon = 4;
			time.tm_mday = 19;
			time.tm_hour = 12;
			time.tm_min = 23;

			time_t set_time;
			set_time = mktime(&time);
			Message mess;
			mess.SetTime(set_time);
		}

		TEST_METHOD(get_time) 
		{
			tm time;
			memset(&time, 0, sizeof(tm));
			time.tm_year = 2020 - 1900;
			time.tm_mon = 4;
			time.tm_mday = 19;
			time.tm_hour = 12;
			time.tm_min = 23;

			time_t set_time;
			set_time = mktime(&time);
			Message mess;
			mess.SetTime(set_time);
			tm ret_time = mess.GetTime();
		}

		TEST_METHOD(check_time) 
		{
			tm time;
			memset(&time, 0, sizeof(tm));
			time.tm_year = 2020 - 1900;
			time.tm_mon = 4;
			time.tm_mday = 19;
			time.tm_hour = 12;
			time.tm_min = 23;

			time_t set_time;
			set_time = mktime(&time);
			Message mess;
			mess.SetTime(set_time);
			tm ret_time = mess.GetTime();
			Assert::AreEqual(time.tm_year, ret_time.tm_year);
			Assert::AreEqual(time.tm_mon, ret_time.tm_mon);
			Assert::AreEqual(time.tm_mday, ret_time.tm_mday);
			Assert::AreEqual(time.tm_hour, ret_time.tm_hour);
			Assert::AreEqual(time.tm_min, ret_time.tm_min);
		}
		TEST_METHOD(add_group) 
		{
			Message mess;
			mess.AddGroup(message_id_group1, message_name_group1);
		}

		TEST_METHOD(check_group_count) 
		{
			Message mess;
			mess.AddGroup(message_id_group1, message_name_group1);
			list_info i = mess.GetGroupList();
			Assert::AreEqual(1, (int)i.size());
		}

		TEST_METHOD(check_group) 
		{
			Message mess;
			mess.AddGroup(message_id_group1, message_name_group1);
			list_info i = mess.GetGroupList();
			Assert::AreEqual(message_id_group1, i[0].first);
			Assert::AreEqual(message_name_group1, i[0].second);
		}

		TEST_METHOD(add_group3) 
		{
			Message mess;
			mess.AddGroup(message_id_group1, message_name_group1);
			mess.AddGroup(message_id_group2, message_name_group2);
			mess.AddGroup(message_id_group3, message_name_group3);

		}

		TEST_METHOD(check_group3) 
		{
			Message mess;
			mess.AddGroup(message_id_group1, message_name_group1);
			mess.AddGroup(message_id_group2, message_name_group2);
			mess.AddGroup(message_id_group3, message_name_group3);
			list_info i = mess.GetGroupList();
			Assert::AreEqual(3, (int)i.size());
			Assert::AreEqual(message_id_group1, i[0].first);
			Assert::AreEqual(message_name_group1, i[0].second);
			Assert::AreEqual(message_id_group2, i[1].first);
			Assert::AreEqual(message_name_group2, i[1].second);
			Assert::AreEqual(message_id_group3, i[2].first);
			Assert::AreEqual(message_name_group3, i[2].second);
		}

		TEST_METHOD(add_rule)
		{
			Message mess;
			mess.AddGroup(message_id_rule1, message_name_rule1);
		}

		TEST_METHOD(check_rule_count)
		{
			Message mess;
			mess.AddRule(message_id_rule1, message_name_rule1);
			list_info i = mess.GetRulesList();
			Assert::AreEqual(1, (int)i.size());
		}

		TEST_METHOD(check_rule)
		{
			Message mess;
			mess.AddRule(message_id_rule1, message_name_rule1);
			list_info i = mess.GetRulesList();
			Assert::AreEqual(message_id_rule1, i[0].first);
			Assert::AreEqual(message_name_rule1, i[0].second);
		}

		TEST_METHOD(add_rule3)
		{
			Message mess;
			mess.AddRule(message_id_rule1, message_name_rule1);
			mess.AddRule(message_id_rule2, message_name_rule2);
			mess.AddRule(message_id_rule3, message_name_rule3);
		}

		TEST_METHOD(check_rule3)
		{
			Message mess;
			mess.AddRule(message_id_rule1, message_name_rule1);
			mess.AddRule(message_id_rule2, message_name_rule2);
			mess.AddRule(message_id_rule3, message_name_rule3);
			list_info i = mess.GetRulesList();
			Assert::AreEqual(3, (int)i.size());
			Assert::AreEqual(message_id_rule1, i[0].first);
			Assert::AreEqual(message_name_rule1, i[0].second);
			Assert::AreEqual(message_id_rule2, i[1].first);
			Assert::AreEqual(message_name_rule2, i[1].second);
			Assert::AreEqual(message_id_rule3, i[2].first);
			Assert::AreEqual(message_name_rule3, i[2].second);
		}

		TEST_METHOD(add_premise) 
		{
			Message mess;
			std::vector<std::string> vec;
			vec.push_back(message_premise1);
			vec.push_back(message_premise2);
			mess.AddPremiseList(vec);
		}

		TEST_METHOD(check_count_premise) 
		{
			Message mess;
			std::vector<std::string> vec;
			vec.push_back(message_premise1);
			vec.push_back(message_premise2);
			mess.AddPremiseList(vec);
			Assert::AreEqual(2, (int)mess.GetListPremise().size());
		}

		TEST_METHOD(ckecl_premise) 
		{
			Message mess;
			std::vector<std::string> vec, vec2;
			vec.push_back(message_premise1);
			vec.push_back(message_premise2);
			mess.AddPremiseList(vec);

			vec2 = mess.GetListPremise();
			Assert::AreEqual(message_premise1, vec2[0]);
			Assert::AreEqual(message_premise2, vec2[1]);
		}

		TEST_METHOD(get_char) 
		{
			Message mess;
			mess.GetMessageToSend();
		}

		TEST_METHOD(get_number) 
		{
			Message mess;
			mess.GetSizeMessageToSend();
		}

		TEST_METHOD(check_char_not_empty) 
		{
			Message mess;
			const char *c = mess.GetMessageToSend();
			Assert::AreNotEqual("", c);
		}

		TEST_METHOD(check_size_not_null)
		{
			Message mess;
			mess.GetMessageToSend();
			Assert::AreNotEqual(0, mess.GetSizeMessageToSend());
		}

	};

	TEST_CLASS(message_receive_test)
	{
		TEST_METHOD(create_mess_is_char)
		{
			Message orig_mess;

			Message mess(orig_mess.GetMessageToSend(), orig_mess.GetSizeMessageToSend());
		}

		TEST_METHOD(set_id_emp)
		{
			Message orig_mess;
			orig_mess.SetIdEmployee(message_id_emp1);
			Message mess(orig_mess.GetMessageToSend(), orig_mess.GetSizeMessageToSend());
		}

		TEST_METHOD(get_id_emp)
		{
			Message orig_mess;
			orig_mess.SetIdEmployee(message_id_emp1);
			Message mess(orig_mess.GetMessageToSend(), orig_mess.GetSizeMessageToSend());
			Assert::AreEqual(message_id_emp1, mess.GetId());
		}

		TEST_METHOD(set_f_name)
		{
			Message orig_mess;
			orig_mess.SetFirstName(message_first_name1);
			Message mess(orig_mess.GetMessageToSend(), orig_mess.GetSizeMessageToSend());
		}

		TEST_METHOD(get_f_name)
		{
			Message orig_mess;
			orig_mess.SetFirstName(message_first_name1);
			Message mess(orig_mess.GetMessageToSend(), orig_mess.GetSizeMessageToSend());
			Assert::AreEqual(message_first_name1, mess.GetFirstName());
		}

		TEST_METHOD(set_l_name)
		{
			Message orig_mess;
			orig_mess.SetLastName(message_last_name1);
			Message mess(orig_mess.GetMessageToSend(), orig_mess.GetSizeMessageToSend());
		}

		TEST_METHOD(get_l_name)
		{
			Message orig_mess;
			orig_mess.SetLastName(message_last_name1);
			Message mess(orig_mess.GetMessageToSend(), orig_mess.GetSizeMessageToSend());
			Assert::AreEqual(message_last_name1, mess.GetLastName());
		}

		TEST_METHOD(set_m_name)
		{
			Message orig_mess;
			orig_mess.SetMidName(message_mid_name1);
			Message mess(orig_mess.GetMessageToSend(), orig_mess.GetSizeMessageToSend());
		}

		TEST_METHOD(get_m_name)
		{
			Message orig_mess;
			orig_mess.SetMidName(message_mid_name1);
			Message mess(orig_mess.GetMessageToSend(), orig_mess.GetSizeMessageToSend());
			Assert::AreEqual(message_mid_name1, mess.GetMidName());
		}

		TEST_METHOD(add_info)
		{
			Message orig_mess;
			orig_mess.AddInfo(message_add_info1);
			Message mess(orig_mess.GetMessageToSend(), orig_mess.GetSizeMessageToSend());

		}

		TEST_METHOD(check_add_info)
		{
			Message orig_mess;
			orig_mess.AddInfo(message_add_info1);
			Message mess(orig_mess.GetMessageToSend(), orig_mess.GetSizeMessageToSend());
			Assert::AreEqual(message_add_info1, mess.GetInfo());
		}

		TEST_METHOD(add_group)
		{
			Message orig_mess;
			orig_mess.AddGroup(message_id_group1, message_name_group1);
			Message mess(orig_mess.GetMessageToSend(), orig_mess.GetSizeMessageToSend());
			
		}

		TEST_METHOD(check_group_count)
		{
			Message orig_mess;
			orig_mess.AddGroup(message_id_group1, message_name_group1);
			Message mess(orig_mess.GetMessageToSend(), orig_mess.GetSizeMessageToSend());
			list_info i = mess.GetGroupList();
			Assert::AreEqual(1, (int)i.size());
		}

		TEST_METHOD(check_group)
		{
			Message orig_mess;
			orig_mess.AddGroup(message_id_group1, message_name_group1);
			Message mess(orig_mess.GetMessageToSend(), orig_mess.GetSizeMessageToSend());
			list_info i = mess.GetGroupList();
			Assert::AreEqual(message_id_group1, i[0].first);
			Assert::AreEqual(message_name_group1, i[0].second);
		}

		TEST_METHOD(add_group3)
		{
			Message orig_mess;
			orig_mess.AddGroup(message_id_group1, message_name_group1);
			orig_mess.AddGroup(message_id_group2, message_name_group2);
			orig_mess.AddGroup(message_id_group3, message_name_group3);
			Message mess(orig_mess.GetMessageToSend(), orig_mess.GetSizeMessageToSend());
		}

		TEST_METHOD(check_group3)
		{
			Message orig_mess;
			orig_mess.AddGroup(message_id_group1, message_name_group1);
			orig_mess.AddGroup(message_id_group2, message_name_group2);
			orig_mess.AddGroup(message_id_group3, message_name_group3);
			Message mess(orig_mess.GetMessageToSend(), orig_mess.GetSizeMessageToSend());
			list_info i = mess.GetGroupList();
			Assert::AreEqual(3, (int)i.size());
			Assert::AreEqual(message_id_group1, i[0].first);
			Assert::AreEqual(message_name_group1, i[0].second);
			Assert::AreEqual(message_id_group2, i[1].first);
			Assert::AreEqual(message_name_group2, i[1].second);
			Assert::AreEqual(message_id_group3, i[2].first);
			Assert::AreEqual(message_name_group3, i[2].second);
		}

		TEST_METHOD(add_rule)
		{
			Message orig_mess;
			orig_mess.AddGroup(message_id_rule1, message_name_rule1);
			Message mess;
		}

		TEST_METHOD(check_rule_count)
		{
			Message orig_mess;
			orig_mess.AddGroup(message_id_rule1, message_name_rule1);
			Message mess(orig_mess.GetMessageToSend(), orig_mess.GetSizeMessageToSend());
			mess.AddRule(message_id_rule1, message_name_rule1);
			list_info i = mess.GetRulesList();
			Assert::AreEqual(1, (int)i.size());
		}

		TEST_METHOD(check_rule)
		{
			Message orig_mess;
			orig_mess.AddGroup(message_id_rule1, message_name_rule1);
			orig_mess.AddRule(message_id_rule1, message_name_rule1);
			Message mess(orig_mess.GetMessageToSend(), orig_mess.GetSizeMessageToSend());

			list_info i = mess.GetRulesList();
			Assert::AreEqual(message_id_rule1, i[0].first);
			Assert::AreEqual(message_name_rule1, i[0].second);
		}

		TEST_METHOD(add_rule3)
		{
			Message orig_mess;
			orig_mess.AddRule(message_id_rule1, message_name_rule1);
			orig_mess.AddRule(message_id_rule2, message_name_rule2);
			orig_mess.AddRule(message_id_rule3, message_name_rule3);
			Message mess(orig_mess.GetMessageToSend(), orig_mess.GetSizeMessageToSend());
		}

		TEST_METHOD(check_rule3)
		{
			Message orig_mess;
			orig_mess.AddRule(message_id_rule1, message_name_rule1);
			orig_mess.AddRule(message_id_rule2, message_name_rule2);
			orig_mess.AddRule(message_id_rule3, message_name_rule3);
			Message mess(orig_mess.GetMessageToSend(), orig_mess.GetSizeMessageToSend());

			list_info i = mess.GetRulesList();
			Assert::AreEqual(3, (int)i.size());
			Assert::AreEqual(message_id_rule1, i[0].first);
			Assert::AreEqual(message_name_rule1, i[0].second);
			Assert::AreEqual(message_id_rule2, i[1].first);
			Assert::AreEqual(message_name_rule2, i[1].second);
			Assert::AreEqual(message_id_rule3, i[2].first);
			Assert::AreEqual(message_name_rule3, i[2].second);
		}

		TEST_METHOD(add_premise)
		{
			Message orig_mess;
			std::vector<std::string> vec;
			vec.push_back(message_premise1);
			vec.push_back(message_premise2);
			orig_mess.AddPremiseList(vec);
			Message mess(orig_mess.GetMessageToSend(), orig_mess.GetSizeMessageToSend());
		}

		TEST_METHOD(check_count_premise)
		{
			Message orig_mess;
			std::vector<std::string> vec;
			vec.push_back(message_premise1);
			vec.push_back(message_premise2);
			orig_mess.AddPremiseList(vec);
			Message mess(orig_mess.GetMessageToSend(), orig_mess.GetSizeMessageToSend());

			Assert::AreEqual(2, (int)mess.GetListPremise().size());
		}

		TEST_METHOD(ckeck_premise)
		{
			Message orig_mess;
			std::vector<std::string> vec, vec2;
			vec.push_back(message_premise1);
			vec.push_back(message_premise2);
			orig_mess.AddPremiseList(vec);
			Message mess(orig_mess.GetMessageToSend(), orig_mess.GetSizeMessageToSend());

			vec2 = mess.GetListPremise();
			Assert::AreEqual(message_premise1, vec2[0]);
			Assert::AreEqual(message_premise2, vec2[1]);
		}


		TEST_METHOD(set_time)
		{
			
			tm time;
			memset(&time, 0, sizeof(tm));
			time.tm_year = 2020 - 1900;
			time.tm_mon = 4;
			time.tm_mday = 19;
			time.tm_hour = 12;
			time.tm_min = 23;

			time_t set_time;
			set_time = mktime(&time);
			Message orig_mess;
			orig_mess.SetTime(set_time);
			Message mess(orig_mess.GetMessageToSend(), orig_mess.GetSizeMessageToSend());

		}

		TEST_METHOD(get_time)
		{
			tm time;
			memset(&time, 0, sizeof(tm));
			time.tm_year = 2020 - 1900;
			time.tm_mon = 4;
			time.tm_mday = 19;
			time.tm_hour = 12;
			time.tm_min = 23;

			time_t set_time;
			set_time = mktime(&time);
			Message orig_mess;
			orig_mess.SetTime(set_time);
			Message mess(orig_mess.GetMessageToSend(), orig_mess.GetSizeMessageToSend());
			tm ret_time = mess.GetTime();
		}

		TEST_METHOD(check_time)
		{
			tm time;
			memset(&time, 0, sizeof(tm));
			time.tm_year = 2020 - 1900;
			time.tm_mon = 4;
			time.tm_mday = 19;
			time.tm_hour = 12;
			time.tm_min = 23;

			time_t set_time;
			set_time = mktime(&time);
			Message orig_mess;
			orig_mess.SetTime(set_time);
			Message mess(orig_mess.GetMessageToSend(), orig_mess.GetSizeMessageToSend());
			tm ret_time = mess.GetTime();
			Assert::AreEqual(time.tm_year, ret_time.tm_year);
			Assert::AreEqual(time.tm_mon, ret_time.tm_mon);
			Assert::AreEqual(time.tm_mday, ret_time.tm_mday);
			Assert::AreEqual(time.tm_hour, ret_time.tm_hour);
			Assert::AreEqual(time.tm_min, ret_time.tm_min);
		}
	};
}
