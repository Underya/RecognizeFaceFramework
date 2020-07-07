#include "pch.h"
#include "CppUnitTest.h"
#include "..//MessageServer/ListenSocket.h"
#include "..///MessageServer/SendSocket.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace messagetest
{
	TEST_CLASS(listen_and_send_socket)
	{
	public:

		TEST_METHOD(create_send_socket) 
		{
			SendSocket ss("127.12.12.12", "999000");
		}

		TEST_METHOD(create_listen_socket) 
		{
			ListenSocket ls("128.1.1.1", "900000");
		}

		TEST_METHOD(send_error_mess) 
		{
			Message mess;
			mess.SetFirstName("xyz");
			SendSocket ss("127.12.12.12", "999000");
			bool exec = false;
			try {
				ss.SendMess(mess, "122.0.0.0", "90000");
			}
			catch (...) {
				exec = true;
			}

			Assert::AreEqual(true, exec);
		}
	};
}
