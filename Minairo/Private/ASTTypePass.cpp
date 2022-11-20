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

module Minairo.AST.TypePass;


import Minairo.AST;
import Minairo.Exception;
import Minairo.TypesAndValues;


using namespace minairo;

std::string TypeException::print_error() const
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


void TypePass::visit(Binary& binary)
{
	binary.left->accept(*this);
	binary.right->accept(*this);

	TypeRepresentation argument_types[2] = { deduce_type(*binary.left).type, deduce_type(*binary.right).type };


	switch (binary.op)
	{
	case Terminal::OP_OR:
	case Terminal::OP_AND:

	case Terminal::OP_ADD:
	case Terminal::OP_SUB:
	case Terminal::OP_MUL:
	case Terminal::OP_DIV:
	case Terminal::OP_MOD:
	case Terminal::OP_BIT_AND:
	case Terminal::OP_BIT_OR:
	case Terminal::OP_BIT_XOR:

	case Terminal::OP_EQ:
	case Terminal::OP_NEQ:
	case Terminal::OP_LT:
	case Terminal::OP_GT:
	case Terminal::OP_LTE:
	case Terminal::OP_GTE:
	{
		if ((argument_types[0].is_integral() || argument_types[0].is_float() || argument_types[0] == BuildInType::Bool)
			&& (argument_types[1].is_integral() || argument_types[1].is_float() || argument_types[1] == BuildInType::Bool))
		{
			if (!(implicit_cast(argument_types[0], binary.right) || implicit_cast(argument_types[1], binary.left)))
			{
				throw message_exception("can't implicitly cast operators!", binary);
			}


			// TODO more checks?
		}
		else
		{
			throw message_exception("binary operator only defined between numbers", binary);
		}

		break;
	}
	default:
		assert(false); // TODO
	}
}

void TypePass::visit(BuildInTypeDeclaration&)
{
	// -------
}

void TypePass::visit(Call& call)
{
	call.callee->accept(*this);
	call.arguments.accept(*this);

	TypeRepresentation callee_type = deduce_type(*call.callee).type;
	std::shared_ptr<FunctionType> as_function = get<FunctionType>(callee_type);

	if (as_function == nullptr)
	{
		std::shared_ptr<MultifunctionType> as_multifunction = get<MultifunctionType>(callee_type);

		if (as_multifunction == nullptr)
		{
			throw message_exception("Expected a function\n", *call.callee);
		}
		else
		{
			// TODO move to a function?
			std::vector<FunctionType> candidates;

			int best_needed_casts = 0x7fffffff;

			for (auto& candidate : as_multifunction->functions)
			{
				int needed_casts = 0;
				if (implicit_cast(candidate.parameters, call.arguments, false, &needed_casts))
				{
					if (needed_casts < best_needed_casts)
					{
						candidates.clear();
						best_needed_casts = needed_casts;
					}

					if (needed_casts == best_needed_casts)
					{
						candidates.push_back(candidate);
					}
				}
			}

			if (candidates.size() == 1)
			{
				Cast cast;
				cast.target_type = candidates[0];
				cast.expr = std::move(call.callee);
				call.callee = cast.deep_copy();

				as_function = std::make_shared<FunctionType>(candidates[0]);
			}
			else if (candidates.size() == 0)
			{
				throw message_exception("No overload found for this arguments", call.arguments);
			}
			else
			{
				throw message_exception("Too many overloads found", call.arguments);
			}
		}
	}

	if (!implicit_cast(as_function->parameters, call.arguments, false))
	{
		throw message_exception("Initializer has not the right type", call.arguments);
	}
}

void TypePass::visit(Cast& cast)
{
	cast.expr->accept(*this);
}

void TypePass::visit(ConceptDeclaration& concept_declaration)
{
	assert(concept_declaration.tuple_names.size() == concept_declaration.tuple_declarations.size());
	assert(concept_declaration.function_names.size() == concept_declaration.function_declarations.size());

	for (int i = 0; i < concept_declaration.tuple_names.size(); ++i)
	{
		concept_declaration.tuple_declarations[i].accept(*this);
	}

	for (int i = 0; i < concept_declaration.function_names.size(); ++i)
	{
		concept_declaration.function_declarations[i].accept(*this);
	}

	assert(false); // TODO
}

void TypePass::visit(Grouping& grouping)
{
	grouping.expr->accept(*this);
}

void TypePass::visit(InitializerList& initializer_list)
{
	for (auto& expr : initializer_list.expressions)
	{
		expr->accept(*this);
	}
}

void TypePass::visit(Literal& literal)
{
	// ------
}

void TypePass::visit(MemberRead& member_read)
{
	member_read.left->accept(*this);
	auto left_type = deduce_type(*member_read.left);
	if (auto tuple = get<TupleType>(left_type.type))
	{
		if (tuple->has_field(member_read.member.text))
		{
			member_read.index = tuple->get_field_index(member_read.member.text);
			member_read.type = tuple->get_field_type(member_read.member.text);
			member_read.constant = left_type.constant;
		}
		else
		{
			throw message_exception("tuple doesn't have a member of this name", member_read);
		}
	}
	else if (auto tuple_ref = get<TupleReferenceType>(left_type.type))
	{
		if (tuple_ref->tuple.has_field(member_read.member.text))
		{
			member_read.index = tuple_ref->tuple.get_field_index(member_read.member.text);
			member_read.type = tuple_ref->tuple.get_field_type(member_read.member.text);
			member_read.constant = left_type.constant || tuple_ref->constant;
		}
		else
		{
			throw message_exception("tuple doesn't have a member of this name", member_read);
		}
	}
	else
	{
		throw message_exception("Expected a tuple before '.'", *member_read.left);
	}
}

void TypePass::visit(MemberWrite& member_write)
{
	member_write.left->accept(*this);
	auto left_type = deduce_type(*member_write.left);
	if (auto tuple = get<TupleType>(left_type.type))
	{
		if (!tuple->has_field(member_write.member.text))
		{
			throw message_exception("tuple doesn't have a member of this name\n", member_write);
		}
		else if (left_type.constant)
		{
			throw message_exception("can't assign to a member of a constant tuple\n", member_write);
		}
		else
		{
			member_write.right->accept(*this);

			member_write.index = tuple->get_field_index(member_write.member.text);
			member_write.type = tuple->get_field_type(member_write.member.text);

			if (!implicit_cast(*member_write.type, member_write.right))
			{
				throw message_exception("Assignment of different types", member_write);
			}
		}
	}
	else if (auto tuple_ref = get<TupleReferenceType>(left_type.type))
	{
		if (!tuple_ref->tuple.has_field(member_write.member.text))
		{
			throw message_exception("tuple doesn't have a member of this name\n", member_write);
		}
		else if (left_type.constant || tuple_ref->constant)
		{
			throw message_exception("can't assign to a member of a constant tuple\n", member_write);
		}
		else
		{
			member_write.right->accept(*this);

			member_write.index = tuple_ref->tuple.get_field_index(member_write.member.text);
			member_write.type = tuple_ref->tuple.get_field_type(member_write.member.text);


			if (*member_write.type != deduce_type(*member_write.right).type)
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

void TypePass::visit(FunctionDeclaration& function_declaration)
{
	visit(*function_declaration.header);

	std::vector<VariableBlock> old_locals = std::move(variable_blocks);
	variable_blocks.resize(0);

	VariableBlock parameter_block = {};
	parameter_block.stack_size_at_beginning = 0;
	for (int i = 0; i < function_declaration.header->parameter_tuple->tuple.get_num_fields(); ++i)
	{
		VariableInfo info;
		info.type = function_declaration.header->parameter_tuple->tuple.get_field_type(i);
		info.index = parameter_block.stack_size_at_beginning + i;
		info.constant = true; // TODO(?)
		parameter_block.variables[(std::string)function_declaration.header->parameter_tuple->field_names[i].text] = info;

	}

	variable_blocks.push_back(std::move(parameter_block));
	bool was_in_pure_function_context = in_pure_function_context;
	bool did_allow_return = allow_return;
	std::optional<TypeRepresentation> outer_return_type = return_type;

	if (function_declaration.header->type.is_pure)
		in_pure_function_context = true;

	if (function_declaration.header->return_type)
	{
		return_type = function_declaration.header->type.return_type;
	}

	allow_return = true;

	function_declaration.body->accept(*this);

	allow_return = did_allow_return;

	if (function_declaration.header->return_type == nullptr)
	{
		if (return_type)
			function_declaration.header->type.return_type = *return_type;
		else if (function_declaration.header->type.is_pure)
			throw message_exception("Can't deduce return type of a function", function_declaration);
	}

	if (function_declaration.header->type.return_type != BuildInType::Void && !all_paths_lead_to_a_return(*function_declaration.body))
	{
		throw message_exception("All paths must end in a return statement", *function_declaration.body);
	}

	return_type = outer_return_type;
	in_pure_function_context = was_in_pure_function_context;

	assert(variable_blocks.size() == 1);
	variable_blocks = std::move(old_locals);
}

void TypePass::visit(FunctionTypeDeclaration& function_type_declaration)
{
	function_type_declaration.type.is_pure = function_type_declaration.is_pure;
	function_type_declaration.parameter_tuple->accept(*this);


	if (function_type_declaration.type.is_pure)
	{
		for (int i = 0; i < function_type_declaration.parameter_tuple->tuple.get_num_fields(); ++i)
		{
			if (auto function = get<FunctionType>(function_type_declaration.parameter_tuple->tuple.get_field_type(i)))
			{
				if (!function->is_pure)
				{
					throw message_exception("Pure functions can only take other pure functions as parameters", function_type_declaration.parameter_tuple->field_names[i]);
				}
			}
		}
	}

	function_type_declaration.type.parameters = *get_compile_time_type_value<TupleType>(*function_type_declaration.parameter_tuple);

	if (function_type_declaration.return_type)
	{
		function_type_declaration.return_type->accept(*this);
		if (deduce_type(*function_type_declaration.return_type).type == BuildInType::Typedef)
			function_type_declaration.type.return_type = get_compile_time_type_value(*function_type_declaration.return_type);
		else
			throw message_exception("Expected a type", *function_type_declaration.return_type);
	}
	else
	{
		function_type_declaration.type.return_type = BuildInType::Void;
	}
}

void TypePass::visit(TableDeclaration& table_declaration)
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

void TypePass::visit(TupleDeclaration& tuple_declaration)
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
			field_type = get_compile_time_type_value(*tuple_declaration.field_types[i]);
			initial_value = std::nullopt;
		}

		if (tuple_declaration.field_initializers[i])
		{
			tuple_declaration.field_initializers[i]->accept(*this);

			if (!tuple_declaration.field_types[i])
			{
				field_type = deduce_type(*tuple_declaration.field_initializers[i]).type;
			}

			if (auto init = get_compile_time_value(*tuple_declaration.field_initializers[i]))
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
			if (!implicit_cast(get_compile_time_type_value(*tuple_declaration.field_types[i]), tuple_declaration.field_initializers[i]))
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

void TypePass::visit(UnaryPre& unary_pre)
{
	assert(false); // TODO
}

void TypePass::visit(UnaryPost& unary_post)
{
	assert(false); // TODO
}

void TypePass::visit(VariableAssign& variable_assign)
{
	variable_assign.exp->accept(*this);

	auto variable = find_variable(variable_assign.identifier);
	if (variable.constant)
	{
		throw const_write_exception(variable_assign.identifier);
	}
	else if (in_pure_function_context && variable.index == -1)
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

void TypePass::visit(VariableRead& variable_read)
{
	if (auto type = find_typedef(variable_read.identifier))
	{
		variable_read.static_type = type;
		variable_read.type = BuildInType::Typedef;
	}
	else
	{
		auto variable = find_variable(variable_read.identifier);
		if (in_pure_function_context && variable.index == -1)
		{
			if (!variable.constant)
			{
				throw message_exception("Can't read from non-constant global inside a pure function!", variable_read);
			}
			else if (auto fun = get<FunctionType>(variable.type))
			{
				if (!fun->is_pure)
				{
					throw message_exception("Can't call a non-pure function inside a pure function!", variable_read);
				}
			}
		}

		variable_read.type = variable.type;
		variable_read.index = variable.index;
		variable_read.constant = variable.constant;
	}
}

// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------

void TypePass::visit(Block& block)
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

void TypePass::visit(ExpressionStatement& expression_statement)
{
	expression_statement.exp->accept(*this);
}

void TypePass::visit(ForeachStatement& foreach_statement)
{
	foreach_statement.table->accept(*this);

	std::shared_ptr<TableType> type = get<TableType>(deduce_type(*foreach_statement.table).type);

	if (type == nullptr)
		throw message_exception("foreach iterable must be a table", *foreach_statement.table);

	VariableInfo info;
	info.index = 0;
	TupleReferenceType iteratedType;
	iteratedType.tuple = type->base_tuple;
	info.constant = iteratedType.constant = foreach_statement.constant;
	info.type = iteratedType;

	push_variable_block();
	variable_blocks.back().variables[(std::string)foreach_statement.tuple.text] = info;

	foreach_statement.body->accept(*this);

	pop_variable_block();
}

void TypePass::visit(IfStatement& if_statement)
{
	push_variable_block();

	if (if_statement.initialization != nullptr)
		if_statement.initialization->accept(*this);
	if (if_statement.condition != nullptr)
		if_statement.condition->accept(*this);

	if_statement.yes->accept(*this);
	if (if_statement.no != nullptr)
		if_statement.no->accept(*this);



	if (if_statement.initialization != nullptr && if_statement.condition == nullptr && *if_statement.initialization->type != BuildInType::Bool)
		throw message_exception("If statement condition must be of type boolean", *if_statement.initialization);

	if (if_statement.condition != nullptr && deduce_type(*if_statement.condition).type != BuildInType::Bool)
		throw message_exception("If statement condition must be of type boolean", *if_statement.condition);

	pop_variable_block();
}

void TypePass::visit(ReturnStatement& return_statement)
{
	if (!allow_return)
		throw message_exception("Can't use a return outside of a function", return_statement);

	if (return_statement.exp)
		return_statement.exp->accept(*this);

	if (!return_type)
	{
		if (!return_statement.exp)
			return_type = BuildInType::Void;
		else
			return_type = deduce_type(*return_statement.exp).type;
	}
	else if (return_statement.exp == nullptr)
	{
		if (*return_type != BuildInType::Void)
			throw message_exception("Expected an expression", return_statement);
	}
	else if (!implicit_cast(*return_type, return_statement.exp))
	{
		throw message_exception("Wrong return type", *return_statement.exp);
	}
}

void TypePass::visit(VariableDefinition& variable_definition)
{
	assert(variable_definition.type_definition != nullptr || variable_definition.initialization != nullptr);


	if (variable_definition.type_definition != nullptr)
	{
		variable_definition.type_definition->accept(*this);

		if (deduce_type(*variable_definition.type_definition).type != BuildInType::Typedef)
		{
			throw message_exception("Expected a type definition\n", *variable_definition.type_definition);
		}
		variable_definition.type = get_compile_time_type_value(*variable_definition.type_definition);
	}

	if (variable_definition.initialization != nullptr)
	{
		variable_definition.initialization->accept(*this);
		if (variable_definition.type_definition == nullptr)
		{
			variable_definition.type = deduce_type(*variable_definition.initialization).type;
			if (variable_definition.type->is_integral())
			{
				switch (std::get<BuildInType>(*variable_definition.type))
				{
				case BuildInType::I8:
				case BuildInType::I16:
					variable_definition.type = BuildInType::I32;
					implicit_cast(BuildInType::I32, variable_definition.initialization);
					break;
				case BuildInType::U8:
				case BuildInType::U16:
					variable_definition.type = BuildInType::U32;
					implicit_cast(BuildInType::U32, variable_definition.initialization);
					break;
				}
			}
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
			throw message_exception("typedefs must be constant", variable_definition);
		}

		if (variable_blocks.empty())
		{
			if (globals.variables.contains((std::string)variable_definition.variable.text) || globals.types.contains((std::string)variable_definition.variable.text))
			{
				throw variable_redefinition_exception(variable_definition.variable);
			}

			globals.types[(std::string)variable_definition.variable.text] = get_compile_time_type_value(*variable_definition.initialization);
			globals.types[(std::string)variable_definition.variable.text].set_name(variable_definition.variable.text);
		}
		else
		{
			if (variable_blocks.back().variables.contains((std::string)variable_definition.variable.text) || variable_blocks.back().types.contains((std::string)variable_definition.variable.text))
			{
				throw variable_redefinition_exception(variable_definition.variable);
			}

			variable_blocks.back().types[(std::string)variable_definition.variable.text] = get_compile_time_type_value(*variable_definition.initialization);
			variable_blocks.back().types[(std::string)variable_definition.variable.text].set_name(variable_definition.variable.text);
		}
	}
	else
	{
		VariableInfo info;
		info.type = *variable_definition.type;
		info.constant = variable_definition.constant;

		auto as_function = get<FunctionType>(info.type);

		if (as_function && info.constant)
		{
			MultifunctionType multi;

			if (variable_blocks.empty())
			{
				info.index = -1;
				if (globals.variables.contains((std::string)variable_definition.variable.text))
				{
					VariableInfo stored_info = globals.variables[(std::string)variable_definition.variable.text];
					assert(stored_info.index = -1);
					assert(stored_info.constant = true);

					auto as_multi = get<MultifunctionType>(stored_info.type);

					if (as_multi == nullptr)
					{
						throw variable_redefinition_exception(variable_definition.variable);
					}
					else if (as_multi->is_pure != as_function->is_pure)
					{
						throw message_exception("All function overloads must be all pure or impure", variable_definition);
					}
					else
					{
						multi = *as_multi;
					}
				}
				else if (globals.types.contains((std::string)variable_definition.variable.text))
				{
					throw variable_redefinition_exception(variable_definition.variable);
				}
				else
				{
					variable_definition.multifunction_first = true;
					multi.is_pure = as_function->is_pure;
				}
			}
			else
			{
				if (variable_blocks.back().variables.contains((std::string)variable_definition.variable.text))
				{
					VariableInfo stored_info = variable_blocks.back().variables[(std::string)variable_definition.variable.text];
					assert(stored_info.constant = true);
					variable_definition.index = info.index = stored_info.index;

					auto as_multi = get<MultifunctionType>(stored_info.type);

					if (as_multi == nullptr)
					{
						throw variable_redefinition_exception(variable_definition.variable);
					}
					else if (as_multi->is_pure != as_function->is_pure)
					{
						throw message_exception("All function overloads must be all pure or impure", variable_definition);
					}
					else
					{
						multi = *as_multi;
					}
				}
				else if (variable_blocks.back().types.contains((std::string)variable_definition.variable.text))
				{
					throw variable_redefinition_exception(variable_definition.variable);
				}
				else
				{
					variable_definition.index = info.index = variable_blocks.back().stack_size_at_beginning + (int)variable_blocks.back().variables.size();
					variable_definition.multifunction_first = true;
					multi.is_pure = as_function->is_pure;
				}
			}

			for (FunctionType const& old_overload : multi.functions)
			{
				if (old_overload == *as_function)
				{
					throw message_exception("overload already exists", variable_definition);
				}
			}
			multi.functions.push_back(std::move(*as_function));
			info.type = multi;

			if (variable_blocks.empty())
			{
				globals.variables[(std::string)variable_definition.variable.text] = info;
			}
			else
			{
				variable_blocks.back().variables[(std::string)variable_definition.variable.text] = info;
			}
		}
		else
		{
			if (variable_blocks.empty())
			{
				if (globals.variables.contains((std::string)variable_definition.variable.text) || globals.types.contains((std::string)variable_definition.variable.text))
				{
					throw variable_redefinition_exception(variable_definition.variable);
				}

				info.index = -1;
				globals.variables[(std::string)variable_definition.variable.text] = info;
			}
			else
			{
				if (variable_blocks.back().variables.contains((std::string)variable_definition.variable.text) || variable_blocks.back().types.contains((std::string)variable_definition.variable.text))
				{
					throw variable_redefinition_exception(variable_definition.variable);
				}

				variable_definition.index = info.index = variable_blocks.back().stack_size_at_beginning + (int)variable_blocks.back().variables.size();
				variable_blocks.back().variables[(std::string)variable_definition.variable.text] = info;
			}
		}
	}

}

void TypePass::visit(WhileStatement& while_statement)
{
	while_statement.condition->accept(*this);
	while_statement.body->accept(*this);

	if (deduce_type(*while_statement.condition).type != BuildInType::Bool)
		throw message_exception("While statement condition must be of type boolean", *while_statement.condition);
}

// ----------------------------------------------------------------------------------------------

void TypePass::push_variable_block()
{
	int stack_size_at_beginning = 0;
	if (!variable_blocks.empty())
		stack_size_at_beginning = variable_blocks.back().stack_size_at_beginning + (int)variable_blocks.back().variables.size();

	variable_blocks.push_back({ stack_size_at_beginning });
}

void TypePass::pop_variable_block()
{
	variable_blocks.pop_back();
}

TypePass::VariableInfo TypePass::find_variable(TerminalData identifier) const
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

std::optional<TypeRepresentation> TypePass::find_typedef(TerminalData identifier) const
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

bool TypePass::implicit_cast(TupleType target, InitializerList& origin, bool let_undefined_fields, int* needed_casts) const
{
	if (needed_casts == nullptr)
	{
		origin.destination_type = target;
	}

	std::vector<int> indexes, default_initializers;

	int last_index = -1;
	for (int i = 0; i < (int)origin.expressions.size(); ++i)
	{
		int index;
		if (origin.names[i])
		{
			if (!target.has_field(origin.names[i]->text))
			{
				throw message_exception("tuple doesn't have this field\n", *origin.names[i]);
			}
			index = target.get_field_index(origin.names[i]->text);
			if (std::find(indexes.begin(), indexes.end(), index) != indexes.end())
			{
				throw message_exception("this field has already been initialized", *origin.names[i]);
			}
		}
		else
		{
			++last_index;
			while (std::find(indexes.begin(), indexes.end(), last_index) != indexes.end())
			{
				++last_index;
			}
			index = last_index;

			if (index >= target.get_num_fields())
			{
				throw message_exception("too many initializer values for this tuple", *origin.expressions[i]);
			}
		}

		if (!implicit_cast(target.get_field_type(index), origin.expressions[i], needed_casts))
		{
			throw message_exception("initializer has the wrong type", *origin.expressions[i]);
		}

		indexes.push_back(index);
		last_index = index;
	}

	for (int i = 0; i < target.get_num_fields(); ++i)
	{
		if (std::find(indexes.begin(), indexes.end(), i) == indexes.end())
		{
			default_initializers.push_back(i);

			if (!let_undefined_fields && !target.get_field_init_value(i).has_value())
			{
				throw message_exception("missing arguments!", origin);
			}
		}
	}

	if (needed_casts == nullptr)
	{
		origin.indexes = indexes;
		origin.default_initializers = default_initializers;
	}
	else
	{
		*needed_casts += (int)default_initializers.size();
	}

	return true;
}

bool TypePass::implicit_cast(TypeRepresentation target, std::unique_ptr<Expression>& origin, int* needed_casts) const
{
	TypeRepresentation original_type = deduce_type(*origin).type;
	if (target == original_type)
	{
		if (auto target_function = get<FunctionType>(target))
		{
			auto origin_function = get<FunctionType>(original_type);
			assert(origin_function);
			for (int i = 0; i < origin_function->parameters.get_num_fields(); ++i)
			{
				if (auto init = origin_function->parameters.get_field_init_value(i))
				{
					auto target_init = target_function->parameters.get_field_init_value(i);
					if (!target_init || *target_init != init)
						return false;
				}
			}
		}
		return true;
	}
	else if (get<TupleType>(target) && original_type == BuildInType::InitializerList)
	{
		assert(dynamic_cast<InitializerList*>(origin.get()));
		return implicit_cast(*get<TupleType>(target), *static_cast<InitializerList*>(origin.get()), true, needed_casts);
	}
	else if ((target.is_integral() || target.is_float()) && (original_type.is_integral() || original_type.is_float()))
	{
		bool o_sign, t_sign;
		int o_bits, t_bits;
		switch (std::get<BuildInType>(target))
		{
		case BuildInType::I8:
			t_sign = true;
			t_bits = 8;
			break;
		case BuildInType::I16:
			t_sign = true;
			t_bits = 16;
			break;
		case BuildInType::I32:
			t_sign = true;
			t_bits = 32;
			break;
		case BuildInType::I64:
			t_sign = true;
			t_bits = 64;
			break;
		case BuildInType::U8:
			t_sign = false;
			t_bits = 8;
			break;
		case BuildInType::U16:
			t_sign = false;
			t_bits = 16;
			break;
		case BuildInType::U32:
			t_sign = false;
			t_bits = 32;
			break;
		case BuildInType::U64:
			t_sign = false;
			t_bits = 64;
			break;
		case BuildInType::F32:
			t_sign = true;
			t_bits = 32;
			break;
		case BuildInType::F64:
			t_sign = true;
			t_bits = 64;
			break;
		}

		switch (std::get<BuildInType>(original_type))
		{
		case BuildInType::I8:
			o_sign = true;
			o_bits = 8;
			break;
		case BuildInType::I16:
			o_sign = true;
			o_bits = 16;
			break;
		case BuildInType::I32:
			o_sign = true;
			o_bits = 32;
			break;
		case BuildInType::I64:
			o_sign = true;
			o_bits = 64;
			break;
		case BuildInType::U8:
			o_sign = false;
			o_bits = 8;
			break;
		case BuildInType::U16:
			o_sign = false;
			o_bits = 16;
			break;
		case BuildInType::U32:
			o_sign = false;
			o_bits = 32;
			break;
		case BuildInType::U64:
			o_sign = false;
			o_bits = 64;
			break;
		case BuildInType::F32:
			o_sign = true;
			o_bits = 32;
			break;
		case BuildInType::F64:
			o_sign = true;
			o_bits = 64;
			break;
		}

		bool can_cast = false;
		if (target.is_integral() && original_type.is_integral())
		{
			if (o_bits < t_bits)
			{
				if (!o_sign || t_sign)
					can_cast = true;
			}
		}
		else if (target.is_float())
		{
			if (t_bits == 32 && o_bits <= 16)
				can_cast = true;
			else if (o_bits <= 32)
				can_cast = true;
		}

		if (can_cast)
		{
			if (needed_casts == nullptr)
			{
				auto cast = std::make_unique<Cast>();
				cast->expr = std::move(origin);
				cast->target_type = target;

				origin = std::move(cast);
			}
			else
			{
				++* needed_casts;
			}

			return true;
		}
		else
		{
			return false;
		}
	}
	else
		return false;
}
