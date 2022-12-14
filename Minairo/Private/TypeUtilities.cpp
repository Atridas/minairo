module;

#include <cassert>
//
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>

module Minairo.AST.TypePass:TypeUtilities;

import Minairo.AST;
import Minairo.AST.TypePass;
import Minairo.TypesAndValues;

using namespace minairo;

bool minairo::all_paths_lead_to_a_return(Statement const& statement)
{
	class AllPathsLeadToReturn final : public StatementConstVisitor
	{
	public:
		bool found_return = false;

		virtual void visit(Block const& block)
		{
			for (auto& st : block.statements)
			{
				st->accept(*this);
			}
		}
		virtual void visit(ExpressionStatement const& expression_statement)
		{
			// ---
		}
		virtual void visit(ForeachStatement const& foreach_statement)
		{
			// ---
		}
		virtual void visit(IfStatement const& if_statement)
		{
			if (found_return)
				return;

			if (if_statement.no != nullptr)
			{
				if_statement.yes->accept(*this);
				if (found_return)
				{
					found_return = false;
					if_statement.no->accept(*this);
				}
			}

		}
		virtual void visit(ReturnStatement const& return_statement)
		{
			found_return = true;
		}
		virtual void visit(VariableDefinition const& variable_definition)
		{
			// ---
		}
		virtual void visit(WhileStatement const& while_statement)
		{
			// ---
		}

	} visitor;

	statement.accept(visitor);
	return visitor.found_return;
}

TypeInformation minairo::deduce_type(Expression const& expression)
{
	class DeduceType final : public ExpressionConstVisitor
	{
	public:
		TypeInformation type_information;

		void visit(Binary const& binary) override
		{
			switch (binary.op)
			{
			case Terminal::OP_ADD:
			case Terminal::OP_SUB:
			case Terminal::OP_MUL:
			case Terminal::OP_DIV:
			case Terminal::OP_MOD:
			case Terminal::OP_BIT_AND:
			case Terminal::OP_BIT_OR:
			case Terminal::OP_BIT_XOR:
			{
				type_information.type = deduce_type(*binary.left).type;
				break;
			}
			case Terminal::OP_OR:
			case Terminal::OP_AND:
			case Terminal::OP_EQ:
			case Terminal::OP_NEQ:
			case Terminal::OP_LT:
			case Terminal::OP_GT:
			case Terminal::OP_LTE:
			case Terminal::OP_GTE:
			{
				type_information.type = BuildInType::Bool;
				break;
			}
			default:
				assert(false); // TODO
			}

			type_information.constant = true;
		}
		void visit(BuildInTypeDeclaration const& build_in_type_declaration) override
		{
			type_information.type = BuildInType::Typedef;
			type_information.constant = true;
		}
		void visit(Call const& call) override
		{
			if (call.callee != nullptr)
			{
				std::shared_ptr<FunctionType> c = get<FunctionType>(deduce_type(*call.callee).type);
				if (c != nullptr)
				{
					type_information.type = c->return_type;
				}
			}
			type_information.constant = true;
		}
		void visit(Cast const& cast) override
		{
			type_information.type = cast.target_type;
			type_information.constant = true;
		}
		void visit(ConceptDeclaration const& concept_declaration) override
		{
			type_information.type = BuildInType::Typedef;
			type_information.constant = true;
		}
		void visit(Grouping const& grouping) override
		{
			type_information.type = deduce_type(*grouping.expr).type;
			type_information.constant = true;
		}
		void visit(InitializerList const& initializer_list) override
		{
			if (initializer_list.explicit_type)
			{
				type_information.type = initializer_list.destination_type;
			}
			else
			{
				type_information.type = BuildInType::InitializerList;
			}
			type_information.constant = true;
		}
		void visit(Literal const& literal) override
		{
			type_information.type = literal.type_representation;
			type_information.constant = true;
		}
		void visit(MemberRead const& member_read) override
		{
			type_information.type = *member_read.type;
			type_information.constant = member_read.constant;
		}
		void visit(MemberWrite const& member_write) override
		{
			type_information.type = *member_write.type;
			type_information.constant = false;
		}
		void visit(FunctionDeclaration const& function_declaration) override
		{
			type_information.type = function_declaration.header->type;
			type_information.constant = true;
		}
		void visit(FunctionTypeDeclaration const& function_type_declaration) override
		{
			type_information.type = BuildInType::Typedef;
			type_information.constant = true;
		}
		void visit(TableDeclaration const& table_declaration) override
		{
			type_information.type = BuildInType::Typedef;
			type_information.constant = true;
		}
		void visit(TupleDeclaration const& tuple_declaration) override
		{
			type_information.type = BuildInType::Typedef;
			type_information.constant = true;
		}
		void visit(UnaryPre const& unary_pre) override
		{
			if (unary_pre.function_to_call)
				type_information.type = unary_pre.function_to_call->get_return_type();
			type_information.constant = true;
		}
		void visit(UnaryPost const& unary_post) override
		{
			if (unary_post.function_to_call)
				type_information.type = unary_post.function_to_call->get_return_type();
			type_information.constant = true;
		}
		void visit(VariableAssign const& variable_assign) override
		{
			type_information.type = *variable_assign.type;
			type_information.constant = false;
		}
		void visit(VariableRead const& variable_read) override
		{
			type_information.type = *variable_read.type;
			type_information.constant = variable_read.constant;
		}
	};

	DeduceType type_deducer;
	expression.accept(type_deducer);

	return type_deducer.type_information;
}

std::optional<Value> minairo::get_compile_time_value(Expression const& expression)
{
	// TODO use the interpreter somehow

	class CompileTimeValue final : public ExpressionConstVisitor
	{
	public:
		std::optional<Value> result;

		void visit(Binary const& binary) override
		{
			result = std::nullopt;
		}
		void visit(BuildInTypeDeclaration const& build_in_type_declaration) override
		{
			result = build_in_type_declaration.type;
		}
		void visit(Call const& call) override
		{
			result = std::nullopt;
		}
		void visit(Cast const& cast) override
		{
			cast.expr->accept(*this);
			if (result)
			{
				if (cast.target_type.is_buildin())
				{
					result = std::visit([target_type = std::get<BuildInType>(cast.target_type)]<typename T>(T v) -> std::optional<Value>
					{
						if constexpr (std::is_same_v<T, int8_t> || std::is_same_v<T, int16_t> || std::is_same_v<T, int32_t> || std::is_same_v<T, int64_t> ||
							std::is_same_v<T, uint8_t> || std::is_same_v<T, uint16_t> || std::is_same_v<T, uint32_t> || std::is_same_v<T, uint64_t>)
						{
							switch (target_type)
							{
							case BuildInType::I8:
								return (int8_t)v;
							case BuildInType::I16:
								return (int16_t)v;
							case BuildInType::I32:
								return (int32_t)v;
							case BuildInType::I64:
								return (int64_t)v;
							case BuildInType::U8:
								return (uint8_t)v;
							case BuildInType::U16:
								return (uint16_t)v;
							case BuildInType::U32:
								return (uint32_t)v;
							case BuildInType::U64:
								return (uint64_t)v;
							case BuildInType::F32:
								return (float)v;
							case BuildInType::F64:
								return (double)v;
							default:
								return std::nullopt;
							}
						}
						else
						{
							return std::nullopt; // TODO
						}
					}, * result);
				}
			}
		}
		void visit(ConceptDeclaration const& concept_declaration) override
		{
			result = concept_declaration.type;
		}
		void visit(Grouping const& grouping) override
		{
			result = std::nullopt;
		}
		void visit(InitializerList const& initializer_list) override
		{
			result = std::nullopt;
		}
		void visit(Literal const& literal) override
		{
			if (std::holds_alternative<uint64_t>(literal.value))
			{
				result = cast(std::get<BuildInType>(literal.type_representation), literal.value);
			}
			else if (std::holds_alternative<bool>(literal.value))
			{
				result = cast(std::get<BuildInType>(literal.type_representation), literal.value);
			}
			else if (std::holds_alternative<std::string>(literal.value))
			{
				result = cast(std::get<BuildInType>(literal.type_representation), literal.value);
			}
			else
			{
				assert(false); // TODO
			}
		}
		void visit(MemberRead const& member_read) override
		{
			result = member_read.compile_time_value;
		}
		void visit(MemberWrite const& member_write) override
		{
			result = std::nullopt;
		}
		void visit(FunctionDeclaration const& function_declaration) override
		{
			result = (std::shared_ptr<ComplexValue>)std::make_shared<Function>(function_declaration.header->type, function_declaration.body->deep_copy());
		}
		void visit(FunctionTypeDeclaration const& function_type_declaration) override
		{
			result = function_type_declaration.type;
		}
		void visit(TableDeclaration const& table_declaration) override
		{
			result = table_declaration.table;
		}
		void visit(TupleDeclaration const& tuple_declaration) override
		{
			result = tuple_declaration.tuple;
		}
		void visit(UnaryPre const& unary_pre) override
		{
			result = std::nullopt;
		}
		void visit(UnaryPost const& unary_post) override
		{
			result = std::nullopt;
		}
		void visit(VariableAssign const& variable_assign) override
		{
			result = std::nullopt;
		}
		void visit(VariableRead const& variable_read) override
		{
			if (variable_read.static_type.has_value())
				result = *variable_read.static_type;
			else
				result = std::nullopt;
		}
	};

	CompileTimeValue compile_time_value;
	expression.accept(compile_time_value);

	return compile_time_value.result;
}
