#include "pch.h"
#include "CppUnitTest.h"
#include "..//file_manager/vcam_file.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace filemanagertest
{
	int vc_id = 1;

	std::string vc_addres = "addres_1";

	std::string vc_adress_num = "0";

	int vc_address_num_int = 0;

	std::string vc_position = "n";

	int vc_premise = 2;

	TEST_CLASS(vcam_test)
	{
	public:

		TEST_METHOD(create)
		{
			vcam_file vf;
		}

		TEST_METHOD(set_id) 
		{
			vcam_file vf;
			vf.id = vc_id;
		}

		TEST_METHOD(check_id) 
		{
			vcam_file vf;
			vf.id = vc_id;
			Assert::AreEqual(vc_id, vf.id);
		}

		TEST_METHOD(set_str_addr) 
		{
			vcam_file vf;
			vf.address = vc_addres;

		}

		TEST_METHOD(check_str_addr) 
		{
			vcam_file vf;
			vf.address = vc_addres;
			Assert::AreEqual(vc_addres, vf.address);
		}

		TEST_METHOD(set_number_add) 
		{
			vcam_file vf;
			vf.address = vc_adress_num;
		}

		TEST_METHOD(check_is_num)
		{
			vcam_file vf;
			vf.address = vc_adress_num;
			Assert::AreEqual(true, vf.AddressIsNumber());
		}

		TEST_METHOD(check_num_addr) 
		{
			vcam_file vf;
			vf.address = vc_adress_num;
			Assert::AreEqual(vc_address_num_int, vf.GetAddressNumber());
		}

		TEST_METHOD(check_is_wrong_num) 
		{
			vcam_file vf;
			vf.address = vc_addres;
			Assert::AreEqual(false, vf.AddressIsNumber());
		}

		TEST_METHOD(check_wrong_num_address) 
		{
			vcam_file vf;
			vf.address = vc_addres;
			bool exec = false;
			try {
				vf.GetAddressNumber();
			}
			catch (...) {
				exec = true;
			}

			Assert::AreEqual(true, exec);
		}

		TEST_METHOD(set_position)
		{
			vcam_file vf;
			vf.position = vc_position;
		}

		TEST_METHOD(check_position) 
		{
			vcam_file vf;
			vf.position = vc_position;
			Assert::AreEqual(vc_position, vf.position);
		}

		TEST_METHOD(set_premise) 
		{
			vcam_file vf;
			vf.id_premise = vc_premise;
		}

		TEST_METHOD(check_premise) 
		{
			vcam_file vf;
			vf.id_premise = vc_premise;
			Assert::AreEqual(vc_premise, vf.id_premise);
		}
	};
}