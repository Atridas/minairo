module;

#include <cassert>

#include <iostream>
#include <memory>
#include <string_view>
#include <type_traits>
#include <variant>

module Minairo;

import Minairo.AST;
import Minairo.AST.Interpreter;
import Minairo.Parser;
import Minairo.Scanner;

namespace minairo
{
	void interpret(std::string_view code)
	{
		std::cout << "interpreting " << code << std::endl;


		auto expression = generate_AST(code);


		Interpreter interpreter;
		expression->accept(interpreter);

		std::visit([] <typename T>(T value) {
			if constexpr (std::is_same_v<T, uint64_t>)
			{
				std::cout << "uint64 " << value << std::endl;
			}
		}, interpreter.get_last_expression_value());

	}
}
