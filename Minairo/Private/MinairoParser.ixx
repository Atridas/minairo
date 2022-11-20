module;

#include <cassert>

#include <iostream>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>
#include <variant>
#include <vector>

export module Minairo.Parser;

import Minairo.AST;
import Minairo.AST.Interpreter;
import Minairo.Exception;
import Minairo.Scanner;
import Minairo.TypesAndValues;

namespace minairo
{
	using StatementPtr = std::unique_ptr<Statement>;

	export struct ParseException
	{
		enum class Type
		{
			Message,
			ScannerError,
			UnexpectedEnd,
			UnexpectedPrefix,
			UnexpectedTerminal,
			UnexpectedType
		} type;

		Terminal terminal;
		TerminalData terminal_data, terminal_data2;

		std::string message;

		std::string print_error() const;
	};

	export StatementPtr generate_AST(Scanner code);
}
