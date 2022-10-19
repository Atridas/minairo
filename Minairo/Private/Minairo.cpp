module;

#include <cassert>

#include <iostream>
#include <memory>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <variant>

module Minairo;

import Minairo.AST;
import Minairo.AST.Interpreter;
import Minairo.FunctionRepresentation;
import Minairo.Parser;
import Minairo.Scanner;
import Minairo.AST.TypePass;

namespace minairo
{

	template<typename Ret, typename Param1, typename Param2, bool Mod = true>
	struct AddOperatorToFunctionMap
	{
		void operator()(FunctionMap& function_map, bool with_callable)
		{
			auto add = std::make_unique<TypedFunctionRepresentation<Ret, Param1, Param2>>();
			auto sub = std::make_unique<TypedFunctionRepresentation<Ret, Param1, Param2>>();
			auto mul = std::make_unique<TypedFunctionRepresentation<Ret, Param1, Param2>>();
			auto div = std::make_unique<TypedFunctionRepresentation<Ret, Param1, Param2>>();

			if (with_callable)
			{
				add->set_callable([](Param1 a, Param2 b) -> Ret { return (Ret)a + (Ret)b; });
				sub->set_callable([](Param1 a, Param2 b) -> Ret { return (Ret)a - (Ret)b; });
				mul->set_callable([](Param1 a, Param2 b) -> Ret { return (Ret)a * (Ret)b; });
				div->set_callable([](Param1 a, Param2 b) -> Ret { return (Ret)a / (Ret)b; });
			}

			function_map.store("operator+", std::move(add));
			function_map.store("operator-", std::move(sub));
			function_map.store("operator*", std::move(mul));
			function_map.store("operator/", std::move(div));

			if constexpr (Mod)
			{
				auto mod = std::make_unique<TypedFunctionRepresentation<Ret, Param1, Param2>>();
				if (with_callable)
				{
					mod->set_callable([](Param1 a, Param2 b) -> Ret { return (Ret)a % (Ret)b; });
				}
				function_map.store("operator%", std::move(mod));
			}
		}
	};

	FunctionMap create_function_map(bool with_callable)
	{
		FunctionMap function_map;

		AddOperatorToFunctionMap<int8_t, int8_t, int8_t>{}(function_map, with_callable);
		AddOperatorToFunctionMap<int16_t, int16_t, int16_t>{}(function_map, with_callable);
		AddOperatorToFunctionMap<int32_t, int32_t, int32_t>{}(function_map, with_callable);
		AddOperatorToFunctionMap<int64_t, int64_t, int64_t>{}(function_map, with_callable);
		AddOperatorToFunctionMap<uint8_t, uint8_t, uint8_t>{}(function_map, with_callable);
		AddOperatorToFunctionMap<uint16_t, uint16_t, uint16_t>{}(function_map, with_callable);
		AddOperatorToFunctionMap<uint32_t, uint32_t, uint32_t>{}(function_map, with_callable);
		AddOperatorToFunctionMap<uint64_t, uint64_t, uint64_t>{}(function_map, with_callable);
		AddOperatorToFunctionMap<float, float, float, false>{}(function_map, with_callable);
		AddOperatorToFunctionMap<double, double, double, false>{}(function_map, with_callable);

		return function_map;
	}

	struct VMImpl
	{
		FunctionMap fm;
		TypePass::GlobalMap global_types;
		Interpreter::GlobalStack globals;
	};


	VMImpl* create_VM()
	{
		VMImpl*vm = new VMImpl();
		vm->fm = create_function_map(true);
		return vm;
	}

	void destroy_VM(VMImpl* vm)
	{
		delete vm;
	}

	void interpret(std::string_view code)
	{
		std::cout << "interpreting " << code << std::endl;

		FunctionMap fm = create_function_map(true);

		auto expression = generate_AST(code);

		TypePass type_pass(fm);
		expression->accept(type_pass);


		Interpreter interpreter;
		expression->accept(interpreter);

	}

	void interpret(VMImpl* vm, std::string_view code)
	{
		assert(vm != nullptr);

		try
		{

			auto expression = generate_AST(code);

			{
				TypePass type_pass(vm->fm);
				type_pass.set_globals(vm->global_types);
				expression->accept(type_pass);
				vm->global_types = type_pass.get_globals();
			}

			Interpreter interpreter((int)vm->global_types.variables.size());
			interpreter.set_globals(vm->globals);
			expression->accept(interpreter);
			vm->globals = interpreter.get_globals();


			std::visit([] <typename T>(T value) {
				if constexpr (std::is_same_v<T, char32_t>)
				{
					std::cout << "char32" << std::endl;
				}
				else if constexpr (std::is_integral_v<T>)
				{
					std::cout << value << std::endl;
				}
				else if constexpr (std::is_same_v<T, TypeRepresentation>)
				{
					std::cout << "typedef ";
					std::visit([] <typename Q>(Q value) {
						if constexpr (std::is_same_v<Q, BuildInType>)
						{
							switch (value)
							{
							case BuildInType::Void:
								std::cout << "void";
								break;
							case BuildInType::Bool:
								std::cout << "bool";
								break;
							case BuildInType::I8:
								std::cout << "int8";
								break;
							case BuildInType::I16:
								std::cout << "int16";
								break;
							case BuildInType::I32:
								std::cout << "int32";
								break;
							case BuildInType::I64:
								std::cout << "int64";
								break;
							case BuildInType::U8:
								std::cout << "uint8";
								break;
							case BuildInType::U16:
								std::cout << "uint16";
								break;
							case BuildInType::U32:
								std::cout << "uint32";
								break;
							case BuildInType::U64:
								std::cout << "uint64";
								break;
							case BuildInType::F32:
								std::cout << "float";
								break;
							case BuildInType::F64:
								std::cout << "double";
								break;
							case BuildInType::Typedef:
								std::cout << "typedef";
								break;
							default:
								assert(false);
							}
						}
						else
						{
							// TODO
							std::cout << "????";
						}
					}, value);
					std::cout << std::endl;
				}
				else
				{
					std::cout << "unknown" << std::endl;
				}
			}, interpreter.get_last_expression_value());
		}
		catch (ParseException pe)
		{
			std::cerr << pe.print_error() << std::endl;
		}
		catch (TypeException te)
		{
			std::cerr << te.print_error() << std::endl;
		}
	}

}
