#include "pch.h"
#include "CppUnitTest.h"
#include "..//face_recognition/neironWeb.h"
#include "..//face_detection/Camera_file.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace recognitiontest
{
	//Тест всех остальных элементов библиотеки
	TEST_CLASS(neironWeb_test)
	{
	public:

		TEST_METHOD(create)
		{
			neironWeb web;
		}
	};
}