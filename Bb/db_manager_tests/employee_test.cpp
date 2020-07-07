#include "pch.h"
#include "CppUnitTest.h"
#include "..//db/db_employee.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace dbmanagertests
{
	int db_employee_add_id = -1;

	int db_employee_other_id = 1613;

	std::string db_employee_unrecognized_name = "Unrecognized";

	std::string db_employee_first = "first_name", db_employee_last = "last_name", 
		db_employee_mid = "mid_name", db_e_desc = "description_test";

	std::string db_employee_first_new = "first_name_new", db_employee_last_new = "last_name_new",
		db_employee_mid_new = "mid_name_new", db_e_desc_new = "description_test_new";

	int db_employee_not_crreate_emp = -130;

	TEST_CLASS(employee_test)
	{
	public:

		TEST_METHOD_INITIALIZE(initialMethod)
		{
			// method initialization code
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", false);
		}

		TEST_METHOD(create_null)
		{
			db_employee emp;
		}

		TEST_METHOD(null_check_name) 
		{
			db_employee emp;
			Assert::AreEqual(db_employee_unrecognized_name, emp.GetFirstName());
		}

		TEST_METHOD(create_undef_emp) 
		{
			db_employee emp(-1);
		}

		TEST_METHOD(check_uncrec_name) 
		{
			db_employee emp(-1);
			Assert::AreEqual(db_employee_unrecognized_name, emp.GetFirstName());
		}


		TEST_METHOD(error_create)
		{
			try {
				db_employee e(db_employee_not_crreate_emp);
			}
			catch (...) {
				return;
			}

			Assert::Fail();
		}
		
		TEST_METHOD(s1p01_create_new_emp) 
		{
			db_employee *new_emp = db_employee::AddNewEmployee(db_employee_first, db_employee_last, db_employee_mid, db_e_desc, db_employee_other_id);
			db_employee_add_id = new_emp->GetId();
		}

		TEST_METHOD(s1p02_check_name) 
		{
			db_employee emp(db_employee_add_id);
			Assert::AreEqual(db_employee_first, emp.GetFirstName());
		}

		TEST_METHOD(s1p03_edit_name) 
		{
			db_employee emp(db_employee_add_id);
			emp.SetFirstName(db_employee_first_new);
		}

		TEST_METHOD(s1p04_check_edit_name) 
		{
			db_employee emp(db_employee_add_id);
			Assert::AreEqual(db_employee_first_new, emp.GetFirstName());
		}

		TEST_METHOD(s1p05_check_l_name) 
		{
			db_employee emp(db_employee_add_id);
			Assert::AreEqual(db_employee_last, emp.GetLastName());
		}

		TEST_METHOD(s1p06_edit_l_name) 
		{
			db_employee emp(db_employee_add_id);
			emp.SetLastName(db_employee_last_new);
		}

		TEST_METHOD(s1p07_check_edit_l_name) 
		{
			db_employee emp(db_employee_add_id);
			Assert::AreEqual(db_employee_last_new, emp.GetLastName());
		}

		TEST_METHOD(s1p08_check_mid_name) 
		{
			db_employee emp(db_employee_add_id);
			Assert::AreEqual(db_employee_mid, emp.GetMidleName());
		}

		TEST_METHOD(s1p09_edit_min_name) 
		{
			db_employee emp(db_employee_add_id);
			emp.SetMidName(db_employee_mid_new);
		}

		TEST_METHOD(s1p10_check_edit_mid_name) 
		{
			db_employee emp(db_employee_add_id);
			Assert::AreEqual(db_employee_mid_new, emp.GetMidleName());
		}

		TEST_METHOD(s1p11_check_desc) 
		{
			db_employee emp(db_employee_add_id);
			Assert::AreEqual(db_e_desc, emp.GetDescrInfo());
		}
		
		TEST_METHOD(s1p12_edit_desc) 
		{
			db_employee emp(db_employee_add_id);
			emp.SetDescrInfo(db_e_desc_new);
		}

		TEST_METHOD(s1p13_check_edit_desc) 
		{
			db_employee emp(db_employee_add_id);
			Assert::AreEqual(db_e_desc_new, emp.GetDescrInfo());
		}

		TEST_METHOD(s1p14_check_other_id) 
		{
			db_employee emp(db_employee_add_id);
			Assert::AreEqual(db_employee_other_id, emp.GetOtherId());
		}

		TEST_METHOD(s1p15_edit_other_id) 
		{
			db_employee emp(db_employee_add_id);
			emp.SetOtherId(db_employee_other_id * 3);
		}

		TEST_METHOD(s1p16_check_other_id) 
		{
			db_employee emp(db_employee_add_id);
			Assert::AreEqual(db_employee_other_id * 3, emp.GetOtherId());
		}

		TEST_METHOD(s1p98_delete) 
		{
			db_employee emp(db_employee_add_id);
			emp.Delete();
		}

		TEST_METHOD(s1p99_check_delete) 
		{
			try {
				db_employee emp(db_employee_add_id);
			}
			catch (...) {
				return;
			}

			Assert::Fail();
		}


		
	};

	std::string db_eg_f1 = "first_name11", db_eg_l1 = "last_name11", db_eg_m1 = "mid_name11";
	std::string db_eg_f2 = "first_name22", db_eg_l2 = "last_name22", db_eg_m2 = "mid_name22";

	int db_eg_eid1 = -101;
	int db_eg_eid2 = -102;

	std::string db_eg_n1 = "group_name_1", db_eg_n2 = "group_name_2", db_eg_n3 = "group_name_3";

	int db_eg_gid1 = -201, db_eg_gid2 = -202, db_eg_gid3 = -203;

	TEST_CLASS(employee_get_group_test) 
	{
	public:

		TEST_METHOD_INITIALIZE(initialMethod)
		{
			// method initialization code
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", false);
		}

		TEST_METHOD(s1p01_create_emp) 
		{
			db_employee* e1 = db_employee::AddNewEmployee(db_eg_n1, "", "");
			db_employee* e2 = db_employee::AddNewEmployee(db_eg_n2, "", "");
			db_eg_eid1 = e1->GetId();
			db_eg_eid2 = e2->GetId();
		}

		TEST_METHOD(s1p02_create_group) 
		{
			db_group g1 = db_group::AddNewGroup(db_eg_n1, "");
			db_group g2 = db_group::AddNewGroup(db_eg_n2, "");
			db_group g3 = db_group::AddNewGroup(db_eg_n3, "");
			db_eg_gid1 = g1.GetId();
			db_eg_gid2 = g2.GetId();
			db_eg_gid3 = g3.GetId();
		}

		TEST_METHOD(s1p03_link) 
		{
			db_group g1(db_eg_gid1);
			db_group g2(db_eg_gid2);
			db_group g3(db_eg_gid3);
			db_employee e1(db_eg_eid1);
			db_employee e2(db_eg_eid2);

			g1.SnapEmployee(e1.GetId());
			g2.SnapEmployee(e2.GetId());

			g3.SnapEmployee(e1.GetId());
			g3.SnapEmployee(e2.GetId());
		}

		TEST_METHOD(s1p04_check_id1) 
		{
			db_group g1(db_eg_gid1);
			db_group g2(db_eg_gid2);
			db_group g3(db_eg_gid3);
			std::vector<db_employee> *r = db_employee::GetEmployeeWithCondition(g1);
			db_employee e1 = (*r)[0];
			Assert::AreEqual(db_eg_eid1, e1.GetId());
		}

		TEST_METHOD(s1p05_check_id2) 
		{
			db_group g1(db_eg_gid1);
			db_group g2(db_eg_gid2);
			db_group g3(db_eg_gid3);
			std::vector<db_employee>* r = db_employee::GetEmployeeWithCondition(g2);
			db_employee e2 = (*r)[0];
			Assert::AreEqual(db_eg_eid2, e2.GetId());
		}

		TEST_METHOD(s1p06_check_id1_and_id2) 
		{
			db_group g1(db_eg_gid1);
			db_group g2(db_eg_gid2);
			db_group g3(db_eg_gid3);
			std::vector<db_employee>* r = db_employee::GetEmployeeWithCondition({ g1, g2 });
			db_employee e1 = (*r)[0];
			db_employee e2 = (*r)[1];
			if (e1.GetId() != db_eg_eid1 && e1.GetId() != db_eg_eid2)
				Assert::Fail();
			if (e2.GetId() != db_eg_eid1 && e2.GetId() != db_eg_eid2)
				Assert::Fail();
		}

		TEST_METHOD(s1p07_check_id3) 
		{
			db_group g1(db_eg_gid1);
			db_group g2(db_eg_gid2);
			db_group g3(db_eg_gid3);
			std::vector<db_employee>* r = db_employee::GetEmployeeWithCondition(g3);
			db_employee e1 = (*r)[0];
			db_employee e2 = (*r)[1];
			if (e1.GetId() != db_eg_eid1 && e1.GetId() != db_eg_eid2)
				Assert::Fail();
			if (e2.GetId() != db_eg_eid1 && e2.GetId() != db_eg_eid2)
				Assert::Fail();
		}

		TEST_METHOD(s1p94_delete_employee) 
		{
			db_employee e1(db_eg_eid1);
			e1.Delete();
			db_employee e2(db_eg_eid2);
			e2.Delete();
		}

		TEST_METHOD(s1p95_delete_group) 
		{
			db_group g1(db_eg_gid1);
			g1.Delete();
			db_group g2(db_eg_gid2);
			g2.Delete();
			db_group g3(db_eg_gid3);
			g3.Delete();
		}

	};
}
