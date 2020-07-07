#include "pch.h"
#include "CppUnitTest.h"
#include "..//file_manager/Configuration.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;



namespace filemanagertest
{
	//Имя тестового файла
	std::string config_test_file = "config_file_test_name";
	//Имя параметра
	std::string config_param_name_1 = "parametr";
	//Значение параметра
	std::string config_param_value_1 = "valu1";
	//Имя параметра, которого нет в файле
	std::string config_not_exist_param_name_1 = "not_exist_parametr";


	std::string config_edit_name = "name_parametr_edit";
	std::string config_edit_value1 = "value_param1";
	std::string config_edit_value2 = "value_param2";
	std::string config_edit_value3 = "value_param3";


	TEST_CLASS(configuration_test)
	{
	public:

		TEST_METHOD(create)
		{
			Configuration conf(config_test_file);
		}

		TEST_METHOD(create_default)
		{
			Configuration conf;
		}

		TEST_METHOD(clear)
		{
			Configuration conf(config_test_file);
			conf.ClearFile();
		}


		TEST_METHOD(s1p01_create) 
		{
			Configuration conf(config_test_file);
		}

		TEST_METHOD(s1p02_add_param) 
		{
			Configuration conf(config_test_file);
			conf.SetParametr(config_param_name_1, config_param_value_1);
			conf.Save();
		}

		TEST_METHOD(s1p03_open_params) 
		{
			Configuration conf(config_test_file);
		}

		TEST_METHOD(s1p04_has_exist_paramter) 
		{
			Configuration conf(config_test_file);
			Assert::AreEqual(true, conf.HasParamert(config_param_name_1));
		}

		TEST_METHOD(s1p05_has_not_exist_parametr) 
		{
			Configuration conf(config_test_file);
			Assert::AreEqual(false, conf.HasParamert(config_not_exist_param_name_1));
		}

		TEST_METHOD(s1p06_get_parametr)
		{
			Configuration conf(config_test_file);
			conf.GetParametr(config_param_name_1);
		}

		TEST_METHOD(s1p07_get_not_exist_parametr) 
		{
			Configuration conf(config_test_file);
			bool exec = false;
			try {
				conf.GetParametr(config_not_exist_param_name_1);
			}
			catch (...) {
				exec = true;
			}

			Assert::AreEqual(true, exec);
		}

		TEST_METHOD(s1p08_check_param_value) 
		{
			Configuration conf(config_test_file);
			std::string res = conf.GetParametr(config_param_name_1);
			Assert::AreEqual(config_param_value_1, res);
		}

		TEST_METHOD(s1p09_set_paremtr) 
		{
			Configuration conf(config_test_file);
			conf.SetParametr(config_edit_name, config_edit_value1);
			conf.Save();
		}

		TEST_METHOD(s1p10_check_parametr_value) 
		{
			Configuration conf(config_test_file);
			Assert::AreEqual(config_edit_value1, conf.GetParametr(config_edit_name));
		}

		TEST_METHOD(s1p11_edit_parametr) 
		{
			Configuration conf(config_test_file);
			conf.SetParametr(config_edit_name, config_edit_value2);
		}

		TEST_METHOD(s1p12_check_edit) 
		{
			Configuration conf(config_test_file);
			conf.SetParametr(config_edit_name, config_edit_value2);
			Assert::AreEqual(config_edit_value2, conf.GetParametr(config_edit_name));
		}


		TEST_METHOD(s1p13_save_edit) 
		{
			Configuration conf(config_test_file);
			conf.SetParametr(config_edit_name, config_edit_value2);
			conf.Save();
		}

		TEST_METHOD(s1p14_check_edit) {
			Configuration conf(config_test_file);
			Assert::AreEqual(config_edit_value2, conf.GetParametr(config_edit_name));
		}


		TEST_METHOD(s1p15_edit2_save) 
		{
			Configuration conf(config_test_file);
			conf.SetParametr(config_edit_name, config_edit_value3);
			conf.Save();
		}

		TEST_METHOD(s1p16_edit2_check) 
		{
			Configuration conf(config_test_file);
			Assert::AreEqual(config_edit_value3, conf.GetParametr(config_edit_name));
		}

		TEST_METHOD(s1p97_clear) 
		{
			Configuration conf(config_test_file);
			conf.ClearFile();
		}

		TEST_METHOD(s1p98_is_empty)
		{
			Configuration conf(config_test_file);
			Assert::AreEqual(true, conf.IsEmpty());
		}


		TEST_METHOD(s1p99_check_clear)
		{
			Configuration conf(config_test_file);
			bool exec = false;
			try {
				conf.GetParametr(config_not_exist_param_name_1);
			}
			catch (...) {
				exec = true;
			}

			Assert::AreEqual(true, exec);

			exec = false;
			try {
				conf.GetParametr(config_param_name_1);
			}
			catch (...) {
				exec = true;
			}
			Assert::AreEqual(true, exec);
		}

	};
}
