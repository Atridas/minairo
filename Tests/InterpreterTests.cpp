import Minairo;

#include "CppUnitTest.h"

#include <sstream>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::literals::string_literals;


namespace InterpreterTests
{
	TEST_CLASS(Arithmetic)
	{
	public:
		
		TEST_METHOD(Addition)
		{
			RunAndExpect("2 + 2;", "4\n");
			RunAndExpect("2 + 5;", "7\n");
			RunAndExpect("2 + 7;", "9\n");
			RunAndExpect("7 + 2;", "9\n");
		}

	private:

		void RunAndExpect(std::string_view code, std::string_view expected_output)
		{
			minairo::VM vm = minairo::create_VM();

			std::stringstream ss;

			minairo::interpret(vm, code, ss);

			Assert::AreEqual(expected_output, (std::string_view)ss.str());
		}

	};
}
