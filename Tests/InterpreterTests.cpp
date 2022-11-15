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

		std::stringstream out, err;
		minairo::interpret(vm, code, out, err);

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
		TEST_METHOD(Shortcircuit)
		{
			std::string preamble = R"codi-minairo(
					t :: function() { print("t"); return true; };
					f :: function() { print("f"); return false; };
					r :: function() { print("r"); };
				)codi-minairo";

			RunAndExpectPrint(preamble + "if(t() && t()) r();", "ttr");
			RunAndExpectPrint(preamble + "if(t() && f()) r();", "tf");
			RunAndExpectPrint(preamble + "if(f() && t()) r();", "f");
			RunAndExpectPrint(preamble + "if(f() && f()) r();", "f");

			RunAndExpectPrint(preamble + "if(t() || t()) r();", "tr");
			RunAndExpectPrint(preamble + "if(t() || f()) r();", "tr");
			RunAndExpectPrint(preamble + "if(f() || t()) r();", "ftr");
			RunAndExpectPrint(preamble + "if(f() || f()) r();", "ff");
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


	TEST_CLASS(Tuples)
	{
	public:

		TEST_METHOD(Definition)
		{
			RunAndExpect(R"codi-minairo(a : tuple{ a, b: int32 };)codi-minairo", "tuple { a: 0, b: 0 }");
			RunAndExpect(R"codi-minairo(t :: tuple{ a, b: int32 }; a : t;)codi-minairo", "tuple t{ a: 0, b: 0 }");
		}

		TEST_METHOD(DefaultValues)
		{
			RunAndExpect(R"codi-minairo(a : tuple{ a, b: int32 = 5 };)codi-minairo", "tuple { a: 5, b: 5 }");
			RunAndExpect(R"codi-minairo(a : tuple{ a := 10, b:= 15 };)codi-minairo", "tuple { a: 10, b: 15 }");
		}

		TEST_METHOD(MemberRead)
		{
			RunAndExpect(R"codi-minairo(a : tuple{ a, b: int32 = 5 }; a.a;)codi-minairo", "5");
			RunAndExpect(R"codi-minairo(a : tuple{ a, b: int32 = 5 }; a.b;)codi-minairo", "5");
			RunAndExpect(R"codi-minairo(a : tuple{ a := 10, b:= 15 }; a.a;)codi-minairo", "10");
			RunAndExpect(R"codi-minairo(a : tuple{ a := 10, b:= 15 }; a.b;)codi-minairo", "15");
		}

		TEST_METHOD(MemberWrite)
		{
			RunAndExpect(R"codi-minairo(a : tuple{ a, b: int32 = 5 }; a.a = 10; a.a;)codi-minairo", "10");
			RunAndExpect(R"codi-minairo(a : tuple{ a, b: int32 = 5 }; a.a = 10; a.b;)codi-minairo", "5");
			RunAndExpect(R"codi-minairo(a : tuple{ a, b: int32 = 5 }; a.a = 10; a;)codi-minairo", "tuple { a: 10, b: 5 }");
		}

		TEST_METHOD(Recursive)
		{
			RunAndExpect(R"codi-minairo(a : tuple{ t : tuple { a, b: int32 = 5 }, c := 10 };)codi-minairo", "tuple { t: tuple { a: 5, b: 5 }, c: 10 }");
			RunAndExpect(R"codi-minairo(a : tuple{ t : tuple { a, b: int32 = 5 }, c := 10 }; a.t;)codi-minairo", "tuple { a: 5, b: 5 }");
			RunAndExpect(R"codi-minairo(a : tuple{ t : tuple { a, b: int32 = 5 }, c := 10 }; a.t.a;)codi-minairo", "5");
			RunAndExpect(R"codi-minairo(a : tuple{ t : tuple { a, b: int32 = 5 }, c := 10 }; a.t.a = 100; a;)codi-minairo", "tuple { t: tuple { a: 100, b: 5 }, c: 10 }");
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


	TEST_CLASS(Functions)
	{
		TEST_METHOD(Pure)
		{
			RunAndExpect(R"codi-minairo(function pure(a,b: int32) { return a + b; }(1,2);)codi-minairo", "3");
			RunAndExpect(R"codi-minairo(f :: function pure(a,b: int32) { return a + b; }; f(1,2);)codi-minairo", "3");

			RunAndExpect(R"codi-minairo(function pure (a,b: int32) { return a / b; }(10,2);)codi-minairo", "5");
			RunAndExpect(R"codi-minairo(function pure (a,b: int32) { return a / b; }(a = 10,2);)codi-minairo", "5");
			RunAndExpect(R"codi-minairo(function pure (a,b: int32) { return a / b; }(b = 2, a = 10);)codi-minairo", "5");
		}
	};

	/*TEST_CLASS(Multifunction)
	{
		TEST_METHOD(Pure)
		{
			RunAndExpect(R"codi-minairo(m : multifunction;)codi-minairo", "");
		}
	};*/

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

		TEST_METHOD(While)
		{
			RunAndExpect(R"codi-minairo(a:= 0; while(a == 0) a = a + 1; a;)codi-minairo", "1");
			RunAndExpect(R"codi-minairo(a:= 0; while(a != 5) a = a + 1; a;)codi-minairo", "5");

			RunAndExpectPrint(R"codi-minairo(a:= 0; while(a != 5) { print("a"); a = a + 1; })codi-minairo", "aaaaa");
			RunAndExpectPrint(R"codi-minairo(a:= 0; while(a == 1) { print("a"); a = a + 1; })codi-minairo", "");
		}

		TEST_METHOD(DoWhile)
		{
			RunAndExpect(R"codi-minairo(a:= 0; do a = a + 1; while(a == 0) a;)codi-minairo", "1");
			RunAndExpect(R"codi-minairo(a:= 0; do a = a + 1; while(a < 5); a;)codi-minairo", "5");

			RunAndExpectPrint(R"codi-minairo(a:= 0; do { print("a"); a = a + 1; } while(a != 5))codi-minairo", "aaaaa");
			RunAndExpectPrint(R"codi-minairo(a:= 0; do { print("a"); a = a + 1; } while(a == 1))codi-minairo", "aa");
		}

		TEST_METHOD(For)
		{
			RunAndExpectPrint(R"codi-minairo(for(a:=0; a < 5; a = a + 1) print("a");)codi-minairo", "aaaaa");
		}

		TEST_METHOD(Foreach_Read)
		{
			RunAndExpectPrint(R"codi-minairo(
				t : table{ a: string, b : int32 };
				t += { "1", 2 };
				t += { "3", 4 };
				t += { "5", 6 };
				t += { "7", 8 };
				t += { "9", 0 };
				foreach(v :: t) print(v.a);
				)codi-minairo",
				"13579");
		}

		TEST_METHOD(Foreach_Write)
		{
			RunAndExpect(R"codi-minairo(
				t : table{ a: string, b : int32 };
				t += { "1", 2 };
				t += { "3", 4 };
				t += { "5", 6 };
				t += { "7", 8 };
				t += { "9", 0 };
				foreach(v := t) v.b = v.b + 1;
				t;
				)codi-minairo",
				"table {\n    { a: 1, b: 3 }\n    { a: 3, b: 5 }\n    { a: 5, b: 7 }\n    { a: 7, b: 9 }\n    { a: 9, b: 1 }\n  }");
		}

	};
}
