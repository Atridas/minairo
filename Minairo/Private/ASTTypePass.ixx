module;

#include <cassert>
//
#include <memory>
#include <optional>
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
			VariableRedefinition,
			ConstWrite,
			Message
		} type;

		std::string message;
		TerminalData terminal_data;
		TerminalData first_token, last_token;

		std::string print_error()
		{
			std::stringstream ss;
			switch (type)
			{
			case Type::UnknownIdentifier:
				ss << "Identifier '" << terminal_data.text << "' is yet undefined\n";
				print_error_line(ss, first_token, last_token);
				break;
			case Type::VariableRedefinition:
				ss << "Variable '" << terminal_data.text << "' has already been defined\n";
				print_error_line(ss, first_token, last_token);
				break;
			case Type::ConstWrite:
				ss << "Variable '" << terminal_data.text << "' is constant and can't be written too\n";
				print_error_line(ss, first_token, last_token);
				break;
			case Type::Message:
				ss << message;
				print_error_line(ss, first_token, last_token);
				break;
			default:
				assert(false);
				break;
			}
			return ss.str();
		}
	};

	TypeException unknown_literal_exception(TerminalData identifier)
	{
		assert(identifier.type == Terminal::IDENTIFIER);
		TypeException result;
		result.type = TypeException::Type::UnknownIdentifier;
		result.first_token = result.last_token = result.terminal_data = identifier;
		return result;
	}

	TypeException variable_redefinition_exception(TerminalData identifier)
	{
		assert(identifier.type == Terminal::IDENTIFIER);
		TypeException result;
		result.type = TypeException::Type::VariableRedefinition;
		result.first_token = result.last_token = result.terminal_data = identifier;
		return result;
	}

	TypeException const_write_exception(TerminalData identifier)
	{
		assert(identifier.type == Terminal::IDENTIFIER);
		TypeException result;
		result.type = TypeException::Type::ConstWrite;
		result.first_token = result.last_token = result.terminal_data = identifier;
		return result;
	}

	TypeException message_exception(std::string_view message, TerminalData token)
	{
		TypeException result;
		result.type = TypeException::Type::Message;
		result.first_token = result.last_token = token;
		return result;
	}

	TypeException message_exception(std::string_view message, TerminalData first_token, TerminalData last_token)
	{
		TypeException result;
		result.type = TypeException::Type::Message;
		result.message = message;
		result.first_token = first_token;
		result.last_token = last_token;
		return result;
	}

	TypeException message_exception(std::string_view message, Statement const& statement)
	{
		return message_exception(message, statement.get_first_terminal(), statement.get_last_terminal());
	}

	TypeException message_exception(std::string_view message, Expression const& expression)
	{
		return message_exception(message, expression.get_first_terminal(), expression.get_last_terminal());
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
				binary.function_to_call = function_map.get("operator+", argument_types);
				break;
			}
			case Terminal::OP_SUB:
			{
				binary.function_to_call = function_map.get("operator-", argument_types);
				break;
			}
			case Terminal::OP_MUL:
			{
				binary.function_to_call = function_map.get("operator*", argument_types);
				break;
			}
			case Terminal::OP_DIV:
			{
				binary.function_to_call = function_map.get("operator/", argument_types);
				break;
			}
			case Terminal::OP_MOD:
			{
				binary.function_to_call = function_map.get("operator%", argument_types);
				break;
			}
			default:
				assert(false); // TODO
			}

			assert(binary.function_to_call != nullptr);
		}

		void visit(BuildInTypeDeclaration&) override
		{
			// -------
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

		void visit(VariableAssign& variable_assign) override
		{
			variable_assign.exp->accept(*this);

			auto variable = find_variable(variable_assign.identifier);
			if (variable.constant)
			{
				throw const_write_exception(variable_assign.identifier);
			}
			variable_assign.type = variable.type;
			variable_assign.index = variable.index;

			if (*variable_assign.type != *variable_assign.exp->get_expression_type())
			{
				throw message_exception("Assignment of different types\n", variable_assign.identifier);
			}
		}

		void visit(VariableOperatorAndAssign& variable_op_assign) override
		{
			variable_op_assign.exp->accept(*this);

			auto variable = find_variable(variable_op_assign.identifier);
			if (variable.constant)
			{
				throw const_write_exception(variable_op_assign.identifier);
			}
			variable_op_assign.type = variable.type;
			variable_op_assign.index = variable.index;

			if (*variable_op_assign.type != *variable_op_assign.exp->get_expression_type())
			{
				throw message_exception("Assignment of different types\n", variable_op_assign.op);
			}

			TypeRepresentation argument_types[2] = { *variable_op_assign.type, *variable_op_assign.exp->get_expression_type() };
			FunctionRepresentation const* function = nullptr;
			switch (variable_op_assign.op.type)
			{
			case Terminal::OP_ASSIGN_ADD:
			{
				variable_op_assign.function_to_call = function_map.get("operator+", argument_types);
				break;
			}
			case Terminal::OP_ASSIGN_SUB:
			{
				variable_op_assign.function_to_call = function_map.get("operator-", argument_types);
				break;
			}
			case Terminal::OP_ASSIGN_MUL:
			{
				variable_op_assign.function_to_call = function_map.get("operator*", argument_types);
				break;
			}
			case Terminal::OP_ASSIGN_DIV:
			{
				variable_op_assign.function_to_call = function_map.get("operator/", argument_types);
				break;
			}
			case Terminal::OP_ASSIGN_MOD:
			{
				variable_op_assign.function_to_call = function_map.get("operator%", argument_types);
				break;
			}
			default:
				assert(false); // TODO
			}

			assert(variable_op_assign.function_to_call != nullptr);
		}

		void visit(VariableRead& variable_read) override
		{
			auto variable = find_variable(variable_read.identifier);
			variable_read.type = variable.type;
			variable_read.index = variable.index;
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
				info.type = *variable_definition.initialization->get_expression_type();
				if (!variable_definition.type.has_value())
				{
					variable_definition.type = info.type;
				}
				else if(*variable_definition.type != info.type)
				{
					throw message_exception("wrong variable type\n", variable_definition);
				}
				
				if (variable_definition.type == BuildInType::Typedef && !variable_definition.constant)
				{
					throw message_exception("typedefs must be constant\n", variable_definition);
				}

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

		VariableInfo find_variable(TerminalData identifier)
		{
			for (int i = (int)(variable_blocks.size() - 1); i >= 0; --i)
			{
				auto info = variable_blocks[i].variables.find((std::string)identifier.text);
				if (info != variable_blocks[i].variables.end())
				{
					assert(info->second.index >= 0);
					assert(info->second.index < variable_blocks[i].stack_size_at_beginning + variable_blocks[i].variables.size());
					return info->second;
				}
			}
			throw unknown_literal_exception(identifier);
		}
	};
}
