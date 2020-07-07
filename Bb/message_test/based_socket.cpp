#include "pch.h"
#include "CppUnitTest.h"
#include "..//MessageServer/BasedSocket.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace messagetest
{
	TEST_CLASS(basedSocket_test)
	{
	public:

		TEST_METHOD(create_127)
		{
			BasedSocket sock("127.0.0.1", "8000");
		}

		TEST_METHOD(create_192) 
		{
			BasedSocket sock("192.168.1.1", "2342");
		}

		TEST_METHOD(create_rand_addr)
		{
			BasedSocket sock("189.14.14.1", "1233");
		}

		TEST_METHOD(check_addr) 
		{
			std::string addr = "192.168.1.1";
			BasedSocket sock(addr, "2342");
			Assert::AreEqual(addr, sock.GetAddress());
		}


		TEST_METHOD(check_port) 
		{
			std::string addr = "192.168.1.1", port = "2342";
			BasedSocket sock(addr, port);
			Assert::AreEqual(port, sock.GetPort());
		}
	};
}
