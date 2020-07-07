#include "employee_info.h"

employee_info::employee_info(int id, string name, string family, string mid_name, string db_description)
{
	_id = id;
	_first_name = name;
	_last_name = family;
	_mid_name = mid_name;
	_db_description = db_description;
}

int employee_info::GetId()
{
	return _id;
}

void employee_info::SetId(int id)
{
	_id = id;
}

int employee_info::GetOtherId()
{
	return _other_id;
}

void employee_info::SetOtherId(int other_id)
{
	_other_id = other_id;
}

string employee_info::GetFirstName()
{
	return _first_name;
}

void employee_info::SetFisrtName(string name)
{
	_first_name = name;
}

string employee_info::GetLastName()
{
	return _last_name;
}

void employee_info::SetLastName(string family)
{
	_last_name = family;
}

string employee_info::GetMidName()
{
	return _mid_name;
}

void employee_info::SetMidName(string mid_name)
{
	_mid_name = mid_name;
}

string employee_info::GetDBDescriptor()
{
	return _db_description;
}

void employee_info::SetDBDescriptor(string db_descriptor)
{
	_db_description = db_descriptor;
}
