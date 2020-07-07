#include "pch.h"
#include "CppUnitTest.h"
#include "..//file_manager/file_faces.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;



namespace filemanagertest
{
	//Имя тестового файла
	std::string faces_file_name = "faces_file_test_name";
	//Имя сотрудника
	std::string faces_ffname1 = "first_name_1", faces_ffname2 = "first_name_2", faces_ffname3 = "first_name_3";
	//Фамилия сотрудника
	std::string faces_lname1 = "last_name_1", faces_lname2 = "last_name_2", faces_lname3 = "last_name_3";
	//Отчество сотрудника
	std::string faces_mname1 = "mid_name_1", faces_mname2 = "mid_name_2", faces_mname3 = "mid_name_3";
	//Описание сотрудника
	std::string faces_desc1 = "description_employee_1";
	//Идентификатор сотрудника
	int faces_face_id1 = 10, faces_face_id2 = 11, faces_face_id3 = 12;
	int faces_id_not_exist1 = -11, faces_id_not_exist2 = -12;
	//Отчество сотрудника
	int faces_other_face_id1 = 101, faces_other_face_id2 = 102, faces_other_face_id3 = 103;

	//Дескрипторы лиц
	//Идентификаторы дескрипторов
	int faces_id_desc1 = 1, faces_id_desc2 = 2;
	std::string faces_face_desc1 = "0 0 0", faces_face_desc2 = "0.02 0.12 0.9";

	//Вектора с идентификатороми и дескрипторам
	std::vector<int> faces_vector_id = { faces_id_desc1, faces_id_desc2 };
	std::vector<std::string> faces_vector_desc = {faces_face_desc1, faces_face_desc2 };

	TEST_CLASS(file_faces_test)
	{
	public:

		TEST_METHOD(create_default)
		{
			file_faces ff;
		}

		TEST_METHOD(create)
		{
			file_faces ff(faces_file_name);
		}

		TEST_METHOD(s1p01_create)
		{
			file_faces ff(faces_file_name);
		}

		TEST_METHOD(s1p02_add_face)
		{
			file_faces ff(faces_file_name);
			ff.AddFace(faces_face_id1, faces_ffname1, faces_lname1, faces_mname1, faces_desc1, faces_vector_desc, faces_vector_id, faces_other_face_id1);
		}

		TEST_METHOD(s1p03_save_add_face)
		{
			file_faces ff(faces_file_name);
			ff.AddFace(faces_face_id1, faces_ffname1, faces_lname1, faces_mname1, faces_desc1, faces_vector_desc, faces_vector_id, faces_other_face_id1);
			ff.Save();
		}

		TEST_METHOD(s1p04_open_file_faces)
		{
			file_faces ff(faces_file_name);
		}

		TEST_METHOD(s1p05_check_open_file_faces)
		{
			file_faces ff(faces_file_name);
			ff.GetFaceInfo();
		}

		TEST_METHOD(s1p06_check_info)
		{
			file_faces ff(faces_file_name);
			std::list<face_info> ll = ff.GetFaceInfo();
			face_info face = ll.front();
			Assert::AreEqual(faces_face_id1, face.id);
			Assert::AreEqual(faces_ffname1, face.first_name);
			Assert::AreEqual(faces_lname1, face.last_name);
			Assert::AreEqual(faces_mname1, face.mid_name);
			Assert::AreEqual(faces_other_face_id1, face.other_id);
			Assert::AreEqual(faces_desc1, face.descinfo);
		}

		TEST_METHOD(s1p07_check_desc)
		{
			file_faces ff(faces_file_name);
			std::list<face_info> ll = ff.GetFaceInfo();
			face_info face = ll.front();
			std::vector<int> id_desc = face.id_desc;
			std::vector<std::string> desc = face.desc;
			for (int i = 0; i < faces_vector_id.size(); i++) {
				Assert::AreEqual(faces_vector_id[i], id_desc[i]);
				Assert::AreEqual(faces_vector_desc[i], desc[i]);
			}
		}

		TEST_METHOD(s1p08_add_2_face)
		{
			file_faces ff(faces_file_name);
			ff.AddFace(faces_face_id2, faces_ffname2, faces_lname2, faces_mname2, faces_desc1, faces_vector_desc, faces_vector_id, faces_other_face_id2);
			ff.AddFace(faces_face_id3, faces_ffname3, faces_lname3, faces_mname3, faces_desc1, faces_vector_desc, faces_vector_id, faces_other_face_id3);
			ff.Save();
		}

		TEST_METHOD(s1p09_check_count_face)
		{
			file_faces ff(faces_file_name);
			Assert::AreEqual(3, ff.GetCountFace());
		}

		TEST_METHOD(s1p10_check_for_id_exist) 
		{
			file_faces ff(faces_file_name);
			Assert::AreEqual(true, ff.CheckFace(faces_face_id1));
			Assert::AreEqual(true, ff.CheckFace(faces_face_id2));
			Assert::AreEqual(true, ff.CheckFace(faces_face_id3));
		}

		TEST_METHOD(s1p11_check_for_id_not_exist) 
		{
			file_faces ff(faces_file_name);
			Assert::AreEqual(false, ff.CheckFace(faces_id_not_exist1));
			Assert::AreEqual(false, ff.CheckFace(faces_id_not_exist2));
		}

		TEST_METHOD(s1p12_get_info_for_id) 
		{
			file_faces ff(faces_file_name);
			face_info f1 = ff.GetFace(faces_face_id1);
			face_info f2 = ff.GetFace(faces_face_id2);
			face_info f3 = ff.GetFace(faces_face_id3);
			Assert::AreEqual(f1.id, faces_face_id1);
			Assert::AreEqual(f2.id, faces_face_id2);
			Assert::AreEqual(f3.id, faces_face_id3);
		}
		
		TEST_METHOD(s1p13_get_info_for_not_exist)
		{
			file_faces ff(faces_file_name);
			bool exec = false;
			try {
				ff.GetFace(faces_id_not_exist1);
			}
			catch (...) {
				exec = true;
			}

			Assert::AreEqual(true, exec);

			exec = false;
			try {
				ff.GetFace(faces_id_not_exist2);
			}
			catch (...) {
				exec = true;
			}

			Assert::AreEqual(true, exec);


		}

		TEST_METHOD(s1p14_clear_file) 
		{
			file_faces ff(faces_file_name);
			ff.ClearFile();
		}

		TEST_METHOD(s1p15_check_clear_file)
		{
			file_faces ff(faces_file_name);
			Assert::AreEqual(0, ff.GetCountFace());
		}

	};
}