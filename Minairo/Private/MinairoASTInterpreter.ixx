module;

#include <cassert>
#include <cinttypes>

#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <variant>
#include <vector>

export module Minairo.AST.Interpreter;

import Minairo.AST;
import Minairo.AST.TypePass;
import Minairo.Scanner;
import Minairo.TypesAndValues;


export namespace minairo
{
	class Interpreter final : public ExpressionConstVisitor, public StatementConstVisitor
	{
	public:
		explicit Interpreter(int _number_of_globals = 0, int _number_of_tuples = 0)
			: number_of_globals(_number_of_globals)
			, number_of_tuples(_number_of_tuples)
		{}

		struct Globals
		{
			// TODO not a string map please. I'm just lazy rn
			std::unordered_map<std::string, Value> variables;
		};

		void set_globals(Globals const& _globals)
		{
			globals = _globals;
		}

		Globals const& get_globals() const
		{
			return globals;
		}

		Value get_last_expression_value() const noexcept { return last_expression_value; }

		void visit(Binary const& binary) override
		{
			binary.left->accept(*this);
			Value left = last_expression_value;
			binary.right->accept(*this);
			Value right = last_expression_value;

			void* arguments[2] = { get_ptr(left), get_ptr(right) };

			TypeRepresentation return_type = *binary.get_expression_type();
			void* result_ptr = set_to_type(last_expression_value, return_type);

			binary.function_to_call->call(result_ptr, arguments);
		}

		void visit(BuildInTypeDeclaration const& build_tn_type_declaration) override
		{
			last_expression_value = build_tn_type_declaration.type;
		}

		void visit(Grouping const& grouping) override
		{
			grouping.expr->accept(*this);
		}

		void visit(InitializerList const& initializer_list) override
		{
			Tuple temporary_tuple;
			temporary_tuple.type = initializer_list.destination_type;

			temporary_tuple.fields.resize(temporary_tuple.type.get_num_fields());
			for (int i = 0; i < (int)initializer_list.default_initializers.size(); ++i)
			{
				int index = initializer_list.default_initializers[i];

				auto field_type = temporary_tuple.type.get_field_type(index);
				temporary_tuple.fields[index] = temporary_tuple.type.get_field_init_value(index);
			}

			for (int i = 0; i < (int)initializer_list.indexes.size(); ++i)
			{
				int index = initializer_list.indexes[i];
				initializer_list.expressions[i]->accept(*this);

				temporary_tuple.fields[index] = last_expression_value;
			}
			last_expression_value = temporary_tuple;
		}

		void visit(Literal const& literal) override
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

		void visit(MemberRead const& member_read) override
		{
			member_read.left->accept(*this);
			Value result = std::get<TupleReference>(last_expression_value).get_field(member_read.index);
			last_expression_value = result;
		}

		void visit(MemberWrite const& member_write) override
		{
			member_write.right->accept(*this);
			Value value = last_expression_value;

			member_write.left->accept(*this);
			Value result = std::get<TupleReference>(last_expression_value).get_field(member_write.index) = value;
			last_expression_value = result;
		}

		void visit(ProcedureDeclaration const& procedure_declaration) override
		{
			assert(false); // TODO
		}

		void visit(TableDeclaration const& table_declaration) override
		{
			last_expression_value = table_declaration.table;
		}

		void visit(TupleDeclaration const& tuple_declaration) override
		{
			last_expression_value = tuple_declaration.tuple;
		}

		void visit(UnaryPre const& unary_pre) override
		{
			unary_pre.exp->accept(*this);
			Value exp = last_expression_value;

			void* arguments[1] = {get_ptr(exp)};

			TypeRepresentation return_type = *unary_pre.get_expression_type();
			void* result_ptr = set_to_type(last_expression_value, return_type);

			unary_pre.function_to_call->call(result_ptr, arguments);
		}

		void visit(UnaryPost const& unary_post) override
		{
			unary_post.exp->accept(*this);
			Value exp = last_expression_value;

			void* arguments[1] = { get_ptr(exp) };

			TypeRepresentation return_type = *unary_post.get_expression_type();
			void* result_ptr = set_to_type(last_expression_value, return_type);

			unary_post.function_to_call->call(result_ptr, arguments);
		}

		void visit(VariableAssign const& variable_assign) override
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
				if (variable_assign.type->is_table())
				{
					TableType table_type = *variable_assign.type->as_table();
					Table& table = std::get<Table>((variable_assign.index == -1) ? globals.variables[(std::string)variable_assign.identifier.text] : variables[variable_assign.index]);
					Tuple& tuple = std::get<Tuple>(last_expression_value);
					for (int i = 0; i < table_type.base_tuple.get_num_fields(); ++i)
					{
						table.fields[i].push_back(tuple.fields[i]);
					}
					++table.rows;
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

		void visit(VariableRead const& variable_read) override
		{
			if (*variable_read.type == BuildInType::Typedef)
			{
				assert(variable_read.index == -1);
				last_expression_value = *variable_read.static_type;
			}
			else if (variable_read.type->is_tuple_reference())
			{
				TupleReferenceOnStack tuple_ref;
				assert(variable_read.index >= 0 && variable_read.index < variables.size());
				tuple_ref.tuple = &std::get<Tuple>(variables[variable_read.index]);
				last_expression_value = tuple_ref;
			}
			else if (variable_read.index == -1)
			{
				assert(globals.variables.find((std::string)variable_read.identifier.text) != globals.variables.end());
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

		void visit(Block const &block) override
		{
			int current_stack_size = (int)variables.size();

			for (auto& statement : block.statements)
			{
				statement->accept(*this);
			}

			variables.resize(current_stack_size);
		}

		void visit(ExpressionStatement const &expression_statement) override
		{
			expression_statement.exp->accept(*this);

			if (std::holds_alternative<TupleReference>(last_expression_value))
			{
				last_expression_value = std::get<TupleReference>(last_expression_value).as_tuple();
			}
		}

		void visit(VariableDefinition const& variable_definition) override
		{
			if (*variable_definition.type == BuildInType::Typedef)
			{
				assert(variable_definition.index == -1);
				last_expression_value = *variable_definition.initialization->get_type_value();
			}
			else if(variable_definition.index == -1)
			{
				if (variable_definition.initialization)
				{
					variable_definition.initialization->accept(*this);
					globals.variables[(std::string)variable_definition.variable.text] = last_expression_value;
				}
				else if (!variable_definition.explicitly_uninitialized)
				{
					last_expression_value = get_default_value(*variable_definition.type);
					globals.variables[(std::string)variable_definition.variable.text] = last_expression_value;
				}
				else if (std::holds_alternative<TupleType>(*variable_definition.type))
				{
					Tuple tuple;
					tuple.type = std::get<TupleType>(*variable_definition.type);
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
				else if (std::holds_alternative<TupleType>(*variable_definition.type))
				{
					Tuple tuple;
					tuple.type = std::get<TupleType>(*variable_definition.type); 
					last_expression_value = std::move(tuple);
					variables.push_back(last_expression_value);
				}
				else
				{
					variables.emplace_back();
				}
			}
		}


	private:
		Value last_expression_value;

		std::vector<Value> variables;
		Globals globals;

		int number_of_globals;
		int number_of_tuples;
	};
}
