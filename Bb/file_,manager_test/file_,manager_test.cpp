#include "pch.h"
#include "CppUnitTest.h"
#include "..//file_manager/file_parametr.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;



namespace filemanagertest
{
	//Èלÿ עוסעמגמדמ פאיכא
	std::string test_filename = "test.file";
	std::string empty_str = "";


	TEST_CLASS(file_parametr_test)
	{
	public:
		
		TEST_METHOD(create)
		{
			file_parametr fp(test_filename);
		}

		TEST_METHOD(save) 
		{
			file_parametr fp(test_filename);
			fp.Save();
		}

		TEST_METHOD(clear) 
		{
			file_parametr fp(test_filename);
			fp.ClearFile();
		}

	};
}
