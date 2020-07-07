#include "pch.h"
#include "CppUnitTest.h"
#include "..//MessageServer/winsock_init.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace messagetest
{
	TEST_CLASS(winsock_init_test)
	{
	public:

		TEST_METHOD(create)
		{
			winsock_init w;
		}

		TEST_METHOD(delet) 
		{
			winsock_init* w = new winsock_init();
			delete w;
		}
	};
}
