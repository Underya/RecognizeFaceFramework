#include "pch.h"
#include "CppUnitTest.h"
#include "..//face_detection/OneFrame.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace facedetetctiontests
{
	TEST_CLASS(oneFrame_test)
	{
	public:
		
		TEST_METHOD(create_empty)
		{
			OneFrame f;
		}
	};
}
