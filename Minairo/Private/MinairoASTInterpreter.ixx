module;

#include <cassert>
#include <cinttypes>

#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <variant>

export module Minairo.AST.Interpreter;

import Minairo.AST;
import Minairo.AST.TypePass;
import Minairo.FunctionRepresentation;
import Minairo.Scanner;
import Minairo.TypeRepresentation;


export namespace minairo
{
	using Value = std::variant<
		int8_t, int16_t, int32_t, int64_t,
		uint8_t, uint16_t, uint32_t, uint64_t,
		float, double,
		std::string,
		char32_t,
		bool>;

	TypeRepresentation get_type_representation(Value value)
	{
		return std::visit([]<typename T>(T v) -> TypeRepresentation
		{
			if constexpr (std::is_same_v<T, int8_t>)
			{
				return BuildInType::I8;
			}
			else if constexpr (std::is_same_v<T, int16_t>)
			{
				return BuildInType::I16;
			}
			else if constexpr (std::is_same_v<T, int32_t>)
			{
				return BuildInType::I32;
			}
			else if constexpr (std::is_same_v<T, int64_t>)
			{
				return BuildInType::I64;
			}
			else if constexpr (std::is_same_v<T, uint8_t>)
			{
				return BuildInType::U8;
			}
			else if constexpr (std::is_same_v<T, uint16_t>)
			{
				return BuildInType::U16;
			}
			else if constexpr (std::is_same_v<T, uint32_t>)
			{
				return BuildInType::U32;
			}
			else if constexpr (std::is_same_v<T, uint64_t>)
			{
				return BuildInType::U64;
			}
			else if constexpr (std::is_same_v<T, float>)
			{
				return BuildInType::F32;
			}
			else if constexpr (std::is_same_v<T, double>)
			{
				return BuildInType::F64;
			}
			else if constexpr (std::is_same_v<T, bool>)
			{
				return BuildInType::Bool;
			}
			else
			{
				assert(false);
				return BuildInType::Void;
			}
		}, value);
	}

	void* get_ptr(Value &value)
	{
		return std::visit([]<typename T>(T &v) -> void*
		{
			return (void*)&v;
		}, value);
	}

	void* set_to_type(Value& value, TypeRepresentation type)
	{
		if (std::holds_alternative<BuildInType>(type))
		{
			switch (std::get<BuildInType>(type))
			{
			case BuildInType::I8:
				value = (int8_t)0;
				return (void*)&std::get<int8_t>(value);
			case BuildInType::I16:
				value = (int16_t)0;
				return (void*)&std::get<int16_t>(value);
			case BuildInType::I32:
				value = (int32_t)0;
				return (void*)&std::get<int32_t>(value);
			case BuildInType::I64:
				value = (int64_t)0;
				return (void*)&std::get<int64_t>(value);
			case BuildInType::U8:
				value = (uint8_t)0;
				return (void*)&std::get<uint8_t>(value);
			case BuildInType::U16:
				value = (uint16_t)0;
				return (void*)&std::get<uint16_t>(value);
			case BuildInType::U32:
				value = (uint32_t)0;
				return (void*)&std::get<uint32_t>(value);
			case BuildInType::U64:
				value = (uint64_t)0;
				return (void*)&std::get<uint64_t>(value);
			case BuildInType::F32:
				value = (float)0;
				return (void*)&std::get<float>(value);
			case BuildInType::F64:
				value = (double)0;
				return (void*)&std::get<double>(value);
			case BuildInType::Bool:
				value = false;
				return (void*)&std::get<bool>(value);
			default:
				assert(false);
				return nullptr;
			}
		}
		else
		{
			assert(false);
			return nullptr;
		}
	}

	class Interpreter final : public ExpressionConstVisitor, public StatementConstVisitor
	{
	public:
		explicit Interpreter(int _number_of_globals = 0) : number_of_globals(_number_of_globals) {}

		using GlobalStack = std::vector<Value>;

		void set_globals(GlobalStack const& _globals)
		{
			globals = _globals;
		}

		GlobalStack const& get_globals() const
		{
			return globals;
		}

		Value get_last_expression_value() const noexcept { return last_expression_value; }

		void visit(Binary const& binary) override
		{
			binary.left->accept(*this);
			Value left = last_expression_value;
			binary.right->accept(*this);
			Value right = last_expression_value;

			void* arguments[2] = { get_ptr(left), get_ptr(right) };

			TypeRepresentation return_type = *binary.get_expression_type();
			void* result_ptr = set_to_type(last_expression_value, return_type);

			binary.function_to_call->call(result_ptr, arguments);
		}

		void visit(Grouping const& grouping) override
		{
			grouping.expr->accept(*this);
		}

		void visit(Literal const& literal) override
		{
			if (std::holds_alternative<BuildInType>(literal.type_representation))
			{
				switch (std::get<BuildInType>(literal.type_representation))
				{
				case BuildInType::I8:
					last_expression_value = (int8_t)std::get<uint64_t>(literal.value);
					break;
				case BuildInType::I16:
					last_expression_value = (int16_t)std::get<uint64_t>(literal.value);
					break;
				case BuildInType::I32:
					last_expression_value = (int32_t)std::get<uint64_t>(literal.value);
					break;
				case BuildInType::I64:
					last_expression_value = (int64_t)std::get<uint64_t>(literal.value);
					break;
				case BuildInType::U8:
					last_expression_value = (uint8_t)std::get<uint64_t>(literal.value);
					break;
				case BuildInType::U16:
					last_expression_value = (uint16_t)std::get<uint64_t>(literal.value);
					break;
				case BuildInType::U32:
					last_expression_value = (uint32_t)std::get<uint64_t>(literal.value);
					break;
				case BuildInType::U64:
					last_expression_value = (uint64_t)std::get<uint64_t>(literal.value);
					break;
				case BuildInType::F32:
					last_expression_value = (float)std::get<double>(literal.value);
					break;
				case BuildInType::F64:
					last_expression_value = (double)std::get<double>(literal.value);
					break;
				case BuildInType::Bool:
					last_expression_value = std::get<bool>(literal.value);
					break;
				default:
					assert(false);
					break;
				}
			}
			else
			{
				assert(false);
			}
		}

		void visit(UnaryPre const& unary_pre) override
		{
			unary_pre.exp->accept(*this);
			Value exp = last_expression_value;

			void* arguments[1] = {get_ptr(exp)};

			TypeRepresentation return_type = *unary_pre.get_expression_type();
			void* result_ptr = set_to_type(last_expression_value, return_type);

			unary_pre.function_to_call->call(result_ptr, arguments);
		}

		void visit(UnaryPost const& unary_post) override
		{
			unary_post.exp->accept(*this);
			Value exp = last_expression_value;

			void* arguments[1] = { get_ptr(exp) };

			TypeRepresentation return_type = *unary_post.get_expression_type();
			void* result_ptr = set_to_type(last_expression_value, return_type);

			unary_post.function_to_call->call(result_ptr, arguments);
		}

		void visit(VariableRead const& variable_read) override
		{
			assert(variable_read.index < variables.size());
			last_expression_value = variables[variable_read.index];
		}

		// ----------------------------------------------------------------------------------------
		// ----------------------------------------------------------------------------------------
		// ----------------------------------------------------------------------------------------

		void visit(Block const &block) override
		{
			int current_stack_size = (int)variables.size();

			if (block.is_global)
			{
				variables = std::move(globals);
			}

			for (auto& statement : block.statements)
			{
				statement->accept(*this);
			}

			if (block.is_global)
			{
				globals = std::move(variables);
			}

			variables.resize(current_stack_size);
		}

		void visit(ExpressionStatement const &expression_statement) override
		{
			expression_statement.exp->accept(*this);
		}

		void visit(VariableDefinition const& variable_definition) override
		{
			if (variable_definition.initialization)
			{
				variable_definition.initialization->accept(*this);
			}
			else if (!variable_definition.explicitly_uninitialized)
			{
				assert(false);
				// TODO zero initialization
				// last_expression_value = 0
			}

			assert(variables.size() == variable_definition.index);
			if (!variable_definition.explicitly_uninitialized)
			{
				variables.push_back(last_expression_value);
			}
			else
			{
				variables.emplace_back();
			}
		}


	private:
		Value last_expression_value;

		std::vector<Value> variables;
		std::vector<Value> globals;

		int number_of_globals;
	};
}
