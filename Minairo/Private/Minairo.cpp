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
import Minairo.FunctionRepresentation;
import Minairo.Parser;
import Minairo.Scanner;

namespace minairo
{

	template<typename Ret, typename Param1, typename Param2>
	struct AddOperatorToFunctionMap
	{
		void operator()(FunctionMap& function_map, bool with_callable)
		{
			auto add = std::make_unique<TypedFunctionRepresentation<Ret, Param1, Param2>>();
			auto sub = std::make_unique<TypedFunctionRepresentation<Ret, Param1, Param2>>();
			auto mul = std::make_unique<TypedFunctionRepresentation<Ret, Param1, Param2>>();
			auto div = std::make_unique<TypedFunctionRepresentation<Ret, Param1, Param2>>();
			auto mod = std::make_unique<TypedFunctionRepresentation<Ret, Param1, Param2>>();

			if (with_callable)
			{
				add->set_callable([](Param1 a, Param2 b) -> Ret { return (Ret)a + (Ret)b; });
				sub->set_callable([](Param1 a, Param2 b) -> Ret { return (Ret)a - (Ret)b; });
				mul->set_callable([](Param1 a, Param2 b) -> Ret { return (Ret)a * (Ret)b; });
				div->set_callable([](Param1 a, Param2 b) -> Ret { return (Ret)a / (Ret)b; });
				mod->set_callable([](Param1 a, Param2 b) -> Ret { return (Ret)a % (Ret)b; });
			}

			function_map.store("operator+", std::move(add));
			function_map.store("operator-", std::move(sub));
			function_map.store("operator*", std::move(mul));
			function_map.store("operator/", std::move(div));
			function_map.store("operator%", std::move(mod));
		}
	};

	FunctionMap create_function_map(bool with_callable)
	{
		FunctionMap function_map;

		AddOperatorToFunctionMap<int64_t, int64_t, int64_t>{}(function_map, with_callable);
		AddOperatorToFunctionMap<uint64_t, uint64_t, uint64_t>{}(function_map, with_callable);

		return function_map;
	}

	void interpret(std::string_view code)
	{
		std::cout << "interpreting " << code << std::endl;

		FunctionMap fm = create_function_map(true);

		auto expression = generate_AST(code);


		Interpreter interpreter(std::move(fm));
		expression->accept(interpreter);

		std::visit([] <typename T>(T value) {
			if constexpr (std::is_same_v<T, uint64_t>)
			{
				std::cout << "uint64 " << value << std::endl;
			}
		}, interpreter.get_last_expression_value());

	}
}
