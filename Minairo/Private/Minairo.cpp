module;

#include <cassert>

#include <iostream>
#include <memory>
#include <string_view>
#include <type_traits>
#include <variant>

module Minairo;

import Minairo.AST;
import Minairo.AST.Interpreter;
import Minairo.Scanner;

namespace minairo
{
	namespace {
		using ExpressionPtr = std::unique_ptr<Expression>;

		// ------------------------------------------------------------------------------------
		// ------------------------------------------------------------------------------------
		// ------------------------------------------------------------------------------------

		void consume(Terminal terminal, Scanner& scanner)
		{
			TerminalData symbol = scanner.get_next_symbol();
			if (symbol.type != terminal)
			{
				// TODO
				throw 0;
			}
		}

		// ------------------------------------------------------------------------------------
		// ------------------------------------------------------------------------------------
		// ------------------------------------------------------------------------------------

		ExpressionPtr expression(Scanner& scanner);

		// ------------------------------------------------------------------------------------

		Literal generate_literal(TerminalData const& terminal)
		{
			Literal result;
			result.first_terminal = result.last_terminal = terminal;
			return result;
		}

		Literal parse_integer(TerminalData terminal)
		{
			Literal result = generate_literal(terminal);

			// TODO U, L, LL, Z

			if (terminal.text[0] == '0')
			{
				if (terminal.text.size() == 1)
				{
					result.value = (uint64_t)0;
				}
				else if (terminal.text[1] == 'x' || terminal.text[1] == 'X')
				{
					// hex literal
					uint64_t value = 0;
					for (char c : terminal.text)
					{
						if (c != '\'')
						{
							value *= 16;
							if(c >= '0' && c <= '9')
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
					result.value = value;
				}
				else if (terminal.text[1] == 'b' || terminal.text[1] == 'B')
				{
					// binary literal
					uint64_t value = 0;
					for (char c : terminal.text)
					{
						if (c != '\'')
						{
							assert(c == '0' || c == '1');
							value *= 2;
							value += c - '0';
						}
					}
					result.value = value;
				}
				else
				{
					// octal literal
					uint64_t value = 0;
					for (char c : terminal.text)
					{
						if (c != '\'')
						{
							assert(c >= '0' && c <= '7');
							value *= 8;
							value += c - '0';
						}
					}
					result.value = value;
				}
			}
			else
			{
				// decimal literal
				uint64_t value = 0;
				for (char c : terminal.text)
				{
					if (c != '\'')
					{
						assert(c >= '0' && c <= '9');
						value *= 10;
						value += c - '0';
					}
				}
				result.value = value;
			}

			return result;
		}
		Literal parse_float(TerminalData terminal)
		{
			Literal result = generate_literal(terminal);
			assert(false); // TODO
			return result;
		}
		Literal parse_char(TerminalData terminal)
		{
			Literal result = generate_literal(terminal);
			assert(false); // TODO
			return result;
		}
		Literal parse_string(TerminalData terminal)
		{
			Literal result = generate_literal(terminal);
			assert(false); // TODO
			return result;
		}
		Literal parse_bool(TerminalData terminal)
		{
			Literal result = generate_literal(terminal);

			if (terminal.text == "true")
			{
				result.value = true;
			}
			else
			{
				result.value = false;
			}
			return result;
		}

		ExpressionPtr primary(Scanner& scanner)
		{
			switch (scanner.peek_next_symbol().type)
			{
			case Terminal::INTEGER_LITERAL: return std::make_unique<Literal>(parse_integer(scanner.get_next_symbol()));
			case Terminal::FLOAT_LITERAL: return std::make_unique<Literal>(parse_float(scanner.get_next_symbol()));
			case Terminal::CHAR_LITERAL: return std::make_unique<Literal>(parse_char(scanner.get_next_symbol()));
			case Terminal::STRING_LITERAL: return std::make_unique<Literal>(parse_string(scanner.get_next_symbol()));
			case Terminal::BOOL_LITERAL: return std::make_unique<Literal>(parse_bool(scanner.get_next_symbol()));
			case Terminal::IDENTIFIER: break;// TODO
			case Terminal::OP_PARENTHESIS_OPEN:
			{
				scanner.get_next_symbol();
				ExpressionPtr result = expression(scanner);
				consume(Terminal::OP_PARENTHESIS_CLOSE, scanner);
				return result;
			}
			default:
			assert(false); // TODO
			}

			return nullptr;
		}

		// ------------------------------------------------------------------------------------

		ExpressionPtr binary(Scanner& scanner)
		{
			ExpressionPtr left = primary(scanner);
			Terminal op = Terminal::END;
			switch (scanner.peek_next_symbol().type)
			{
			case Terminal::OP_ADD:
				op = Terminal::OP_ADD;
				break;
				//TODO
			}

			if (op != Terminal::END)
			{
				consume(op, scanner);

				auto binary = std::make_unique<Binary>();
				binary->left = std::move(left);
				binary->right = primary(scanner);
				binary->op = op;

				binary->first_terminal = binary->left->first_terminal;
				binary->last_terminal = binary->right->last_terminal;

				return binary;
			}
			else
			{
				return left;
			}
		}

		// ------------------------------------------------------------------------------------

		ExpressionPtr expression(Scanner& scanner)
		{
			return primary(scanner);
		}

		// ------------------------------------------------------------------------------------

		ExpressionPtr generate_AST(Scanner code)
		{
			return binary(code);
		}
	}

	void interpret(std::string_view code)
	{
		std::cout << "interpreting " << code << std::endl;


		ExpressionPtr expression = generate_AST(code);


		Interpreter interpreter;
		expression->accept(interpreter);

		std::visit([] <typename T>(T value) {
			if constexpr (std::is_same_v<T, uint64_t>)
			{
				std::cout << "uint64 " << value << std::endl;
			}
		}, interpreter.get_last_expression_value());

	}
}
