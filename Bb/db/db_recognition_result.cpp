#include "pch.h"
#include "db_recognition_result.h"


using namespace std;

void db_recognition_result::addNewRecognitionResult(int id_rec, int id_camera)
{
	//������������ ���������� ���������
	std::list<std::string> params;
	params.push_back(std::to_string(id_rec));
	params.push_back(std::to_string(id_camera));
	//����� �������
	try {
		conn.ExecuteAddProcedure("addrecognit", &params);
	}
	catch (...) {
		std::string str_error = "";
		str_error += "Exceptio! No to add Recognition information! Location: db_recognition_result/addNewRecognitionResult\n ";
		throw new std::exception(str_error.c_str());
	}
}

std::vector<std::string> db_recognition_result::GetRecogntionAll()
{
	std::vector<std::string> result;

	PGresult *res = conn.GetAllRowTable2("recognit");
	string recognit;

	for (int i = 0, max = PQntuples(res); i < max; i++) {
		recognit = "id:";
		recognit += PQgetvalue(res, i, 0);
		recognit += ";\n";
		recognit += "id_camera:";
		recognit += PQgetvalue(res, i, 1);
		recognit += ";\n";
		recognit += "id_employee:";
		recognit += PQgetvalue(res, i, 2);
		recognit += ";\n";
		recognit += "time:";
		recognit += PQgetvalue(res, i, 3);
		recognit += ";\n";
		result.push_back(recognit);
	}

	return result;
}

std::vector<oneRecognit> db_recognition_result::GetRecognitionResult(int id_cam, int id_employee, time_t start_time, time_t end_time)
{
	//����������� ������ �������
	std::string query_text = "select * from recognit where 1=1 ";
	//������ �� ���������� ������
	if (id_cam != -100) {
		query_text += " and id_camera=" + to_string(id_cam);
	}
	//������ �� ����������� ����������
	if (id_employee != -100) {
		query_text += " and id_employee=" + to_string(id_employee);
	}

	if (start_time != -100) {
		string str_time = GetTime(start_time);
		query_text += "and time_r >= '" + str_time + "'";
	}

	if (end_time != -100) {
		string str_time = GetTime(end_time);
		query_text += "and time_r <= '" + str_time + "'";
	}

	PGresult* res = conn.GetRowWithQuerry(query_text);
	int id_row = 0;

	std::vector<oneRecognit> vectorRec;

	int row_count = PQntuples(res);

	for (int i = 0; i < row_count; i++) {
		vectorRec.push_back(GetOneRecognit(i, res));
	}


	return vectorRec;
}

oneRecognit db_recognition_result::GetOneRecognit(int id_row, PGresult* res)
{
	//��������� ������
	string stime = PQgetvalue(res, id_row, 3);
	time_t t_time = GetTime(stime);
	
	oneRecognit oneRec;
	//��������� �������
	oneRec._time = t_time;
	//id ������
	oneRec._id = atoi(PQgetvalue(res, id_row, 0));
	//�� ������
	oneRec._id_camera = atoi(PQgetvalue(res, id_row, 1));
	//�� ����������
	oneRec._id_employee = atoi(PQgetvalue(res, id_row, 2));

	return oneRec;
}

time_t db_recognition_result::GetTime(std::string time)
{
	tm tm_time;

	//������ ������ ��� ��������� ����
	//������ ������
	string buff = "";

	//������������������ ����
	int i = 0;
	int size = time.size();

	//��������� ����
	for (; time[i] != '-'; i++) buff += time[i];
	//��������� ����
	tm_time.tm_year = atoi(buff.c_str()) - 1900;
	//��������� ������
	buff = "";
	for (i++; time[i] != '-'; i++) buff += time[i];
	//��������� ������
	tm_time.tm_mon = atoi(buff.c_str()) - 1;
	//��������� ���
	buff = "";
	for (i++; time[i] != ' '; i++) buff += time[i];
	//��������� ���
	tm_time.tm_mday = atoi(buff.c_str());
	buff = "";

	//��������� �������

	//��������� �����
	for (; time[i] != ':'; i++)  buff += time[i];
	//��������� �����
	tm_time.tm_hour = atoi(buff.c_str());
	buff = "";
	//��������� �����
	for (i++; time[i] != ':'; i++)  buff += time[i];
	//��������� �����
	tm_time.tm_min = atoi(buff.c_str());
	buff = "";
	//��������� ������
	for (i++; i < size; i++)  buff += time[i];
	//��������� ������
	tm_time.tm_sec = atoi(buff.c_str());
	buff = "";
	
	return mktime(&tm_time);
}

std::string db_recognition_result::GetTime(time_t t)
{
	string stime = "";
	tm time;
	localtime_s(&time, &t);
	//��������� ������������ ����
	string data = "";
	data += to_string(time.tm_year + 1900) + "-";
	data += to_string(time.tm_mon + 1) + "-";
	data += to_string(time.tm_mday);
	//���������� ����������
	stime = data;
	//��������� ������������ �������
	string times = "";
	times += to_string(time.tm_hour) + ":";
	times += to_string(time.tm_min) + ":";
	times += to_string(time.tm_sec);
	//���������� ����������
	stime += " " + times;
	return stime;
}
