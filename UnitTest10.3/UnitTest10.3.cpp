#include "pch.h"
#include "CppUnitTest.h"
#include "../Project10.3/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest103
{
	TEST_CLASS(UnitTest103)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            Office offices[MAX_OFFICES];
            int officeCount = 0;
            addEmployee(offices, officeCount, "123456789", "Barchuk", 101);
            Assert::AreEqual(1, officeCount);
            Assert::AreEqual(1, offices[0].employeeCount);

		}
	};
}
