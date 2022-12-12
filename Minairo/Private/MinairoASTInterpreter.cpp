module;

#include <cassert>
#include <cinttypes>

#include <memory>
#include <span>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <variant>
#include <vector>

module Minairo.AST.Interpreter;

import Minairo.AST;
import Minairo.AST.TypePass;
import Minairo.TypesAndValues;


using namespace minairo;

void Interpreter::visit(Binary const& binary)
{
	binary.left->accept(*this);
	Value left = last_expression_value;

	if (binary.op == Terminal::OP_OR)
	{
		if (!std::get<bool>(left))
		{
			binary.right->accept(*this);
		}
	}
	else if (binary.op == Terminal::OP_AND)
	{
		if (std::get<bool>(left))
		{
			binary.right->accept(*this);
		}
	}
	else
	{
		binary.right->accept(*this);
		Value right = last_expression_value;


		auto operation = [&binary]<typename T>(T left, T right)->Value
		{
			if constexpr (std::is_same_v<T, int8_t> || std::is_same_v<T, int16_t> || std::is_same_v<T, int32_t> || std::is_same_v<T, int64_t> ||
				std::is_same_v<T, uint8_t> || std::is_same_v<T, uint16_t> || std::is_same_v<T, uint32_t> || std::is_same_v<T, uint64_t>)
			{
				switch (binary.op)
				{
				case Terminal::OP_ADD:
					return (T)(left + right);
				case Terminal::OP_SUB:
					return (T)(left - right);
				case Terminal::OP_MUL:
					return (T)(left * right);
				case Terminal::OP_DIV:
					return (T)(left / right);
				case Terminal::OP_MOD:
					return (T)(left % right);

				case Terminal::OP_BIT_AND:
					return (T)(left & right);
				case Terminal::OP_BIT_OR:
					return (T)(left | right);
				case Terminal::OP_BIT_XOR:
					return (T)(left ^ right);

				case Terminal::OP_EQ:
					return left == right;
				case Terminal::OP_NEQ:
					return left != right;
				case Terminal::OP_LT:
					return left < right;
				case Terminal::OP_GT:
					return left > right;
				case Terminal::OP_LTE:
					return left <= right;
				case Terminal::OP_GTE:
					return left >= right;
				default:
					assert(false);
					return false;
				}
			}
			else if constexpr (std::is_same_v<T, float> || std::is_same_v<T, double>)
			{
				switch (binary.op)
				{
				case Terminal::OP_ADD:
					return left + right;
				case Terminal::OP_SUB:
					return left - right;
				case Terminal::OP_MUL:
					return left * right;
				case Terminal::OP_DIV:
					return left / right;

				case Terminal::OP_EQ:
					return left == right;
				case Terminal::OP_NEQ:
					return left != right;
				case Terminal::OP_LT:
					return left < right;
				case Terminal::OP_GT:
					return left > right;
				case Terminal::OP_LTE:
					return left <= right;
				case Terminal::OP_GTE:
					return left >= right;
				default:
					assert(false);
					return false;
				}
			}
			else if constexpr (std::is_same_v<T, bool> || std::is_same_v<T, bool>)
			{
				switch (binary.op)
				{
				case Terminal::OP_EQ:
					return left == right;
				case Terminal::OP_NEQ:
					return left != right;
				default:
					assert(false);
					return false;
				}
			}
			else
			{
				assert(false);
				return false;
			}
		};

		assert(get<BuildInType>(deduce_type(*binary.left).type));
		assert(deduce_type(*binary.left).type == deduce_type(*binary.right).type);

		switch (*get<BuildInType>(deduce_type(*binary.left).type))
		{
		case BuildInType::I8:
			last_expression_value = operation(std::get<int8_t>(left), std::get<int8_t>(right));
			break;
		case BuildInType::I16:
			last_expression_value = operation(std::get<int16_t>(left), std::get<int16_t>(right));
			break;
		case BuildInType::I32:
			last_expression_value = operation(std::get<int32_t>(left), std::get<int32_t>(right));
			break;
		case BuildInType::I64:
			last_expression_value = operation(std::get<int64_t>(left), std::get<int64_t>(right));
			break;
		case BuildInType::U8:
			last_expression_value = operation(std::get<uint8_t>(left), std::get<uint8_t>(right));
			break;
		case BuildInType::U16:
			last_expression_value = operation(std::get<uint16_t>(left), std::get<uint16_t>(right));
			break;
		case BuildInType::U32:
			last_expression_value = operation(std::get<uint32_t>(left), std::get<uint32_t>(right));
			break;
		case BuildInType::U64:
			last_expression_value = operation(std::get<uint64_t>(left), std::get<uint64_t>(right));
			break;
		case BuildInType::F32:
			last_expression_value = operation(std::get<float>(left), std::get<float>(right));
			break;
		case BuildInType::F64:
			last_expression_value = operation(std::get<double>(left), std::get<double>(right));
			break;
		case BuildInType::Bool:
			last_expression_value = operation(std::get<bool>(left), std::get<bool>(right));
			break;
		}
	}
}

void Interpreter::visit(BuildInTypeDeclaration const& build_tn_type_declaration)
{
	last_expression_value = build_tn_type_declaration.type;
}

void Interpreter::visit(Call const& call)
{
	call.callee->accept(*this);
	Value callee_value = last_expression_value;
	call.arguments.accept(*this);
	std::shared_ptr<Tuple> arguments = get<Tuple>(last_expression_value);

	std::shared_ptr<FunctionRepresentation> callee;
	if (auto virtual_function_type = get<ConceptType::VirtualFunctionType>(deduce_type(*call.callee).type))
	{
		auto virtual_function = get<VirtualFunction>(callee_value);
		if (virtual_function_type->interface_paramenters.size() == 1)
		{
			Value& field = arguments->fields[virtual_function_type->interface_paramenters[0]];
			std::shared_ptr<InterfaceReference> interface = get<InterfaceReference>(field);
			Concept::VirtualTable const& virtual_table = interface->get_virtual_table();
			callee = virtual_table.single_dispatch_functions[virtual_function_type->index];

			field = interface->as_tuple_reference();
		}
		else
		{
			assert(false); // TODO multi dispatch
		}
	}
	else
	{
		callee = get<FunctionRepresentation>(callee_value);
		assert(callee != nullptr);
	}


	if (Function* function = dynamic_cast<Function*>(callee.get()))
	{
		std::vector<Value> outer_variables = std::move(variables);
		variables = std::move(arguments->fields);

		bool returned = false;

		try {
			function->body->accept(*this);
		}
		catch (ReturnException)
		{
			returned = true;
		}

		assert(returned || function->get_return_type() == BuildInType::Void);
		variables = std::move(outer_variables);
	}
	else
	{
		std::vector<void*> args;
		args.reserve(arguments->fields.size());
		for (Value& argument : arguments->fields)
		{
			args.push_back(get_ptr(argument));
		}

		TypeRepresentation return_type = deduce_type(call).type;
		void* result_ptr = set_to_type(last_expression_value, return_type);

		callee->call(result_ptr, args);
	}
}

void Interpreter::visit(Cast const& cast)
{
	cast.expr->accept(*this);
	if (cast.target_type.is_buildin())
	{
		last_expression_value = std::visit([target_type = std::get<BuildInType>(cast.target_type)]<typename T>(T v) -> Value
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
					assert(false);
					return {};
				}
			}
			else
			{
				assert(false);
				return {}; // TODO
			}
		}, last_expression_value);
	}
	else if (auto function_type = get<FunctionType>(cast.target_type))
	{
		assert(get<MultifunctionType>(deduce_type(*cast.expr).type));
		auto multifunction = get<Multifunction>(last_expression_value);
		bool found = false;
		for (auto& candidate : multifunction->variants)
		{
			if (candidate->get_type() == *function_type)
			{
				last_expression_value = (std::shared_ptr<ComplexValue>)candidate;
				found = true;
				break;
			}
		}
		assert(found);
	}
	else if (auto interface_type = get<InterfaceType>(cast.target_type))
	{
		auto tuple_type = get<TupleType>(deduce_type(*cast.expr).type);
		assert(tuple_type);

		Concept const& concept_impl = type_globals.concepts.find(interface_type->get_concept_name())->second;

		Interface interface;
		interface.type = *interface_type;
		interface.virtual_table = concept_impl.get_virtual_table(*tuple_type, *interface_type);
		interface.tuple = *get<Tuple>(last_expression_value);
		assert(interface.tuple.type == *tuple_type);

		last_expression_value = interface;
	}
	else
	{
		assert(false);
	}
}

void Interpreter::visit(ConceptDeclaration const& concept_declaration)
{
	assert(false); // TODO
}

void Interpreter::visit(Grouping const& grouping)
{
	grouping.expr->accept(*this);
}

void Interpreter::visit(InitializerList const& initializer_list)
{
	Tuple temporary_tuple;
	temporary_tuple.type = initializer_list.destination_type;

	temporary_tuple.fields.resize(temporary_tuple.type.get_num_fields());
	for (int i = 0; i < (int)initializer_list.default_initializers.size(); ++i)
	{
		int index = initializer_list.default_initializers[i];

		auto field_type = temporary_tuple.type.get_field_type(index);
		if (auto default_value = temporary_tuple.type.get_field_init_value(index))
			temporary_tuple.fields[index] = *default_value;
		else
			temporary_tuple.fields[index] = get_default_value(field_type);
	}

	for (int i = 0; i < (int)initializer_list.indexes.size(); ++i)
	{
		int index = initializer_list.indexes[i];
		initializer_list.expressions[i]->accept(*this);

		temporary_tuple.fields[index] = last_expression_value;
	}
	last_expression_value = temporary_tuple;
}

void Interpreter::visit(Literal const& literal)
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

void Interpreter::visit(MemberRead const& member_read)
{
	if (member_read.compile_time_value)
	{
		last_expression_value = *member_read.compile_time_value;
		return;
	}

	member_read.left->accept(*this);

	Value* field = nullptr;
	auto left_type = deduce_type(*member_read.left).type;
	if (auto concept_type = get<ConceptType>(left_type))
	{
		auto concept_impl = type_globals.concepts.find(concept_type->name);
		assert(concept_impl != type_globals.concepts.end());
		last_expression_value = VirtualFunction{ concept_impl->second, member_read.index };
		return;
	}
	else if (get<InterfaceType>(left_type)/* || get<InterfaceReference>(left_type)*/)
	{
		field = &get<InterfaceReference>(last_expression_value)->get_field(member_read.index);
	}
	else
	{
		assert(get<TupleType>(left_type) || get<TupleReferenceType>(left_type));
		field = &get<TupleReference>(last_expression_value)->get_field(member_read.index);
	}

	if (get<TupleType>(*member_read.type))
	{
		TupleReferenceOnStack tuple_ref;
		tuple_ref.tuple = get<Tuple>(*field);
		assert(tuple_ref.tuple != nullptr);
		last_expression_value = tuple_ref;
	}
	else if (get<InterfaceType>(*member_read.type))
	{
		InterfaceReferenceOnStack interface_ref;
		interface_ref.interface = get<Interface>(*field);
		assert(interface_ref.interface != nullptr);
		last_expression_value = interface_ref;
	}
	else
	{
		last_expression_value = *field;
	}
}

void Interpreter::visit(MemberWrite const& member_write)
{
	if (auto concept_type = get<ConceptType>(deduce_type(*member_write.left).type))
	{
		// concept
		assert(member_write.op.type == Terminal::OP_ASSIGN_ADD);
		switch (concept_type->get_member_kind((TypeShortName)member_write.member.text))
		{
		case ConceptType::Kind::Interface:
		{
			// NOOP
			break;
		}
		case ConceptType::Kind::Function:
		{
			// NOOP
			break;
		}
		case ConceptType::Kind::None:
		default:
			assert(false); // invalid path
			break;
		}
	}
	else
	{
		// tuple
		member_write.right->accept(*this);
		Value value = last_expression_value;

		member_write.left->accept(*this);
		Value result;
		auto left_type = deduce_type(*member_write.left).type;
		if (get<InterfaceType>(left_type)/* || get<InterfaceReference>(left_type)*/)
		{
			result = get<InterfaceReference>(last_expression_value)->get_field(member_write.index) = value;
		}
		else
		{
			assert(get<TupleType>(left_type) || get<TupleReferenceType>(left_type));
			result = get<TupleReference>(last_expression_value)->get_field(member_write.index) = value;
		}
		last_expression_value = result;
	}
}

void Interpreter::visit(FunctionDeclaration const& function_declaration)
{
	last_expression_value = (std::shared_ptr<ComplexValue>)std::make_shared<Function>(function_declaration.header->type, function_declaration.body->deep_copy());
}

void Interpreter::visit(FunctionTypeDeclaration const& function_type_declaration)
{
	last_expression_value = function_type_declaration.type;
}

void Interpreter::visit(TableDeclaration const& table_declaration)
{
	last_expression_value = table_declaration.table;
}

void Interpreter::visit(TupleDeclaration const& tuple_declaration)
{
	last_expression_value = tuple_declaration.tuple;
}

void Interpreter::visit(UnaryPre const& unary_pre)
{
	unary_pre.exp->accept(*this);
	Value exp = last_expression_value;

	void* arguments[1] = { get_ptr(exp) };

	TypeRepresentation return_type = deduce_type(unary_pre).type;
	void* result_ptr = set_to_type(last_expression_value, return_type);

	unary_pre.function_to_call->call(result_ptr, arguments);
}

void Interpreter::visit(UnaryPost const& unary_post)
{
	unary_post.exp->accept(*this);
	Value exp = last_expression_value;

	void* arguments[1] = { get_ptr(exp) };

	TypeRepresentation return_type = deduce_type(unary_post).type;
	void* result_ptr = set_to_type(last_expression_value, return_type);

	unary_post.function_to_call->call(result_ptr, arguments);
}

void Interpreter::visit(VariableAssign const& variable_assign)
{
	assert(variable_assign.index < (int)variables.size());
	variable_assign.exp->accept(*this);

	switch (variable_assign.op.type)
	{
	case Terminal::OP_ASSIGN:
		if (variable_assign.index == -1)
		{
			globals.variables[(std::string)variable_assign.identifier.text] = last_expression_value;
		}
		else
		{
			variables[variable_assign.index] = last_expression_value;
		}
		break;
	case Terminal::OP_ASSIGN_ADD:
		if (auto table_type = get<TableType>(*variable_assign.type))
		{
			std::shared_ptr<Table> table = get<Table>((variable_assign.index == -1) ? globals.variables[(std::string)variable_assign.identifier.text] : variables[variable_assign.index]);
			std::shared_ptr<Tuple> tuple = get<Tuple>(last_expression_value);
			for (int i = 0; i < table_type->base_tuple.get_num_fields(); ++i)
			{
				table->fields[i].push_back(tuple->fields[i]);
			}
			++table->rows;
			// TODO table reference
			if (variable_assign.index == -1)
			{
				last_expression_value = globals.variables[(std::string)variable_assign.identifier.text];
			}
			else
			{
				last_expression_value = variables[variable_assign.index];
			}
		}
		else
		{
			assert(false);
		}
		break;
	case Terminal::OP_ASSIGN_SUB:
	case Terminal::OP_ASSIGN_MUL:
	case Terminal::OP_ASSIGN_DIV:
	case Terminal::OP_ASSIGN_MOD:
	default:
		assert(false);
		break;
	}
}

void Interpreter::visit(VariableRead const& variable_read)
{
	if (*variable_read.type == BuildInType::Typedef)
	{
		assert(variable_read.index == -1);
		last_expression_value = *variable_read.static_type;
	}
	else if (*variable_read.type == BuildInType::Typedef)
	{
		assert(variable_read.index == -1);
		last_expression_value = *variable_read.static_type;
	}
	else if (get<TupleType>(*variable_read.type))
	{
		TupleReferenceOnStack tuple_ref;
		if (variable_read.index == -1)
		{
			assert(globals.variables.find((std::string)variable_read.identifier.text) != globals.variables.end());
			tuple_ref.tuple = get<Tuple>(globals.variables[(std::string)variable_read.identifier.text]);
		}
		else
		{
			assert(variable_read.index >= 0 && variable_read.index < variables.size());
			tuple_ref.tuple = get<Tuple>(variables[variable_read.index]);
		}
		assert(tuple_ref.tuple != nullptr);
		last_expression_value = tuple_ref;
	}
	else if (get<InterfaceType>(*variable_read.type))
	{
		InterfaceReferenceOnStack interface_ref;
		if (variable_read.index == -1)
		{
			assert(globals.variables.find((std::string)variable_read.identifier.text) != globals.variables.end());
			interface_ref.interface = get<Interface>(globals.variables[(std::string)variable_read.identifier.text]);
		}
		else
		{
			assert(variable_read.index >= 0 && variable_read.index < variables.size());
			interface_ref.interface = get<Interface>(variables[variable_read.index]);
		}
		assert(interface_ref.interface != nullptr);
		last_expression_value = interface_ref;
	}
	else if (auto concept_type = get<ConceptType>(*variable_read.type))
	{
		// -------
	}
	else if (variable_read.index == -1)
	{
		auto global = globals.variables.find((std::string)variable_read.identifier.text);
		assert(global != globals.variables.end());
		
		last_expression_value = globals.variables[(std::string)variable_read.identifier.text];
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

void Interpreter::visit(Block const& block)
{
	int current_stack_size = (int)variables.size();

	for (auto& statement : block.statements)
	{
		statement->accept(*this);
	}

	variables.resize(current_stack_size);
}

void Interpreter::visit(ExpressionStatement const& expression_statement)
{
	expression_statement.exp->accept(*this);

	if (auto tuple_reference = get<TupleReference>(last_expression_value))
	{
		last_expression_value = tuple_reference->as_tuple();
	}
	else if (auto interface_reference = get<InterfaceReference>(last_expression_value))
	{
		last_expression_value = interface_reference->as_interface();
	}
}

void Interpreter::visit(ForeachStatement const& for_statement)
{
	for_statement.table->accept(*this);
	TupleReferenceOnATable reference;
	reference.table = get<Table>(last_expression_value);

	int current_stack_size = (int)variables.size();

	variables.push_back(reference);

	for (reference.row = 0; reference.row < reference.table->rows; ++reference.row)
	{
		variables[current_stack_size] = reference;

		for_statement.body->accept(*this);
	}

	variables.resize(current_stack_size);
}

void Interpreter::visit(IfStatement const& if_statement)
{
	int current_stack_size = (int)variables.size();

	if (if_statement.initialization != nullptr)
		if_statement.initialization->accept(*this);

	if (if_statement.condition != nullptr)
		if_statement.condition->accept(*this);

	if (*get<bool>(last_expression_value))
	{
		if_statement.yes->accept(*this);
	}
	else if (if_statement.no != nullptr)
	{
		if_statement.no->accept(*this);
	}

	variables.resize(current_stack_size);
}

void Interpreter::visit(ReturnStatement const& return_statement)
{
	return_statement.exp->accept(*this);
	throw ReturnException{};
}

void Interpreter::visit(VariableDefinition const& variable_definition)
{
	if (*variable_definition.type == BuildInType::Typedef)
	{
		assert(variable_definition.index == -1);
		last_expression_value = *get_compile_time_value(*variable_definition.initialization);
	}
	else if (variable_definition.index == -1)
	{
		if (get<MultifunctionType>(*variable_definition.type))
		{
			assert(variable_definition.initialization);
			variable_definition.initialization->accept(*this);
			auto old_multi = globals.variables.find((std::string)variable_definition.variable.text);
			if (old_multi == globals.variables.end())
			{
				Multifunction multi;
				multi.variants.push_back(get<FunctionRepresentation>(last_expression_value));
				globals.variables[(std::string)variable_definition.variable.text] = multi;
			}
			else
			{
				get<Multifunction>(old_multi->second)->variants.push_back(get<FunctionRepresentation>(last_expression_value));
			}
		}
		else if (auto concept_type = get<ConceptType>(*variable_definition.type))
		{
			// NOOP
		}
		else if (variable_definition.initialization)
		{
			variable_definition.initialization->accept(*this);
			globals.variables[(std::string)variable_definition.variable.text] = last_expression_value;
		}
		else if (!variable_definition.explicitly_uninitialized)
		{
			last_expression_value = get_default_value(*variable_definition.type);
			globals.variables[(std::string)variable_definition.variable.text] = last_expression_value;
		}
		else if (auto tuple_type = get<TupleType>(*variable_definition.type))
		{
			Tuple tuple;
			tuple.type = *tuple_type;
			last_expression_value = std::move(tuple);
			globals.variables[(std::string)variable_definition.variable.text] = last_expression_value;
		}
		else
		{
			globals.variables[(std::string)variable_definition.variable.text] = {};
		}
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
		else if (auto tuple_type = get<TupleType>(*variable_definition.type))
		{
			Tuple tuple;
			tuple.type = *tuple_type;
			last_expression_value = std::move(tuple);
			variables.push_back(last_expression_value);
		}
		else
		{
			variables.emplace_back();
		}
	}
}

void Interpreter::visit(WhileStatement const& while_statement)
{
	if (!while_statement.do_while)
	{
		if (while_statement.condition != nullptr)
			while_statement.condition->accept(*this);

		if (!*get<bool>(last_expression_value))
		{
			return;
		}
	}

	do
	{
		while_statement.body->accept(*this);
		while_statement.condition->accept(*this);
	} while (*get<bool>(last_expression_value));

}
