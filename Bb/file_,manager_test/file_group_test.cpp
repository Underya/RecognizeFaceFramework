#include "pch.h"
#include "CppUnitTest.h"
#include "..//file_manager/file_group.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace filemanagertest
{

	std::string group_file_name_test = "file_group.test";
	int groups_id1 = 1, groups_id2 = 2, groups_id3 = 3;
	int groups_id_not_exist = 4;
	std::string groups_name1 = "group_test_name1", groups_name2 = "group_test_nam2", groups_name3 = "group_test_nam3";
	std::string groups_desc1 = "description_group1", groups_desc2 = "description_group2", groups_desc3 = "description_group3";

	std::string groups_new_name = "new_group_test_name1", groups_new_descr = "new_descruption_group1";
	

	//Идентификаторы сотрудников
	int groups_emp1 = 1, groups_emp2 = 2, groups_emp3 = 3;
	int groups_emp_not_exist = 4;
	//Первый связан с первой группой, второй со второй, третий с первой и второй

	TEST_CLASS(file_group_test)
	{
	public:

		TEST_METHOD(create_default)
		{
			file_group ff;
		}

		TEST_METHOD(s1p01_create)
		{
			file_group ff(group_file_name_test);
		}

		TEST_METHOD(s1p02_add_group)
		{
			file_group ff(group_file_name_test);
			ff.AddNewGroup(groups_name1, groups_desc1, groups_id1);
			ff.AddNewGroup(groups_name2, groups_desc2, groups_id2);
		}

		TEST_METHOD(s1p03_check_add_count)
		{
			file_group ff(group_file_name_test);
			ff.AddNewGroup(groups_name1, groups_desc1, groups_id1);
			ff.AddNewGroup(groups_name2, groups_desc2, groups_id2);

			Assert::AreEqual(2, (int)ff.GetAllId().size());
		}

		TEST_METHOD(s1p04_check_add_id)
		{
			file_group ff(group_file_name_test);
			ff.AddNewGroup(groups_name1, groups_desc1, groups_id1);
			ff.AddNewGroup(groups_name2, groups_desc2, groups_id2);

			std::vector<int> id_vec = ff.GetAllId();

			Assert::AreEqual(groups_id1, id_vec[0]);
			Assert::AreEqual(groups_id2, id_vec[1]);
		}

		TEST_METHOD(s1p05_check_add_name)
		{
			file_group ff(group_file_name_test);
			ff.AddNewGroup(groups_name1, groups_desc1, groups_id1);
			ff.AddNewGroup(groups_name2, groups_desc2, groups_id2);

			Assert::AreEqual(groups_name1, ff.GetName(groups_id1));
			Assert::AreEqual(groups_name2, ff.GetName(groups_id2));
		}

		TEST_METHOD(s1p06_checK_add_desc)
		{
			file_group ff(group_file_name_test);
			ff.AddNewGroup(groups_name1, groups_desc1, groups_id1);
			ff.AddNewGroup(groups_name2, groups_desc2, groups_id2);

			Assert::AreEqual(groups_name1, ff.GetName(groups_id1));
			Assert::AreEqual(groups_name2, ff.GetName(groups_id2));
		}

		TEST_METHOD(s1p07_add_save)
		{
			file_group ff(group_file_name_test);
			ff.AddNewGroup(groups_name1, groups_desc1, groups_id1);
			ff.AddNewGroup(groups_name2, groups_desc2, groups_id2);
			ff.Save();
		}

		TEST_METHOD(s1p08_open_save)
		{
			file_group ff(group_file_name_test);
		}

		TEST_METHOD(s1p09_check_count_save)
		{
			file_group ff(group_file_name_test);
			Assert::AreEqual(2, (int)ff.GetAllId().size());
		}

		TEST_METHOD(s1p10_check_add_id)
		{
			file_group ff(group_file_name_test);

			std::vector<int> id_vec = ff.GetAllId();

			Assert::AreEqual(groups_id1, id_vec[0]);
			Assert::AreEqual(groups_id2, id_vec[1]);
		}

		TEST_METHOD(s1p11_check_add_name)
		{
			file_group ff(group_file_name_test);

			Assert::AreEqual(groups_name1, ff.GetName(groups_id1));
			Assert::AreEqual(groups_name2, ff.GetName(groups_id2));
		}

		TEST_METHOD(s1p12_checK_add_desc)
		{
			file_group ff(group_file_name_test);

			Assert::AreEqual(groups_name1, ff.GetName(groups_id1));
			Assert::AreEqual(groups_name2, ff.GetName(groups_id2));
		}

		TEST_METHOD(s1p13_add_not_id)
		{
			file_group ff(group_file_name_test);
			ff.AddNewGroup(groups_name3, groups_desc3);
		}

		TEST_METHOD(s1p14_add_not_id_check_id)
		{
			file_group ff(group_file_name_test);
			ff.AddNewGroup(groups_name3, groups_desc3);

			std::vector<int> vec_id = ff.GetAllId();

			Assert::AreEqual(groups_id3, vec_id[2]);
		}

		TEST_METHOD(s1p15_add_not_id_save)
		{
			file_group ff(group_file_name_test);
			ff.AddNewGroup(groups_name3, groups_desc3);
			ff.Save();
		}

		TEST_METHOD(s1p16_check_add_not_id)
		{
			file_group ff(group_file_name_test);
			std::vector<int> vec_id = ff.GetAllId();
			Assert::AreEqual(groups_id3, vec_id[2]);

			Assert::AreEqual(groups_name3, ff.GetName(groups_id3));
			Assert::AreEqual(groups_desc3, ff.GetDesc(groups_id3));
		}

		TEST_METHOD(s1p17_snap_emp)
		{
			file_group ff(group_file_name_test);
			ff.AddNewSnap(groups_id1, groups_emp1);
			ff.AddNewSnap(groups_id2, groups_emp2);
			ff.AddNewSnap(groups_id1, groups_emp3);
			ff.AddNewSnap(groups_id2, groups_emp3);
		}

		TEST_METHOD(s1p18_snap_emp_check)
		{
			file_group ff(group_file_name_test);
			ff.AddNewSnap(groups_id1, groups_emp1);
			ff.AddNewSnap(groups_id2, groups_emp2);
			ff.AddNewSnap(groups_id1, groups_emp3);
			ff.AddNewSnap(groups_id2, groups_emp3);

			std::vector<int> v;
			v = ff.GetEmployeeId(groups_id1);
			Assert::AreEqual(groups_emp1, v[0]);
			Assert::AreEqual(groups_emp3, v[1]);
			v = ff.GetEmployeeId(groups_id2);
			Assert::AreEqual(groups_emp2, v[0]);
			Assert::AreEqual(groups_emp3, v[1]);
		}

		TEST_METHOD(s1p19_snap_save)
		{
			file_group ff(group_file_name_test);
			ff.AddNewSnap(groups_id1, groups_emp1);
			ff.AddNewSnap(groups_id2, groups_emp2);
			ff.AddNewSnap(groups_id1, groups_emp3);
			ff.AddNewSnap(groups_id2, groups_emp3);
			ff.Save();
		}

		TEST_METHOD(s1p20_open_snap_save)
		{
			file_group ff(group_file_name_test);
		}

		TEST_METHOD(s1p21_check_snap)
		{
			file_group ff(group_file_name_test);

			std::vector<int> v;
			v = ff.GetEmployeeId(groups_id1);
			Assert::AreEqual(groups_emp1, v[0]);
			Assert::AreEqual(groups_emp3, v[1]);
			v = ff.GetEmployeeId(groups_id2);
			Assert::AreEqual(groups_emp2, v[0]);
			Assert::AreEqual(groups_emp3, v[1]);
		}

		TEST_METHOD(s1p22_get_groups)
		{
			file_group ff(group_file_name_test);
			std::vector<int> v;
			v = ff.GetGroupFromId(groups_emp1);
			Assert::AreEqual(groups_id1, v[0]);
			v = ff.GetGroupFromId(groups_emp2);
			Assert::AreEqual(groups_id2, v[0]);
			v = ff.GetGroupFromId(groups_emp3);
			Assert::AreEqual(groups_id1, v[0]);
			Assert::AreEqual(groups_id2, v[1]);

		}

		TEST_METHOD(s1p22_add_2_snap)
		{
			bool exec = false;
			file_group ff(group_file_name_test);
			try {
				ff.AddNewSnap(groups_id1, groups_emp1);
			}
			catch (...) {
				exec = true;
			}

			Assert::AreEqual(true, exec);

		}

		TEST_METHOD(s1p23_add_2_snap2) 
		{
			bool exec = false;
			file_group ff(group_file_name_test);
			try {
				ff.AddNewSnap(groups_id2, groups_emp2);
			}
			catch (...) {
				exec = true;
			}

			Assert::AreEqual(true, exec);
		}

		TEST_METHOD(s1p24_delete_snap) 
		{
			file_group ff(group_file_name_test);
			ff.DeleteSnap(groups_id1, groups_emp3);
		}

		TEST_METHOD(s1p25_delete_snap_save) 
		{
			file_group ff(group_file_name_test);
			ff.DeleteSnap(groups_id1, groups_emp3);
			ff.Save();
		}


		TEST_METHOD(s1p26_check_delete) 
		{
			file_group ff(group_file_name_test);
			std::vector<int> v = ff.GetGroupFromId(groups_emp3);
			Assert::AreEqual(1, (int)v.size());
			Assert::AreEqual(groups_id2, v[0]);
		}

		TEST_METHOD(s1p27_get_error_group) 
		{
			bool exec = false;
			file_group ff(group_file_name_test);
			try {
				ff.GetEmployeeId(groups_id_not_exist);
			}
			catch (...) {
				exec = true;
			}

			Assert::AreEqual(true, exec);
		}

		TEST_METHOD(s1p28_get_error_id_emp) 
		{
			file_group ff(group_file_name_test);
			Assert::AreEqual(0, (int)(ff.GetGroupFromId(groups_emp_not_exist).size()));
		}

		TEST_METHOD(s1p29_edit_group) 
		{
			file_group ff(group_file_name_test);
			ff.EditGroupInfo(groups_id2, groups_new_name, groups_new_descr);
			ff.Save();
		}

		TEST_METHOD(s1p30_edit_group_checl) 
		{
			file_group ff(group_file_name_test);
			Assert::AreEqual(groups_new_name, ff.GetName(groups_id2));
			Assert::AreEqual(groups_new_descr, ff.GetDesc(groups_id2));
		}

		TEST_METHOD(s1p98_clear_file) 
		{
			file_group ff(group_file_name_test);
			ff.ClearFile();
		}

		TEST_METHOD(s1p99_check_claer) 
		{
			file_group ff(group_file_name_test);
			Assert::AreEqual(0, (int)ff.GetAllId().size());
		}
	};
}