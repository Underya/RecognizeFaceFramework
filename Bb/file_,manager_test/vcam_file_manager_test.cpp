#include "pch.h"
#include "CppUnitTest.h"
#include "..//file_manager/vcam_file_manager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace filemanagertest
{
	std::string camera_file_name = "camera_file_name.test";

	std::string camera_address1 = "address_cam1", camera_address2 = "address_cam2";

	std::string camera_description1 = "camera_description_test1", camera_description2 = "camera_description_test2";

	std::string camera_addr_num = "21";

	int camera_addr_num_int = 21;

	int camera_id1 = 1, camera_id2 = 2;

	int camera_premission1 = 10, camera_premission2 = 11;

	std::string camera_position1 = "n", camera_position2 = "i";

	std::string camera_not_exist = "123";


	TEST_CLASS(file_vcam_test)
	{
	public:

		TEST_METHOD(create)
		{
			vcam_file_manager vfm(camera_file_name);
		}

		TEST_METHOD(create_default) 
		{
			vcam_file_manager vfm;
		}

		TEST_METHOD(s1p01_create) 
		{
			vcam_file_manager vfm(camera_file_name);
		}

		TEST_METHOD(s1p02_add_camear)
		{
			vcam_file_manager vfm(camera_file_name);
			vfm.AddNewCamera(camera_address1,  camera_description1, camera_premission1, camera_position1, camera_id1);
		}

		TEST_METHOD(s1p03_check_get) 
		{
			vcam_file_manager vfm(camera_file_name);
			vfm.AddNewCamera(camera_address1, camera_description1, camera_premission1, camera_position1, camera_id1);
			vcam_file cam = vfm.GetCamera(camera_id1);
		}

		TEST_METHOD(s1p04_id) 
		{
			vcam_file_manager vfm(camera_file_name);
			vfm.AddNewCamera(camera_address1, camera_description1, camera_premission1, camera_position1, camera_id1);
			vcam_file cam = vfm.GetCamera(camera_id1);
			Assert::AreEqual(camera_id1, cam.id);
		}

		TEST_METHOD(s1p05_address)
		{
			vcam_file_manager vfm(camera_file_name);
			vfm.AddNewCamera(camera_address1, camera_description1, camera_premission1, camera_position1, camera_id1);
			vcam_file cam = vfm.GetCamera(camera_id1);
			Assert::AreEqual(camera_address1, cam.address);
		}

		TEST_METHOD(s1p06_descr) 
		{
			vcam_file_manager vfm(camera_file_name);
			vfm.AddNewCamera(camera_address1, camera_description1, camera_premission1, camera_position1, camera_id1);
			vcam_file cam = vfm.GetCamera(camera_id1);
			Assert::AreEqual(camera_description1, cam.description);
		}

		TEST_METHOD(s1p07_id_position) 
		{
			vcam_file_manager vfm(camera_file_name);
			vfm.AddNewCamera(camera_address1, camera_description1, camera_premission1, camera_position1, camera_id1);
			vcam_file cam = vfm.GetCamera(camera_id1);
			Assert::AreEqual(camera_position1, cam.position);
		}

		TEST_METHOD(s1p08_id_premise)
		{
			vcam_file_manager vfm(camera_file_name);
			vfm.AddNewCamera(camera_address1, camera_description1, camera_premission1, camera_position1, camera_id1);
			vcam_file cam = vfm.GetCamera(camera_id1);
			Assert::AreEqual(camera_premission1, cam.id_premise);
		}

		TEST_METHOD(s1p09_set_num_addr) 
		{
			vcam_file_manager vfm(camera_file_name);
			vfm.AddNewCamera(camera_addr_num, camera_description2, camera_premission2, camera_position2, camera_id2);
			vcam_file cam = vfm.GetCamera(camera_id2);

		}

		TEST_METHOD(s1p10_check_num_addr)
		{
			vcam_file_manager vfm(camera_file_name);
			vfm.AddNewCamera(camera_addr_num, camera_description2, camera_premission2, camera_position2, camera_id2);
			vcam_file cam = vfm.GetCamera(camera_id2);
			Assert::AreEqual(true, cam.AddressIsNumber());
		}

		TEST_METHOD(s1p11_check_value_addr) 
		{
			vcam_file_manager vfm(camera_file_name);
			vfm.AddNewCamera(camera_addr_num, camera_description2, camera_premission2, camera_position2, camera_id2);
			vcam_file cam = vfm.GetCamera(camera_id2);
			Assert::AreEqual(camera_addr_num_int, cam.GetAddressNumber());
		}

		TEST_METHOD(s1p12_save) 
		{
			vcam_file_manager vfm(camera_file_name);
			vfm.AddNewCamera(camera_address1, camera_description1, camera_premission1, camera_position1, camera_id1);
			vfm.AddNewCamera(camera_addr_num, camera_description2, camera_premission2, camera_position2, camera_id2);
			vfm.Save();
		}

		TEST_METHOD(s1p13_open_save) 
		{
			vcam_file_manager vfm(camera_file_name);
		}

		TEST_METHOD(s1p14_check_get)
		{
			vcam_file_manager vfm(camera_file_name);
			vcam_file cam = vfm.GetCamera(camera_id1);
		}

		TEST_METHOD(s1p15_id)
		{
			vcam_file_manager vfm(camera_file_name);
			vcam_file cam = vfm.GetCamera(camera_id1);
			Assert::AreEqual(camera_id1, cam.id);
		}

		TEST_METHOD(s1p16_address)
		{
			vcam_file_manager vfm(camera_file_name);
			vcam_file cam = vfm.GetCamera(camera_id1);
			Assert::AreEqual(camera_address1, cam.address);
		}

		TEST_METHOD(s1p17_descr)
		{
			vcam_file_manager vfm(camera_file_name);
			vcam_file cam = vfm.GetCamera(camera_id1);
			Assert::AreEqual(camera_description1, cam.description);
		}

		TEST_METHOD(s1p18_id_position)
		{
			vcam_file_manager vfm(camera_file_name);
			vcam_file cam = vfm.GetCamera(camera_id1);
			Assert::AreEqual(camera_position1, cam.position);
		}

		TEST_METHOD(s1p19_id_premise)
		{
			vcam_file_manager vfm(camera_file_name);
			vcam_file cam = vfm.GetCamera(camera_id1);
			Assert::AreEqual(camera_premission1, cam.id_premise);
		}

		TEST_METHOD(s1p20_set_num_addr)
		{
			vcam_file_manager vfm(camera_file_name);
			vcam_file cam = vfm.GetCamera(camera_id2);

		}

		TEST_METHOD(s1p21_check_num_addr)
		{
			vcam_file_manager vfm(camera_file_name);
			vcam_file cam = vfm.GetCamera(camera_id2);
			Assert::AreEqual(true, cam.AddressIsNumber());
		}

		TEST_METHOD(s1p21_check_value_addr)
		{
			vcam_file_manager vfm(camera_file_name);
			vcam_file cam = vfm.GetCamera(camera_id2);
			Assert::AreEqual(camera_addr_num_int, cam.GetAddressNumber());
		}

		TEST_METHOD(s1p22_count) 
		{
			vcam_file_manager vfm(camera_file_name);
			Assert::AreEqual(2, (int)vfm.GetList()->size());
		}

		TEST_METHOD(s1p23_search) 
		{
			vcam_file_manager vfm(camera_file_name);
			Assert::AreEqual(camera_id1, vfm.SearchCamera(camera_address1));
		}

		TEST_METHOD(s1p23_search_error) 
		{
			vcam_file_manager vfm(camera_file_name);
			Assert::AreEqual(-1, vfm.SearchCamera(camera_not_exist));
		}

		TEST_METHOD(s1p98_clear_file) 
		{
			vcam_file_manager vfm(camera_file_name);
			vfm.ClearFile();
		}

		TEST_METHOD(sp99_check_clear) 
		{
			vcam_file_manager vfm(camera_file_name);
			std::list<vcam_file> *files = vfm.GetList();
			Assert::AreEqual(0, (int)files->size());
		}
	};
}
