#include "pch.h"
#include "vcam_file_manager.h"
using namespace std;

vcam_file_manager::vcam_file_manager(std::string file_name) : file_parametr(file_name)
{
	//�������� ������
	this->list = new std::list<vcam_file>();

	//������ ����� � ��������� ���������� �� ����
	ReadVcamInfo();
}

vcam_file_manager::vcam_file_manager() : file_parametr("vcam_date.txt")
{

	//�������� ������
	this->list = new std::list<vcam_file>();

	//������ ����� � ��������� ���������� �� ����
	ReadVcamInfo();
}

vcam_file_manager::~vcam_file_manager()
{
}

void vcam_file_manager::AddNewCamera(string address, string description, int id_premise, string position, int id)
{
	vcam_file* vf = new vcam_file();
	vf->address = address;
	vf->position = position;
	vf->description = description;
	vf->id_premise = id_premise;
	//���� id �� �������, �� ������������ ���������
	vf->id = id;
	if (id == -1) {
		vf->id = GetNewId(); 
	}
	list->push_back(*vf);
}

list<vcam_file>* vcam_file_manager::GetList()
{
	//������������ ��������� �� ����
	return list;
}

vcam_file vcam_file_manager::GetCamera(int id)
{
	//����� ����� ���� �����, ����� � ����� �� id
	for (auto cam = list->begin(); cam != list->end(); cam++) {
		if (cam->id == id) return *cam;
	}

	//���� ������ �� �������, ������� ����������
	throw new exception(("Not camera with id, where id = " + to_string(id)).c_str());
}

int vcam_file_manager::SearchCamera(string address)
{
	//����� ����� ���� �������� ������ � ����� �� ��������
	for (auto cam = list->begin(); cam != list->end(); cam++) {
		if (cam->address == address) return cam->id;
	}
	return -1;
}

string vcam_file_manager::GetContentList()
{
	//���������� ���� ���������
	string content = "";

	for (auto iter = list->begin(); iter != list->end(); iter++) {
		content += "cam\n";
		content += "address:" + iter->address + ";\n";
		content += "position:" + iter->position + ";\n";
		content += "id:" + iter->id_str() + ";\n";
		content += "description:" + iter->description + ";\n";
		content += "id_premise:" + to_string(iter->id_premise) + ";\n";
	}

	//����������� ����������� �����
	return content;
}

void vcam_file_manager::ReadVcamInfo()
{
	//�������� ����� ��� ������
	OpenFileForRead();
	string line, nameParam, valueParam;
	//������ ����� �����
	while (getline(*_rFile, line)) {
		//�������� ����� ��������� ���������� �� ������ �� �����
		vcam_file* vf = new vcam_file();
		//��������, �� ������������
		//������ cam
		if (line != "cam") throw new exception("Error! File is not correct!");

		//address
		//������ ����� �� ��������� ����������
		getline(*_rFile, line);
		//��������� ��������� address �� ������
		GetValueForString(line, nameParam, valueParam);
		//�������, ���������� �� ��� ��������
		if(nameParam != "address") throw new exception("Error! File is not correct!");
		//���������� ��������� � ����������
		vf->address = valueParam;

		//postion
		//������ ����� �� ��������� ����������
		getline(*_rFile, line);
		//��������� ��������� address �� ������
		GetValueForString(line, nameParam, valueParam);
		//�������, ���������� �� ��� ��������
		if (nameParam != "position") throw new exception("Error! File is not correct!");
		//���������� ��������� � ����������
		vf->position = valueParam;

		//id
		//������ ����� �� ��������� ����������
		getline(*_rFile, line);
		//��������� ��������� address �� ������
		GetValueForString(line, nameParam, valueParam);
		//�������, ���������� �� ��� ��������
		if (nameParam != "id") throw new exception("Error! File is not correct!");
		//���������� ��������� � ����������
		vf->id = atoi(valueParam.c_str());

		//description
		//������ ����� �� ��������� ����������
		getline(*_rFile, line);
		//��������� ��������� address �� ������
		GetValueForString(line, nameParam, valueParam);
		//�������, ���������� �� ��� ��������
		if (nameParam != "description") throw new exception("Error! File is not correct!");
		//���������� ��������� � ����������
		vf->description = valueParam;

		//id_premise
		getline(*_rFile, line);
		//��������� ��������� address �� ������
		GetValueForString(line, nameParam, valueParam);
		//�������, ���������� �� ��� ��������
		if (nameParam != "id_premise") throw new exception("Error! File is not correct!");
		//���������� ��������� � ����������
		vf->id_premise = atoi(valueParam.c_str());

		//���������� ������ � ������
		list->push_back(*vf);

		//�������� ���������� id
		SetLastUsId(vf->id);
	}

}
