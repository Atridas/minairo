import Minairo;

#include "CppUnitTest.h"

#include <sstream>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::literals::string_literals;


namespace InterpreterTests
{
	void RunAndExpect(std::string_view code, std::string_view expected_output)
	{
		minairo::VM vm = minairo::create_VM();

		std::stringstream out;
		minairo::interpret(vm, code, out);

		Assert::AreEqual(expected_output, (std::string_view)out.str());
	}

	void RunAndExpectPrint(std::string_view code, std::string_view expected_output)
	{
		std::stringstream print;
		minairo::VM vm = minairo::create_VM(print);

		std::stringstream out;
		minairo::interpret(vm, code, out);

		Assert::AreEqual(expected_output, (std::string_view)print.str());
	}


	TEST_CLASS(Arithmetic)
	{
	public:
		
		TEST_METHOD(Addition)
		{
			RunAndExpect("2 + 2;", "4");
			RunAndExpect("2 + 5;", "7");
			RunAndExpect("2 + 7;", "9");
			RunAndExpect("7 + 2;", "9");
		}

	private:

		
	};


	TEST_CLASS(Strings)
	{
	public:

		TEST_METHOD(Literal)
		{
			RunAndExpect(R"codi-minairo("";)codi-minairo", "");
			RunAndExpect(R"codi-minairo("string";)codi-minairo", "string");
			RunAndExpect(R"codi-minairo("string with spaces";)codi-minairo", "string with spaces");
		}
	};


	TEST_CLASS(Print)
	{
	public:

		TEST_METHOD(Simple)
		{
			RunAndExpectPrint(R"codi-minairo(print("hola");)codi-minairo", "hola");
		}
	};


	TEST_CLASS(Statements)
	{
	public:

		TEST_METHOD(If)
		{
			RunAndExpectPrint(R"codi-minairo(if(true) print("yes");)codi-minairo", "yes");
			RunAndExpectPrint(R"codi-minairo(if(false) print("yes");)codi-minairo", "");
			RunAndExpectPrint(R"codi-minairo(if(true) print("yes"); else print("no");)codi-minairo", "yes");
			RunAndExpectPrint(R"codi-minairo(if(false) print("yes"); else print("no");)codi-minairo", "no");
		}

		TEST_METHOD(If_BoolInitializer)
		{
			RunAndExpectPrint(R"codi-minairo(if(a :: true) print("yes");)codi-minairo", "yes");
			RunAndExpectPrint(R"codi-minairo(if(a :: false) print("yes");)codi-minairo", "");
			RunAndExpectPrint(R"codi-minairo(if(a :: true) print("yes"); else print("no");)codi-minairo", "yes");
			RunAndExpectPrint(R"codi-minairo(if(a :: false) print("yes"); else print("no");)codi-minairo", "no");
			RunAndExpectPrint(R"codi-minairo(if(a := true) print("yes");)codi-minairo", "yes");
			RunAndExpectPrint(R"codi-minairo(if(a := false) print("yes");)codi-minairo", "");
			RunAndExpectPrint(R"codi-minairo(if(a := true) print("yes"); else print("no");)codi-minairo", "yes");
			RunAndExpectPrint(R"codi-minairo(if(a := false) print("yes"); else print("no");)codi-minairo", "no");
		}

		TEST_METHOD(If_StringInitializer)
		{
			RunAndExpectPrint(R"codi-minairo(if(a :: "catacrocker"; true) print(a);)codi-minairo", "catacrocker");
			RunAndExpectPrint(R"codi-minairo(if(a :: "catacrocker"; false) print(a);)codi-minairo", "");
			RunAndExpectPrint(R"codi-minairo(if(a :: "catacrocker"; true) print(a); else print("no");)codi-minairo", "catacrocker");
			RunAndExpectPrint(R"codi-minairo(if(a :: "catacrocker"; false) print(a); else print("no");)codi-minairo", "no");

			RunAndExpectPrint(R"codi-minairo(if(a :: "catacrocker"; true) print("yes");)codi-minairo", "yes");
			RunAndExpectPrint(R"codi-minairo(if(a :: "catacrocker"; false) print("yes");)codi-minairo", "");
			RunAndExpectPrint(R"codi-minairo(if(a :: "catacrocker"; true) print("yes"); else print(a);)codi-minairo", "yes");
			RunAndExpectPrint(R"codi-minairo(if(a :: "catacrocker"; false) print("yes"); else print(a);)codi-minairo", "catacrocker");
		}
	};
}
