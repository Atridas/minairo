module;

#include <cassert>
#include <cinttypes>

#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <variant>
#include <vector>

export module Minairo.AST.Interpreter;

import Minairo.AST;
import Minairo.AST.TypePass;
import Minairo.FunctionRepresentation;
import Minairo.Scanner;
import Minairo.TypeRepresentation;


export namespace minairo
{
	class Value;

	struct Tuple
	{
		TupleType type;
		std::vector<Value> fields;
	};

	struct TupleReferenceOnStack
	{
		Tuple* tuple;

		Value& get_field(int index)
		{
			return tuple->fields[index];
		}

		Tuple& as_tuple() const
		{
			return *tuple;
		}
	};

	struct TupleReference : public std::variant<TupleReferenceOnStack>
	{
		Value& get_field(int index)
		{
			return std::visit([index](auto self) -> Value&
				{
					return self.get_field(index);
				}, *this);
		}

		Tuple as_tuple() const
		{
			return std::visit([](auto self) -> Tuple&
				{
					return self.as_tuple();
				}, *this);
		}
	};

	class Value : public std::variant<
		int8_t, int16_t, int32_t, int64_t,
		uint8_t, uint16_t, uint32_t, uint64_t,
		float, double,
		std::string,
		char32_t,
		bool,
		TypeRepresentation,
		Tuple,
		TupleReference>
	{
		using Base = std::variant<
			int8_t, int16_t, int32_t, int64_t,
			uint8_t, uint16_t, uint32_t, uint64_t,
			float, double,
			std::string,
			char32_t,
			bool,
			TypeRepresentation,
			Tuple,
			TupleReference>;


	public:
		Value() = default;
		Value(int8_t const& i) : Base{ i } {};
		Value(int16_t const& i) : Base{ i } {};
		Value(int32_t const& i) : Base{ i } {};
		Value(int64_t const& i) : Base{ i } {};
		Value(uint8_t const& i) : Base{ i } {};
		Value(uint16_t const& i) : Base{ i } {};
		Value(uint32_t const& i) : Base{ i } {};
		Value(uint64_t const& i) : Base{ i } {};
		Value(float const& i) : Base{ i } {};
		Value(double const& i) : Base{ i } {};
		Value(bool const& i) : Base{ i } {};
		Value(TypeRepresentation const& i) : Base{ i } {};
		Value(BuildInType const& i) : Base{ (TypeRepresentation)i } {};
		Value(TupleType const& i) : Base{ (TypeRepresentation)i } {};
		Value(Tuple const& i) : Base{ i } {};
		Value(TupleReferenceOnStack const& i) : Base{ (TupleReference)i } {};

		Value(Value const&) = default;
		Value(Value&&) = default;
		Value& operator=(Value const&) = default;
		Value& operator=(Value&&) = default;
	};



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
			else if constexpr (std::is_same_v<T, TypeRepresentation>)
			{
				return BuildInType::Typedef;
			}
			else
			{
				assert(false);
				return BuildInType::Void;
			}
		}, value);
	}

	Value cast(BuildInType type, std::variant<uint64_t, double, std::string, char32_t, bool> const& value)
	{
		switch (type)
		{
		case BuildInType::I8:
			return (int8_t)std::get<uint64_t>(value);
		case BuildInType::I16:
			return (int16_t)std::get<uint64_t>(value);
		case BuildInType::I32:
			return (int32_t)std::get<uint64_t>(value);
		case BuildInType::I64:
			return (int64_t)std::get<uint64_t>(value);
		case BuildInType::U8:
			return (uint8_t)std::get<uint64_t>(value);
		case BuildInType::U16:
			return (uint16_t)std::get<uint64_t>(value);
		case BuildInType::U32:
			return (uint32_t)std::get<uint64_t>(value);
		case BuildInType::U64:
			return (uint64_t)std::get<uint64_t>(value);
		case BuildInType::F32:
			return (float)std::get<double>(value);
		case BuildInType::F64:
			return (double)std::get<double>(value);
		case BuildInType::Bool:
			return std::get<bool>(value);
		default:
			assert(false);
			return (int32_t)0;
		}
	}

	Value get_default_value(BuildInType type);
	Value get_default_value(TupleType const& type);
	Value get_default_value(TypeRepresentation const& type);

	Value get_default_value(BuildInType type)
	{
		switch (type)
		{
		case BuildInType::I8:
			return (int8_t)0;
		case BuildInType::I16:
			return (int16_t)0;
		case BuildInType::I32:
			return (int32_t)0;
		case BuildInType::I64:
			return (int64_t)0;
		case BuildInType::U8:
			return (uint8_t)0;
		case BuildInType::U16:
			return (uint16_t)0;
		case BuildInType::U32:
			return (uint32_t)0;
		case BuildInType::U64:
			return (uint64_t)0;
		case BuildInType::F32:
			return (float)0;
		case BuildInType::F64:
			return (double)0;
		case BuildInType::Bool:
			return false;
		case BuildInType::Typedef:
			return BuildInType::Void;
		default:
			assert(false);
			return BuildInType::Void;
		}
	}

	Value get_default_value(TupleType const& type)
	{
		Tuple result;
		result.type = type;

		for (int i = 0; i < type.get_num_fields(); ++i)
		{
			if (type.get_field_type(i).is_build_in())
			{
				result.fields.push_back(cast(*type.get_field_type(i).as_build_in(), type.get_field_init_value(i)));
			}
			else
			{
				result.fields.push_back(get_default_value(type.get_field_type(i)));
			}
		}

		return result;
	}

	Value get_default_value(TypeRepresentation const& type)
	{
		return std::visit([](auto t) { return get_default_value(t); }, type);
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
			case BuildInType::Typedef:
				value = BuildInType::Void;
				return (void*)&std::get<TypeRepresentation>(value);
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
		explicit Interpreter(int _number_of_globals = 0, int _number_of_tuples = 0)
			: number_of_globals(_number_of_globals)
			, number_of_tuples(_number_of_tuples)
		{}

		struct GlobalStack
		{
			std::vector<Value> variables;
		};

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

		void visit(BuildInTypeDeclaration const& build_tn_type_declaration) override
		{
			last_expression_value = build_tn_type_declaration.type;
		}

		void visit(Grouping const& grouping) override
		{
			grouping.expr->accept(*this);
		}

		void visit(InitializerList const& initializer_list) override
		{
			Tuple temporary_tuple;
			temporary_tuple.type = initializer_list.destination_type;

			temporary_tuple.fields.resize(temporary_tuple.type.get_num_fields());
			for (int i = 0; i < (int)initializer_list.default_initializers.size(); ++i)
			{
				int index = initializer_list.default_initializers[i];

				auto field_type = temporary_tuple.type.get_field_type(index);
				if (field_type.is_build_in())
				{
					temporary_tuple.fields[index] = cast(*field_type.as_build_in(), temporary_tuple.type.get_field_init_value(index));
				}
				else
				{
					temporary_tuple.fields[index] = get_default_value(temporary_tuple.type.get_field_type(index));
				}


			}

			for (int i = 0; i < (int)initializer_list.indexes.size(); ++i)
			{
				int index = initializer_list.indexes[i];
				initializer_list.expressions[i]->accept(*this);

				temporary_tuple.fields[index] = last_expression_value;
			}
			last_expression_value = temporary_tuple;
		}

		void visit(Literal const& literal) override
		{
			if (std::holds_alternative<BuildInType>(literal.type_representation))
			{
				last_expression_value = cast(std::get<BuildInType>(literal.type_representation), literal.value);
			}
			else
			{
				assert(false);
			}
		}

		void visit(MemberRead const& member_read) override
		{
			member_read.left->accept(*this);
			Value result = std::get<TupleReference>(last_expression_value).get_field(member_read.index);
			last_expression_value = result;
		}

		void visit(MemberWrite const& member_write) override
		{
			member_write.right->accept(*this);
			Value value = last_expression_value;

			member_write.left->accept(*this);
			Value result = std::get<TupleReference>(last_expression_value).get_field(member_write.index) = value;
			last_expression_value = result;
		}

		void visit(TupleDeclaration const& tuple_declaration) override
		{
			last_expression_value = tuple_declaration.tuple;
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

		void visit(VariableAssign const& variable_assign) override
		{
			assert(variable_assign.index < variables.size());
			variable_assign.exp->accept(*this);
			variables[variable_assign.index] = last_expression_value;
		}

		void visit(VariableRead const& variable_read) override
		{
			if (*variable_read.type == BuildInType::Typedef)
			{
				assert(variable_read.index == -1);
				last_expression_value = *variable_read.static_type;
			}
			else if (variable_read.type->is_tuple_reference())
			{
				TupleReferenceOnStack tuple_ref;
				assert(variable_read.index >= 0 && variable_read.index < variables.size());
				tuple_ref.tuple = &std::get<Tuple>(variables[variable_read.index]);
				last_expression_value = tuple_ref;
			}
			else
			{
				assert(variable_read.index >= 0 && variable_read.index < variables.size());
				last_expression_value = variables[variable_read.index];
			}
		}

		// ----------------------------------------------------------------------------------------
		// ----------------------------------------------------------------------------------------
		// ----------------------------------------------------------------------------------------

		void visit(Block const &block) override
		{
			int current_stack_size = (int)variables.size();

			if (block.is_global)
			{
				variables = std::move(globals.variables);
			}

			for (auto& statement : block.statements)
			{
				statement->accept(*this);
			}

			if (block.is_global)
			{
				globals.variables = std::move(variables);
			}

			variables.resize(current_stack_size);
		}

		void visit(ExpressionStatement const &expression_statement) override
		{
			expression_statement.exp->accept(*this);

			if (std::holds_alternative<TupleReference>(last_expression_value))
			{
				last_expression_value = std::get<TupleReference>(last_expression_value).as_tuple();
			}
		}

		void visit(VariableDefinition const& variable_definition) override
		{
			if (*variable_definition.type == BuildInType::Typedef)
			{
				assert(variable_definition.index == -1);
				last_expression_value = *variable_definition.initialization->get_type_value();
			}
			else
			{
				assert(variables.size() == variable_definition.index);

				if (variable_definition.initialization)
				{
					variable_definition.initialization->accept(*this);
					variables.push_back(last_expression_value);
				}
				else if (!variable_definition.explicitly_uninitialized)
				{
					last_expression_value = get_default_value(*variable_definition.type);
					variables.push_back(last_expression_value);
				}
				else if (std::holds_alternative<TupleType>(*variable_definition.type))
				{
					Tuple tuple;
					tuple.type = std::get<TupleType>(*variable_definition.type); 
					last_expression_value = std::move(tuple);
					variables.push_back(last_expression_value);
				}
				else
				{
					variables.emplace_back();
				}
			}
		}


	private:
		Value last_expression_value;

		std::vector<Value> variables;
		GlobalStack globals;

		int number_of_globals;
		int number_of_tuples;
	};
}
