module;

#include <cassert>
//#include <cinttypes>
//
#include <memory>
//#include <string>
//#include <type_traits>
#include <unordered_map>
//#include <variant>

export module Minairo.AST.TypePass;

import Minairo.AST;
import Minairo.FunctionRepresentation;
import Minairo.Scanner;
import Minairo.TypeRepresentation;


export namespace minairo
{
	class TypePass final : public ExpressionVisitor, public StatementVisitor
	{
	public:
		explicit TypePass(FunctionMap _function_map) : function_map(std::move(_function_map)) {}

		void visit(Binary& binary) override
		{
			binary.left->accept(*this);
			binary.right->accept(*this);

			TypeRepresentation argument_types[2] = { *binary.left->get_expression_type(), *binary.right->get_expression_type() };
			
			FunctionRepresentation const* function = nullptr;

			switch (binary.op)
			{
			case Terminal::OP_ADD:
			{
				function = function_map.get("operator+", argument_types);
				break;
			}
			case Terminal::OP_SUB:
			{
				function = function_map.get("operator-", argument_types);
				break;
			}
			case Terminal::OP_MUL:
			{
				function = function_map.get("operator*", argument_types);
				break;
			}
			case Terminal::OP_DIV:
			{
				function = function_map.get("operator/", argument_types);
				break;
			}
			case Terminal::OP_MOD:
			{
				function = function_map.get("operator%", argument_types);
				//last_expression_value = std::get<uint64_t>(left) % std::get<uint64_t>(last_expression_value);
				break;
			}
			default:
				assert(false); // TODO
			}

			assert(function != nullptr);
			binary.function_to_call = function;
		}

		void visit(Grouping& grouping) override
		{
			grouping.expr->accept(*this);
		}

		void visit(Literal& literal) override
		{
			// ------
		}

		void visit(UnaryPre& unary_pre) override
		{
			assert(false); // TODO
		}

		void visit(UnaryPost& unary_post) override
		{
			assert(false); // TODO
		}

		void visit(VariableRead& variable_read) override
		{
			// TODO local variables

			auto global = global_variables.find((std::string)variable_read.identifier.text);
			if (global == global_variables.end())
			{
				// TODO variable is yet undefined
				throw 0;
			}
			else
			{
				variable_read.is_gloval = true;
				variable_read.type = global->second.type;
			}
		}

		// ----------------------------------------------------------------------------------------
		// ----------------------------------------------------------------------------------------
		// ----------------------------------------------------------------------------------------

		void visit(Block& block) override
		{
			for (auto& statement : block.statements)
			{
				statement->accept(*this);
			}
		}
		
		void visit(ExpressionStatement& expression_statement) override
		{
			expression_statement.exp->accept(*this);
		}

		void visit(VariableDefinition& variable_definition) override
		{
			// TODO change this assumptions
			assert(variable_definition.initialization != nullptr);
			assert(!variable_definition.explicitly_uninitialized);

			// TODO local variables
			variable_definition.is_global = true;

			if (global_variables.contains((std::string)variable_definition.variable.text))
			{
				// TODO
				throw 0;
			}
			else
			{
				variable_definition.initialization->accept(*this);
				GlobalVariableInfo info;
				variable_definition.type = info.type = *variable_definition.initialization->get_expression_type();
				info.constant = variable_definition.constant;
				global_variables[(std::string)variable_definition.variable.text] =  info;
			}
		}

	private:
		FunctionMap function_map;

		struct GlobalVariableInfo
		{
			TypeRepresentation type;
			bool constant;
		};

		// TODO not a string map please. I'm just lazy rn
		std::unordered_map<std::string, GlobalVariableInfo> global_variables;
	};
}
