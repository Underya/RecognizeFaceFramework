#include "pch.h"
#include "CppUnitTest.h"
#include "..//MessageServer/BlowfishCoder.h"
#include "..//MessageServer/Message.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace messagetest
{

	//Тестирование кодирования и декадирования сообщений
	TEST_CLASS(coder_message)
	{
	public:

		TEST_METHOD(code_empty_mess)
		{
			BlowfishCoder coder;
			Message mess;
		 	const char* buff = mess.GetMessageToSend();
			int size = mess.GetSizeMessageToSend();
			int new_size = -1;
			coder.Coding(buff, size, new_size);
		}

		TEST_METHOD(code_empty_encode)
		{
			BlowfishCoder coder;
			Message mess;
			const char* buff = mess.GetMessageToSend();
			char *coder_mess = NULL,* encode_mess = NULL;
			int size = mess.GetSizeMessageToSend();
			int new_size = -1, encode_size = -1;
			coder_mess = coder.Coding(buff, size, new_size);
			encode_mess = coder.UnCodind(coder_mess, new_size, encode_size);
		}

		TEST_METHOD(code_empty_encode_size) 
		{
			BlowfishCoder coder;
			Message mess;
			const char* buff = mess.GetMessageToSend();
			char* coder_mess = NULL, * encode_mess = NULL;
			int size = mess.GetSizeMessageToSend();
			int new_size = -1, encode_size = -1;
			coder_mess = coder.Coding(buff, size, new_size);
			encode_mess = coder.UnCodind(coder_mess, new_size, encode_size);
			Assert::AreEqual(size, encode_size);
		}

		TEST_METHOD(code_empty_mess_for_char) 
		{
			BlowfishCoder coder;
			Message mess;
			const char* buff = mess.GetMessageToSend();
			char* coder_mess = NULL, * encode_mess = NULL;
			int size = mess.GetSizeMessageToSend();
			int new_size = -1, encode_size = -1;
			coder_mess = coder.Coding(buff, size, new_size);
			encode_mess = coder.UnCodind(coder_mess, new_size, encode_size);
			for (int i = 0; i < size; i++) {
				Assert::AreEqual(buff[i], encode_mess[i]);
			}
		}

		TEST_METHOD(coder_empty_for_message) 
		{
			BlowfishCoder coder;
			Message mess;
			const char* buff = mess.GetMessageToSend();
			char* coder_mess = NULL, * encode_mess = NULL;
			int size = mess.GetSizeMessageToSend();
			int new_size = -1, encode_size = -1;
			coder_mess = coder.Coding(buff, size, new_size);
			encode_mess = coder.UnCodind(coder_mess, new_size, encode_size);
			Message mess2(encode_mess, encode_size);
		}

		TEST_METHOD(coder_full_message) 
		{
			BlowfishCoder coder;
			Message mess;
			std::string first_name = "first_name";
			mess.SetFirstName(first_name);
			std::string last_name = "last_name";
			mess.SetLastName(last_name);
			std::string mid_name = "mid_name";
			mess.SetMidName(mid_name);


			const char* buff = mess.GetMessageToSend();
			int size = mess.GetSizeMessageToSend();
			int new_size = -1;
			coder.Coding(buff, size, new_size);
		}

		TEST_METHOD(code_full_encode_size)
		{
			BlowfishCoder coder;
			Message mess;
			std::string first_name = "first_name";
			mess.SetFirstName(first_name);
			std::string last_name = "last_name";
			mess.SetLastName(last_name);
			std::string mid_name = "mid_name";
			mess.SetMidName(mid_name);

			const char* buff = mess.GetMessageToSend();
			char* coder_mess = NULL, * encode_mess = NULL;
			int size = mess.GetSizeMessageToSend();
			int new_size = -1, encode_size = -1;
			coder_mess = coder.Coding(buff, size, new_size);
			encode_mess = coder.UnCodind(coder_mess, new_size, encode_size);
			Assert::AreEqual(size, encode_size);
		}


		TEST_METHOD(code_full_mess_for_char)
		{
			BlowfishCoder coder;
			Message mess;
			std::string first_name = "first_name";
			mess.SetFirstName(first_name);
			std::string last_name = "last_name";
			mess.SetLastName(last_name);
			std::string mid_name = "mid_name";
			mess.SetMidName(mid_name);

			const char* buff = mess.GetMessageToSend();
			char* coder_mess = NULL, * encode_mess = NULL;
			int size = mess.GetSizeMessageToSend();
			int new_size = -1, encode_size = -1;
			coder_mess = coder.Coding(buff, size, new_size);
			encode_mess = coder.UnCodind(coder_mess, new_size, encode_size);
			for (int i = 0; i < size; i++) {
				Assert::AreEqual(buff[i], encode_mess[i]);
			}
		}

		TEST_METHOD(coder_full_for_message)
		{
			BlowfishCoder coder;
			Message mess;
			std::string first_name = "first_name";
			mess.SetFirstName(first_name);
			std::string last_name = "last_name";
			mess.SetLastName(last_name);
			std::string mid_name = "mid_name";
			mess.SetMidName(mid_name);

			const char* buff = mess.GetMessageToSend();
			char* coder_mess = NULL, * encode_mess = NULL;
			int size = mess.GetSizeMessageToSend();
			int new_size = -1, encode_size = -1;
			coder_mess = coder.Coding(buff, size, new_size);
			encode_mess = coder.UnCodind(coder_mess, new_size, encode_size);
			Message mess2(encode_mess, encode_size);
		}

		TEST_METHOD(coder_full_for_message_check)
		{
			BlowfishCoder coder;
			Message mess;
			std::string first_name = "first_name";
			mess.SetFirstName(first_name);
			std::string last_name = "last_name";
			mess.SetLastName(last_name);
			std::string mid_name = "mid_name";
			mess.SetMidName(mid_name);

			const char* buff = mess.GetMessageToSend();
			char* coder_mess = NULL, * encode_mess = NULL;
			int size = mess.GetSizeMessageToSend();
			int new_size = -1, encode_size = -1;
			coder_mess = coder.Coding(buff, size, new_size);
			encode_mess = coder.UnCodind(coder_mess, new_size, encode_size);
			Message mess2(encode_mess, encode_size);
			Assert::AreEqual(mess.GetFirstName(), mess2.GetFirstName());
			Assert::AreEqual(mess.GetLastName(), mess2.GetLastName());
			Assert::AreEqual(mess.GetMidName(), mess2.GetMidName());
		}
	};
}