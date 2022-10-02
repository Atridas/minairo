module;

#include <cinttypes>

#include <memory>
#include <string>
#include <variant>

export module Minairo.AST;

import Minairo.Scanner;

export namespace minairo
{
	class ExpressionVisitor;

	class Expression
	{
	public:
		TerminalData first_terminal, last_terminal;

		virtual void accept(ExpressionVisitor& visitor) const = 0;
	};

	class Binary final : public Expression
	{
	public:
		std::unique_ptr<Expression> left, right;
		Terminal op;

		void accept(ExpressionVisitor& visitor) const override;
	};

	class Grouping final : public Expression
	{
	public:
		std::unique_ptr<Expression> expr;

		void accept(ExpressionVisitor& visitor) const override;
	};

	class Literal final : public Expression
	{
	public:
		std::variant<uint64_t, double, std::string, char32_t, bool> value;

		void accept(ExpressionVisitor& visitor) const override;
	};

	class UnaryPre final : public Expression
	{
	public:
		std::unique_ptr<Expression> exp;
		Terminal op;

		void accept(ExpressionVisitor& visitor) const override;
	};

	class UnaryPost final : public Expression
	{
	public:
		std::unique_ptr<Expression> exp;
		Terminal op;

		void accept(ExpressionVisitor& visitor) const override;
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
