#include "pch.h"
#include "CppUnitTest.h"
#include "..//file_manager/file_rule.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace filemanagertest
{
	using std::vector;
	using std::string;
	using std::map;

	string rule_file_name = "rule_file_name.test";
	string rule_name1 = "rule_name_1", rule_name2 = "rule_name_2", rule_name3 = "rule_name_3", rule_name4 = "rule_name_4";
	string rule_desc1 = "desc_rule_test1", rule_desc2 = "desc_rule_test2", rule_desc3 = "desc_rule_test3", rule_desc4 = "desc_rule_test4";
	
	int rule_id1 = 1, rule_id2 = 2, rule_id3 = 3, rule_id4 = 4;

	int rule_id_not_exist = 51;

	int rule_camera1 = 11, rule_camera2 = 12;
	int rule_premise1 = 21, rule_premise2 = 22;

	int rule_camera_not_exist = 31;
	int rule_premise_not_exist = 41;

	TEST_CLASS(file_rule_test)
	{
	public:

		TEST_METHOD(create)
		{
			file_rule fr(rule_file_name);
		}


		TEST_METHOD(create_default)
		{
			file_rule fr;
		}

		TEST_METHOD(s1p01_create)
		{
			file_rule fr(rule_file_name);
		}

		TEST_METHOD(s1p02_add) 
		{
			file_rule fr(rule_file_name);
			fr.AddRule(rule_name1, rule_desc1, rule_id1);
		}

		TEST_METHOD(s1p03_get_for_id) 
		{
			file_rule fr(rule_file_name);
			fr.AddRule(rule_name1, rule_desc1, rule_id1);
			rule rul = fr.GetRule(rule_id1);
		}

		TEST_METHOD(s1p04_id) 
		{
			file_rule fr(rule_file_name);
			fr.AddRule(rule_name1, rule_desc1, rule_id1);
			rule rul = fr.GetRule(rule_id1);
			Assert::AreEqual(rule_id1, rul.id);
		}

		TEST_METHOD(s1p05_name) 
		{
			file_rule fr(rule_file_name);
			fr.AddRule(rule_name1, rule_desc1, rule_id1);
			rule rul = fr.GetRule(rule_id1);
			Assert::AreEqual(rule_name1, rul.name);
		}

		TEST_METHOD(s1p06_desc)
		{
			file_rule fr(rule_file_name);
			fr.AddRule(rule_name1, rule_desc1, rule_id1);
			rule rul = fr.GetRule(rule_id1);
			Assert::AreEqual(rule_desc1, rul.description);
		}

		TEST_METHOD(s1p07_check_all) 
		{
			file_rule fr(rule_file_name);
			fr.AddRule(rule_name1, rule_desc1, rule_id1);
			Assert::AreEqual(1, (int)fr.GetAllRule().size());
		}

		TEST_METHOD(s1p08_save) 
		{
			file_rule fr(rule_file_name);
			fr.AddRule(rule_name1, rule_desc1, rule_id1);
			fr.Save();
		}

		TEST_METHOD(s1p09_open_save)
		{
			file_rule fr(rule_file_name);
		}

		TEST_METHOD(s1p10_open_save_cont) 
		{
			file_rule fr(rule_file_name);
			Assert::AreEqual(1, (int)fr.GetAllRule().size());
		}

		TEST_METHOD(s1p11_id) 
		{
			file_rule fr(rule_file_name);
			rule rul = fr.GetRule(rule_id1);
			Assert::AreEqual(rule_id1, rul.id);
		}

		TEST_METHOD(s1p12_name)
		{
			file_rule fr(rule_file_name);
			rule rul = fr.GetRule(rule_id1);
			Assert::AreEqual(rule_name1, rul.name);
		}

		TEST_METHOD(s1p13_desc)
		{
			file_rule fr(rule_file_name);
			rule rul = fr.GetRule(rule_id1);
			Assert::AreEqual(rule_desc1, rul.description);
		}

		TEST_METHOD(s1p14_get_error_rule) 
		{
			file_rule fr(rule_file_name);
			bool exec = false;
			try {
				fr.GetRule(rule_id2);
			}
			catch (...) {
				exec = true;
			}
		}

		TEST_METHOD(s1p15_link_camera)
		{
			file_rule fr(rule_file_name);
			fr.LinkWithCamera(rule_id1, rule_camera1);
			fr.AddRule(rule_name2, rule_desc2, rule_id2);
			fr.LinkWithCamera(rule_id2, rule_camera2);
		}

		TEST_METHOD(s1p16_link_save) 
		{
			file_rule fr(rule_file_name);
			fr.LinkWithCamera(rule_id1, rule_camera1);
			fr.AddRule(rule_name2, rule_desc2, rule_id2);
			fr.LinkWithCamera(rule_id1, rule_camera2);
			fr.LinkWithCamera(rule_id2, rule_camera2);
			fr.Save();
		}
		
		TEST_METHOD(s1p17_open_save) 
		{
			file_rule fr(rule_file_name);
		}

		TEST_METHOD(s1p18_check_count1) 
		{
			file_rule fr(rule_file_name);
			vector<rule> vec;
			vec = fr.GetRuleWithCamera(rule_camera1);
			Assert::AreEqual(1, (int)vec.size());
		}

		TEST_METHOD(s1p19_check_count2)
		{
			file_rule fr(rule_file_name);
			vector<rule> vec;
			vec = fr.GetRuleWithCamera(rule_camera2);
			Assert::AreEqual(2, (int)vec.size());
		}

		TEST_METHOD(s1p20_check_rule_id1) 
		{
			file_rule fr(rule_file_name);
			vector<rule> vec;
			vec = fr.GetRuleWithCamera(rule_camera2);
			Assert::AreEqual(rule_id1, vec[0].id);
		}

		TEST_METHOD(s1p21_check_rule_id2)
		{
			file_rule fr(rule_file_name);
			vector<rule> vec;
			vec = fr.GetRuleWithCamera(rule_camera2);
			Assert::AreEqual(rule_id2, vec[1].id);
		}

		TEST_METHOD(s1p22_check_error_cam) 
		{
			file_rule fr(rule_file_name);
			bool exec = false;
			try {
				fr.LinkWithCamera(rule_id_not_exist, rule_camera1);
			}
			catch (...) {
				exec = true;
			}

			Assert::AreEqual(true, exec);
		}

		TEST_METHOD(s1p23_delete_link) 
		{
			file_rule fr(rule_file_name);
			fr.UnLinkWithCamera(rule_id1, rule_camera1);
		}

		TEST_METHOD(s1p24_save_delet)
		{
			file_rule fr(rule_file_name);
			fr.UnLinkWithCamera(rule_id1, rule_camera1);
			fr.Save();
		}

		TEST_METHOD(s1p25_check_delete)
		{
			file_rule fr(rule_file_name);
			vector<rule> v = fr.GetRuleWithCamera(rule_id1);
			Assert::AreEqual(0, (int)v.size());
		}

		TEST_METHOD(s1p26_link_premise)
		{
			file_rule fr(rule_file_name);
			fr.LinkWithPremise(rule_id1, rule_premise1);
			fr.LinkWithPremise(rule_id2, rule_premise2);
		}

		TEST_METHOD(s1p27_link_save)
		{
			file_rule fr(rule_file_name);
			fr.LinkWithPremise(rule_id1, rule_premise1);
			fr.LinkWithPremise(rule_id1, rule_premise2);
			fr.LinkWithPremise(rule_id2, rule_premise2);
			fr.Save();
		}

		TEST_METHOD(s1p28_open_save)
		{
			file_rule fr(rule_file_name);
		}

		TEST_METHOD(s1p29_check_count1)
		{
			file_rule fr(rule_file_name);
			vector<rule> vec;
			vec = fr.GetRuleWirhPremuse(rule_premise1);
			Assert::AreEqual(1, (int)vec.size());
		}

		TEST_METHOD(s1p30_check_count2)
		{
			file_rule fr(rule_file_name);
			vector<rule> vec;
			vec = fr.GetRuleWirhPremuse(rule_premise2);
			Assert::AreEqual(2, (int)vec.size());
		}

		TEST_METHOD(s1p31_check_rule_id1)
		{
			file_rule fr(rule_file_name);
			vector<rule> vec;
			vec = fr.GetRuleWirhPremuse(rule_premise2);
			Assert::AreEqual(rule_id1, vec[0].id);
		}

		TEST_METHOD(s1p32_check_rule_id2)
		{
			file_rule fr(rule_file_name);
			vector<rule> vec;
			vec = fr.GetRuleWirhPremuse(rule_premise2);
			Assert::AreEqual(rule_id2, vec[1].id);
		}

		TEST_METHOD(s1p33_check_error_cam)
		{
			file_rule fr(rule_file_name);
			bool exec = false;
			try {
				fr.UnLinkWithPremise(rule_id_not_exist, rule_premise2);
			}
			catch (...) {
				exec = true;
			}

			Assert::AreEqual(true, exec);
		}

		TEST_METHOD(s1p34_delete_link)
		{
			file_rule fr(rule_file_name);
			fr.UnLinkWithPremise(rule_id1, rule_premise1);
		}

		TEST_METHOD(s1p35_save_delet)
		{
			file_rule fr(rule_file_name);
			fr.UnLinkWithPremise(rule_id1, rule_premise1);
			fr.Save();
		}

		TEST_METHOD(s1p36_check_delete)
		{
			file_rule fr(rule_file_name);
			vector<rule> v = fr.GetRuleWirhPremuse(rule_id1);
			Assert::AreEqual(0, (int)v.size());
		}


		TEST_METHOD(s1p98_clear) 
		{
			file_rule fr(rule_file_name);
			fr.ClearFile();
		}

		TEST_METHOD(s1p99_check_clear)
		{
			file_rule fr(rule_file_name);
			Assert::AreEqual(0, (int)fr.GetAllRule().size());
		}
	};
}