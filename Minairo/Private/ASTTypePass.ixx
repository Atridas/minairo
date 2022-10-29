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
		explicit TypePass(FunctionMap& _function_map) : function_map(_function_map) {}

		struct GlobalMap
		{
			// TODO not a string map please. I'm just lazy rn
			std::unordered_map<std::string, VariableInfo> variables;
			std::unordered_map<std::string, TypeRepresentation> types;
		};

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

		void visit(InitializerList& initializer_list) override
		{
			for (auto &expr : initializer_list.expressions)
			{
				expr->accept(*this);
			}
		}

		void visit(Literal& literal) override
		{
			// ------
		}

		void visit(MemberRead& member_read) override
		{
			member_read.left->accept(*this);
			TypeRepresentation left_type = *member_read.left->get_expression_type();
			if (auto tupleopt = left_type.as_tuple_reference())
			{
				TupleReferenceType tuple_ref = *std::move(tupleopt);
				if (tuple_ref.tuple.has_field(member_read.member.text))
				{
					member_read.index = tuple_ref.tuple.get_field_index(member_read.member.text);
					member_read.type = tuple_ref.tuple.get_field_type(member_read.member.text);
				}
				else
				{
					throw message_exception("tuple doesn't have a member of this name\n", member_read);
				}
			}
			else
			{
				throw message_exception("Expected a tuple before '.'\n", *member_read.left);
			}
		}

		void visit(MemberWrite& member_write) override
		{
			member_write.left->accept(*this);
			TypeRepresentation left_type = *member_write.left->get_expression_type();
			if (auto tupleopt = left_type.as_tuple_reference())
			{
				TupleReferenceType tuple_ref = *std::move(tupleopt);
				if (!tuple_ref.tuple.has_field(member_write.member.text))
				{
					throw message_exception("tuple doesn't have a member of this name\n", member_write);
				}
				else if (tuple_ref.constant)
				{
					throw message_exception("can't assign to a member of a constant tuple\n", member_write);
				}
				else
				{
					member_write.right->accept(*this);

					member_write.index = tuple_ref.tuple.get_field_index(member_write.member.text);
					member_write.type = tuple_ref.tuple.get_field_type(member_write.member.text);


					if (*member_write.type != *member_write.right->get_expression_type())
					{
						throw message_exception("Assignment of different types\n", member_write);
					}
				}
			}
			else
			{
				throw message_exception("Expected a tuple before '.'\n", *member_write.left);
			}
		}

		void visit(TupleDeclaration& tuple_declaration) override
		{
			assert(tuple_declaration.field_names.size() == tuple_declaration.field_types.size());


			TypeRepresentation last_type;
			uint64_t last_initial_value = 0;


			for (int i = 0; i < tuple_declaration.field_names.size(); ++i)
			{
				if (tuple_declaration.tuple.has_field(tuple_declaration.field_names[i].text))
				{
					throw message_exception("Repeated field in tuple declaration\n", tuple_declaration.field_names[i]);
				}

				TypeRepresentation field_type;
				uint64_t initial_value = 0;

				if (tuple_declaration.field_types[i])
				{
					tuple_declaration.field_types[i]->accept(*this);
					field_type = *tuple_declaration.field_types[i]->get_type_value();
				}

				if (tuple_declaration.field_initializers[i])
				{
					tuple_declaration.field_initializers[i]->accept(*this);
					if (auto init = tuple_declaration.field_initializers[i]->get_constant_value())
					{
						initial_value = *init;
					}
					else
					{
						throw message_exception("Couldn't get constant\n", *tuple_declaration.field_initializers[i]);
					}
				}

				if (tuple_declaration.field_types[i] && tuple_declaration.field_initializers[i])
				{
					if(!implicit_cast(*tuple_declaration.field_types[i]->get_type_value(), tuple_declaration.field_initializers[i]))
					{
						throw message_exception("Initializer has not the right type\n", *tuple_declaration.field_initializers[i]);
					}
				}
				else if (tuple_declaration.field_initializers[i])
				{
					assert(!tuple_declaration.field_types[i]);
					field_type = *tuple_declaration.field_initializers[i]->get_expression_type();
				}
				else if (!tuple_declaration.field_types[i] && !tuple_declaration.field_initializers[i])
				{
					field_type = last_type;
					initial_value = last_initial_value;
				}
				
				tuple_declaration.tuple.add_field(tuple_declaration.field_names[i].text, field_type, initial_value);

				last_type = field_type;
				last_initial_value = initial_value;
			}
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


			if (!implicit_cast(*variable_assign.type, variable_assign.exp))
			{
				throw message_exception("Assignment of different types", *variable_assign.exp);
			}
		}

		void visit(VariableRead& variable_read) override
		{
			if (auto type = find_typedef(variable_read.identifier))
			{
				variable_read.static_type = type;
				variable_read.type = BuildInType::Typedef;
			}
			else
			{
				auto variable = find_variable(variable_read.identifier);
				if (variable.type.is_tuple())
				{
					TupleReferenceType as_reference;
					as_reference.tuple = *variable.type.as_tuple();
					as_reference.constant = variable.constant;
					variable_read.type = as_reference;
				}
				else
				{
					variable_read.type = variable.type;
				}
				variable_read.index = variable.index;
			}
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
				variable_blocks.back().variables = std::move(globals.variables);
				variable_blocks.back().types = std::move(globals.types);
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
				globals.variables = std::move(variable_blocks.back().variables);
				globals.types = std::move(variable_blocks.back().types);
			}

			pop_variable_block();
		}

		void visit(ExpressionStatement& expression_statement) override
		{
			expression_statement.exp->accept(*this);
		}

		void visit(VariableDefinition& variable_definition) override
		{
			assert(!variable_blocks.empty());

			VariableBlock& current_block = variable_blocks.back();

			if (current_block.variables.contains((std::string)variable_definition.variable.text))
			{
				throw variable_redefinition_exception(variable_definition.variable);
			}

			assert(variable_definition.type_definition != nullptr || variable_definition.initialization != nullptr);


			if (variable_definition.type_definition != nullptr)
			{
				variable_definition.type_definition->accept(*this);

				if (*variable_definition.type_definition->get_expression_type() != BuildInType::Typedef)
				{
					throw message_exception("Expected a type definition\n", *variable_definition.type_definition);
				}
				variable_definition.type = variable_definition.type_definition->get_type_value();
			}

			if (variable_definition.initialization != nullptr)
			{
				variable_definition.initialization->accept(*this);
				if (variable_definition.type_definition == nullptr)
				{
					variable_definition.type = *variable_definition.initialization->get_expression_type();
				}
				else if (!implicit_cast(*variable_definition.type, variable_definition.initialization))
				{
					throw message_exception("wrong variable type\n", variable_definition);
				}
			}

			if (variable_definition.type == BuildInType::Typedef)
			{
				if (variable_definition.type == BuildInType::Typedef && !variable_definition.constant)
				{
					throw message_exception("typedefs must be constant\n", variable_definition);
				}

				current_block.types[(std::string)variable_definition.variable.text] = *variable_definition.initialization->get_type_value();
			}
			else
			{
				VariableInfo info;
				info.type = *variable_definition.type;
				variable_definition.index = info.index = current_block.stack_size_at_beginning + (int)current_block.variables.size();
				info.constant = variable_definition.constant;
				current_block.variables[(std::string)variable_definition.variable.text] = info;
			}
		}

	private:
		FunctionMap& function_map;

		struct VariableBlock
		{
			int stack_size_at_beginning;
			// TODO not a string map please. I'm just lazy rn
			std::unordered_map<std::string, VariableInfo> variables;
			std::unordered_map<std::string, TypeRepresentation> types;
		};

		std::vector<VariableBlock> variable_blocks;

		GlobalMap globals;

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

		std::optional<TypeRepresentation> find_typedef(TerminalData identifier)
		{
			for (int i = (int)(variable_blocks.size() - 1); i >= 0; --i)
			{
				auto info = variable_blocks[i].types.find((std::string)identifier.text);
				if (info != variable_blocks[i].types.end())
				{
					return info->second;
				}
			}
			return std::nullopt;
		}

		bool implicit_cast(TypeRepresentation target, std::unique_ptr<Expression> &origin)
		{
			if (target == origin->get_expression_type())
				return true;
			else if (target.is_tuple() && origin->get_expression_type() == BuildInType::InitializerList)
			{
				assert(dynamic_cast<InitializerList*>(origin.get()));
				InitializerList* initializer_list = static_cast<InitializerList*>(origin.get());
				initializer_list->destination_type = *target.as_tuple();

				int last_index = -1;
				for (int i = 0; i < (int)initializer_list->expressions.size(); ++i)
				{
					int index;
					if (initializer_list->names[i])
					{
						if (!initializer_list->destination_type.has_field(initializer_list->names[i]->text))
						{
							throw message_exception("tuple doesn't have this field\n", *initializer_list->names[i]);
						}
						index = initializer_list->destination_type.get_field_index(initializer_list->names[i]->text);
						if (std::find(initializer_list->indexes.begin(), initializer_list->indexes.end(), index) != initializer_list->indexes.end())
						{
							throw message_exception("this field has already been initialized", *initializer_list->names[i]);
						}
					}
					else
					{
						++last_index;
						while (std::find(initializer_list->indexes.begin(), initializer_list->indexes.end(), last_index) != initializer_list->indexes.end())
						{
							++last_index;
						}
						index = last_index;

						if (index >= initializer_list->destination_type.get_num_fields())
						{
							throw message_exception("too many initializer values for this tuple", *initializer_list->expressions[i]);
						}
					}

					if (!implicit_cast(initializer_list->destination_type.get_field_type(index), initializer_list->expressions[i]))
					{
						throw message_exception("initializer has the wrong type", *initializer_list->expressions[i]);
					}

					initializer_list->indexes.push_back(index);
					last_index = index;
				}

				for (int i = 0; i < initializer_list->destination_type.get_num_fields(); ++i)
				{
					if (std::find(initializer_list->indexes.begin(), initializer_list->indexes.end(), i) == initializer_list->indexes.end())
					{
						initializer_list->default_initializers.push_back(i);
					}
				}

				return true;
			}
			else
				return false;
		}

	};
}
