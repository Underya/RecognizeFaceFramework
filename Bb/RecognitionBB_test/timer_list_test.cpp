#include "pch.h"
#include "CppUnitTest.h"
#include <thread>
#include "..////RecognitionBB/timer_list.h"

using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RecognitionBBtest_thead_obj
{
	double timett_t_sec = 0.01;
	int timett_t_milisec = 1000;

	int timett_obj1 = 1, timett_obj2 = 2, timett_obj3 = 3;

	TEST_CLASS(timer_list_test)
	{
	public:

		TEST_METHOD(create)
		{
			timer_list<int> tl;
		}

		TEST_METHOD(create_an)
		{
			timer_list<int> tl(timett_t_sec);
		}

		TEST_METHOD(add) 
		{
			timer_list<int> tl;
			tl.AddNewObject(timett_obj1);
		}

		TEST_METHOD(add_10) 
		{
			timer_list<int> tl;
			for (int i = 0; i < 10; i++) 
			{
				tl.EndTimeToObj(i);
			}
		}

		TEST_METHOD(check_add) 
		{
			timer_list<int> tl;
			tl.AddNewObject(timett_obj1);
			Assert::IsTrue(tl.CheckObj(timett_obj1));
		}

		TEST_METHOD(check_add_x10) 
		{
			timer_list<int> tl;
			for (int i = 0; i < 10; i++)
			{
				tl.AddNewObject(i);
			}
			for (int i = 0; i < 10; i++)
			{
				Assert::IsTrue(tl.CheckObj(i));
			}
		}


		TEST_METHOD(not_end_time) 
		{
			timer_list<int> tl;
			tl.AddNewObject(timett_obj1);
			Assert::IsFalse(tl.EndTimeToObj(timett_obj1));
		}

		TEST_METHOD(end_time) 
		{
			timer_list<int> tl;
			tl.AddNewObject(timett_obj1);
			this_thread::sleep_for(std::chrono::microseconds(timett_t_milisec));
			bool res = tl.EndTimeToObj(timett_obj1);
			Assert::IsFalse(res);
		}

		TEST_METHOD(pop_for_time) 
		{
			timer_list<int> tl;
			tl.AddNewObject(timett_obj1);
			this_thread::sleep_for(std::chrono::milliseconds(timett_t_milisec));
			tl.EndTimeToObj(timett_obj1);
			Assert::IsTrue(tl.CheckObj(timett_obj1));
		}
	};
}
