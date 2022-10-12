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
			for (int i = (int)(variable_blocks.size() - 1); i >= 0; --i)
			{
				auto info = variable_blocks[i].variables.find((std::string)variable_read.identifier.text);
				if (info != variable_blocks[i].variables.end())
				{
					assert(info->second.index >= 0);
					assert(info->second.index < variable_blocks[i].stack_size_at_beginning + variable_blocks[i].variables.size());
					variable_read.index = info->second.index;
					variable_read.type = info->second.type;
					return;
				}
			}

			// TODO variable is yet undefined
			throw 0;
		}

		// ----------------------------------------------------------------------------------------
		// ----------------------------------------------------------------------------------------
		// ----------------------------------------------------------------------------------------

		void visit(Block& block) override
		{
			push_variable_block();
			for (auto& statement : block.statements)
			{
				statement->accept(*this);
			}
			// TODO throw(?)
			pop_variable_block();
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

			assert(!variable_blocks.empty());

			VariableBlock& current_block = variable_blocks.back();

			if (current_block.variables.contains((std::string)variable_definition.variable.text))
			{
				// TODO
				throw 0;
			}
			else
			{
				variable_definition.initialization->accept(*this);
				VariableInfo info;
				variable_definition.type = info.type = *variable_definition.initialization->get_expression_type();
				variable_definition.index = info.index = current_block.stack_size_at_beginning + (int)current_block.variables.size();
				info.constant = variable_definition.constant;
				current_block.variables[(std::string)variable_definition.variable.text] =  info;
			}
		}

	private:
		FunctionMap function_map;

		struct VariableInfo
		{
			TypeRepresentation type;
			int index;
			bool constant;
		};

		struct VariableBlock
		{
			int stack_size_at_beginning;
			// TODO not a string map please. I'm just lazy rn
			std::unordered_map<std::string, VariableInfo> variables;
		};

		std::vector<VariableBlock> variable_blocks;

		void push_variable_block()
		{
			int stack_size_at_beginning = 0;
			if (!variable_blocks.empty())
				stack_size_at_beginning = variable_blocks.back().stack_size_at_beginning + (int)variable_blocks.back().variables.size();

			variable_blocks.push_back({ stack_size_at_beginning });
		}

		void pop_variable_block()
		{
			variable_blocks.pop_back();
		}
	};
}
