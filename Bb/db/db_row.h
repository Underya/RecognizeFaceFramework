#pragma once


//���������, ������� ��������� �������� ��������, ������� �������� ��������� ��
class db_row
{
public:

	//�������� ������ �� ��
	virtual void Delete() = 0;

protected:

	//������������� ������ � ��
	int _id;

	//���������� ���������� �� �������
	virtual void _db_update() = 0;

};

