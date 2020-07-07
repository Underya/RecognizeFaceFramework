#include "pch.h"
#include "CppUnitTest.h"
#include "..//face_recognition/employee_info.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;



namespace recognitiontest
{
	TEST_CLASS(employee_info_test)
	{
	public:

		TEST_METHOD(create)
		{
			int id = 10;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			employee_info ei(id, name, famyli, mid_name, dbdesc);
		}


		TEST_METHOD(check_id) 
		{
			int id = 10;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			employee_info ei(id, name, famyli, mid_name, dbdesc);
			Assert::AreEqual(id, ei.GetId());
		}
		
		TEST_METHOD(check_first_name)
		{
			int id = 10;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			employee_info ei(id, name, famyli, mid_name, dbdesc);
			Assert::AreEqual(name, ei.GetFirstName());
		}

		TEST_METHOD(check_last_name)
		{
			int id = 10;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			employee_info ei(id, name, famyli, mid_name, dbdesc);
			Assert::AreEqual(famyli, ei.GetLastName());
		}

		TEST_METHOD(check_mid_name)
		{
			int id = 10;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			employee_info ei(id, name, famyli, mid_name, dbdesc);
			Assert::AreEqual(dbdesc, ei.GetDBDescriptor());
		}


		TEST_METHOD(check_db_desc)
		{
			int id = 10;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			employee_info ei(id, name, famyli, mid_name, dbdesc);
			Assert::AreEqual(mid_name, ei.GetMidName());
		}

		TEST_METHOD(set_other_id)
		{
			int id = 10, other_id = 12;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			employee_info ei(id, name, famyli, mid_name, dbdesc);
			ei.SetOtherId(other_id);
		}

		TEST_METHOD(edit_id)
		{
			int id = 10;
			int nid = 11;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			employee_info ei(id, name, famyli, mid_name, dbdesc);
			ei.SetId(nid);
			Assert::AreEqual(nid, ei.GetId());
		}


		TEST_METHOD(edit_name)
		{
			int id = 10;
			int nid = 11;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			string nname = "name", nfamyli = "famyli", nmid_name = "otechestvo", ndbdesc = "";
			employee_info ei(id, name, famyli, mid_name, dbdesc);
			ei.SetFisrtName(nname);
			Assert::AreEqual(nname, ei.GetFirstName());
		}


		TEST_METHOD(edit_last_name)
		{
			int id = 10;
			int nid = 11;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			string nname = "name", nfamyli = "famyli", nmid_name = "otechestvo", ndbdesc = "";
			employee_info ei(id, name, famyli, mid_name, dbdesc);
			ei.SetLastName(nfamyli);
			Assert::AreEqual(nfamyli, ei.GetLastName());
		}

		TEST_METHOD(edit_mid_name) 
		{
			int id = 10;
			int nid = 11;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			string nname = "name", nfamyli = "famyli", nmid_name = "otechestvo", ndbdesc = "";
			employee_info ei(id, name, famyli, mid_name, dbdesc);
			ei.SetMidName(nmid_name);
			Assert::AreEqual(nmid_name, ei.GetMidName());
		}

		TEST_METHOD(edit_db_desc) 
		{
			int id = 10;
			int nid = 11;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			string nname = "name", nfamyli = "famyli", nmid_name = "otechestvo", ndbdesc = "";
			employee_info ei(id, name, famyli, mid_name, dbdesc);
			ei.SetDBDescriptor(ndbdesc);
			Assert::AreEqual(ndbdesc, ei.GetDBDescriptor());
		}

		TEST_METHOD(edit_other_id)
		{
			int id = 10, oid = 101;
			int nid = 11, noid = 111;;
			string name = "name", famyli = "famyli", mid_name = "otechestvo", dbdesc = "";
			employee_info ei(id, name, famyli, mid_name, dbdesc);
			ei.SetOtherId(oid);
			ei.SetOtherId(noid);
			Assert::AreEqual(noid, ei.GetOtherId());
		}

	};
}