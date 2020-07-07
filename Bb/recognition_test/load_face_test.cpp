#include "pch.h"
#include "CppUnitTest.h"
#include "..//face_recognition/add_load_face.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace recognitiontest
{
	TEST_CLASS(load_face_test)
	{
	public:

		TEST_METHOD(create)
		{
			add_load_face adlf;
		}

		TEST_METHOD(check_type)
		{
			std::string right = "based type";
			add_load_face adlf;
			Assert::AreEqual(right, adlf.GetType());
		}

	};
}