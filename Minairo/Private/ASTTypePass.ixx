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
import Minairo.Scanner;
import Minairo.TypesAndValues;


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
				ss << message << '\n';
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
		result.message = message;
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

	struct Procedure final : public FunctionRepresentation
	{
		ProcedureType type;
		std::shared_ptr<Statement> body;

		Procedure() = default;
		Procedure(ProcedureType const& _type, std::shared_ptr<Statement> const& _body) : type(_type), body(_body) {}
		Procedure(ProcedureType const& _type, std::shared_ptr<Statement>&& _body) : type(_type), body(std::move(_body)) {}
		Procedure(ProcedureType const& _type, std::unique_ptr<Statement>&& _body) : type(_type), body(std::move(_body)) {}

		TypeRepresentation get_return_type() const noexcept override
		{
			return type.return_type;
		}
		bool has_parameter_types(std::span<TypeRepresentation const> _parameter_types) const noexcept
		{
			if (_parameter_types.size() != type.parameters.get_num_fields())
				return false;
			else
			{
				for (int i = 0; i < (int)type.parameters.get_num_fields(); ++i)
				{
					if (_parameter_types[i] != type.parameters.get_field_type(i))
					{
						return false;
					}
				}
				return true;
			}
		}
		std::span<TypeRepresentation const> get_parameter_types() const noexcept override
		{
			return type.parameters.get_types();
		}
		ProcedureType get_type() const noexcept override
		{
			return type;
		}

		void call(void* return_value, std::span<void*> _arguments) const noexcept override
		{
			assert(false);
		}

		operator Value() const
		{
			return (std::shared_ptr<ComplexValue>)std::make_shared<Procedure>(*this);
		}

		std::unique_ptr<FunctionRepresentation> deep_copy() const override
		{
			return std::make_unique<Procedure>(*this);
		}

	protected:
		virtual bool equals(ComplexValue const&) const
		{
			assert(false); // TODO
			return false;
		}
	};

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
			case Terminal::OP_EQ:
			{
				binary.function_to_call = function_map.get("operator==", argument_types);
				break;
			}
			case Terminal::OP_NEQ:
			{
				binary.function_to_call = function_map.get("operator!=", argument_types);
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

		void visit(Call& call) override
		{
			call.callee->accept(*this);
			call.arguments.accept(*this);

			TypeRepresentation callee_type = *call.callee->get_expression_type();
			std::shared_ptr<ProcedureType> as_procedure = get<ProcedureType>(callee_type);

			if(as_procedure == nullptr)
			{
				throw message_exception("Expected a procedure\n", *call.callee);
			}


			if (!implicit_cast(as_procedure->parameters, call.arguments, false))
			{
				throw message_exception("Initializer has not the right type\n", call.arguments);
			}
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
			if (auto tupleopt = get<TupleReferenceType>(left_type))
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
			if (auto tupleopt = get<TupleReferenceType>(left_type))
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
						throw message_exception("Assignment of different types", member_write);
					}
				}
			}
			else
			{
				throw message_exception("Expected a tuple before '.'", *member_write.left);
			}

			if (member_write.op.type != Terminal::OP_ASSIGN)
			{
				// TODO
				throw message_exception("Operator not supported", member_write.op);
			}
		}

		void visit(ProcedureDeclaration& procedure_declaration) override
		{
			procedure_declaration.type.is_function = (procedure_declaration.kind.type == Terminal::KW_FUNCTION);
			procedure_declaration.parameter_tuple->accept(*this);

			procedure_declaration.type.parameters = *get<TupleType>(*procedure_declaration.parameter_tuple->get_type_value());

			if (procedure_declaration.return_type)
			{
				procedure_declaration.return_type->accept(*this);
				if (procedure_declaration.return_type->get_expression_type())
					procedure_declaration.type.return_type = *procedure_declaration.return_type->get_type_value();
				else
					throw message_exception("Expected a type", *procedure_declaration.return_type);
			}
			else
			{
				procedure_declaration.type.return_type = BuildInType::Void;
			}


			std::vector<VariableBlock> old_locals = std::move(variable_blocks);
			variable_blocks.resize(0);

			VariableBlock parameter_block = {};
			parameter_block.stack_size_at_beginning = 0;
			TypeRepresentation last_type;
			for (int i = 0; i < (int)procedure_declaration.parameter_tuple->field_names.size(); ++i)
			{
				VariableInfo info;
				if (procedure_declaration.parameter_tuple->field_types[i] == nullptr)
				{
					info.type = last_type;
				}
				else
				{
					last_type = info.type = *procedure_declaration.parameter_tuple->field_types[i]->get_type_value();
				}
				info.index = parameter_block.stack_size_at_beginning + i;
				info.constant = true; // TODO(?)
				parameter_block.variables[(std::string)procedure_declaration.parameter_tuple->field_names[i].text] = info;
			}

			variable_blocks.push_back(std::move(parameter_block));
			bool was_in_function_context = in_function_context;
			bool did_allow_return = allow_return;
			std::optional<TypeRepresentation> outer_return_type = return_type;

			if (procedure_declaration.type.is_function)
				in_function_context = true;

			if (procedure_declaration.return_type)
			{
				return_type = procedure_declaration.type.return_type;
			}

			assert(!has_found_return);
			allow_return = true;

			procedure_declaration.body->accept(*this);

			allow_return = did_allow_return;

			if (procedure_declaration.return_type == nullptr)
			{
				if(return_type)
					procedure_declaration.type.return_type = *return_type;
				else if (procedure_declaration.type.is_function)
					throw message_exception("Can't deduce return type of a function", procedure_declaration);
			}
			else if (!has_found_return)
			{
				throw message_exception("All paths must end in a return statement", procedure_declaration);
			}
			has_found_return = false;

			return_type = outer_return_type;
			in_function_context = was_in_function_context;

			assert(variable_blocks.size() == 1);
			variable_blocks = std::move(old_locals);
		}

		void visit(TableDeclaration& table_declaration) override
		{
			if (table_declaration.inner_tuple == nullptr)
			{
				assert(table_declaration.tuple_name.type == Terminal::IDENTIFIER);

				if (auto type = find_typedef(table_declaration.tuple_name))
				{
					if (auto t = get<TupleType>(*type))
					{
						table_declaration.table.base_tuple = *t;
					}
					else
					{
						throw message_exception("Type is not a tuple", table_declaration.tuple_name);
					}
				}
				else
				{
					throw message_exception("Can't find type identifier", table_declaration.tuple_name);
				}
			}
			else
			{
				table_declaration.inner_tuple->accept(*this);

				table_declaration.table.base_tuple = table_declaration.inner_tuple->tuple;
			}
		}

		void visit(TupleDeclaration& tuple_declaration) override
		{
			assert(tuple_declaration.field_names.size() == tuple_declaration.field_types.size());

			TypeRepresentation last_type;
			std::optional<Value> last_initial_value;

			for (int i = 0; i < tuple_declaration.field_names.size(); ++i)
			{
				if (tuple_declaration.tuple.has_field(tuple_declaration.field_names[i].text))
				{
					throw message_exception("Repeated field in tuple declaration\n", tuple_declaration.field_names[i]);
				}

				TypeRepresentation field_type;
				std::optional<Value> initial_value;

				if (tuple_declaration.field_types[i])
				{
					tuple_declaration.field_types[i]->accept(*this);
					field_type = *tuple_declaration.field_types[i]->get_type_value();
					initial_value = std::nullopt;
				}

				if (tuple_declaration.field_initializers[i])
				{
					tuple_declaration.field_initializers[i]->accept(*this);

					if (!tuple_declaration.field_types[i])
					{
						field_type = *tuple_declaration.field_initializers[i]->get_expression_type();
					}

					if (auto init = tuple_declaration.field_initializers[i]->get_constant_value())
					{
						initial_value = cast(*get<BuildInType>(field_type), *init);
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
			else if (in_function_context && variable.index == -1)
			{
				throw message_exception("Can't write to a global inside a function!", variable_assign);
			}
			variable_assign.type = variable.type;
			variable_assign.index = variable.index;

			switch (variable_assign.op.type)
			{
			case Terminal::OP_ASSIGN:
				if (!implicit_cast(*variable_assign.type, variable_assign.exp))
				{
					throw message_exception("Assignment of different types", *variable_assign.exp);
				}
				break;
			case Terminal::OP_ASSIGN_ADD:
				if (auto t = get<TableType>(*variable_assign.type))
				{
					if (!implicit_cast(t->base_tuple, variable_assign.exp))
					{
						throw message_exception("table insertion needs a tuple of the right type", *variable_assign.exp);
					}
				}
				else
				{
					throw message_exception("Operator not supported", variable_assign.op);
				}
				break;
			case Terminal::OP_ASSIGN_SUB:
			case Terminal::OP_ASSIGN_MUL:
			case Terminal::OP_ASSIGN_DIV:
			case Terminal::OP_ASSIGN_MOD:
				throw message_exception("Operator not supported", variable_assign.op);
			default:
				assert(false);
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
				if (in_function_context && variable.index == -1 && !variable.constant)
				{
					throw message_exception("Can't read from non-constant global inside a function!", variable_read);
				}

				if (auto t = get<TupleType>(variable.type))
				{
					TupleReferenceType as_reference;
					as_reference.tuple = *t;
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

			if (block.is_global)
			{
				assert(variable_blocks.size() == 0);
			}
			else
			{
				push_variable_block();
			}

			for (auto& statement : block.statements)
			{
				if (has_found_return)
					throw message_exception("You can't have statements after a return statement.", *statement);

				statement->accept(*this);
			}
			// TODO throw(?)

			if (block.is_global)
			{
				assert(variable_blocks.size() == 0);
			}
			else
			{
				pop_variable_block();
			}
		}

		void visit(ExpressionStatement& expression_statement) override
		{
			expression_statement.exp->accept(*this);
		}

		void visit(IfStatement& if_statement) override
		{
			push_variable_block();

			if(if_statement.initialization != nullptr)
				if_statement.initialization->accept(*this);
			if(if_statement.condition != nullptr)
				if_statement.condition->accept(*this);

			if_statement.yes->accept(*this);
			if(if_statement.no != nullptr)
				if_statement.no->accept(*this);
			


			if (if_statement.initialization != nullptr && if_statement.condition == nullptr && *if_statement.initialization->type != BuildInType::Bool)
				throw message_exception("If statement condition must be of type boolean", *if_statement.initialization);

			if (if_statement.condition != nullptr && if_statement.condition->get_expression_type() != BuildInType::Bool)
				throw message_exception("If statement condition must be of type boolean", *if_statement.condition);

			pop_variable_block();
		}

		void visit(ReturnStatement& return_statement) override
		{
			if(!allow_return)
				throw message_exception("Can't use a return outside of a function", return_statement);

			if(return_statement.exp)
				return_statement.exp->accept(*this);

			if (!return_type)
			{
				if (!return_statement.exp)
					return_type = BuildInType::Void;
				else
					return_type = *return_statement.exp->get_expression_type();
			}
			else if (return_statement.exp == nullptr)
			{
				if(*return_type != BuildInType::Void)
					throw message_exception("Expected an expression", return_statement);
			}
			else if (!implicit_cast(*return_type, return_statement.exp))
			{
				throw message_exception("Wrong return type", *return_statement.exp);
			}

			has_found_return = true;
		}

		void visit(VariableDefinition& variable_definition) override
		{
			if (variable_blocks.empty())
			{
				if (globals.variables.contains((std::string)variable_definition.variable.text))
				{
					throw variable_redefinition_exception(variable_definition.variable);
				}
			}
			else
			{
				if (variable_blocks.back().variables.contains((std::string)variable_definition.variable.text))
				{
					throw variable_redefinition_exception(variable_definition.variable);
				}
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

				if (variable_blocks.empty())
				{
					globals.types[(std::string)variable_definition.variable.text] = *variable_definition.initialization->get_type_value();
					globals.types[(std::string)variable_definition.variable.text].set_name(variable_definition.variable.text);
				}
				else
				{
					variable_blocks.back().types[(std::string)variable_definition.variable.text] = *variable_definition.initialization->get_type_value();
					variable_blocks.back().types[(std::string)variable_definition.variable.text].set_name(variable_definition.variable.text);
				}
			}
			else
			{
				VariableInfo info;
				info.type = *variable_definition.type;
				info.constant = variable_definition.constant;
				if (variable_blocks.empty())
				{
					info.index = -1;
					globals.variables[(std::string)variable_definition.variable.text] = info;
				}
				else
				{
					variable_definition.index = info.index = variable_blocks.back().stack_size_at_beginning + (int)variable_blocks.back().variables.size();
					variable_blocks.back().variables[(std::string)variable_definition.variable.text] = info;
				}
			}
		}

		void visit(WhileStatement& while_statement) override
		{
			while_statement.condition->accept(*this);
			while_statement.code->accept(*this);

			if (while_statement.condition->get_expression_type() != BuildInType::Bool)
				throw message_exception("While statement condition must be of type boolean", *while_statement.condition);
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
		bool allow_return = false, in_function_context = false, has_found_return = false;
		std::optional<TypeRepresentation> return_type;

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

			auto info = globals.variables.find((std::string)identifier.text);
			if (info != globals.variables.end())
			{
				return info->second;
			}

			if (auto f = function_map.get(identifier.text))
			{
				assert(f->size() == 1);
				VariableInfo result;
				result.constant = true;
				result.index = -1;
				result.type = (*f)[0]->get_type();
				return result;
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

			auto info = globals.types.find((std::string)identifier.text);
			if (info != globals.types.end())
			{
				return info->second;
			}

			return std::nullopt;
		}

		bool implicit_cast(TupleType target, InitializerList &origin, bool let_undefined_fields)
		{
			origin.destination_type = target;

			int last_index = -1;
			for (int i = 0; i < (int)origin.expressions.size(); ++i)
			{
				int index;
				if (origin.names[i])
				{
					if (!origin.destination_type.has_field(origin.names[i]->text))
					{
						throw message_exception("tuple doesn't have this field\n", *origin.names[i]);
					}
					index = origin.destination_type.get_field_index(origin.names[i]->text);
					if (std::find(origin.indexes.begin(), origin.indexes.end(), index) != origin.indexes.end())
					{
						throw message_exception("this field has already been initialized", *origin.names[i]);
					}
				}
				else
				{
					++last_index;
					while (std::find(origin.indexes.begin(), origin.indexes.end(), last_index) != origin.indexes.end())
					{
						++last_index;
					}
					index = last_index;

					if (index >= origin.destination_type.get_num_fields())
					{
						throw message_exception("too many initializer values for this tuple", *origin.expressions[i]);
					}
				}

				if (!implicit_cast(origin.destination_type.get_field_type(index), origin.expressions[i]))
				{
					throw message_exception("initializer has the wrong type", *origin.expressions[i]);
				}

				origin.indexes.push_back(index);
				last_index = index;
			}

			for (int i = 0; i < origin.destination_type.get_num_fields(); ++i)
			{
				if (std::find(origin.indexes.begin(), origin.indexes.end(), i) == origin.indexes.end())
				{
					origin.default_initializers.push_back(i);
					if (!let_undefined_fields && !target.get_field_init_value(i).has_value())
					{
						throw message_exception("missing arguments!", origin);
					}
				}
			}

			return true;
		}

		bool implicit_cast(TypeRepresentation target, std::unique_ptr<Expression> &origin)
		{
			if (target == origin->get_expression_type())
				return true;
			else if (get<TupleType>(target) && origin->get_expression_type() == BuildInType::InitializerList)
			{
				assert(dynamic_cast<InitializerList*>(origin.get()));
				return implicit_cast(*get<TupleType>(target), *static_cast<InitializerList*>(origin.get()), true);
			}
			else
				return false;
		}

	};
}
