#include "pch.h"
#include "CppUnitTest.h"
#include "..//file_manager/file_premise.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace filemanagertest
{
	//Название файла
	std::string premise_faile_name = "file_premise.test";
	
	//Название комнат
	std::string premise_name1 = "premise_name1", premise_name2 = "premise_name2", premise_name3 = "premise_name3";
	//Описание комнат
	std::string premise_desc1 = "premise_description_test1", premise_desc2 = "premise_description_test2", premise_desc3 = "premise_description_test3";
	//Идентификаторы помещений
	int premise_id1 = 1, premise_id2 = 2, premise_id3 = 3;
	int premise_id_not_exist = 70;

	//Новая информация о помещении
	std::string premise_new_name = "new_premise_name3", premise_new_desc = "new_premise_description3";


	TEST_CLASS(file_premise_test)
	{
	public:

		TEST_METHOD(create_default)
		{
			file_premise fp;
		}

		TEST_METHOD(s1p01_create)
		{
			file_premise fp(premise_faile_name);
		}
		
		TEST_METHOD(s1p02_add_premise)
		{
			file_premise fp(premise_faile_name);
			fp.AddNewPremise(premise_name1, premise_desc1, premise_id1);
		}

		TEST_METHOD(s1p03_add_premise_save) 
		{
			file_premise fp(premise_faile_name);
			fp.AddNewPremise(premise_name1, premise_desc1, premise_id1);
			fp.Save();
		}

		TEST_METHOD(s1p04_open_save) 
		{
			file_premise fp(premise_faile_name);
		}

		TEST_METHOD(s1p05_save_premise_check_count)
		{
			file_premise fp(premise_faile_name);
			Assert::AreEqual(1, (int)fp.GetAllPremise().size());
		}

		TEST_METHOD(s1p06_save_premise_id) 
		{
			file_premise fp(premise_faile_name);
			premise prem = fp.GetPremise(premise_id1);
			Assert::AreEqual(premise_id1, prem.id);
		}

		TEST_METHOD(s1p07_save_name) 
		{
			file_premise fp(premise_faile_name);
			premise prem = fp.GetPremise(premise_id1);
			Assert::AreEqual(premise_name1, prem.name);
		}

		TEST_METHOD(s1p08_save_desc) 
		{
			file_premise fp(premise_faile_name);
			premise prem = fp.GetPremise(premise_id1);
			Assert::AreEqual(premise_desc1, prem.description);
		}

		TEST_METHOD(s1p09_save_parent) 
		{
			file_premise fp(premise_faile_name);
			premise prem = fp.GetPremise(premise_id1);
			Assert::AreEqual(-1, prem.id_parent);
		}

		TEST_METHOD(s1p10_add_and_parent) 
		{
			file_premise fp(premise_faile_name);
			fp.AddNewPremise(premise_name2, premise_desc2, premise_id2, premise_id1);
			fp.AddNewPremise(premise_name3, premise_desc3, premise_id3, premise_id2);
			fp.Save();
		}

		TEST_METHOD(s1p11_check_all_premise_count)
		{
			file_premise fp(premise_faile_name);
			std::vector<premise> prem = fp.GetAllPremise();
			Assert::AreEqual(3, (int)prem.size());
		}

		TEST_METHOD(s1p12_check_premise_parrent) 
		{
			file_premise fp(premise_faile_name);
			std::vector<premise> prem = fp.GetAllPremise();
			Assert::AreEqual(premise_id1, prem[1].id_parent);
			Assert::AreEqual(premise_id2, prem[2].id_parent);
		}

		TEST_METHOD(s1p13_get_all_parenr_count1) 
		{
			file_premise fp(premise_faile_name);
			std::vector<premise> prem = fp.GetAllParent(premise_id2);
			Assert::AreEqual(1, (int)prem.size());
		}

		TEST_METHOD(s1p14_all_parent_check1) 
		{
			file_premise fp(premise_faile_name);
			std::vector<premise> prem = fp.GetAllParent(premise_id2);
			Assert::AreEqual(premise_id1, prem[0].id);
		}

		TEST_METHOD(s1p15_get_all_parenr_count2)
		{
			file_premise fp(premise_faile_name);
			std::vector<premise> prem = fp.GetAllParent(premise_id3);
			Assert::AreEqual(2, (int)prem.size());
		}

		TEST_METHOD(s1p16_all_parent_check2)
		{
			file_premise fp(premise_faile_name);
			std::vector<premise> prem = fp.GetAllParent(premise_id3);
			Assert::AreEqual(premise_id2, prem[0].id);
			Assert::AreEqual(premise_id1, prem[1].id);
		}

		TEST_METHOD(s1p17_get_with_parent_cout) 
		{
			file_premise fp(premise_faile_name);
			std::vector<premise> prem = fp.GetPremiseWithParrent(premise_id3);
			Assert::AreEqual(3, (int)prem.size());
		}

		TEST_METHOD(s1p18_get_with_parent) 
		{
			file_premise fp(premise_faile_name);
			std::vector<premise> prem = fp.GetPremiseWithParrent(premise_id3);
			Assert::AreEqual(3, prem[0].id);
			Assert::AreEqual(2, prem[1].id);
			Assert::AreEqual(1, prem[2].id);
		}

		TEST_METHOD(s1p19_edit_parent) 
		{
			file_premise fp(premise_faile_name);
			fp.EditPremisse(premise_id3, premise_new_name, premise_new_desc);
			fp.Save();
		}

		TEST_METHOD(s1p20_edit_check) 
		{
			file_premise fp(premise_faile_name);
			premise prem = fp.GetPremise(premise_id3);
			Assert::AreEqual(premise_id3, prem.id);
			Assert::AreEqual(premise_new_name, prem.name);
			Assert::AreEqual(premise_new_desc, prem.description);
		}

		TEST_METHOD(s1p21_delete) 
		{
			file_premise fp(premise_faile_name);
			fp.DeletePremise(premise_id3);
			fp.Save();
		}

		TEST_METHOD(s1p22_check_delete) 
		{
			file_premise fp(premise_faile_name);
			std::vector<premise> prem = fp.GetAllPremise();
			Assert::AreEqual(2, (int)prem.size());
		}

		TEST_METHOD(s1p23_get_error_parent1) 
		{
			file_premise fp(premise_faile_name);
			bool exec = false;
			try {
				fp.GetPremise(premise_id3);
			}
			catch (...) {
				exec = true;
			}

			Assert::AreEqual(true, exec);
		}

		TEST_METHOD(s1p24_get_error_parent2)
		{
			file_premise fp(premise_faile_name);
			bool exec = false;
			try {
				fp.GetPremise(premise_id_not_exist);
			}
			catch (...) {
				exec = true;
			}

			Assert::AreEqual(true, exec);
		}

		TEST_METHOD(s1p25_get_error_parent) 
		{
			file_premise fp(premise_faile_name);
			bool exec = false;
			try {
				fp.GetAllParent(premise_id3);
			}
			catch (...) {
				exec = true;
			}

			Assert::AreEqual(true, exec);
		}

		TEST_METHOD(s1p26_get_error_with_parent) 
		{
			file_premise fp(premise_faile_name);
			bool exec = false;
			try {
				fp.GetPremiseWithParrent(premise_id3);
			}
			catch (...) {
				exec = true;
			}

			Assert::AreEqual(true, exec);
		}

		TEST_METHOD(s1p27_get_parent_from_parent) 
		{
			file_premise fp(premise_faile_name);
			premise new_prem;
			new_prem.id = 2;
			std::vector<premise> vec = fp.GetAllParent(new_prem);
			Assert::AreEqual(1, (int)vec.size());
			Assert::AreEqual(premise_id1, vec[0].id);
		}

		TEST_METHOD(s1p98_clear_file) 
		{
			file_premise fp(premise_faile_name);
			fp.ClearFile();
		}

		TEST_METHOD(s1p99_check_clear)
		{
			file_premise fp(premise_faile_name);
			Assert::AreEqual(0, (int) fp.GetAllPremise().size());
		}

	};
}