#include "pch.h"	
#include "CppUnitTest.h"
#include "..//db/db_vcam.h";

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace dbmanagertests
{

	int db_vcam_id_cam = -1;

	int db_vcam_id_premise1 = -2, db_vcam_id_premise2 = -3;

	TEST_CLASS(vcam_test)
	{
	public:

		TEST_METHOD_INITIALIZE(initialMethod)
		{
			// method initialization code
			db_connect::SetInfoConnect("localhost", "5432", "postgres", "1", "postgres", false);
		}

		TEST_METHOD(load)
		{
			db_vcam v(-2);
			db_vcam v1(-3);
		}

		TEST_METHOD(check_addr1)
		{
			std::string address = "test_address1", postit = "n", desc = "desc";
			db_vcam v(-2);
			Assert::AreEqual(v.GetAddress(), address);
		}

		TEST_METHOD(check_addr2)
		{
			std::string address = "0", postit = "n", desc = "desc";
			db_vcam v(-3);
			Assert::AreEqual(v.GetAddress(), address);
		}

		TEST_METHOD(check_pos)
		{
			std::string address = "test_address1", postit = "n", desc = "desc";
			db_vcam v(-2);
			Assert::AreEqual(v.GetPosition(), postit);
		}

		TEST_METHOD(check_desc)
		{
			std::string address = "test_address1", postit = "n", desc = "desc";
			db_vcam v(-2);
			Assert::AreEqual(v.GetDescription(), desc);
		}

		TEST_METHOD(check_user_id) 
		{
			db_vcam v(-2);
			Assert::AreEqual(-2, v.GetUserId());
		}

		TEST_METHOD(load_as_user)
		{
			std::vector<db_vcam> vec_cam = db_vcam::GetAllLinkVcam(-2);
			int id1 = -2, id2 = -3;

			db_vcam cam = vec_cam[0];
			if (cam.GetId() != id1 && cam.GetId() != id2) {
				Assert::Fail();
			}

			cam = vec_cam[1];
			if (cam.GetId() != id1 && cam.GetId() != id2) {
				Assert::Fail();
			}
		}

		TEST_METHOD(s1p1_edit_name)
		{
			std::string address = "test_address1", postit = "n", desc = "desc";
			std::string naddres = "test_add2", nposit = "o", ndesc = "n_desc";
			db_vcam cam(-2);
			cam.SetAddress(naddres);
			Assert::AreEqual(cam.GetAddress(), naddres);

			db_vcam cam2(-2);
			Assert::AreEqual(cam2.GetAddress(), naddres);
		}

		TEST_METHOD(s1p2_edit_desc)
		{
			std::string address = "test_address1", postit = "n", desc = "desc";
			std::string naddres = "test_add2", nposit = "o", ndesc = "n_desc";
			db_vcam cam(-2);
			cam.SetDescription(ndesc);
			Assert::AreEqual(cam.GetDescription(), ndesc);

			db_vcam cam2(-2);
			Assert::AreEqual(cam2.GetDescription(), ndesc);
		}

		TEST_METHOD(s1p3_edit_pos) 
		{
			std::string address = "test_address1", postit = "n", desc = "desc";
			std::string naddres = "test_add2", nposit = "o", ndesc = "n_desc";
			db_vcam cam(-2);
			cam.SetPosition(nposit);
			Assert::AreEqual(cam.GetPosition(), nposit);

			db_vcam cam2(-2);
			Assert::AreEqual(cam2.GetPosition(), nposit);
		}

		TEST_METHOD(s1p4_return_value) 
		{
			std::string address = "test_address1", postit = "n", desc = "desc";
			db_vcam cam(-2);
			cam.SetAddress(address);
			cam.SetDescription(desc);
			cam.SetPosition(postit);
		}

		TEST_METHOD(add_delete) 
		{
			std::string add = "1", p = "n";
			int user = -2;
			db_vcam newCam = db_vcam::addNewCamera(add, p, user);
			Assert::AreEqual(add, newCam.GetAddress());
			Assert::AreEqual(p, newCam.GetPosition());
			Assert::AreEqual(newCam.GetUserId(), user);
			int id = newCam.GetId();

			db_vcam newCam2(id);
			Assert::AreEqual(add, newCam2.GetAddress());
			Assert::AreEqual(p, newCam2.GetPosition());
			Assert::AreEqual(newCam2.GetUserId(), user);

			newCam2.Delete();

			bool exec = false;
			try{
				db_vcam cam3(id);
			}
			catch (...) {
				exec = true;
			}

			if (!exec) {
				Assert::Fail();
			}

		}
	
		TEST_METHOD(edit_wrong_params)
		{
			db_vcam d(-3);
			bool exec = false;
			try {
				d.SetPosition("e");
			}
			catch (...) {
				exec = true;
			}
			if (!exec) {
				Assert::Fail();
			}
		}

		TEST_METHOD(add_wrong_params) 
		{
			bool exec = false;
			try {
				db_vcam::addNewCamera("dadwadawdawdawdwa", "z", -2, -1);
			}
			catch (...) {
				exec = true;
			}
			if (!exec) {
				Assert::Fail();
			}
		}

		TEST_METHOD(s2p01_add_premise) 
		{
			db_vcam_id_premise1 = db_premise::AddNewPremise("db_vcam_premise_test1").GetId();
			db_vcam_id_premise2 = db_premise::AddNewPremise("db_vcam_premise_test2").GetId();
		}

		TEST_METHOD(s2p02_create_cam) 
		{
			db_vcam_id_cam = db_vcam::addNewCamera("create_test_cam_addr", "n", -2, db_vcam_id_premise1).GetId();

		}

		TEST_METHOD(s2p03_check_premise) 
		{
			db_vcam cam(db_vcam_id_cam);
			Assert::AreEqual(db_vcam_id_premise1, cam.GetPremise().GetId());
		}

		TEST_METHOD(s2p04_edite_premise) 
		{
			db_vcam cam(db_vcam_id_cam);
			cam.SetPremise(db_vcam_id_premise2);
		}

		TEST_METHOD(s2p05_check_edite) 
		{
			db_vcam cam(db_vcam_id_cam);
			Assert::AreEqual(db_vcam_id_premise2, cam.GetPremise().GetId());
		}

		TEST_METHOD(s2p06_delet_cam) 
		{
			db_vcam cam(db_vcam_id_cam);
			cam.Delete();
		}

		TEST_METHOD(s2p07_delet_premise) 
		{
			db_premise prem1(db_vcam_id_premise1);
			prem1.Delete();
			db_premise prem2(db_vcam_id_premise2);
			prem2.Delete();
		}
	};
}
