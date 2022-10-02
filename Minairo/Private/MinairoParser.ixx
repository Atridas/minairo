module;

#include <cassert>

#include <iostream>
#include <memory>
#include <string_view>
#include <type_traits>
#include <variant>
#include <vector>

export module Minairo.Parser;

import Minairo.AST;
import Minairo.AST.Interpreter;
import Minairo.Scanner;

namespace minairo
{
	namespace
	{
		using ExpressionPtr = std::unique_ptr<Expression>;

		// ------------------------------------------------------------------------------------
		// ------------------------------------------------------------------------------------
		// ------------------------------------------------------------------------------------

		TerminalData consume(Terminal terminal, Scanner& scanner)
		{
			TerminalData symbol = scanner.get_next_symbol();
			if (symbol.type != terminal)
			{
				// TODO
				throw 0;
			}
			return symbol;
		}

		// ------------------------------------------------------------------------------------
		// ------------------------------------------------------------------------------------
		// ------------------------------------------------------------------------------------

		enum class Precedence
		{
			None,
			Assignment,
			Or,
			And,
			Equality,
			Comparison,
			Term,
			Factor,
			Unary,
			Call,
			Primary
		};
		ExpressionPtr parse_precedence(Scanner& scanner, Precedence precedence);
		ExpressionPtr expression(Scanner& scanner);

		// ------------------------------------------------------------------------------------
		

		// ------------------------------------------------------------------------------------
		// ------------------------------------------------------------------------------------
		// ------------------------------------------------------------------------------------

		bool operator<=(Precedence a, Precedence b)
		{
			return (int)a <= (int)b;
		}
		Precedence operator+(Precedence a, int i)
		{
			return (Precedence)((int)a + i);
		}

		// ------------------------------------------------------------------------------------
		// ------------------------------------------------------------------------------------
		// ------------------------------------------------------------------------------------

		ExpressionPtr grouping(Scanner& scanner)
		{
			auto result = std::make_unique<Grouping>();
			result->open = consume(Terminal::OP_PARENTHESIS_OPEN, scanner);
			result->expr = expression(scanner);
			result->close = consume(Terminal::OP_PARENTHESIS_CLOSE, scanner);
			return result;
		}

		ExpressionPtr integer_literal(Scanner& scanner)
		{
			auto result = std::make_unique<Literal>();
			result->terminal = consume(Terminal::INTEGER_LITERAL, scanner);
			// TODO U, L, LL, Z

			if (result->terminal.text[0] == '0')
			{
				if (result->terminal.text.size() == 1)
				{
					result->value = (uint64_t)0;
				}
				else if (result->terminal.text[1] == 'x' || result->terminal.text[1] == 'X')
				{
					// hex literal
					uint64_t value = 0;
					for (char c : result->terminal.text)
					{
						if (c != '\'' && c != 'x' && c != 'X')
						{
							value *= 16;
							if (c >= '0' && c <= '9')
								value += c - '0';
							else if (c >= 'a' && c <= 'f')
								value += c - 'a' + 10;
							else
							{
								assert(c >= 'A' && c <= 'F');
								value += c - 'A' + 10;
							}
						}
					}
					result->value = value;
				}
				else if (result->terminal.text[1] == 'b' || result->terminal.text[1] == 'B')
				{
					// binary literal
					uint64_t value = 0;
					for (char c : result->terminal.text)
					{
						if (c != '\'' && c != 'b' && c != 'B')
						{
							assert(c == '0' || c == '1');
							value *= 2;
							value += c - '0';
						}
					}
					result->value = value;
				}
				else
				{
					// octal literal
					uint64_t value = 0;
					for (char c : result->terminal.text)
					{
						if (c != '\'')
						{
							assert(c >= '0' && c <= '7');
							value *= 8;
							value += c - '0';
						}
					}
					result->value = value;
				}
			}
			else
			{
				// decimal literal
				uint64_t value = 0;
				for (char c : result->terminal.text)
				{
					if (c != '\'')
					{
						assert(c >= '0' && c <= '9');
						value *= 10;
						value += c - '0';
					}
				}
				result->value = value;
			}

			return result;
		}

		ExpressionPtr unary(Scanner& scanner)
		{
			TerminalData op = scanner.get_next_symbol();
			
			auto result = std::make_unique<UnaryPre>();
			result->exp = expression(scanner);
			result->op = op.type;

			return result;
		}


		// ------------------------------------------------------------------------------------
		
		ExpressionPtr binary(ExpressionPtr left, Precedence current_precendence, Scanner& scanner)
		{
			auto result = std::make_unique<Binary>();
			result->left = std::move(left);
			result->op = scanner.get_next_symbol().type;
			result->right = parse_precedence(scanner, current_precendence + 1);

			return result; // TODO
		}


		// ------------------------------------------------------------------------------------
		// ------------------------------------------------------------------------------------
		// ------------------------------------------------------------------------------------

		using PrattPrefix = ExpressionPtr(*)(Scanner& scanner);
		using PrattInfix = ExpressionPtr(*)(ExpressionPtr left, Precedence current_precendence, Scanner& scanner);

		PrattPrefix pratt_prefixes[(int)Terminal::COUNT] = {};
		PrattInfix pratt_infixes[(int)Terminal::COUNT] = {};
		Precedence pratt_precedences[(int)Terminal::COUNT] = {};

		void initialize_pratt_parser()
		{
			pratt_prefixes[(int)Terminal::OP_PARENTHESIS_OPEN] = &grouping;
			pratt_prefixes[(int)Terminal::OP_SUB] = &unary;
			pratt_prefixes[(int)Terminal::OP_ADD] = &unary;
			pratt_prefixes[(int)Terminal::OP_NOT] = &unary;
			pratt_prefixes[(int)Terminal::OP_BIT_NOT] = &unary;
			pratt_prefixes[(int)Terminal::INTEGER_LITERAL] = &integer_literal;

			//	case Terminal::FLOAT_LITERAL: return std::make_unique<Literal>(parse_float(scanner.get_next_symbol()));
			//	case Terminal::CHAR_LITERAL: return std::make_unique<Literal>(parse_char(scanner.get_next_symbol()));
			//	case Terminal::STRING_LITERAL: return std::make_unique<Literal>(parse_string(scanner.get_next_symbol()));
			//	case Terminal::BOOL_LITERAL: return std::make_unique<Literal>(parse_bool(scanner.get_next_symbol()));

			pratt_infixes[(int)Terminal::OP_ADD] = &binary;
			pratt_precedences[(int)Terminal::OP_ADD] = Precedence::Term;
			pratt_infixes[(int)Terminal::OP_SUB] = &binary;
			pratt_precedences[(int)Terminal::OP_SUB] = Precedence::Term;
			pratt_infixes[(int)Terminal::OP_MUL] = &binary;
			pratt_precedences[(int)Terminal::OP_MUL] = Precedence::Factor;
			pratt_infixes[(int)Terminal::OP_DIV] = &binary;
			pratt_precedences[(int)Terminal::OP_DIV] = Precedence::Factor;
			pratt_infixes[(int)Terminal::OP_MOD] = &binary;
			pratt_precedences[(int)Terminal::OP_MOD] = Precedence::Factor;
		}


		// ------------------------------------------------------------------------------------
		// ------------------------------------------------------------------------------------
		// ------------------------------------------------------------------------------------

		ExpressionPtr parse_precedence(Scanner& scanner, Precedence precedence)
		{
			PrattPrefix prefix_rule = pratt_prefixes[(int)scanner.peek_next_symbol().type];
			if (prefix_rule == nullptr)
			{
				// TODO
				throw 0;
			}
			ExpressionPtr result = prefix_rule(scanner);

			while (precedence <= pratt_precedences[(int)scanner.peek_next_symbol().type])
			{
				PrattInfix infix_rule = pratt_infixes[(int)scanner.peek_next_symbol().type];
				result = infix_rule(std::move(result), pratt_precedences[(int)scanner.peek_next_symbol().type], scanner);
			}

			return result;
		}

		// ------------------------------------------------------------------------------------

		ExpressionPtr expression(Scanner& scanner)
		{
			return parse_precedence(scanner, Precedence::Assignment);
		}

		// ------------------------------------------------------------------------------------
	}

	export ExpressionPtr generate_AST(Scanner code)
	{
		initialize_pratt_parser();
		return expression(code);
	}
}
