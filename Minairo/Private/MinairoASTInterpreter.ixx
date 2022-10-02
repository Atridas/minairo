module;

#include <cassert>
#include <cinttypes>

#include <memory>
#include <string>
#include <variant>

export module Minairo.AST.Interpreter;

import Minairo.AST;
import Minairo.Scanner;

export namespace minairo
{
	class Interpreter : public ExpressionVisitor
	{
	public:
		using Value = std::variant<int64_t, uint64_t, double, std::string, char32_t, bool>;

		Value get_last_expression_value() const noexcept { return last_expression_value; }


		void visit(Binary const& binary) override
		{
			binary.left->accept(*this);
			Value left = last_expression_value;
			binary.right->accept(*this);

			switch (binary.op)
			{
			case Terminal::OP_ADD:
			{
				if (std::holds_alternative<uint64_t>(left) && std::holds_alternative<uint64_t>(last_expression_value))
				{
					last_expression_value = std::get<uint64_t>(left) + std::get<uint64_t>(last_expression_value);
				}
				else
				{
					assert(false); // TODO
				}
				break;
			}
			default:
				assert(false); // TODO
			}
		}
		void visit(Grouping const& grouping) override
		{
			grouping.expr->accept(*this);
		}
		void visit(Literal const& literal) override
		{
			std::visit([this](auto&& v) { last_expression_value = v; }, literal.value);
		}
		void visit(UnaryPre const& unary_pre) override
		{

		}
		void visit(UnaryPost const& unary_post) override
		{

		}


	private:
		Value last_expression_value;
	};
}
