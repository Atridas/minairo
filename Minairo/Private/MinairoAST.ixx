module;

#include <cinttypes>

#include <memory>
#include <string>
#include <variant>

export module Minairo.AST;

import Minairo.Scanner;
import Minairo.TypeRepresentation;

export namespace minairo
{
	class ExpressionVisitor;

	class Expression
	{
	public:
		virtual void accept(ExpressionVisitor& visitor) const = 0;

		virtual TerminalData get_first_terminal() const = 0;
		virtual TerminalData get_last_terminal() const = 0;
	};

	class Binary final : public Expression
	{
	public:
		std::unique_ptr<Expression> left, right;
		Terminal op;

		void accept(ExpressionVisitor& visitor) const override;
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

		void accept(ExpressionVisitor& visitor) const override;
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

		void accept(ExpressionVisitor& visitor) const override;
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
		Terminal op;
		std::unique_ptr<Expression> exp;

		void accept(ExpressionVisitor& visitor) const override;
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
		Terminal op;

		void accept(ExpressionVisitor& visitor) const override;
		virtual TerminalData get_first_terminal() const override
		{
			return exp->get_last_terminal();
		}
		virtual TerminalData get_last_terminal() const override
		{
			return op;
		}
	};

	class ExpressionVisitor
	{
	public:
		virtual void visit(Binary const& binary) = 0;
		virtual void visit(Grouping const& grouping) = 0;
		virtual void visit(Literal const& literal) = 0;
		virtual void visit(UnaryPre const& unary_pre) = 0;
		virtual void visit(UnaryPost const& unary_post) = 0;
	};
}


void minairo::Binary::accept(ExpressionVisitor& visitor) const
{
	visitor.visit(*this);
}
void minairo::Literal::accept(ExpressionVisitor& visitor) const
{
	visitor.visit(*this);
}
void minairo::Grouping::accept(ExpressionVisitor& visitor) const
{
	visitor.visit(*this);
}
void minairo::UnaryPre::accept(ExpressionVisitor& visitor) const
{
	visitor.visit(*this);
}
void minairo::UnaryPost::accept(ExpressionVisitor& visitor) const
{
	visitor.visit(*this);
}
