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

export import :TypeUtilities;

import Minairo.AST;
import Minairo.Concepts;
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

		std::string print_error() const;
	};

	// --------------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------------

	struct Function final : public FunctionRepresentation
	{
		FunctionType type;
		std::shared_ptr<Statement> body;

		Function() = default;
		Function(FunctionType const& _type, std::shared_ptr<Statement> const& _body) : type(_type), body(_body) {}
		Function(FunctionType const& _type, std::shared_ptr<Statement>&& _body) : type(_type), body(std::move(_body)) {}
		Function(FunctionType const& _type, std::unique_ptr<Statement>&& _body) : type(_type), body(std::move(_body)) {}

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
		FunctionType get_type() const noexcept override
		{
			return type;
		}

		void call(void* return_value, std::span<void*> _arguments) const noexcept override
		{
			assert(false);
		}

		operator Value() const
		{
			return (std::shared_ptr<ComplexValue>)std::make_shared<Function>(*this);
		}

		std::unique_ptr<FunctionRepresentation> deep_copy() const override
		{
			return std::make_unique<Function>(*this);
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
		struct GlobalMap
		{
			// TODO not a string map please. I'm just lazy rn
			std::unordered_map<std::string, VariableInfo> variables;
			std::unordered_map<std::string, TypeRepresentation> types;

			void add_global(std::string_view name, TypeRepresentation type, bool constant = true)
			{
				assert(variables.find((std::string)name) == variables.end());
				variables[(std::string)name] = { type, -1, constant };
			}
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

		void visit(Binary& binary) override;
		void visit(BuildInTypeDeclaration&) override;
		void visit(Call& call) override;
		void visit(Cast& cast) override;
		void visit(ConceptDeclaration& concept_declaration) override;
		void visit(Grouping& grouping) override;
		void visit(InitializerList& initializer_list) override;
		void visit(Literal& literal) override;
		void visit(MemberRead& member_read) override;
		void visit(MemberWrite& member_write) override;
		void visit(FunctionDeclaration& function_declaration) override;
		void visit(FunctionTypeDeclaration& function_type_declaration) override;
		void visit(TableDeclaration& table_declaration) override;
		void visit(TupleDeclaration& tuple_declaration) override;
		void visit(UnaryPre& unary_pre) override;
		void visit(UnaryPost& unary_post) override;
		void visit(VariableAssign& variable_assign) override;
		void visit(VariableRead& variable_read) override;

		// ----------------------------------------------------------------------------------------
		// ----------------------------------------------------------------------------------------
		// ----------------------------------------------------------------------------------------

		void visit(Block& block) override;
		void visit(ExpressionStatement& expression_statement) override;
		void visit(ForeachStatement& foreach_statement) override;
		void visit(IfStatement& if_statement) override;
		void visit(ReturnStatement& return_statement) override;
		void visit(VariableDefinition& variable_definition) override;
		void visit(WhileStatement& while_statement) override;

	private:
		struct VariableBlock
		{
			int stack_size_at_beginning;
			// TODO not a string map please. I'm just lazy rn
			std::unordered_map<std::string, VariableInfo> variables;
			std::unordered_map<std::string, TypeRepresentation> types;
		};

		std::vector<VariableBlock> variable_blocks;
		std::unordered_map<std::string, InterfaceType> current_concept_interfaces;

		GlobalMap globals;
		bool allow_return = false, in_pure_function_context = false;
		std::optional<TypeRepresentation> return_type;
		std::vector<std::string> current_scope;

		std::unordered_map<std::string, Concept> concepts;

		void push_variable_block();
		void pop_variable_block();
		VariableInfo find_variable(TerminalData identifier) const;
		std::optional<Concept> find_concept(TerminalData identifier) const;
		std::optional<TypeRepresentation> find_typedef(TerminalData identifier) const;
		bool implicit_cast(TupleType target, InitializerList& origin, bool let_undefined_fields, int* needed_casts = nullptr) const;
		bool implicit_cast(TypeRepresentation target, std::unique_ptr<Expression>& origin, int* needed_casts = nullptr) const;

	};
}
