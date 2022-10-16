module;

#include <cinttypes>

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

export module Minairo.AST;

import Minairo.FunctionRepresentation;
import Minairo.Scanner;
import Minairo.TypeRepresentation;

export namespace minairo
{
	class ExpressionVisitor;
	class ExpressionConstVisitor;
	class StatementVisitor;
	class StatementConstVisitor;

	// -----------------------------------------------------------------------------------------------
	// EXPRESSIONS -----------------------------------------------------------------------------------
	// -----------------------------------------------------------------------------------------------

	class Expression
	{
	public:
		virtual void accept(ExpressionVisitor& visitor) = 0;
		virtual void accept(ExpressionConstVisitor& visitor) const = 0;

		virtual std::optional<TypeRepresentation> get_expression_type() const = 0;
		virtual TerminalData get_first_terminal() const = 0;
		virtual TerminalData get_last_terminal() const = 0;
	};

	class Binary final : public Expression
	{
	public:
		std::unique_ptr<Expression> left, right;
		FunctionRepresentation const* function_to_call = nullptr;
		Terminal op;

		void accept(ExpressionVisitor& visitor) override;
		void accept(ExpressionConstVisitor& visitor) const override;
		virtual std::optional<TypeRepresentation> get_expression_type() const override
		{
			if (function_to_call == nullptr)
				return std::nullopt;
			else
				return function_to_call->get_return_type();
		}
		virtual TerminalData get_first_terminal() const override
		{
			return left->get_first_terminal();
		}
		virtual TerminalData get_last_terminal() const override
		{
			return right->get_last_terminal();
		}
	};

	class Grouping final : public Expression
	{
	public:
		std::unique_ptr<Expression> expr;
		TerminalData open, close;

		void accept(ExpressionVisitor& visitor) override;
		void accept(ExpressionConstVisitor& visitor) const override;
		virtual std::optional<TypeRepresentation> get_expression_type() const override
		{
			return expr->get_expression_type();
		}
		virtual TerminalData get_first_terminal() const override
		{
			return open;
		}
		virtual TerminalData get_last_terminal() const override
		{
			return close;
		}
	};

	class Literal final : public Expression
	{
	public:
		std::variant<uint64_t, double, std::string, char32_t, bool> value;
		TypeRepresentation type_representation;
		TerminalData terminal;

		void accept(ExpressionVisitor& visitor) override;
		void accept(ExpressionConstVisitor& visitor) const override;
		virtual std::optional<TypeRepresentation> get_expression_type() const override
		{
			return type_representation;
		}
		virtual TerminalData get_first_terminal() const override
		{
			return terminal;
		}
		virtual TerminalData get_last_terminal() const override
		{
			return terminal;
		}
	};

	class UnaryPre final : public Expression
	{
	public:
		TerminalData op;
		std::unique_ptr<Expression> exp;
		FunctionRepresentation const* function_to_call = nullptr;

		void accept(ExpressionVisitor& visitor) override;
		void accept(ExpressionConstVisitor& visitor) const override;
		virtual std::optional<TypeRepresentation> get_expression_type() const override
		{
			if (function_to_call == nullptr)
				return std::nullopt;
			else
				return function_to_call->get_return_type();
		}
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

		void accept(ExpressionVisitor& visitor) override;
		void accept(ExpressionConstVisitor& visitor) const override;
		virtual std::optional<TypeRepresentation> get_expression_type() const override
		{
			if (function_to_call == nullptr)
				return std::nullopt;
			else
				return function_to_call->get_return_type();
		}
		virtual TerminalData get_first_terminal() const override
		{
			return exp->get_last_terminal();
		}
		virtual TerminalData get_last_terminal() const override
		{
			return op;
		}
	};

	class VariableRead final : public Expression
	{
	public:
		TerminalData identifier;
		std::optional<TypeRepresentation> type;
		int index = -1;

		void accept(ExpressionVisitor& visitor) override;
		void accept(ExpressionConstVisitor& visitor) const override;
		virtual std::optional<TypeRepresentation> get_expression_type() const override
		{
			return type;
		}
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

	class Statement
	{
	public:
		virtual void accept(StatementVisitor& visitor) = 0;
		virtual void accept(StatementConstVisitor& visitor) const = 0;

		virtual TerminalData get_first_terminal() const = 0;
		virtual TerminalData get_last_terminal() const = 0;
	};

	// TODO "global" block?
	class Block final : public Statement
	{
	public:
		std::vector<std::unique_ptr<Statement>> statements;
		std::optional<TerminalData> open, close;
		bool is_global = false;

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

		void accept(StatementVisitor& visitor) override;
		void accept(StatementConstVisitor& visitor) const override;
		virtual TerminalData get_first_terminal() const override
		{
			return exp->get_last_terminal();
		}
		virtual TerminalData get_last_terminal() const override
		{
			return semicolon;
		}
	};

	class VariableDefinition final : public Statement
	{
	public:
		// TODO store precomputed hash(?)
		TerminalData variable, semicolon;
		TypeRepresentation type = BuildInType::Void;
		std::unique_ptr<Expression> initialization;
		int index = -1;
		bool constant = false, explicitly_uninitialized = false;

		void accept(StatementVisitor& visitor) override;
		void accept(StatementConstVisitor& visitor) const override;
		virtual TerminalData get_first_terminal() const override
		{
			return variable;
		}
		virtual TerminalData get_last_terminal() const override
		{
			return semicolon;
		}
	};


	// -----------------------------------------------------------------------------------------------
	// VISITORS --------------------------------------------------------------------------------------
	// -----------------------------------------------------------------------------------------------

	class ExpressionVisitor
	{
	public:
		virtual void visit(Binary& binary) = 0;
		virtual void visit(Grouping& grouping) = 0;
		virtual void visit(Literal& literal) = 0;
		virtual void visit(UnaryPre& unary_pre) = 0;
		virtual void visit(UnaryPost& unary_post) = 0;
		virtual void visit(VariableRead& unary_post) = 0;
	};
	class ExpressionConstVisitor
	{
	public:
		virtual void visit(Binary const& binary) = 0;
		virtual void visit(Grouping const& grouping) = 0;
		virtual void visit(Literal const& literal) = 0;
		virtual void visit(UnaryPre const& unary_pre) = 0;
		virtual void visit(UnaryPost const& unary_post) = 0;
		virtual void visit(VariableRead const& unary_post) = 0;
	};
	class StatementVisitor
	{
	public:
		virtual void visit(Block& binary) = 0;
		virtual void visit(ExpressionStatement& binary) = 0;
		virtual void visit(VariableDefinition& binary) = 0;
	};
	class StatementConstVisitor
	{
	public:
		virtual void visit(Block const& binary) = 0;
		virtual void visit(ExpressionStatement const& binary) = 0;
		virtual void visit(VariableDefinition const& binary) = 0;
	};
}


// ------------------------------------------------------------------------------------------------
void minairo::Binary::accept(ExpressionVisitor& visitor)
{
	visitor.visit(*this);
}
void minairo::Literal::accept(ExpressionVisitor& visitor)
{
	visitor.visit(*this);
}
void minairo::Grouping::accept(ExpressionVisitor& visitor)
{
	visitor.visit(*this);
}
void minairo::UnaryPre::accept(ExpressionVisitor& visitor)
{
	visitor.visit(*this);
}
void minairo::UnaryPost::accept(ExpressionVisitor& visitor)
{
	visitor.visit(*this);
}
void minairo::VariableRead::accept(ExpressionVisitor& visitor)
{
	visitor.visit(*this);
}
// ------------------------------------------------------------------------------------------------
void minairo::Binary::accept(ExpressionConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void minairo::Literal::accept(ExpressionConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void minairo::Grouping::accept(ExpressionConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void minairo::UnaryPre::accept(ExpressionConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void minairo::UnaryPost::accept(ExpressionConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void minairo::VariableRead::accept(ExpressionConstVisitor& visitor) const
{
	visitor.visit(*this);
}
// ------------------------------------------------------------------------------------------------
void minairo::Block::accept(StatementVisitor& visitor)
{
	visitor.visit(*this);
}
void minairo::ExpressionStatement::accept(StatementVisitor& visitor)
{
	visitor.visit(*this);
}
void minairo::VariableDefinition::accept(StatementVisitor& visitor)
{
	visitor.visit(*this);
}
// ------------------------------------------------------------------------------------------------
void minairo::Block::accept(StatementConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void minairo::ExpressionStatement::accept(StatementConstVisitor& visitor) const
{
	visitor.visit(*this);
}
void minairo::VariableDefinition::accept(StatementConstVisitor& visitor) const
{
	visitor.visit(*this);
}