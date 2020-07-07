
#include "thread_obj.h"

thread_obj::thread_obj()
{
	pipe = new simple_pipe<ControlMessage>();
}

simple_pipe<ControlMessage>* thread_obj::GetControlPipe()
{
	return pipe;
}

void thread_obj::operator()()
{
	this->ThreadMethod();
}

void thread_obj::ThreadMethod()
{
	std::cout << "Call based class\n";
}

void thread_obj::ParseControlMess()
{
}
