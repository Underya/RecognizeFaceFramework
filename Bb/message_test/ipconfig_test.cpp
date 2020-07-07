#include "pch.h"
#include "CppUnitTest.h"
#include "..//MessageServer/Ipcofnig.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace std;

namespace messagetest
{

	std::string ipc_empty = "";

	TEST_CLASS(ipconfig_test)
	{
	public:

		TEST_METHOD(create)
		{
			Ipcofnig ip;
		}

		TEST_METHOD(ipv4_not_enmpty) 
		{
			Ipcofnig ip;
			Assert::AreNotEqual(ipc_empty, ip.GetIpV4());
		}

		TEST_METHOD(ipv4_test_format) 
		{
			Ipcofnig ip;
			std::string resIP = ip.GetIpV4();
			//Поиск 4 точек
			int point = 0;
			int index = 0;
			int res = -1;
			res = resIP.find('.', index);
			if (res != -1) {
				index = res + 1;
				point++;
			}
			res = resIP.find('.', index);
			if (res != -1) {
				index = res + 1;
				point++;
			}
			res = resIP.find('.', index);
			if (res != -1) {
				index = res + 1;
				point++;
			}
			Assert::AreEqual(3, point);
		}

		TEST_METHOD(ipv6_not_empty) 
		{
			Ipcofnig ip;
			Assert::AreNotEqual(ipc_empty, ip.GetIpV6());
		}

		TEST_METHOD(ipv6_format) 
		{
			Ipcofnig ip;
			int point = 0;
			int index = 0;
			int res = -1;
			std::string resIP = ip.GetIpV6();
			for (int i = 0; i < 5; i++) {
				res = resIP.find(':', index);
				if (res != -1) {
					index = res + 1;
					point++;
				}
			}

			Assert::AreEqual(5, point);
		}
	};
}
