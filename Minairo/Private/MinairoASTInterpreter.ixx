module;

#include <cassert>
#include <cinttypes>

#include <memory>
#include <string>
#include <variant>

export module Minairo.AST.Interpreter;

import Minairo.AST;
import Minairo.FunctionRepresentation;
import Minairo.Scanner;
import Minairo.TypeRepresentation;

export namespace minairo
{
	class Interpreter : public ExpressionVisitor
	{
	public:
		explicit Interpreter(FunctionMap _function_map) : function_map(std::move(_function_map)) {}


		using Value = std::variant<int64_t, uint64_t, double, std::string, char32_t, bool>;

		Value get_last_expression_value() const noexcept { return last_expression_value; }


		void visit(Binary const& binary) override
		{
			binary.left->accept(*this);
			Value left = last_expression_value;
			binary.right->accept(*this);

			// TODO get the actual argument types
			TypeRepresentation argument_types[2] = { get_type_representation<uint64_t>(), get_type_representation<uint64_t>() };
			FunctionRepresentation const* function = nullptr;

			switch (binary.op)
			{
			case Terminal::OP_ADD:
			{
				function = function_map.get("operator+", argument_types);
				break;
			}
			case Terminal::OP_SUB:
			{
				function = function_map.get("operator-", argument_types);
				break;
			}
			case Terminal::OP_MUL:
			{
				function = function_map.get("operator*", argument_types);
				break;
			}
			case Terminal::OP_DIV:
			{
				function = function_map.get("operator/", argument_types);
				break;
			}
			case Terminal::OP_MOD:
			{
				function = function_map.get("operator%", argument_types);
				//last_expression_value = std::get<uint64_t>(left) % std::get<uint64_t>(last_expression_value);
				break;
			}
			default:
				assert(false); // TODO
			}

			// TODO get the actual argument types
			FunctionRepresentationWithArgs<uint64_t, uint64_t> const* ft = (FunctionRepresentationWithArgs<uint64_t, uint64_t>*)function;
			// TODO actual result type
			uint64_t result;
			ft->call(&result, std::get<uint64_t>(left), std::get<uint64_t>(last_expression_value));
			last_expression_value = result;

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
		FunctionMap function_map;
		Value last_expression_value;
	};
}
