#include "pch.h"
#include "CppUnitTest.h"
#include "..///RecognitionBB/timer_list.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RecognitionBBtest_thead_obj
{
	double timett_t_sec = 0.01;

	TEST_CLASS(timer_list_test)
	{
	public:
		
		TEST_METHOD(create)
		{
			timer_list tl;
		}

		TEST_METHOD(create_an) 
		{
			timer_list tl(timett_t_sec);
		}
	};
}
