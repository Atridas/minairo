module;

#include <cassert>
//
#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>

export module Minairo.AST.TypePass;

import Minairo.AST;
import Minairo.Exception;
import Minairo.FunctionRepresentation;
import Minairo.Scanner;
import Minairo.TypeRepresentation;


export namespace minairo
{
	struct TypeException
	{
		enum class Type
		{
			UnknownIdentifier,
			VariableRedefinition
		} type;

		TerminalData terminal_data;

		std::string print_error()
		{
			std::stringstream ss;
			switch (type)
			{
			case Type::UnknownIdentifier:
				ss << "Identifier '" << terminal_data.text << "' is yet undefined\n";
				print_error_line(ss);
				break;
			case Type::VariableRedefinition:
				ss << "Variable '" << terminal_data.text << "' has already been defined\n";
				print_error_line(ss);
				break;
			default:
				assert(false);
				break;
			}
			return ss.str();
		}

	private:
		void print_error_line(std::stringstream& ss)
		{
			minairo::print_error_line(ss, terminal_data.line, terminal_data.text, terminal_data.line_begin, terminal_data.line_end);
		}
	};

	TypeException unknown_literal_exception(TerminalData identifier)
	{
		assert(identifier.type == Terminal::IDENTIFIER);
		TypeException result;
		result.type = TypeException::Type::UnknownIdentifier;
		result.terminal_data = identifier;
		return result;
	}

	TypeException variable_redefinition_exception(TerminalData identifier)
	{
		assert(identifier.type == Terminal::IDENTIFIER);
		TypeException result;
		result.type = TypeException::Type::VariableRedefinition;
		result.terminal_data = identifier;
		return result;
	}

	// --------------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------------

	class TypePass final : public ExpressionVisitor, public StatementVisitor
	{
		struct VariableInfo
		{
			TypeRepresentation type;
			int index;
			bool constant;
		};

	public:
		explicit TypePass(FunctionMap &_function_map) : function_map(_function_map) {}

		using GlobalMap = std::unordered_map<std::string, VariableInfo>;

		void set_globals(GlobalMap const& global_map)
		{
			globals = global_map;
		}

		GlobalMap const& get_globals() const
		{
			return globals;
		}

		// ----------------------------------------------------------------------------------------------

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

			throw unknown_literal_exception(variable_read.identifier);
		}

		// ----------------------------------------------------------------------------------------
		// ----------------------------------------------------------------------------------------
		// ----------------------------------------------------------------------------------------

		void visit(Block& block) override
		{
			push_variable_block();

			if (block.is_global)
			{
				assert(variable_blocks.size() == 1);
				// set up inhereted globals
				variable_blocks.back().variables = std::move(globals);
			}

			for (auto& statement : block.statements)
			{
				statement->accept(*this);
			}
			// TODO throw(?)

			if (block.is_global)
			{
				assert(variable_blocks.size() == 1);
				// store the globals back
				globals = std::move(variable_blocks.back().variables);
			}

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
				throw variable_redefinition_exception(variable_definition.variable);
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
		FunctionMap &function_map;

		struct VariableBlock
		{
			int stack_size_at_beginning;
			// TODO not a string map please. I'm just lazy rn
			std::unordered_map<std::string, VariableInfo> variables;
		};

		std::vector<VariableBlock> variable_blocks;

		// TODO not a string map please. I'm just lazy rn
		std::unordered_map<std::string, VariableInfo> globals;

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
