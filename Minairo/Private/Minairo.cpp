module;

#include <cassert>

#include <iostream>
#include <memory>
#include <string>
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

using namespace std::string_literals;

namespace minairo
{
	struct VMImpl
	{
		TypePass::Globals global_types;
		Interpreter::Globals globals;
	};

	void add_print_function(VMImpl &vm, std::ostream& out)
	{
		TypedFunctionRepresentation<false, void, std::string> print;

		print.set_callable([&out](std::string str) -> void { out << str; });


		vm.global_types.add_global("print", print.get_type());
		vm.globals.variables["print"s] = (Value)print;
	}


	VMImpl* create_VM(std::ostream& out)
	{
		VMImpl *vm = new VMImpl();

		add_print_function(*vm, out);
		return vm;
	}

	void destroy_VM(VMImpl* vm)
	{
		delete vm;
	}

	void interpret(std::string_view code)
	{
		std::cout << "interpreting " << code << std::endl;

		VMImpl vm;
		add_print_function(vm, std::cout);

		auto expression = generate_AST(code);

		TypePass type_pass;
		expression->accept(type_pass);


		Interpreter interpreter(std::move(type_pass).get_globals());
		expression->accept(interpreter);

	}

	std::string print_type(TypeRepresentation const& type);
	std::string print_table(Table const& table);
	std::string print_tuple(Tuple const& tuple);
	std::string print_function(FunctionType const& function);
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
			else if constexpr (std::is_same_v<T, int8_t> || std::is_same_v<T, uint8_t>)
			{
				std::stringstream ss;
				ss << (int)value;
				return ss.str();
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
				ss << "typedef " << print_type(value);
				
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

	std::string print_type(TypeRepresentation const& type)
	{
		return std::visit([] <typename T>(T value) -> std::string {
			if constexpr (std::is_same_v<T, BuildInType>)
			{
				switch (value)
				{
				case BuildInType::Void:
					return "void";
				case BuildInType::Bool:
					return "bool";
				case BuildInType::I8:
					return "int8";
				case BuildInType::I16:
					return "int16";
				case BuildInType::I32:
					return "int32";
				case BuildInType::I64:
					return "int64";
				case BuildInType::U8:
					return "uint8";
				case BuildInType::U16:
					return "uint16";
				case BuildInType::U32:
					return "uint32";
				case BuildInType::U64:
					return "uint64";
				case BuildInType::F32:
					return "float";
				case BuildInType::F64:
					return "double";
				case BuildInType::Typedef:
					return "typedef";
				default:
					assert(false);
					return "????";
				}
			}
			else if constexpr (std::is_same_v<T, std::shared_ptr<ComplexType>>)
			{
				if (auto function = get<FunctionType>((TypeRepresentation)value))
				{
					return print_function(*function);
				}
				else
				{
					return "?????";
				}
			}
			else
			{
				// TODO
				return "??????";
			}
		}, type);
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

	std::string print_function(FunctionType const& function_type)
	{
		std::stringstream ss;
		if (function_type.is_pure)
			ss << "pure ";
		ss << "function " << function_type.name << " ( ";

		const char* comma = "";
		for (int i = 0; i < function_type.parameters.get_num_fields(); ++i)
		{
			ss << comma << function_type.parameters.get_field_name(i) << ": " << print_type(function_type.parameters.get_field_type(i));
			comma = ", ";
		}
		ss << " ) -> " << print_type(function_type.return_type);
		return ss.str();
	}

	std::string print_function(FunctionRepresentation const& function)
	{
		return "instance of " + print_function(function.get_type());
	}

	void interpret(VMImpl* vm, std::string_view code, std::ostream &out, std::ostream& err)
	{
		assert(vm != nullptr);

		try
		{
			auto expression = generate_AST(code);

			{
				TypePass type_pass;
				type_pass.set_globals(std::move(vm->global_types));
				expression->accept(type_pass);
				vm->global_types = std::move(type_pass).get_globals();
			}

			Interpreter interpreter(vm->global_types);
			interpreter.set_globals(vm->globals);
			expression->accept(interpreter);
			vm->globals = interpreter.get_globals();

			out << print_value(interpreter.get_last_expression_value());
			
		}
		catch (ParseException pe)
		{
			err << pe.print_error() << std::endl;
		}
		catch (TypeException te)
		{
			err << te.print_error() << std::endl;
		}
	}

}
