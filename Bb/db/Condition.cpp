#include "pch.h"
#include "Condition.h"

Condition::Condition()
{
}

void Condition::AddGroup(int group_name)
{
	_group.push_back(group_name);
}

std::list<int> Condition::GetGroup()
{
	return _group;
}

void Condition::ClearGroup()
{
	_group.clear();
}

void Condition::AddPremise(int premise)
{
}

std::list<int> Condition::GetPremise()
{
	return std::list<int>();
}

void Condition::ClearPremise()
{
}
