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

TypeException unknown_identifier_exception(TerminalData identifier)
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
	assert(current_concept_interfaces.size() == 0);

	assert(concept_declaration.tuple_names.size() == concept_declaration.tuple_declarations.size());
	assert(concept_declaration.function_names.size() == concept_declaration.function_declarations.size());

	TypeFullName concept_name(current_scope);
	concept_declaration.type.set_name(concept_name);

	for (int i = 0; i < concept_declaration.tuple_names.size(); ++i)
	{
		concept_declaration.tuple_declarations[i].accept(*this);

		if (current_concept_interfaces.find((std::string)concept_declaration.tuple_names[i].text) != current_concept_interfaces.end())
		{
			throw message_exception("interface name appears more than once!", concept_declaration.tuple_names[i]);
		}

		InterfaceType interface_type;
		interface_type.set_name(TypeFullName{ current_scope, TypeShortName{ concept_declaration.tuple_names[i].text } });
		interface_type.base_tuple = *get_compile_time_type_value<TupleType>(concept_declaration.tuple_declarations[i]);

		current_concept_interfaces[(std::string)concept_declaration.tuple_names[i].text] = interface_type;
		concept_declaration.type.add_interface(interface_type);
	}

	for (int i = 0; i < concept_declaration.function_names.size(); ++i)
	{
		concept_declaration.function_declarations[i].accept(*this);

		std::vector<int> interface_paramenters;

		for (int f = 0; f < concept_declaration.function_declarations[i].type.parameters.get_num_fields(); ++f)
		{
			TypeRepresentation const& parameter_type = concept_declaration.function_declarations[i].type.parameters.get_field_type(f);
			if (auto as_interface = get<InterfaceType>(parameter_type))
			{
				if (as_interface->get_concept_name() == concept_name)
				{
					interface_paramenters.push_back(f);
				}
			}
		}

		if (interface_paramenters.size() == 0)
		{
			throw message_exception("functions in a concept must have at least one paramenter with a concept's interface", concept_declaration.function_declarations[i]);
		}
		else
		{
			// TODO add function be found by other functions?
			std::shared_ptr<FunctionType> virtual_function_signature = get_compile_time_type_value<FunctionType>(concept_declaration.function_declarations[i]);
			virtual_function_signature->set_name(TypeFullName{ current_scope, TypeShortName{ concept_declaration.function_names[i].text } });
			concept_declaration.type.add_function(*virtual_function_signature, std::move(interface_paramenters));
		}
	}

	current_concept_interfaces.clear();
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

	if (initializer_list.explicit_type)
	{
		initializer_list.explicit_type->accept(*this);
		
		if (auto tuple_type = get_compile_time_type_value<TupleType>(*initializer_list.explicit_type))
		{
			initializer_list.destination_type = *tuple_type;

		}
		else
		{
			throw message_exception("expecting a tuple name before initialization list", *initializer_list.explicit_type);
		}

		if (!implicit_cast(initializer_list.destination_type, initializer_list, true))
		{
			assert(false); // the implicit cast should itself throw
		}
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
	else if (auto interface_type = get<InterfaceType>(left_type.type))
	{
		if (interface_type->base_tuple.has_field(member_read.member.text))
		{
			member_read.index = interface_type->base_tuple.get_field_index(member_read.member.text);
			member_read.type = interface_type->base_tuple.get_field_type(member_read.member.text);
			member_read.constant = left_type.constant;
		}
		else
		{
			throw message_exception("interface doesn't have a member of this name", member_read);
		}
	}
	else if (auto concept_type = get<ConceptType>(left_type.type))
	{
		switch (concept_type->get_member_kind((TypeShortName)member_read.member.text))
		{
		case ConceptType::Kind::Interface:
		{
			member_read.compile_time_value = concept_type->get_interface((TypeShortName)member_read.member.text);
			member_read.index = -1;
			member_read.type = BuildInType::Typedef;
			member_read.constant = true;
			break;
		}
		case ConceptType::Kind::Function:
		{
			auto virtual_function = concept_type->get_function((TypeShortName)member_read.member.text);
			member_read.type = virtual_function;
			member_read.index = virtual_function.index;
			member_read.constant = true;
			break;
		}
		default:
			throw message_exception("unrecognized member of concept", member_read.member);
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
			throw message_exception("tuple doesn't have a member of this name", member_write);
		}
		else if (left_type.constant || tuple_ref->constant)
		{
			throw message_exception("can't assign to a member of a constant tuple", member_write);
		}
		else
		{
			member_write.right->accept(*this);

			member_write.index = tuple_ref->tuple.get_field_index(member_write.member.text);
			member_write.type = tuple_ref->tuple.get_field_type(member_write.member.text);


			if (!implicit_cast(*member_write.type, member_write.right))
			{
				throw message_exception("Assignment of different types", member_write);
			}
		}
	}
	else if (auto interface_ref = get<InterfaceType>(left_type.type))
	{
		if (!interface_ref->base_tuple.has_field(member_write.member.text))
		{
			throw message_exception("interface doesn't have a member of this name", member_write);
		}
		else if (left_type.constant)
		{
			throw message_exception("can't assign to a member of a constant interface", member_write);
		}
		else
		{
			member_write.right->accept(*this);

			member_write.index = interface_ref->base_tuple.get_field_index(member_write.member.text);
			member_write.type = interface_ref->base_tuple.get_field_type(member_write.member.text);


			if (!implicit_cast(*member_write.type, member_write.right))
			{
				throw message_exception("Assignment of different types", member_write);
			}
		}
	}
	else if (auto concept_type = get<ConceptType>(left_type.type))
	{
		if (member_write.op.type != Terminal::OP_ASSIGN_ADD)
		{
			throw message_exception("Only '+=' allowed to modify concept members", member_write.op);
		}

		assert(concepts.find(concept_type->name) != concepts.end());
		Concept& concep = concepts[concept_type->name];

		member_write.right->accept(*this);
		auto right_type = deduce_type(*member_write.right).type;

		switch (concept_type->get_member_kind((TypeShortName)member_write.member.text))
		{
		case ConceptType::Kind::Interface:
		{
			InterfaceType interface_type = concept_type->get_interface((TypeShortName)member_write.member.text);

			if (right_type != BuildInType::Typedef)
			{
				throw message_exception("Expected a named tuple type to add to an interface", *member_write.right);
			}
			else if (std::shared_ptr<TupleType> tuple_to_add = get_compile_time_type_value<TupleType>(*member_write.right))
			{
				if (tuple_to_add->get_name().is_empty())
				{
					throw message_exception("Expected a named tuple type to add to an interface", *member_write.right);
				}
				else
				{
					for (int i = 0; i < interface_type.base_tuple.get_num_fields(); ++i)
					{
						auto field_name = interface_type.base_tuple.get_field_name(i);
						if (!tuple_to_add->has_field(field_name))
						{
							// TODO better error messages
							throw message_exception("Tuple to be added to the interface is missing a field", *member_write.right);
						}
						else if (tuple_to_add->get_field_type(field_name) != interface_type.base_tuple.get_field_type(i))
						{
							// TODO better error messages
							throw message_exception("Tuple to be added to the interface has a field of an incorrect type", *member_write.right);
						}
					}

					concep.add_interface_implementation(*tuple_to_add, (TypeShortName)member_write.member.text);
				}
			}
			else
			{
				throw message_exception("Expected a named tuple type to add to an interface", *member_write.right);
			}
			break;
		}
		case ConceptType::Kind::Function:
		{
			if (std::optional<Value> compile_time_value = get_compile_time_value(*member_write.right))
			{
				if (auto function = get<Function>(*compile_time_value))
				{
					ConceptType::VirtualFunctionType const& function_type = concept_type->get_function((TypeShortName)member_write.member.text);

					if (function_type.is_pure && !function->type.is_pure)
					{
						throw message_exception("Expecting a pure function", *member_write.right);
					}

					if (function_type.return_type != function->type.return_type)
					{
						throw message_exception("virtual function must have the same return value as the overriden function", *member_write.right);
					}

					if (function_type.parameters.get_num_fields() != function->type.parameters.get_num_fields())
					{
						throw message_exception("virtual function must have the number of parameters as the overriden function", *member_write.right);
					}

					int next_interface_index = 0;
					for (int i = 0; i < function_type.parameters.get_num_fields(); ++i)
					{
						if (next_interface_index == function_type.interface_paramenters.size() || i < function_type.interface_paramenters[next_interface_index])
						{
							if (function->type.parameters.get_field_name(i) != function_type.parameters.get_field_name(i))
							{
								// TODO better error messages
								throw message_exception("Virtual function added is missing parameters", *member_write.right);
							}
							else if (function->type.parameters.get_field_type(i) != function_type.parameters.get_field_type(i))
							{
								// TODO better error messages
								throw message_exception("Virtual function added has a parameter of an incorrect type", *member_write.right);
							}
						}
						else
						{
							if (auto tuple_type = get<TupleType>(function->type.parameters.get_field_type(i)))
							{
								auto interface_type = get<InterfaceType>(function_type.parameters.get_field_type(i));
								assert(interface_type);
								if (!concep.is_interface_implementation(*tuple_type, *interface_type))
								{
									// TODO better error messages
									throw message_exception("Virtual function added has a tuple parameter that does not override the interface", *member_write.right);
								}
							}
							else
							{
								// TODO better error messages
								throw message_exception("Virtual function added has a parameter that is not a tuple overriding an interface", *member_write.right);
							}
							++next_interface_index;
						}
					}

					concep.add_function_override(function, (TypeShortName)member_write.member.text);
				}
				else
				{
					throw message_exception("Virtual function has to be overriden with a function", *member_write.right);
				}
			}
			else
			{
				throw message_exception("Virtual function has to be overriden with a compile time constant", *member_write.right);
			}
			break;
		}
		case ConceptType::Kind::None:
		default:
			throw message_exception("concept doesn't have a member of this name", member_write.member);
			break;
		}

		return;
	}
	else
	{
		throw message_exception("Expected a tuple or a concept before '.'", *member_write.left);
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

	std::vector<VariableBlock> old_locals;

	for (int i = 1; i < variable_blocks.size(); ++i)
	{
		old_locals.push_back(std::move(variable_blocks[i]));
	}

	variable_blocks.resize(1);

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

	assert(variable_blocks.size() == 2);
	variable_blocks.pop_back();
	for (auto& locals : old_locals)
	{
		variable_blocks.push_back(std::move(locals));
	}
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
		else if (auto concept_type = get<ConceptType>(variable.type))
		{
			variable_read.static_type = *concept_type;
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
		assert(variable_blocks.size() == 1);
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
		assert(variable_blocks.size() == 1);
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
	assert(variable_blocks.size() > 0);

	TypePath old_scope = current_scope;
	current_scope = TypePath(current_scope, variable_definition.variable.text);

	if (variable_definition.type_definition != nullptr)
	{
		variable_definition.type_definition->accept(*this);

		auto deduced_type = deduce_type(*variable_definition.type_definition);

		if (deduced_type.type == BuildInType::Typedef)
		{
			variable_definition.type = get_compile_time_type_value(*variable_definition.type_definition);
		}
		else if(auto interface_type = get<InterfaceType>(deduced_type.type))
		{
			variable_definition.type = *interface_type;
		}
		else
		{
			throw message_exception("Expected a type definition", *variable_definition.type_definition);
		}
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

	bool global_scope = (variable_blocks.size() == 1);
	VariableBlock& current_variable_block = variable_blocks.back();

	VariableInfo info;
	info.type = *variable_definition.type;
	info.constant = variable_definition.constant;

	if (variable_definition.initialization)
	{
		info.compile_time_value = get_compile_time_value(*variable_definition.initialization);
	}

	if (variable_definition.type == BuildInType::Typedef)
	{
		if (variable_definition.type == BuildInType::Typedef && !variable_definition.constant)
		{
			throw message_exception("typedefs must be constant", variable_definition);
		}
		assert(info.compile_time_value);
		get<TypeRepresentation>(*info.compile_time_value)->set_name((TypeFullName)current_scope);
	}
	else if (auto concept_type = get<ConceptType>(*variable_definition.type))
	{
		assert(!info.compile_time_value);
		assert(concept_type->name == (TypeFullName)current_scope);

		Concept concept_value;
		concept_value.type = *concept_type;
		concepts[concept_type->name] = concept_value;
	}

	if (info.compile_time_value)
	{
		info.index = -1;
		++current_variable_block.compile_time_constants;
	}
	else if (global_scope)
	{
		info.index = -1;
	}
	else
	{
		// TODO substract "constants"?
		variable_definition.index = info.index = current_variable_block.stack_size_at_beginning - current_variable_block.compile_time_constants + (int)current_variable_block.variables.size();
	}

	auto as_function = get<FunctionType>(info.type);
	if (as_function && info.constant)
	{
		MultifunctionType multi;

		if (current_variable_block.variables.contains((std::string)variable_definition.variable.text))
		{
			VariableInfo stored_info = current_variable_block.variables[(std::string)variable_definition.variable.text];
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
		else
		{
			variable_definition.multifunction_first = true;
			multi.is_pure = as_function->is_pure;
		}

		for (FunctionType const& old_overload : multi.functions)
		{
			if (old_overload == *as_function)
			{
				throw message_exception("overload already exists", variable_definition);
			}
		}
		multi.functions.push_back(std::move(*as_function));
		variable_definition.type = info.type = multi;
	}
	else if (current_variable_block.variables.contains((std::string)variable_definition.variable.text))
	{
		throw variable_redefinition_exception(variable_definition.variable);
	}


	current_variable_block.variables[(std::string)variable_definition.variable.text] = info;
	

	current_scope = old_scope; // TODO try finally?
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
	if (variable_blocks.size() > 1)
		stack_size_at_beginning = variable_blocks.back().stack_size_at_beginning - variable_blocks.back().compile_time_constants + (int)variable_blocks.back().variables.size();

	variable_blocks.push_back({ stack_size_at_beginning, 0 });
}

void TypePass::pop_variable_block()
{
	variable_blocks.pop_back();
}

TypePass::VariableInfo TypePass::find_variable(std::string_view identifier) const
{
	for (int i = (int)(variable_blocks.size() - 1); i >= 0; --i)
	{
		auto info = variable_blocks[i].variables.find((std::string)identifier);
		if (info != variable_blocks[i].variables.end())
		{
			return info->second;
		}
	}

	assert(false);
	return {};
}

TypePass::VariableInfo TypePass::find_variable(TerminalData identifier) const
{
	for (int i = (int)(variable_blocks.size() - 1); i >= 0; --i)
	{
		auto info = variable_blocks[i].variables.find((std::string)identifier.text);
		if (info != variable_blocks[i].variables.end())
		{
			return info->second;
		}
	}

	throw unknown_identifier_exception(identifier);
}

std::optional<TypeRepresentation> TypePass::find_typedef(TerminalData identifier) const
{
	return find_typedef(identifier.text);
}

std::optional<TypeRepresentation> TypePass::find_typedef(std::string_view identifier) const
{
	{
		auto info = current_concept_interfaces.find((std::string)identifier);
		if (info != current_concept_interfaces.end())
		{
			return info->second;
		}
	}

	for (int i = (int)(variable_blocks.size() - 1); i >= 0; --i)
	{
		auto info = variable_blocks[i].variables.find((std::string)identifier);
		if (info != variable_blocks[i].variables.end())
		{
			if (info->second.compile_time_value)
			{
				return get<TypeRepresentation>(*info->second.compile_time_value);
			}
			else
			{
				return std::nullopt;
			}
		}
	}

	return std::nullopt;
}

bool TypePass::implicit_cast(TupleType target, InitializerList& origin, bool let_undefined_fields, int* needed_casts) const
{
	if (origin.explicit_type)
	{
		if (origin.destination_type != target)
		{
			if (needed_casts == nullptr)
				throw message_exception("trying to cast a tuple", origin);
			else
				return false;
		}
	}
	else if (needed_casts == nullptr)
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
				if (needed_casts == nullptr)
					throw message_exception("tuple doesn't have this field", *origin.names[i]);
				else
					return false;
			}
			index = target.get_field_index(origin.names[i]->text);
			if (std::find(indexes.begin(), indexes.end(), index) != indexes.end())
			{
				if (needed_casts == nullptr)
					throw message_exception("this field has already been initialized", *origin.names[i]);
				else
					return false;
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
				if (needed_casts == nullptr)
					throw message_exception("too many initializer values for this tuple", *origin.expressions[i]);
				else
					return false;
			}
		}

		if (!implicit_cast(target.get_field_type(index), origin.expressions[i], needed_casts))
		{
			if (needed_casts == nullptr)
				throw message_exception("initializer has the wrong type", *origin.expressions[i]);
			else
				return false;
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
				if (needed_casts == nullptr)
					throw message_exception("missing arguments!", origin);
				else
					return false;
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
	else if (get<InterfaceType>(target) && get<TupleType>(original_type))
	{
		auto interface_type = get<InterfaceType>(target);
		auto tuple_type = get<TupleType>(original_type);

		Concept const& concept_impl = concepts.find(interface_type->get_concept_name())->second;

		if (!concept_impl.is_complete_interface_implementation(*tuple_type, *interface_type))
		{
			return false;
		}

		if (needed_casts == nullptr)
		{
			auto cast = std::make_unique<Cast>();
			cast->expr = std::move(origin);
			cast->target_type = target;

			origin = std::move(cast);
		}
		else
		{
			++*needed_casts;
		}

		return true;
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
