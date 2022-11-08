module;

#include <cassert>

#include <iostream>
#include <memory>
#include <string_view>
#include <sstream>
#include <type_traits>
#include <unordered_map>
#include <variant>

module Minairo;

import Minairo.AST;
import Minairo.AST.Interpreter;
import Minairo.AST.TypePass;
import Minairo.Parser;
import Minairo.Scanner;
import Minairo.TypesAndValues;

namespace minairo
{

	template<typename Ret, typename Param1, typename Param2, bool Mod = true>
	struct AddOperatorToFunctionMap
	{
		void operator()(FunctionMap& function_map)
		{
			auto add = std::make_unique<TypedFunctionRepresentation<true, Ret, Param1, Param2>>();
			auto sub = std::make_unique<TypedFunctionRepresentation<true, Ret, Param1, Param2>>();
			auto mul = std::make_unique<TypedFunctionRepresentation<true, Ret, Param1, Param2>>();
			auto div = std::make_unique<TypedFunctionRepresentation<true, Ret, Param1, Param2>>();

			add->set_callable([](Param1 a, Param2 b) -> Ret { return (Ret)a + (Ret)b; });
			sub->set_callable([](Param1 a, Param2 b) -> Ret { return (Ret)a - (Ret)b; });
			mul->set_callable([](Param1 a, Param2 b) -> Ret { return (Ret)a * (Ret)b; });
			div->set_callable([](Param1 a, Param2 b) -> Ret { return (Ret)a / (Ret)b; });

			function_map.store("operator+", std::move(add));
			function_map.store("operator-", std::move(sub));
			function_map.store("operator*", std::move(mul));
			function_map.store("operator/", std::move(div));

			if constexpr (Mod)
			{
				auto mod = std::make_unique<TypedFunctionRepresentation<true, Ret, Param1, Param2>>();
				mod->set_callable([](Param1 a, Param2 b) -> Ret { return (Ret)a % (Ret)b; });
				function_map.store("operator%", std::move(mod));
			}
		}
	};

	void add_print_function(FunctionMap& function_map, std::ostream& out)
	{
		auto print = std::make_unique<TypedFunctionRepresentation<false, void, std::string>>();

		print->set_callable([&out](std::string str) -> void { out << str; });

		function_map.store("print", std::move(print));
	}

	FunctionMap create_function_map(std::ostream& out)
	{
		FunctionMap function_map;

		AddOperatorToFunctionMap<int8_t, int8_t, int8_t>{}(function_map);
		AddOperatorToFunctionMap<int16_t, int16_t, int16_t>{}(function_map);
		AddOperatorToFunctionMap<int32_t, int32_t, int32_t>{}(function_map);
		AddOperatorToFunctionMap<int64_t, int64_t, int64_t>{}(function_map);
		AddOperatorToFunctionMap<uint8_t, uint8_t, uint8_t>{}(function_map);
		AddOperatorToFunctionMap<uint16_t, uint16_t, uint16_t>{}(function_map);
		AddOperatorToFunctionMap<uint32_t, uint32_t, uint32_t>{}(function_map);
		AddOperatorToFunctionMap<uint64_t, uint64_t, uint64_t>{}(function_map);
		AddOperatorToFunctionMap<float, float, float, false>{}(function_map);
		AddOperatorToFunctionMap<double, double, double, false>{}(function_map);

		add_print_function(function_map, out);

		return function_map;
	}

	struct VMImpl
	{
		FunctionMap fm;
		TypePass::GlobalMap global_types;
		Interpreter::Globals globals;
	};


	VMImpl* create_VM(std::ostream& out)
	{
		VMImpl*vm = new VMImpl();
		vm->fm = create_function_map(out);
		return vm;
	}

	void destroy_VM(VMImpl* vm)
	{
		delete vm;
	}

	void interpret(std::string_view code)
	{
		std::cout << "interpreting " << code << std::endl;

		FunctionMap fm = create_function_map(std::cout);

		auto expression = generate_AST(code);

		TypePass type_pass(fm);
		expression->accept(type_pass);


		Interpreter interpreter(fm);
		expression->accept(interpreter);

	}

	std::string print_table(Table const& table);
	std::string print_tuple(Tuple const& tuple);
	std::string print_function(FunctionRepresentation const& function);

	std::string print_value(Value const& value)
	{
		return std::visit([] <typename T>(T value) -> std::string {
			if constexpr (std::is_same_v<T, char32_t>)
			{
				std::stringstream ss;
				if (value < 128)
					ss << (char)value;
				else
				{
					ss << "Ux" << (unsigned int)value;
				}
				return ss.str();
			}
			else if constexpr (std::is_same_v<T, bool>)
			{
				if (value)
					return "true";
				else
					return "false";
			}
			else if constexpr (std::is_integral_v<T>)
			{
				std::stringstream ss;
				ss << value;
				return ss.str();
			}
			else if constexpr (std::is_same_v<T, std::string>)
			{
				return value;
			}
			else if constexpr (std::is_same_v<T, TypeRepresentation>)
			{
				std::stringstream ss;
				ss << "typedef ";
				std::visit([&ss] <typename Q>(Q value) {
					if constexpr (std::is_same_v<Q, BuildInType>)
					{
						switch (value)
						{
						case BuildInType::Void:
							ss << "void";
							break;
						case BuildInType::Bool:
							ss << "bool";
							break;
						case BuildInType::I8:
							ss << "int8";
							break;
						case BuildInType::I16:
							ss << "int16";
							break;
						case BuildInType::I32:
							ss << "int32";
							break;
						case BuildInType::I64:
							ss << "int64";
							break;
						case BuildInType::U8:
							ss << "uint8";
							break;
						case BuildInType::U16:
							ss << "uint16";
							break;
						case BuildInType::U32:
							ss << "uint32";
							break;
						case BuildInType::U64:
							ss << "uint64";
							break;
						case BuildInType::F32:
							ss << "float";
							break;
						case BuildInType::F64:
							ss << "double";
							break;
						case BuildInType::Typedef:
							ss << "typedef";
							break;
						default:
							assert(false);
						}
					}
					else
					{
						// TODO
						ss << "????";
					}
				}, value);
				return ss.str();
			}
			else if constexpr (std::is_same_v<T, std::shared_ptr<ComplexValue>>)
			{
				if (auto table = get<Table>(value))
				{
					return print_table(*table);
				}
				else if (auto tuple = get<Tuple>(value))
				{
					return print_tuple(*tuple);
				}
				else if (auto function_representation = get<FunctionRepresentation>(value))
				{
					return print_function(*function_representation);
				}
				else
				{
					return "unknown complex value";
				}
			}
			else
			{
				return "unknown";
			}
		}, value);
	}

	std::string print_table(Table const& table)
	{
		if (table.rows == 0)
		{
			return "table { }";
		}
		else
		{
			std::stringstream ss;
			ss << "table {";

			const char* comma = "";
			for (int r = 0; r < table.rows; ++r)
			{
				ss << "\n    { ";
				comma = "";
				for (int c = 0; c < table.type.base_tuple.get_num_fields(); ++c)
				{
					ss << comma << table.type.base_tuple.get_field_name(c) << ": " << print_value(table.fields[c][r]);
					comma = ", ";
				}
				ss << " }";
			}
			ss << "\n  }";

			return ss.str();
		}
	}

	std::string print_tuple(Tuple const& tuple)
	{
		std::stringstream ss;
		ss << "tuple " << tuple.type.get_name() << "{ ";
		const char* comma = "";
		for (int i = 0; i < tuple.type.get_num_fields(); ++i)
		{
			ss << comma << tuple.type.get_field_name(i) << ": " << print_value(tuple.fields[i]);
			comma = ", ";
		}
		ss << " }";
		return ss.str();
	}

	std::string print_function(FunctionRepresentation const& function)
	{
		return "function TODO";
	}

	void interpret(VMImpl* vm, std::string_view code, std::ostream &out)
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

			Interpreter interpreter(vm->fm, (int)vm->global_types.variables.size());
			interpreter.set_globals(vm->globals);
			expression->accept(interpreter);
			vm->globals = interpreter.get_globals();

			out << print_value(interpreter.get_last_expression_value());
			
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
