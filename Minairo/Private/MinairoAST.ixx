module;

#include <cassert>
#include <cinttypes>

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

export module Minairo.AST;

import Minairo.Scanner;
import Minairo.TypesAndValues;

export namespace minairo
{
	class ExpressionVisitor;
	class ExpressionConstVisitor;
	class StatementVisitor;
	class StatementConstVisitor;

	class Expression
	{
	public:
		virtual void accept(ExpressionVisitor& visitor) = 0;
		virtual void accept(ExpressionConstVisitor& visitor) const = 0;

		virtual std::unique_ptr<Expression> deep_copy() const = 0;
		virtual TerminalData get_first_terminal() const = 0;
		virtual TerminalData get_last_terminal() const = 0;
	};

	class Statement
	{
	public:
		virtual void accept(StatementVisitor& visitor) = 0;
		virtual void accept(StatementConstVisitor& visitor) const = 0;

		virtual std::unique_ptr<Statement> deep_copy() const = 0;
		virtual TerminalData get_first_terminal() const = 0;
		virtual TerminalData get_last_terminal() const = 0;
	};

	// -----------------------------------------------------------------------------------------------
	// EXPRESSIONS -----------------------------------------------------------------------------------
	// -----------------------------------------------------------------------------------------------

	class Binary final : public Expression
	{
	public:
		std::unique_ptr<Expression> left, right;
		Terminal op;

		Binary() = default;
		Binary(Binary&&) = default;
		Binary& operator=(Binary&&) = default;
		Binary(Binary const& b) : left(b.left->deep_copy()), right(b.right->deep_copy()), op(b.op) {}
		Binary& operator=(Binary const& b)
		{
			if (this != &b)
			{
				left = b.left->deep_copy();
				right = b.right->deep_copy();
				op = b.op;
			}
			return *this;
		}
		std::unique_ptr<Expression> deep_copy() const override
		{
			return typed_deep_copy();
		}
		std::unique_ptr<Binary> typed_deep_copy() const
		{
			return std::make_unique<Binary>(*this);
		}

		void accept(ExpressionVisitor& visitor) override;
		void accept(ExpressionConstVisitor& visitor) const override;
		TerminalData get_first_terminal() const override
		{
			return left->get_first_terminal();
		}
		TerminalData get_last_terminal() const override
		{
			return right->get_last_terminal();
		}
	};

	class BuildInTypeDeclaration final : public Expression
	{
	public:
		BuildInType type;
		TerminalData terminal;

		std::unique_ptr<Expression> deep_copy() const override
		{
			return typed_deep_copy();
		}
		std::unique_ptr<BuildInTypeDeclaration> typed_deep_copy() const
		{
			return std::make_unique<BuildInTypeDeclaration>(*this);
		}

		void accept(ExpressionVisitor& visitor) override;
		void accept(ExpressionConstVisitor& visitor) const override;
		virtual TerminalData get_first_terminal() const override
		{
			return terminal;
		}
		virtual TerminalData get_last_terminal() const override
		{
			return terminal;
		}
	};

	class Grouping final : public Expression
	{
	public:
		std::unique_ptr<Expression> expr;
		TerminalData open, close;

		Grouping() = default;
		Grouping(Grouping&&) = default;
		Grouping& operator=(Grouping&&) = default;
		Grouping(Grouping const& b)
			: expr(b.expr->deep_copy())
			, open(b.open)
			, close(b.close)
		{
		}
		Grouping& operator=(Grouping const& b)
		{
			if (this != &b)
			{
				expr = b.expr->deep_copy();
				open = b.open;
				close = b.close;
			}
			return *this;
		}

		std::unique_ptr<Expression> deep_copy() const override
		{
			return typed_deep_copy();
		}
		std::unique_ptr<Grouping> typed_deep_copy() const
		{
			return std::make_unique<Grouping>(*this);
		}

		void accept(ExpressionVisitor& visitor) override;
		void accept(ExpressionConstVisitor& visitor) const override;
		virtual TerminalData get_first_terminal() const override
		{
			return open;
		}
		virtual TerminalData get_last_terminal() const override
		{
			return close;
		}
	};

	class InitializerList final : public Expression
	{
	public:
		std::vector<std::optional<TerminalData>> names;
		std::vector<std::unique_ptr<Expression>> expressions;
		std::vector<int> indexes;
		std::vector<int> default_initializers;
		TupleType destination_type;
		TerminalData open, close;

		InitializerList() = default;
		InitializerList(InitializerList&&) = default;
		InitializerList& operator=(InitializerList&&) = default;
		InitializerList(InitializerList const& b) 
			: names(b.names)
			, indexes(b.indexes)
			, default_initializers(b.default_initializers)
			, destination_type(b.destination_type)
			, open(b.open)
			, close(b.close)
		{
			expressions.resize(b.expressions.size());
			for (int i = 0; i < (int)expressions.size(); ++i)
			{
				expressions[i] = b.expressions[i]->deep_copy();
			}
		}
		InitializerList& operator=(InitializerList const& b)
		{
			if (this != &b)
			{
				indexes = b.indexes;
				default_initializers = b.default_initializers;
				destination_type = b.destination_type;
				open = b.open;
				close = b.close;

				expressions.resize(b.expressions.size());
				for (int i = 0; i < (int)expressions.size(); ++i)
				{
					expressions[i] = b.expressions[i]->deep_copy();
				}
			}
			return *this;
		}

		std::unique_ptr<Expression> deep_copy() const override
		{
			return typed_deep_copy();
		}
		std::unique_ptr<InitializerList> typed_deep_copy() const
		{
			return std::make_unique<InitializerList>(*this);
		}

		void accept(ExpressionVisitor& visitor) override;
		void accept(ExpressionConstVisitor& visitor) const override;
		virtual TerminalData get_first_terminal() const override
		{
			return open;
		}
		virtual TerminalData get_last_terminal() const override
		{
			return close;
		}
	};

	class Call final : public Expression
	{
	public:
		std::unique_ptr<Expression> callee;
		InitializerList arguments;


		Call() = default;
		Call(Call&&) = default;
		Call& operator=(Call&&) = default;
		Call(Call const& b)
			: callee(b.callee->deep_copy())
			, arguments(b.arguments)
		{
		}
		Call& operator=(Call const& b)
		{
			if (this != &b)
			{
				callee = b.callee->deep_copy();
				arguments = b.arguments;
			}
			return *this;
		}

		std::unique_ptr<Expression> deep_copy() const override
		{
			return typed_deep_copy();
		}
		std::unique_ptr<Call> typed_deep_copy() const
		{
			return std::make_unique<Call>(*this);
		}

		void accept(ExpressionVisitor& visitor) override;
		void accept(ExpressionConstVisitor& visitor) const override;
		virtual TerminalData get_first_terminal() const override
		{
			return callee->get_first_terminal();
		}
		virtual TerminalData get_last_terminal() const override
		{
			return arguments.get_last_terminal();
		}
	};

	class Cast final : public Expression
	{
	public:
		std::unique_ptr<Expression> expr;
		TypeRepresentation target_type;


		Cast() = default;
		Cast(Cast&&) = default;
		Cast& operator=(Cast&&) = default;
		Cast(Cast const& b)
			: expr(b.expr->deep_copy())
			, target_type(b.target_type)
		{
		}
		Cast& operator=(Cast const& b)
		{
			if (this != &b)
			{
				expr = b.expr->deep_copy();
				target_type = b.target_type;
			}
			return *this;
		}

		std::unique_ptr<Expression> deep_copy() const override
		{
			return typed_deep_copy();
		}
		std::unique_ptr<Cast> typed_deep_copy() const
		{
			return std::make_unique<Cast>(*this);
		}

		void accept(ExpressionVisitor& visitor) override;
		void accept(ExpressionConstVisitor& visitor) const override;
		virtual TerminalData get_first_terminal() const override
		{
			return expr->get_first_terminal();
		}
		virtual TerminalData get_last_terminal() const override
		{
			return expr->get_last_terminal();
		}
	};

	class Literal final : public Expression
	{
	public:
		std::variant<uint64_t, double, std::string, char32_t, bool> value;
		TypeRepresentation type_representation;
		TerminalData terminal;

		std::unique_ptr<Expression> deep_copy() const override
		{
			return typed_deep_copy();
		}
		std::unique_ptr<Literal> typed_deep_copy() const
		{
			return std::make_unique<Literal>(*this);
		}

		void accept(ExpressionVisitor& visitor) override;
		void accept(ExpressionConstVisitor& visitor) const override;
		virtual TerminalData get_first_terminal() const override
		{
			return terminal;
		}
		virtual TerminalData get_last_terminal() const override
		{
			return terminal;
		}
	};

	class MemberRead final :public Expression
	{
	public:
		std::unique_ptr<Expression> left;
		TerminalData member;
		int index = -1;
		bool constant;
		std::optional<TypeRepresentation> type;

		MemberRead() = default;
		MemberRead(MemberRead&&) = default;
		MemberRead& operator=(MemberRead&&) = default;
		MemberRead(MemberRead const& b)
			: left(b.left->deep_copy())
			, member(b.member)
			, index(b.index)
			, constant(b.constant)
			, type(b.type)
		{
		}
		MemberRead& operator=(MemberRead const& b)
		{
			if (this != &b)
			{
				left = b.left->deep_copy();
				member = b.member;
				index = b.index;
				constant = b.constant;
				type = b.type;
			}
			return *this;
		}

		std::unique_ptr<Expression> deep_copy() const override
		{
			return typed_deep_copy();
		}
		std::unique_ptr<MemberRead> typed_deep_copy() const
		{
			return std::make_unique<MemberRead>(*this);
		}

		void accept(ExpressionVisitor& visitor) override;
		void accept(ExpressionConstVisitor& visitor) const override;
		virtual TerminalData get_first_terminal() const override
		{
			return left->get_first_terminal();
		}
		virtual TerminalData get_last_terminal() const override
		{
			return member;
		}
	};

	class MemberWrite final :public Expression
	{
	public:
		std::unique_ptr<Expression> left;
		TerminalData member, op;
		std::unique_ptr<Expression> right;
		int index = -1;
		std::optional<TypeRepresentation> type;

		MemberWrite() = default;
		MemberWrite(MemberWrite&&) = default;
		MemberWrite& operator=(MemberWrite&&) = default;
		MemberWrite(MemberWrite const& b)
			: left(b.left->deep_copy())
			, member(b.member)
			, op(b.op)
			, right(b.right->deep_copy())
			, index(b.index)
			, type(b.type)
		{
		}
		MemberWrite& operator=(MemberWrite const& b)
		{
			if (this != &b)
			{
				left = b.left->deep_copy();
				member = b.member;
				op = b.op;
				right = b.right->deep_copy();
				index = b.index;
				type = b.type;
			}
			return *this;
		}

		std::unique_ptr<Expression> deep_copy() const override
		{
			return typed_deep_copy();
		}
		std::unique_ptr<MemberWrite> typed_deep_copy() const
		{
			return std::make_unique<MemberWrite>(*this);
		}

		void accept(ExpressionVisitor& visitor) override;
		void accept(ExpressionConstVisitor& visitor) const override;
		virtual TerminalData get_first_terminal() const override
		{
			return left->get_first_terminal();
		}
		virtual TerminalData get_last_terminal() const override
		{
			return member;
		}
	};

	class TupleDeclaration final : public Expression
	{
	public:
		TupleType tuple;
		TerminalData tuple_terminal, closing_bracket;

		std::vector<TerminalData> field_names;
		std::vector<std::unique_ptr<Expression>> field_types;
		std::vector<std::unique_ptr<Expression>> field_initializers;

		TupleDeclaration() = default;
		TupleDeclaration(TupleDeclaration&&) = default;
		TupleDeclaration& operator=(TupleDeclaration&&) = default;
		TupleDeclaration(TupleDeclaration const& b)
			: tuple(b.tuple)
			, tuple_terminal(b.tuple_terminal)
			, closing_bracket(b.closing_bracket)
			, field_names(b.field_names)
		{
			assert(field_names.size() == b.field_types.size());
			assert(field_names.size() == b.field_initializers.size());

			field_types.resize(field_names.size());
			field_initializers.resize(field_names.size());

			for (int i = 0; i < field_names.size(); ++i)
			{
				if (b.field_types[i] != nullptr)
					field_types[i] = b.field_types[i]->deep_copy();
				if (b.field_initializers[i] != nullptr)
					field_initializers[i] = b.field_initializers[i]->deep_copy();
			}
		}
		TupleDeclaration& operator=(TupleDeclaration const& b)
		{
			if (this != &b)
			{
				tuple = b.tuple;
				tuple_terminal = b.tuple_terminal;
				closing_bracket = b.closing_bracket;
				field_names = b.field_names;

				field_types.resize(field_names.size());
				field_initializers.resize(field_names.size());

				for (int i = 0; i < field_names.size(); ++i)
				{
					if (b.field_types[i] != nullptr)
						field_types[i] = b.field_types[i]->deep_copy();
					if (b.field_initializers[i] != nullptr)
						field_initializers[i] = b.field_initializers[i]->deep_copy();
				}
			}
			return *this;
		}
		std::unique_ptr<Expression> deep_copy() const override
		{
			return typed_deep_copy();
		}
		std::unique_ptr<TupleDeclaration> typed_deep_copy() const
		{
			return std::make_unique<TupleDeclaration>(*this);
		}

		void accept(ExpressionVisitor& visitor) override;
		void accept(ExpressionConstVisitor& visitor) const override;
		virtual TerminalData get_first_terminal() const override
		{
			return tuple_terminal;
		}
		virtual TerminalData get_last_terminal() const override
		{
			return closing_bracket;
		}
	};
	
	class FunctionTypeDeclaration final : public Expression
	{
	public:
		TerminalData keyword, parenthesis;
		std::unique_ptr<TupleDeclaration> parameter_tuple;
		std::unique_ptr<Expression> return_type;
		bool is_pure;
		FunctionType type;

		FunctionTypeDeclaration() = default;
		FunctionTypeDeclaration(FunctionTypeDeclaration&&) = default;
		FunctionTypeDeclaration& operator=(FunctionTypeDeclaration&&) = default;
		FunctionTypeDeclaration(FunctionTypeDeclaration const& b)
			: keyword(b.keyword)
			, parenthesis(b.parenthesis)
			, parameter_tuple(b.parameter_tuple->typed_deep_copy())
			, return_type(b.return_type->deep_copy())
			, type(b.type)
		{
		}
		FunctionTypeDeclaration& operator=(FunctionTypeDeclaration const& b)
		{
			if (this != &b)
			{
				keyword = b.keyword;
				parenthesis = b.parenthesis;
				parameter_tuple = b.parameter_tuple->typed_deep_copy();
				return_type = b.return_type->deep_copy();
				type = b.type;
			}
			return *this;
		}

		std::unique_ptr<Expression> deep_copy() const override
		{
			return typed_deep_copy();
		}
		std::unique_ptr<FunctionTypeDeclaration> typed_deep_copy() const
		{
			return std::make_unique<FunctionTypeDeclaration>(*this);
		}

		void accept(ExpressionVisitor& visitor) override;
		void accept(ExpressionConstVisitor& visitor) const override;
		virtual TerminalData get_first_terminal() const override
		{
			return keyword;
		}
		virtual TerminalData get_last_terminal() const override
		{
			return return_type ? return_type->get_last_terminal() : parenthesis;
		}
	};
	
	class FunctionDeclaration final : public Expression
	{
	public:
		std::unique_ptr<FunctionTypeDeclaration> header;
		std::unique_ptr<class Block> body;

		FunctionDeclaration() = default;
		FunctionDeclaration(FunctionDeclaration&&) = default;
		FunctionDeclaration& operator=(FunctionDeclaration&&) = default;
		FunctionDeclaration(FunctionDeclaration const& b);
		FunctionDeclaration& operator=(FunctionDeclaration const& b);

		std::unique_ptr<Expression> deep_copy() const override
		{
			return typed_deep_copy();
		}
		std::unique_ptr<FunctionDeclaration> typed_deep_copy() const
		{
			return std::make_unique<FunctionDeclaration>(*this);
		}

		void accept(ExpressionVisitor& visitor) override;
		void accept(ExpressionConstVisitor& visitor) const override;
		TerminalData get_first_terminal() const override
		{
			return header->get_last_terminal();
		}
		TerminalData get_last_terminal() const override;
	};

	class TableDeclaration final : public Expression
	{
	public:
		TableType table;
		TerminalData table_terminal, last_terminal;
		std::unique_ptr<TupleDeclaration> inner_tuple;
		TerminalData tuple_name;

		TableDeclaration() = default;
		TableDeclaration(TableDeclaration&&) = default;
		TableDeclaration& operator=(TableDeclaration&&) = default;
		TableDeclaration(TableDeclaration const& b)
			: table(b.table)
			, table_terminal(b.table_terminal)
			, last_terminal(b.last_terminal)
			, inner_tuple(b.inner_tuple->typed_deep_copy())
			, tuple_name(b.tuple_name)
		{
		}
		TableDeclaration& operator=(TableDeclaration const& b)
		{
			if (this != &b)
			{
				table = b.table;
				table_terminal = b.table_terminal;
				last_terminal = b.last_terminal;
				inner_tuple = b.inner_tuple->typed_deep_copy();
				tuple_name = b.tuple_name;
			}
			return *this;
		}

		std::unique_ptr<Expression> deep_copy() const override
		{
			return typed_deep_copy();
		}
		std::unique_ptr<TableDeclaration> typed_deep_copy() const
		{
			return std::make_unique<TableDeclaration>(*this);
		}

		void accept(ExpressionVisitor& visitor) override;
		void accept(ExpressionConstVisitor& visitor) const override;
		virtual TerminalData get_first_terminal() const override
		{
			return table_terminal;
		}
		virtual TerminalData get_last_terminal() const override
		{
			return last_terminal;
		}
	};

	class UnaryPre final : public Expression
	{
	public:
		TerminalData op;
		std::unique_ptr<Expression> exp;
		FunctionRepresentation const* function_to_call = nullptr;

		UnaryPre() = default;
		UnaryPre(UnaryPre&&) = default;
		UnaryPre& operator=(UnaryPre&&) = default;
		UnaryPre(UnaryPre const& b)
			: op(b.op)
			, exp(b.exp->deep_copy())
			, function_to_call(b.function_to_call)
		{
		}
		UnaryPre& operator=(UnaryPre const& b)
		{
			if (this != &b)
			{
				op = b.op;
				exp = b.exp->deep_copy();
				function_to_call = b.function_to_call;
			}
			return *this;
		}

		std::unique_ptr<Expression> deep_copy() const override
		{
			return typed_deep_copy();
		}
		std::unique_ptr<UnaryPre> typed_deep_copy() const
		{
			return std::make_unique<UnaryPre>(*this);
		}

		void accept(ExpressionVisitor& visitor) override;
		void accept(ExpressionConstVisitor& visitor) const override;
		virtual TerminalData get_first_terminal() const override
		{
			return op;
		}
		virtual TerminalData get_last_terminal() const override
		{
			return exp->get_last_terminal();
		}
	};

	class UnaryPost final : public Expression
	{
	public:
		std::unique_ptr<Expression> exp;
		TerminalData op;
		FunctionRepresentation const* function_to_call = nullptr;

		UnaryPost() = default;
		UnaryPost(UnaryPost&&) = default;
		UnaryPost& operator=(UnaryPost&&) = default;
		UnaryPost(UnaryPost const& b)
			: op(b.op)
			, exp(b.exp->deep_copy())
			, function_to_call(b.function_to_call)
		{
		}
		UnaryPost& operator=(UnaryPost const& b)
		{
			if (this != &b)
			{
				op = b.op;
				exp = b.exp->deep_copy();
				function_to_call = b.function_to_call;
			}
			return *this;
		}

		std::unique_ptr<Expression> deep_copy() const override
		{
			return typed_deep_copy();
		}
		std::unique_ptr<UnaryPost> typed_deep_copy() const
		{
			return std::make_unique<UnaryPost>(*this);
		}

		void accept(ExpressionVisitor& visitor) override;
		void accept(ExpressionConstVisitor& visitor) const override;
		virtual TerminalData get_first_terminal() const override
		{
			return exp->get_last_terminal();
		}
		virtual TerminalData get_last_terminal() const override
		{
			return op;
		}
	};

	class VariableAssign final : public Expression
	{
	public:
		TerminalData identifier, op;
		std::unique_ptr<Expression> exp;
		std::optional<TypeRepresentation> type;
		int index = -1;

		VariableAssign() = default;
		VariableAssign(VariableAssign&&) = default;
		VariableAssign& operator=(VariableAssign&&) = default;
		VariableAssign(VariableAssign const& b)
			: identifier(b.identifier)
			, op(b.op)
			, exp(b.exp->deep_copy())
			, type(b.type)
			, index(b.index)
		{
		}
		VariableAssign& operator=(VariableAssign const& b)
		{
			if (this != &b)
			{
				identifier = b.identifier;
				op = b.op;
				exp = b.exp->deep_copy();
				type = b.type;
				index = b.index;
			}
			return *this;
		}

		std::unique_ptr<Expression> deep_copy() const override
		{
			return typed_deep_copy();
		}
		std::unique_ptr<VariableAssign> typed_deep_copy() const
		{
			return std::make_unique<VariableAssign>(*this);
		}

		void accept(ExpressionVisitor& visitor) override;
		void accept(ExpressionConstVisitor& visitor) const override;
		virtual TerminalData get_first_terminal() const override
		{
			return identifier;
		}
		virtual TerminalData get_last_terminal() const override
		{
			return exp->get_last_terminal();
		}
	};

	class VariableRead final : public Expression
	{
	public:
		TerminalData identifier;
		std::optional<TypeRepresentation> static_type;
		std::optional<TypeRepresentation> type;
		int index = -1;
		bool constant = true;

		VariableRead() = default;
		VariableRead(VariableRead&&) = default;
		VariableRead& operator=(VariableRead&&) = default;
		VariableRead(VariableRead const& b)
			: identifier(b.identifier)
			, static_type(b.static_type)
			, type(b.type)
			, index(b.index)
			, constant(b.constant)
		{
		}
		VariableRead& operator=(VariableRead const& b)
		{
			if (this != &b)
			{
				identifier = b.identifier;
				static_type = b.static_type;
				type = b.type;
				index = b.index;
				constant = b.constant;
			}
			return *this;
		}

		std::unique_ptr<Expression> deep_copy() const override
		{
			return typed_deep_copy();
		}
		std::unique_ptr<VariableRead> typed_deep_copy() const
		{
			return std::make_unique<VariableRead>(*this);
		}

		void accept(ExpressionVisitor& visitor) override;
		void accept(ExpressionConstVisitor& visitor) const override;
		virtual TerminalData get_first_terminal() const override
		{
			return identifier;
		}
		virtual TerminalData get_last_terminal() const override
		{
			return identifier;
		}
	};

	// -----------------------------------------------------------------------------------------------
	// STATEMENTS ------------------------------------------------------------------------------------
	// -----------------------------------------------------------------------------------------------

	class Block final : public Statement
	{
	public:
		std::vector<std::unique_ptr<Statement>> statements;
		std::optional<TerminalData> open, close;
		bool is_global = false;

		Block() = default;
		Block(Block&&) = default;
		Block& operator=(Block&&) = default;
		Block(Block const& b)
			: open(b.open)
			, close(b.close)
			, is_global(b.is_global)
		{
			statements.resize(b.statements.size());

			for (int i = 0; i < statements.size(); ++i)
			{
				statements[i] = b.statements[i]->deep_copy();
			}
		}
		Block& operator=(Block const& b)
		{
			if (this != &b)
			{
				open = b.open;
				close = b.close;
				is_global = b.is_global;

				statements.resize(b.statements.size());

				for (int i = 0; i < statements.size(); ++i)
				{
					statements[i] = b.statements[i]->deep_copy();
				}
			}
			return *this;
		}

		std::unique_ptr<Statement> deep_copy() const override
		{
			return typed_deep_copy();
		}
		std::unique_ptr<Block> typed_deep_copy() const
		{
			return std::make_unique<Block>(*this);
		}

		void accept(StatementVisitor& visitor) override;
		void accept(StatementConstVisitor& visitor) const override;
		virtual TerminalData get_first_terminal() const override
		{
			if (open.has_value())
				return *open;
			else
				return statements.front()->get_first_terminal();
		}
		virtual TerminalData get_last_terminal() const override
		{
			if (close.has_value())
				return *close;
			else
				return statements.back()->get_last_terminal();
		}
	};

	class ExpressionStatement final : public Statement
	{
	public:
		std::unique_ptr<Expression> exp;
		TerminalData semicolon;

		ExpressionStatement() = default;
		ExpressionStatement(ExpressionStatement&&) = default;
		ExpressionStatement& operator=(ExpressionStatement&&) = default;
		ExpressionStatement(ExpressionStatement const& b)
			: exp(b.exp->deep_copy())
			, semicolon(b.semicolon)
		{
		}
		ExpressionStatement& operator=(ExpressionStatement const& b)
		{
			if (this != &b)
			{
				exp = b.exp->deep_copy();
				semicolon = b.semicolon;
			}
			return *this;
		}

		std::unique_ptr<Statement> deep_copy() const override
		{
			return typed_deep_copy();
		}
		std::unique_ptr<ExpressionStatement> typed_deep_copy() const
		{
			return std::make_unique<ExpressionStatement>(*this);
		}

		void accept(StatementVisitor& visitor) override;
		void accept(StatementConstVisitor& visitor) const override;
		virtual TerminalData get_first_terminal() const override
		{
			return exp->get_first_terminal();
		}
		virtual TerminalData get_last_terminal() const override
		{
			return semicolon;
		}
	};

	class VariableDefinition final : public Statement
	{
	public:
		TerminalData variable;
		std::optional<TerminalData> semicolon;
		std::optional<TypeRepresentation> type;
		std::unique_ptr<Expression> type_definition;
		std::unique_ptr<Expression> initialization;
		int index = -1;
		bool constant = false, explicitly_uninitialized = false;

		VariableDefinition() = default;
		VariableDefinition(VariableDefinition&&) = default;
		VariableDefinition& operator=(VariableDefinition&&) = default;
		VariableDefinition(VariableDefinition const& b)
			: variable(b.variable)
			, type(b.type)
			, type_definition(b.type_definition->deep_copy())
			, initialization(b.type_definition->deep_copy())
			, index(b.index)
			, constant(b.constant)
			, explicitly_uninitialized(b.explicitly_uninitialized)
		{
		}
		VariableDefinition& operator=(VariableDefinition const& b)
		{
			if (this != &b)
			{
				variable = b.variable;
				type = b.type;
				type_definition = b.type_definition->deep_copy();
				initialization = b.initialization->deep_copy();
				index = b.index;
				constant = b.constant;
				explicitly_uninitialized = b.explicitly_uninitialized;
			}
			return *this;
		}

		std::unique_ptr<Statement> deep_copy() const override
		{
			return typed_deep_copy();
		}
		std::unique_ptr<VariableDefinition> typed_deep_copy() const
		{
			return std::make_unique<VariableDefinition>(*this);
		}

		void accept(StatementVisitor& visitor) override;
		void accept(StatementConstVisitor& visitor) const override;
		virtual TerminalData get_first_terminal() const override
		{
			return variable;
		}
		virtual TerminalData get_last_terminal() const override
		{
			return semicolon.has_value() ? *semicolon : initialization != nullptr ? initialization->get_last_terminal() : type_definition->get_last_terminal();
		}
	};

	class ForeachStatement final : public Statement
	{
	public:
		TerminalData keyword;
		TerminalData tuple;
		std::unique_ptr<Expression> table;
		std::unique_ptr<Statement> body;
		bool constant = false;


		ForeachStatement() = default;
		ForeachStatement(ForeachStatement&&) = default;
		ForeachStatement& operator=(ForeachStatement&&) = default;
		ForeachStatement(ForeachStatement const& b)
			: keyword(b.keyword)
			, tuple(b.tuple)
			, table(b.table->deep_copy())
			, body(b.body->deep_copy())
			, constant(b.constant)
		{
		}
		ForeachStatement& operator=(ForeachStatement const& b)
		{
			if (this != &b)
			{
				keyword = b.keyword;
				tuple = b.tuple;
				table = b.table->deep_copy();
				body = b.body->deep_copy();
				constant = b.constant;
			}
			return *this;
		}

		std::unique_ptr<Statement> deep_copy() const override
		{
			return typed_deep_copy();
		}
		std::unique_ptr<ForeachStatement> typed_deep_copy() const
		{
			return std::make_unique<ForeachStatement>(*this);
		}

		void accept(StatementVisitor& visitor) override;
		void accept(StatementConstVisitor& visitor) const override;
		virtual TerminalData get_first_terminal() const override
		{
			return keyword;
		}
		virtual TerminalData get_last_terminal() const override
		{
			return body->get_last_terminal();
		}
	};

	class IfStatement final : public Statement
	{
	public:
		TerminalData if_keyword;
		std::unique_ptr<VariableDefinition> initialization;
		std::unique_ptr<Expression> condition;
		std::unique_ptr<Statement> yes, no;

		IfStatement() = default;
		IfStatement(IfStatement&&) = default;
		IfStatement& operator=(IfStatement&&) = default;
		IfStatement(IfStatement const& b)
			: if_keyword(b.if_keyword)
			, initialization(b.initialization != nullptr ? b.initialization->typed_deep_copy() : nullptr)
			, condition(b.condition != nullptr ? b.condition->deep_copy() : nullptr)
			, yes(b.yes->deep_copy())
			, no(b.no != nullptr ? b.no->deep_copy() : nullptr)
		{
		}
		IfStatement& operator=(IfStatement const& b)
		{
			if (this != &b)
			{
				if_keyword = b.if_keyword;
				initialization = b.initialization != nullptr ? b.initialization->typed_deep_copy() : nullptr;
				condition = b.condition != nullptr ? b.condition->deep_copy() : nullptr;
				yes = b.yes->deep_copy();
				no = b.no != nullptr ? b.no->deep_copy() : nullptr;
			}
			return *this;
		}

		std::unique_ptr<Statement> deep_copy() const override
		{
			return typed_deep_copy();
		}
		std::unique_ptr<IfStatement> typed_deep_copy() const
		{
			return std::make_unique<IfStatement>(*this);
		}

		void accept(StatementVisitor& visitor) override;
		void accept(StatementConstVisitor& visitor) const override;
		virtual TerminalData get_first_terminal() const override
		{
			return if_keyword;
		}
		virtual TerminalData get_last_terminal() const override
		{
			return (no != nullptr ? no : yes)->get_last_terminal();
		}
	};

	class ReturnStatement final : public Statement
	{
	public:
		TerminalData return_keyword;
		std::unique_ptr<Expression> exp;
		TerminalData semicolon;

		ReturnStatement() = default;
		ReturnStatement(ReturnStatement&&) = default;
		ReturnStatement& operator=(ReturnStatement&&) = default;
		ReturnStatement(ReturnStatement const& b)
			: return_keyword(b.return_keyword)
			, exp(b.exp->deep_copy())
			, semicolon(b.semicolon)
		{
		}
		ReturnStatement& operator=(ReturnStatement const& b)
		{
			if (this != &b)
			{
				return_keyword = b.return_keyword;
				exp = b.exp->deep_copy();
				semicolon = b.semicolon;
			}
			return *this;
		}

		std::unique_ptr<Statement> deep_copy() const override
		{
			return typed_deep_copy();
		}
		std::unique_ptr<ReturnStatement> typed_deep_copy() const
		{
			return std::make_unique<ReturnStatement>(*this);
		}

		void accept(StatementVisitor& visitor) override;
		void accept(StatementConstVisitor& visitor) const override;
		virtual TerminalData get_first_terminal() const override
		{
			return return_keyword;
		}
		virtual TerminalData get_last_terminal() const override
		{
			return semicolon;
		}
	};

	class WhileStatement final : public Statement
	{
	public:
		TerminalData while_keyword;
		std::optional<TerminalData> close_parenthesis;
		std::unique_ptr<Expression> condition;
		std::unique_ptr<Statement> body;
		bool do_while;

		WhileStatement() = default;
		WhileStatement(WhileStatement&&) = default;
		WhileStatement& operator=(WhileStatement&&) = default;
		WhileStatement(WhileStatement const& b)
			: while_keyword(b.while_keyword)
			, close_parenthesis(b.close_parenthesis)
			, condition(b.condition->deep_copy())
			, body(b.body->deep_copy())
			, do_while(b.do_while)
		{
		}
		WhileStatement& operator=(WhileStatement const& b)
		{
			if (this != &b)
			{
				while_keyword = b.while_keyword;
				close_parenthesis = b.close_parenthesis;
				condition = b.condition->deep_copy();
				body = b.body->deep_copy();
				do_while = b.do_while;
			}
			return *this;
		}

		std::unique_ptr<Statement> deep_copy() const override
		{
			return typed_deep_copy();
		}
		std::unique_ptr<WhileStatement> typed_deep_copy() const
		{
			return std::make_unique<WhileStatement>(*this);
		}

		void accept(StatementVisitor& visitor) override;
		void accept(StatementConstVisitor& visitor) const override;
		virtual TerminalData get_first_terminal() const override
		{
			return while_keyword;
		}
		virtual TerminalData get_last_terminal() const override
		{
			return do_while ? *close_parenthesis : body->get_last_terminal();
		}
	};


	// -----------------------------------------------------------------------------------------------
	// VISITORS --------------------------------------------------------------------------------------
	// -----------------------------------------------------------------------------------------------

	class ExpressionVisitor
	{
	public:
		virtual void visit(Binary& binary) = 0;
		virtual void visit(BuildInTypeDeclaration& build_in_type_declaration) = 0;
		virtual void visit(Call& call) = 0;
		virtual void visit(Cast& cast) = 0;
		virtual void visit(Grouping& grouping) = 0;
		virtual void visit(InitializerList& initializer_list) = 0;
		virtual void visit(Literal& literal) = 0;
		virtual void visit(MemberRead& member_read) = 0;
		virtual void visit(MemberWrite& member_write) = 0;
		virtual void visit(FunctionDeclaration& function_declaration) = 0;
		virtual void visit(FunctionTypeDeclaration& function_type_declaration) = 0;
		virtual void visit(TableDeclaration& table_declaration) = 0;
		virtual void visit(TupleDeclaration& tuple_declaration) = 0;
		virtual void visit(UnaryPre& unary_pre) = 0;
		virtual void visit(UnaryPost& unary_post) = 0;
		virtual void visit(VariableAssign& variable_assign) = 0;
		virtual void visit(VariableRead& variable_read) = 0;
	};
	class ExpressionConstVisitor
	{
	public:
		virtual void visit(Binary const& binary) = 0;
		virtual void visit(BuildInTypeDeclaration const& build_in_type_declaration) = 0;
		virtual void visit(Call const& call) = 0;
		virtual void visit(Cast const& cast) = 0;
		virtual void visit(Grouping const& grouping) = 0;
		virtual void visit(InitializerList const& initializer_list) = 0;
		virtual void visit(Literal const& literal) = 0;
		virtual void visit(MemberRead const& member_read) = 0;
		virtual void visit(MemberWrite const& member_write) = 0;
		virtual void visit(FunctionDeclaration const& function_declaration) = 0;
		virtual void visit(FunctionTypeDeclaration const& function_type_declaration) = 0;
		virtual void visit(TableDeclaration const& table_declaration) = 0;
		virtual void visit(TupleDeclaration const& tuple_declaration) = 0;
		virtual void visit(UnaryPre const& unary_pre) = 0;
		virtual void visit(UnaryPost const& unary_post) = 0;
		virtual void visit(VariableAssign const& variable_assign) = 0;
		virtual void visit(VariableRead const& variable_read) = 0;
	};
	class StatementVisitor
	{
	public:
		virtual void visit(Block& binary) = 0;
		virtual void visit(ExpressionStatement& binary) = 0;
		virtual void visit(ForeachStatement& binary) = 0;
		virtual void visit(IfStatement& binary) = 0;
		virtual void visit(ReturnStatement& binary) = 0;
		virtual void visit(VariableDefinition& binary) = 0;
		virtual void visit(WhileStatement& binary) = 0;
	};
	class StatementConstVisitor
	{
	public:
		virtual void visit(Block const& binary) = 0;
		virtual void visit(ExpressionStatement const& binary) = 0;
		virtual void visit(ForeachStatement const& binary) = 0;
		virtual void visit(IfStatement const& binary) = 0;
		virtual void visit(ReturnStatement const& binary) = 0;
		virtual void visit(VariableDefinition const& binary) = 0;
		virtual void visit(WhileStatement const& binary) = 0;
	};
}

using namespace minairo;

// ------------------------------------------------------------------------------------------------
FunctionDeclaration::FunctionDeclaration(FunctionDeclaration const& b)
	: header(b.header->typed_deep_copy())
	, body(b.body->typed_deep_copy())
{
}
FunctionDeclaration& FunctionDeclaration::operator=(FunctionDeclaration const& b)
{
	if (this != &b)
	{
		header = b.header->typed_deep_copy();
		body = b.body->typed_deep_copy();
	}
	return *this;
}
TerminalData FunctionDeclaration::get_last_terminal() const
{
	return body->get_last_terminal();
}
// ------------------------------------------------------------------------------------------------
void Binary::accept(ExpressionVisitor& visitor)
{
	visitor.visit(*this);
}
void BuildInTypeDeclaration::accept(ExpressionVisitor& visitor)
{
	visitor.visit(*this);
}
void Call::accept(ExpressionVisitor& visitor)
{
	visitor.visit(*this);
}
void Cast::accept(ExpressionVisitor& visitor)
{
	visitor.visit(*this);
}
void Grouping::accept(ExpressionVisitor& visitor)
{
	visitor.visit(*this);
}
void InitializerList::accept(ExpressionVisitor& visitor)
{
	visitor.visit(*this);
}
void Literal::accept(ExpressionVisitor& visitor)
{
	visitor.visit(*this);
}
void MemberRead::accept(ExpressionVisitor& visitor)
{
	visitor.visit(*this);
}
void MemberWrite::accept(ExpressionVisitor& visitor)
{
	visitor.visit(*this);
}
void FunctionDeclaration::accept(ExpressionVisitor& visitor)
{
	visitor.visit(*this);
}
void FunctionTypeDeclaration::accept(ExpressionVisitor& visitor)
{
	visitor.visit(*this);
}
void TableDeclaration::accept(ExpressionVisitor& visitor)
{
	visitor.visit(*this);
}
void TupleDeclaration::accept(ExpressionVisitor& visitor)
{
	visitor.visit(*this);
}
void UnaryPre::accept(ExpressionVisitor& visitor)
{
	visitor.visit(*this);
}
void UnaryPost::accept(ExpressionVisitor& visitor)
{
	visitor.visit(*this);
}
void VariableAssign::accept(ExpressionVisitor& visitor)
{
	visitor.visit(*this);
}
void VariableRead::accept(ExpressionVisitor& visitor)
{
	visitor.visit(*this);
}
// ------------------------------------------------------------------------------------------------
void Binary::accept(ExpressionConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void BuildInTypeDeclaration::accept(ExpressionConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void Call::accept(ExpressionConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void Cast::accept(ExpressionConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void Grouping::accept(ExpressionConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void InitializerList::accept(ExpressionConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void Literal::accept(ExpressionConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void MemberRead::accept(ExpressionConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void MemberWrite::accept(ExpressionConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void FunctionDeclaration::accept(ExpressionConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void FunctionTypeDeclaration::accept(ExpressionConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void TableDeclaration::accept(ExpressionConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void TupleDeclaration::accept(ExpressionConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void UnaryPre::accept(ExpressionConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void UnaryPost::accept(ExpressionConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void VariableAssign::accept(ExpressionConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void VariableRead::accept(ExpressionConstVisitor& visitor) const
{
	visitor.visit(*this);
}
// ------------------------------------------------------------------------------------------------
void Block::accept(StatementVisitor& visitor)
{
	visitor.visit(*this);
}
void ExpressionStatement::accept(StatementVisitor& visitor)
{
	visitor.visit(*this);
}
void ForeachStatement::accept(StatementVisitor& visitor)
{
	visitor.visit(*this);
}
void IfStatement::accept(StatementVisitor& visitor)
{
	visitor.visit(*this);
}
void ReturnStatement::accept(StatementVisitor& visitor)
{
	visitor.visit(*this);
}
void VariableDefinition::accept(StatementVisitor& visitor)
{
	visitor.visit(*this);
}
void WhileStatement::accept(StatementVisitor& visitor)
{
	visitor.visit(*this);
}
// ------------------------------------------------------------------------------------------------
void Block::accept(StatementConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void ExpressionStatement::accept(StatementConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void ForeachStatement::accept(StatementConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void IfStatement::accept(StatementConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void ReturnStatement::accept(StatementConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void VariableDefinition::accept(StatementConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void WhileStatement::accept(StatementConstVisitor& visitor) const
{
	visitor.visit(*this);
}
