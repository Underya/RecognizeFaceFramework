#include "pch.h"
#include "CppUnitTest.h"
#include "..//MessageServer/recipient.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace std;

namespace messagetest
{
	std::string recipient_address = "127.0.0.4";
	std::string recipient_port = "80001";

	std::string recipient_address2 = "127.0.0.5";
	std::string recipient_port2 = "80002";

	int rec_rule1 = 1, rec_rule2 = 2, rec_rule3 = 3;
	int rec_group1 = 4, rec_group2 = 5, rec_group3 = 6;

	TEST_CLASS(recipient_test)
	{
	public:

		TEST_METHOD(creat_epmty)
		{
			Recipient rec;
		}

		TEST_METHOD(create_addr_and_port) 
		{
			Recipient rec(recipient_address, recipient_port);
		}

		TEST_METHOD(check_construct_addr) 
		{
			Recipient rec(recipient_address, recipient_port);
			Assert::AreEqual(recipient_address, rec.GetAddress());
		}

		TEST_METHOD(check_construct_port) 
		{
			Recipient rec(recipient_address, recipient_port);
			Assert::AreEqual(recipient_port, rec.GetPort());
		}

		TEST_METHOD(create_summ_addr) 
		{
			std::string sum_addr = recipient_address + ":" + recipient_port;
			Recipient rec(sum_addr);
		}

		TEST_METHOD(check_summ_addr) 
		{
			std::string sum_addr = recipient_address + ":" + recipient_port;
			Recipient rec(sum_addr);
			Assert::AreEqual(recipient_address, rec.GetAddress());
		}

		TEST_METHOD(check_summ_port) 
		{
			std::string sum_addr = recipient_address + ":" + recipient_port;
			Recipient rec(sum_addr);
			Assert::AreEqual(recipient_port, rec.GetPort());
		}

		TEST_METHOD(empty_set_addr) 
		{
			Recipient rec;
			rec.SetAddress(recipient_address);
		}

		TEST_METHOD(empty_check_addr) 
		{
			Recipient rec;
			rec.SetAddress(recipient_address);
			Assert::AreEqual(recipient_address, rec.GetAddress());
		}

		TEST_METHOD(empty_set_port) 
		{
			Recipient rec;
			rec.SetPortRecepient(recipient_port);
		}

		TEST_METHOD(empty_check_port) 
		{
			Recipient rec;
			rec.SetPortRecepient(recipient_port);
			Assert::AreEqual(recipient_port, rec.GetPort());
		}
			
		TEST_METHOD(get_not_set_addr) 
		{
			Recipient rec;
			bool exec = false;
			try {
				rec.GetAddress();
			}
			catch (...) {
				exec = true;
			}
			Assert::IsTrue(exec);
		}

		TEST_METHOD(get_not_set_port) 
		{
			Recipient rec;
			bool exec = false;
			try {
				rec.GetPort();
			}
			catch (...) {
				exec = true;
			}
			Assert::IsTrue(exec);
		}

		TEST_METHOD(set_addr_get_port) {
			Recipient rec;
			rec.SetAddress(recipient_address);
			bool exec = false;
			try {
				rec.GetPort();
			}
			catch (...) {
				exec = true;
			}
			Assert::IsTrue(exec);
		}

		TEST_METHOD(set_port_get_addr) {
			Recipient rec;
			rec.SetPortRecepient(recipient_port);
			bool exec = false;
			try {
				rec.GetAddress();
			}
			catch (...) {
				exec = true;
			}
			Assert::IsTrue(exec);
		}

		TEST_METHOD(edit_addr_construct) 
		{
			std::string sum_addr = recipient_address + ":" + recipient_port;
			Recipient rec(sum_addr);
			rec.SetAddress(recipient_address2);
		}

		TEST_METHOD(check_edit_addr) 
		{
			std::string sum_addr = recipient_address + ":" + recipient_port;
			Recipient rec(sum_addr);
			rec.SetAddress(recipient_address2);
			Assert::AreEqual(recipient_address2, rec.GetAddress());
		}

		TEST_METHOD(edit_port_construct) 
		{
			std::string sum_addr = recipient_address + ":" + recipient_port;
			Recipient rec(sum_addr);
			rec.SetPortRecepient(recipient_port2);
		}

		TEST_METHOD(check_edit_port_construct) 
		{
			std::string sum_addr = recipient_address + ":" + recipient_port;
			Recipient rec(sum_addr);
			rec.SetPortRecepient(recipient_port2);
			Assert::AreEqual(recipient_port2, rec.GetPort());
		}

		TEST_METHOD(set_server) 
		{
			Recipient rec(recipient_address, recipient_port);
			SendServer ss("127.0.10.1", "90001");
			rec.SetSendServer(&ss);
		}

		TEST_METHOD(add_class_pair) 
		{
			grPair pair;
			Recipient rec(recipient_address, recipient_port);
			rec.AddPair(pair);
		}

		TEST_METHOD(add_vec_pair)
		{
			Recipient rec(recipient_address, recipient_port);
			rec.AddPair({ rec_group1 }, { rec_rule1 });
		}

		TEST_METHOD(add_3_class_pair) 
		{
			grPair pair1, pair2, pair3;
			pair1.AddRule(rec_rule1);
			pair2.AddGroup(rec_group1);
			pair2.AddRule(rec_rule2);
			pair2.AddGroup(rec_group2);
			pair3.AddRule(rec_rule3);
			pair3.AddGroup(rec_group3);
			Recipient rec(recipient_address, recipient_port);
			rec.AddPair(pair1);
			rec.AddPair(pair2);
			rec.AddPair(pair3);
		}

		TEST_METHOD(add_3_vec_pair) 
		{
			Recipient rec(recipient_address, recipient_port);
			rec.AddPair({ rec_group1 }, { rec_rule1 });
			rec.AddPair({ rec_group2 }, { rec_rule2 });
			rec.AddPair({ rec_group3 }, { rec_rule3 });
		}

		TEST_METHOD(add_2_method) 
		{
			Recipient rec(recipient_address, recipient_port);
			rec.AddPair({ rec_group1 }, { rec_rule1 });
			grPair pair3;
			pair3.AddRule(rec_rule3);
			pair3.AddGroup(rec_group3);
			rec.AddPair(pair3);
		}

		TEST_METHOD(send_not_server) 
		{
			Recipient rec(recipient_address, recipient_port);
			Message mess;
			bool exec = false;
			try {
				rec.SendMess(mess);
			}
			catch (...) {
				exec = true;
			}

			Assert::IsTrue(exec);
		}

		TEST_METHOD(check_send_vec_true) 
		{
			Recipient rec(recipient_address, recipient_port);
			rec.AddPair({ rec_group1 }, { rec_rule1 });
			bool res = false;
			
			res = rec.CheckList({ rec_rule1 }, { rec_group1 });

			Assert::IsTrue(res);
		}

		TEST_METHOD(check_send_vec_false)
		{
			Recipient rec(recipient_address, recipient_port);
			rec.AddPair({ rec_group1 }, { rec_rule1 });
			bool res = false;

			res = rec.CheckList({ rec_rule2 }, { rec_group2 });

			Assert::IsFalse(res);
		}

		TEST_METHOD(check_send_vec_3_pair_1_true) 
		{
			Recipient rec(recipient_address, recipient_port);
			rec.AddPair({ rec_group1 }, { rec_rule1 });
			rec.AddPair({ rec_group2 }, { rec_rule2 });
			rec.AddPair({ rec_group3 }, { rec_rule3 });
			bool res = false;

			res = rec.CheckList({ rec_rule1 }, { rec_group1 });

			Assert::IsTrue(res);
		}

		TEST_METHOD(check_send_vec_3_pair_2_true)
		{
			Recipient rec(recipient_address, recipient_port);
			rec.AddPair({ rec_group1 }, { rec_rule1 });
			rec.AddPair({ rec_group2 }, { rec_rule2 });
			rec.AddPair({ rec_group3 }, { rec_rule3 });
			bool res = false;

			res = rec.CheckList({ rec_rule2 }, { rec_group2 });

			Assert::IsTrue(res);
		}

		TEST_METHOD(check_send_vec_3_pair_3_true)
		{
			Recipient rec(recipient_address, recipient_port);
			rec.AddPair({ rec_group1 }, { rec_rule1 });
			rec.AddPair({ rec_group2 }, { rec_rule2 });
			rec.AddPair({ rec_group3 }, { rec_rule3 });
			bool res = false;

			res = rec.CheckList({ rec_rule3 }, { rec_group3 });

			Assert::IsTrue(res);
		}

		TEST_METHOD(check_send_vec_3_pair_1_false)
		{
			Recipient rec(recipient_address, recipient_port);
			rec.AddPair({ rec_group1 }, { rec_rule1 });
			rec.AddPair({ rec_group2 }, { rec_rule2 });
			rec.AddPair({ rec_group3 }, { rec_rule3 });
			bool res = false;

			res = rec.CheckList({ rec_rule1}, { rec_group2 });

			Assert::IsFalse(res);
		}


		TEST_METHOD(check_send_vec_3_pair_2_false)
		{
			Recipient rec(recipient_address, recipient_port);
			rec.AddPair({ rec_group1 }, { rec_rule1 });
			rec.AddPair({ rec_group2 }, { rec_rule2 });
			rec.AddPair({ rec_group3 }, { rec_rule3 });
			bool res = false;

			res = rec.CheckList({ rec_rule2 }, { rec_group1 });

			Assert::IsFalse(res);
		}


		TEST_METHOD(check_send_vec_pair_in_2_variant_1_true) 
		{
			Recipient rec(recipient_address, recipient_port);
			rec.AddPair({ rec_group1, rec_group2 }, { rec_rule1, rec_rule2 });
			bool res = false;

			res = rec.CheckList({ rec_rule1 }, { rec_group1 });

			Assert::IsTrue(res);
		}

		TEST_METHOD(check_send_vec_pair_in_2_variant_2_true)
		{
			Recipient rec(recipient_address, recipient_port);
			rec.AddPair({ rec_group1, rec_group2 }, { rec_rule1, rec_rule2 });
			bool res = false;

			res = rec.CheckList({ rec_rule2 }, { rec_group2 });

			Assert::IsTrue(res);
		}

		TEST_METHOD(check_send_vec_pair_in_2_variant_3_true)
		{
			Recipient rec(recipient_address, recipient_port);
			rec.AddPair({ rec_group1, rec_group2 }, { rec_rule1, rec_rule2 });
			bool res = false;

			res = rec.CheckList({ rec_rule1 }, { rec_group2 });

			Assert::IsTrue(res);
		}

		TEST_METHOD(check_send_vec_pair_in_2_variant_4_true)
		{
			Recipient rec(recipient_address, recipient_port);
			rec.AddPair({ rec_group1, rec_group2 }, { rec_rule1, rec_rule2 });
			bool res = false;

			res = rec.CheckList({ rec_rule2 }, { rec_group1 });

			Assert::IsTrue(res);
		}

		TEST_METHOD(check_send_class_true)
		{
			Recipient rec(recipient_address, recipient_port);
			grPair pair;
			pair.AddGroup(rec_group1);
			pair.AddRule(rec_rule1);
			rec.AddPair(pair);
			bool res = false;

			res = rec.CheckList({ rec_rule1 }, { rec_group1 });

			Assert::IsTrue(res);
		}

		TEST_METHOD(check_send_class_false)
		{
			Recipient rec(recipient_address, recipient_port);
			grPair pair;
			pair.AddGroup(rec_group1);
			pair.AddRule(rec_rule1);
			rec.AddPair(pair);
			bool res = false;

			res = rec.CheckList({ rec_rule2 }, { rec_group2 });

			Assert::IsFalse(res);
		}

		TEST_METHOD(check_send_class_3_pair_1_true)
		{
			Recipient rec(recipient_address, recipient_port);
			grPair pair1, pair2, pair3;
			pair1.AddGroup(rec_group1);
			pair1.AddRule(rec_rule1);
			pair2.AddGroup(rec_group2);
			pair2.AddRule(rec_rule2);
			pair3.AddGroup(rec_group3);
			pair3.AddRule(rec_rule3);
			rec.AddPair(pair1);
			rec.AddPair(pair2);
			rec.AddPair(pair3);
			bool res = false;

			res = rec.CheckList({ rec_rule1 }, { rec_group1 });

			Assert::IsTrue(res);
		}

		TEST_METHOD(check_send_class_3_pair_2_true)
		{
			Recipient rec(recipient_address, recipient_port);
			grPair pair1, pair2, pair3;
			pair1.AddGroup(rec_group1);
			pair1.AddRule(rec_rule1);
			pair2.AddGroup(rec_group2);
			pair2.AddRule(rec_rule2);
			pair3.AddGroup(rec_group3);
			pair3.AddRule(rec_rule3);
			rec.AddPair(pair1);
			rec.AddPair(pair2);
			rec.AddPair(pair3);
			bool res = false;

			res = rec.CheckList({ rec_rule2 }, { rec_group2 });

			Assert::IsTrue(res);
		}

		TEST_METHOD(check_send_class_3_pair_3_true)
		{
			Recipient rec(recipient_address, recipient_port);
			grPair pair1, pair2, pair3;
			pair1.AddGroup(rec_group1);
			pair1.AddRule(rec_rule1);
			pair2.AddGroup(rec_group2);
			pair2.AddRule(rec_rule2);
			pair3.AddGroup(rec_group3);
			pair3.AddRule(rec_rule3);
			rec.AddPair(pair1);
			rec.AddPair(pair2);
			rec.AddPair(pair3);
			bool res = false;

			res = rec.CheckList({ rec_rule3 }, { rec_group3 });

			Assert::IsTrue(res);
		}

		TEST_METHOD(check_send_class_3_pair_1_false)
		{
			Recipient rec(recipient_address, recipient_port);
			grPair pair1, pair2, pair3;
			pair1.AddGroup(rec_group1);
			pair1.AddRule(rec_rule1);
			pair2.AddGroup(rec_group2);
			pair2.AddRule(rec_rule2);
			pair3.AddGroup(rec_group3);
			pair3.AddRule(rec_rule3);
			rec.AddPair(pair1);
			rec.AddPair(pair2);
			rec.AddPair(pair3);
			bool res = false;

			res = rec.CheckList({ rec_rule1 }, { rec_group2 });

			Assert::IsFalse(res);
		}


		TEST_METHOD(check_send_class_3_pair_2_false)
		{
			Recipient rec(recipient_address, recipient_port);
			grPair pair1, pair2, pair3;
			pair1.AddGroup(rec_group1);
			pair1.AddRule(rec_rule1);
			pair2.AddGroup(rec_group2);
			pair2.AddRule(rec_rule2);
			pair3.AddGroup(rec_group3);
			pair3.AddRule(rec_rule3);
			rec.AddPair(pair1);
			rec.AddPair(pair2);
			rec.AddPair(pair3);
			bool res = false;

			res = rec.CheckList({ rec_rule2 }, { rec_group1 });

			Assert::IsFalse(res);
		}


		TEST_METHOD(check_send_class_pair_in_2_variant_1_true)
		{
			Recipient rec(recipient_address, recipient_port);
			grPair pair1;
			pair1.AddGroup(rec_group1);
			pair1.AddGroup(rec_group2);
			pair1.AddRule(rec_rule1);
			pair1.AddRule(rec_rule2);
			rec.AddPair(pair1);
			bool res = false;

			res = rec.CheckList({ rec_rule1 }, { rec_group1 });

			Assert::IsTrue(res);
		}

		TEST_METHOD(check_send_class_pair_in_2_variant_2_true)
		{
			Recipient rec(recipient_address, recipient_port);
			grPair pair1;
			pair1.AddGroup(rec_group1);
			pair1.AddGroup(rec_group2);
			pair1.AddRule(rec_rule1);
			pair1.AddRule(rec_rule2);
			rec.AddPair(pair1);
			bool res = false;

			res = rec.CheckList({ rec_rule2 }, { rec_group2 });

			Assert::IsTrue(res);
		}

		TEST_METHOD(check_send_class_pair_in_2_variant_3_true)
		{
			Recipient rec(recipient_address, recipient_port);
			grPair pair1;
			pair1.AddGroup(rec_group1);
			pair1.AddGroup(rec_group2);
			pair1.AddRule(rec_rule1);
			pair1.AddRule(rec_rule2);
			rec.AddPair(pair1);
			bool res = false;


			res = rec.CheckList({ rec_rule1 }, { rec_group2 });

			Assert::IsTrue(res);
		}

		TEST_METHOD(check_send_class_pair_in_2_variant_4_true)
		{
			Recipient rec(recipient_address, recipient_port);
			grPair pair1;
			pair1.AddGroup(rec_group1);
			pair1.AddGroup(rec_group2);
			pair1.AddRule(rec_rule1);
			pair1.AddRule(rec_rule2);
			rec.AddPair(pair1);
			bool res = false;

			res = rec.CheckList({ rec_rule2 }, { rec_group1 });

			Assert::IsTrue(res);
		}

		TEST_METHOD(check_send_vec_and_class_1_true) 
		{
			Recipient rec(recipient_address, recipient_port);
			grPair pair1;
			pair1.AddGroup(rec_group1);
			pair1.AddRule(rec_rule1);

			rec.AddPair(pair1);
			rec.AddPair({ rec_group2 }, { rec_rule2 });

			bool res = false;
			res = rec.CheckList({ rec_rule1 }, { rec_group1 });

			Assert::IsTrue(res);

		}

		TEST_METHOD(check_send_vec_and_class_2_true)
		{
			Recipient rec(recipient_address, recipient_port);
			grPair pair1;
			pair1.AddGroup(rec_group1);
			pair1.AddRule(rec_rule1);

			rec.AddPair(pair1);
			rec.AddPair({ rec_group2 }, { rec_rule2 });

			bool res = false;
			res = rec.CheckList({ rec_rule2 }, { rec_group2 });

			Assert::IsTrue(res);

		}

		TEST_METHOD(check_send_vec_and_class_1_false)
		{
			Recipient rec(recipient_address, recipient_port);
			grPair pair1;
			pair1.AddGroup(rec_group1);
			pair1.AddRule(rec_rule1);

			rec.AddPair({ rec_group2 }, { rec_rule2 });

			bool res = false;
			res = rec.CheckList({ rec_rule1 }, { rec_group2 });

			Assert::IsFalse(res);

		}

		TEST_METHOD(check_send_vec_and_class_2_false)
		{
			Recipient rec(recipient_address, recipient_port);
			grPair pair1;
			pair1.AddGroup(rec_group1);
			pair1.AddRule(rec_rule1);

			rec.AddPair({ rec_group2 }, { rec_rule2 });

			bool res = false;
			res = rec.CheckList({ rec_rule2 }, { rec_group1 });

			Assert::IsFalse(res);

		}
	};
}
