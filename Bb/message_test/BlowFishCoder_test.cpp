#include "pch.h"
#include "CppUnitTest.h"
#include "..//MessageServer/BlowfishCoder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace messagetest
{

	TEST_CLASS(coder)
	{
	public:

		TEST_METHOD(create_coder)
		{
			BlowfishCoder coder;
		}

		TEST_METHOD(create_coder_block_64)
		{
			BlowfishCoder coder(64);
		}

		TEST_METHOD(create_coder_block_128)
		{
			BlowfishCoder coder(128);
		}

		TEST_METHOD(create_coder_block_4096)
		{
			BlowfishCoder coder(4096);
		}

		TEST_METHOD(create_coder_block_error_33)
		{
			bool exec = false;
			try {
				BlowfishCoder coder(33);
			}
			catch (...) {
				exec = true;
			}

			Assert::IsTrue(exec);

		}

		TEST_METHOD(create_coder_block_error_1)
		{
			bool exec = false;
			try {
				BlowfishCoder coder(1);
			}
			catch (...) {
				exec = true;
			}

			Assert::IsTrue(exec);
		}

		TEST_METHOD(create_coder_block_error_0)
		{
			bool exec = false;
			try {
				BlowfishCoder coder(0);
			}
			catch (...) {
				exec = true;
			}

			Assert::IsTrue(exec);
		}

		TEST_METHOD(create_coder_block_error_minus_1)
		{
			bool exec = false;
			try {
				BlowfishCoder coder(-1);
			}
			catch (...) {
				exec = true;
			}

			Assert::IsTrue(exec);
		}

		TEST_METHOD(create_key)
		{
			char s[56];
			for (int i = 0; i < 56; i++)
				s[i] = i + 20;
			BlowfishCoder coder((char*)s);
		}

		TEST_METHOD(create_error_key)
		{
			char s[1];
			for (int i = 0; i < 1; i++)
				s[i] = i + 20;
			BlowfishCoder coder((char*)s);
		}

		TEST_METHOD(create_key_and_block_64)
		{
			char s[56];
			for (int i = 0; i < 56; i++)
				s[i] = i + 20;
			BlowfishCoder coder((char*)s, 64);
		}

		TEST_METHOD(create_key_and_block_4096)
		{
			char s[56];
			for (int i = 0; i < 56; i++)
				s[i] = i + 20;
			BlowfishCoder coder((char*)s, 4096);
		}

		TEST_METHOD(create_key_and_error_block_65)
		{
			char s[56];
			for (int i = 0; i < 56; i++)
				s[i] = i + 20;
			bool exec = false;
			try {
				BlowfishCoder coder((char*)s, 65);
			}
			catch (...) {
				exec = true;
			}

			Assert::IsTrue(exec);
		}

		TEST_METHOD(create_key_adn_error_block_0)
		{
			char s[56];
			for (int i = 0; i < 56; i++)
				s[i] = i + 20;
			bool exec = false;
			try {
				BlowfishCoder coder((char*)s, 0);
			}
			catch (...) {
				exec = true;
			}

			Assert::IsTrue(exec);
		}

		TEST_METHOD(create_key_adn_error_block_minus1)
		{
			char s[56];
			for (int i = 0; i < 56; i++)
				s[i] = i + 20;
			bool exec = false;
			try {
				BlowfishCoder coder((char*)s, -1);
			}
			catch (...) {
				exec = true;
			}

			Assert::IsTrue(exec);
		}

		TEST_METHOD(coder_default)
		{
			BlowfishCoder coder;
			int size_mess = 100;
			int new_size = -1;
			char* mess = new char[100]();
			for (int i = 0; i < size_mess; i++) mess[i] = 'a';
			coder.Coding(mess, size_mess, new_size);
		}

		TEST_METHOD(coder_check)
		{
			BlowfishCoder coder;
			int size_mess = 100;
			int new_size = -1;
			char* mess = new char[100]();
			char* res = NULL;
			int equal_sim = 0;
			for (int i = 0; i < size_mess; i++) mess[i] = 'a';
			res = coder.Coding(mess, size_mess, new_size);
			for (int i = 0; i < size_mess; i++) {
				if (mess[i] == res[i]) {
					equal_sim++;
				}
			}

			if (equal_sim > new_size / 2) Assert::Fail();
		}

		TEST_METHOD(coder_check_size)
		{
			int block_size_default = 256;
			BlowfishCoder coder;
			int size_mess = 100;
			int new_size = -1;
			char* mess = new char[100]();
			char* res = NULL;
			int equal_sim = 0;
			for (int i = 0; i < size_mess; i++) mess[i] = 'a';
			res = coder.Coding(mess, size_mess, new_size);
			Assert::AreEqual(block_size_default, new_size);
		}

		TEST_METHOD(coder_check_not_def_size_256)
		{
			int block_size_default = 256;
			int new_block_size = 128;
			BlowfishCoder coder(new_block_size);
			int size_mess = 100;
			int new_size = -1;
			char* mess = new char[100]();
			char* res = NULL;
			int equal_sim = 0;
			for (int i = 0; i < size_mess; i++) mess[i] = 'a';
			res = coder.Coding(mess, size_mess, new_size);
			Assert::AreEqual(new_block_size, new_size);
		}

		TEST_METHOD(coder_check_not_def_size_1024)
		{
			int block_size_default = 256;
			int new_block_size = 1024;
			BlowfishCoder coder(new_block_size);
			int size_mess = 100;
			int new_size = -1;
			char* mess = new char[100]();
			char* res = NULL;
			int equal_sim = 0;
			for (int i = 0; i < size_mess; i++) mess[i] = 'a';
			res = coder.Coding(mess, size_mess, new_size);
			Assert::AreEqual(new_block_size, new_size);
		}

		TEST_METHOD(coder_check_mess_not_def_size_1024)
		{
			int block_size_default = 256;
			int new_block_size = 1024;
			BlowfishCoder coder(new_block_size);
			int size_mess = 100;
			int new_size = -1;
			char* mess = new char[100]();
			char* res = NULL;
			int equal_sim = 0;
			for (int i = 0; i < size_mess; i++) mess[i] = 'a';
			res = coder.Coding(mess, size_mess, new_size);
			for (int i = 0; i < size_mess; i++) {
				if (mess[i] == res[i]) {
					equal_sim++;
				}
			}

			if (equal_sim > new_size / 2) Assert::Fail();
		}

		TEST_METHOD(coder_uncode) 
		{
			int block_size_default = 256;
			int new_block_size = 1024;
			BlowfishCoder coder;
			int size_mess = 100;
			int new_size = -1, encode_size = -1;
			char* mess = new char[100]();
			char* res = NULL;
			char* encode_mess = NULL;
			int equal_sim = 0;
			for (int i = 0; i < size_mess; i++) mess[i] = 'a';
			res = coder.Coding(mess, size_mess, new_size);
			encode_mess = coder.UnCodind(res, new_size, encode_size);

		}

		TEST_METHOD(coder_uncode_check_size) 
		{
			int block_size_default = 256;
			int new_block_size = 1024;
			BlowfishCoder coder;
			int size_mess = 100;
			int new_size = -1, encode_size = -1;
			char* mess = new char[100]();
			char* res = NULL;
			char* encode_mess = NULL;
			int equal_sim = 0;
			for (int i = 0; i < size_mess; i++) mess[i] = 'a';
			res = coder.Coding(mess, size_mess, new_size);
			encode_mess = coder.UnCodind(res, new_size, encode_size);
			Assert::AreEqual(size_mess, encode_size);
		}

		TEST_METHOD(coder_uncode_check) 
		{
			int block_size_default = 256;
			int new_block_size = 1024;
			BlowfishCoder coder;
			int size_mess = 100;
			int new_size = -1, encode_size = -1;
			char* mess = new char[100]();
			char* res = NULL;
			char* encode_mess = NULL;
			int equal_sim = 0;
			for (int i = 0; i < size_mess; i++) mess[i] = 'a';
			res = coder.Coding(mess, size_mess, new_size);
			encode_mess = coder.UnCodind(res, new_size, encode_size);
			for (int i = 0; i < encode_size; i++) 
			{
				Assert::AreEqual(mess[i], encode_mess[i]);
			}
		}

		TEST_METHOD(coder_unblock_not_default_1024) 
		{
			int block_size_default = 256;
			int new_block_size = 1024;
			BlowfishCoder coder(new_block_size);
			int size_mess = 100;
			int new_size = -1, encode_size = -1;
			char* mess = new char[100]();
			char* res = NULL;
			char* encode_mess = NULL;
			int equal_sim = 0;
			for (int i = 0; i < size_mess; i++) mess[i] = 'a';
			res = coder.Coding(mess, size_mess, new_size);
			encode_mess = coder.UnCodind(res, new_size, encode_size);
		}

		TEST_METHOD(coder_uncoder_not_default_1024_check_size) 
		{
			int block_size_default = 256;
			int new_block_size = 1024;
			BlowfishCoder coder(new_block_size);
			int size_mess = 100;
			int new_size = -1, encode_size = -1;
			char* mess = new char[100]();
			char* res = NULL;
			char* encode_mess = NULL;
			int equal_sim = 0;
			for (int i = 0; i < size_mess; i++) mess[i] = 'a';
			res = coder.Coding(mess, size_mess, new_size);
			encode_mess = coder.UnCodind(res, new_size, encode_size);
			Assert::AreEqual(size_mess, encode_size);
		}

		TEST_METHOD(coder_uncoder_not_default_1024_check)
		{
			int block_size_default = 256;
			int new_block_size = 1024;
			BlowfishCoder coder(new_block_size);
			int size_mess = 100;
			int new_size = -1, encode_size = -1;
			char* mess = new char[100]();
			char* res = NULL;
			char* encode_mess = NULL;
			int equal_sim = 0;
			for (int i = 0; i < size_mess; i++) mess[i] = 'a';
			res = coder.Coding(mess, size_mess, new_size);
			encode_mess = coder.UnCodind(res, new_size, encode_size);
			for (int i = 0; i < encode_size; i++)
			{
				Assert::AreEqual(mess[i], encode_mess[i]);
			}
		}
	};
}