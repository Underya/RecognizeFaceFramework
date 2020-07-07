#include "pch.h"
#include "CppUnitTest.h"
#include "..//MessageServer/SendServer.h"
#include "..//MessageServer/ListenServer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace messagetest
{
	std::string listen_address = "127.0.0.3";
	std::string listen_port = "80000";
	std::string send_address = "127.0.0.4";
	std::string send_port = "80001";

	TEST_CLASS(send_and_listen_server)
	{
	public:

		TEST_METHOD(creat_listen_server)
		{
			ListenServer ls(listen_address, listen_port);
		}

		TEST_METHOD(listen_server_check_address) 
		{
			ListenServer ls(listen_address, listen_port);
			Assert::AreEqual(listen_address, ls.GetAddress());
		}

		TEST_METHOD(listen_server_check_port) 
		{
			ListenServer ls(listen_address, listen_port);
			Assert::AreEqual(listen_port, ls.GetPort());
		}

		
		TEST_METHOD(create_and_coder) 
		{
			ListenServer ls(listen_address, listen_port, true);
		}

		TEST_METHOD(check_coder) 
		{
			ListenServer ls(listen_address, listen_port, true);
			Assert::AreEqual(true, ls.HasCoder());
		}
		

		TEST_METHOD(set_coder) 
		{
			ListenServer ls(listen_address, listen_port, true);
			BlowfishCoder coder;
			ls.SetCoder(&coder);
		}

		TEST_METHOD(send_create) 
		{
			SendServer ss(send_address, send_port);
		}

		TEST_METHOD(send_check_addr) 
		{
			SendServer ss(send_address, send_port);
			Assert::AreEqual(send_address, ss.GetAddress());
		}

		TEST_METHOD(send_check_port) 
		{
			SendServer ss(send_address, send_port);
			Assert::AreEqual(send_port, ss.GetPort());
		}
		
		TEST_METHOD(send_create_coder) 
		{
			SendServer ss(send_address, send_port, true);
		}


		TEST_METHOD(send_check_coder) 
		{
			SendServer ss(send_address, send_port, true);
			Assert::AreEqual(true, ss.HasCoder());
		}

		TEST_METHOD(send_set_coder) 
		{
			SendServer ss(send_address, send_port, true);
			BlowfishCoder coder;
			ss.SetCoder(&coder);
		}
	};
}