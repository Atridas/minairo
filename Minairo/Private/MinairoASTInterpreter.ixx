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

export module Minairo.AST.Interpreter;

import Minairo.AST;
import Minairo.AST.TypePass;
import Minairo.Concepts;
import Minairo.TypesAndValues;


export namespace minairo
{
	class ReturnException {};

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
			std::unordered_map<std::string, Concept> concepts;
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

		void visit(Binary const& binary) override;
		void visit(BuildInTypeDeclaration const& build_tn_type_declaration) override;
		void visit(Call const& call) override;
		void visit(Cast const& cast) override;
		void visit(ConceptDeclaration const& concept_declaration) override;
		void visit(Grouping const& grouping) override;
		void visit(InitializerList const& initializer_list) override;
		void visit(Literal const& literal) override;
		void visit(MemberRead const& member_read) override;
		void visit(MemberWrite const& member_write) override;
		void visit(FunctionDeclaration const& function_declaration) override;
		void visit(FunctionTypeDeclaration const& function_type_declaration) override;
		void visit(TableDeclaration const& table_declaration) override;
		void visit(TupleDeclaration const& tuple_declaration) override;
		void visit(UnaryPre const& unary_pre) override;
		void visit(UnaryPost const& unary_post) override;
		void visit(VariableAssign const& variable_assign) override;
		void visit(VariableRead const& variable_read) override;

		// ----------------------------------------------------------------------------------------
		// ----------------------------------------------------------------------------------------
		// ----------------------------------------------------------------------------------------

		void visit(Block const& block) override;
		void visit(ExpressionStatement const& expression_statement) override;
		void visit(ForeachStatement const& for_statement) override;
		void visit(IfStatement const& if_statement) override;
		void visit(ReturnStatement const& return_statement) override;
		void visit(VariableDefinition const& variable_definition) override;
		void visit(WhileStatement const& while_statement) override;

	private:
		Value last_expression_value;

		std::vector<Value> variables;
		Globals globals;

		int number_of_globals;
		int number_of_tuples;
	};
}
