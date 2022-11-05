module;

#include <cassert>

#include <iostream>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>
#include <variant>
#include <vector>

export module Minairo.Parser;

import Minairo.AST;
import Minairo.AST.Interpreter;
import Minairo.Exception;
import Minairo.Scanner;
import Minairo.TypesAndValues;

namespace minairo
{
	using ExpressionPtr = std::unique_ptr<Expression>;
	using StatementPtr = std::unique_ptr<Statement>;

	export StatementPtr generate_AST(Scanner code);
	export struct ParseException;

	StatementPtr statement(Scanner& scanner);

	// ------------------------------------------------------------------------------------
	// ------------------------------------------------------------------------------------
	// ------------------------------------------------------------------------------------

	struct ParseException
	{
		enum class Type
		{
			UnexpectedEnd,
			ScannerError,
			UnexpectedTerminal,
			UnexpectedType,
			UnexpectedPrefix
		} type;

		Terminal terminal;
		TerminalData terminal_data;

		std::string print_error()
		{
			std::stringstream ss;
			switch (type)
			{
			case Type::UnexpectedEnd:
				ss << "Encountered the end of the file while waiting for a " << to_string(terminal);
				break;
			case Type::ScannerError:
				ss << "Encountered an scanner error while waiting for a " << to_string(terminal) << '\n';
				print_error_line(ss, terminal_data);
				break;
			case Type::UnexpectedTerminal:
				ss << "Encountered a " << to_string(terminal_data.type) << " while waiting for a " << to_string(terminal) << '\n';
				print_error_line(ss, terminal_data);
				break;
			case Type::UnexpectedType:
				ss << "Encountered a " << to_string(terminal_data.type) << " while waiting for a type\n";
				print_error_line(ss, terminal_data);
				break;
			case Type::UnexpectedPrefix:
				ss << "Encountered a " << to_string(terminal_data.type) << " on an expression, while expecting a literal, variable, etc... \n";
				print_error_line(ss, terminal_data);
				break;
			default:
				assert(false);
				break;
			}
			return ss.str();
		}
	};

	ParseException unexpected_end_exception(Terminal expected_terminal)
	{
		ParseException result;
		result.type = ParseException::Type::UnexpectedEnd;
		result.terminal = expected_terminal;
		return result;
	}

	ParseException scanner_error_exception(Terminal expected_terminal, TerminalData scanner_error)
	{
		assert(scanner_error.type == Terminal::ERROR);
		ParseException result;
		result.type = ParseException::Type::ScannerError;
		result.terminal = expected_terminal;
		result.terminal_data = scanner_error;
		return result;
	}

	ParseException unexpected_terminal_exception(Terminal expected_terminal, TerminalData unexpected_terminal)
	{
		switch (unexpected_terminal.type)
		{
		case Terminal::END:
			return unexpected_end_exception(expected_terminal);
		case Terminal::ERROR:
			return scanner_error_exception(expected_terminal, unexpected_terminal);
		default:
			ParseException result;
			result.type = ParseException::Type::UnexpectedTerminal;
			result.terminal = expected_terminal;
			result.terminal_data = unexpected_terminal;
			return result;
		}
	}

	ParseException unexpected_type_exception(TerminalData unexpected_terminal)
	{
		ParseException result;
		result.type = ParseException::Type::UnexpectedType;
		result.terminal_data = unexpected_terminal;
		return result;
	}

	ParseException unexpected_prefix(TerminalData unexpected_terminal)
	{
		ParseException result;
		result.type = ParseException::Type::UnexpectedPrefix;
		result.terminal_data = unexpected_terminal;
		return result;
	}

	// ------------------------------------------------------------------------------------
	// ------------------------------------------------------------------------------------
	// ------------------------------------------------------------------------------------

	TerminalData consume(Terminal terminal, Scanner& scanner)
	{
		TerminalData symbol = scanner.get_next_symbol();
		if (symbol.type != terminal)
		{
			throw unexpected_terminal_exception(terminal, symbol);
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
	ExpressionPtr type_declaration(Scanner& scanner);

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

	ExpressionPtr assign(std::unique_ptr<VariableRead> left, Scanner& scanner)
	{
		auto result = std::make_unique<VariableAssign>();
		result->identifier = left->identifier;
		result->op = scanner.get_next_symbol();
		result->exp = parse_precedence(scanner, Precedence::Assignment);
		return result;
	}

	ExpressionPtr assign(std::unique_ptr<MemberRead> left, Scanner& scanner)
	{
		auto result = std::make_unique<MemberWrite>();
		result->left = std::move(left->left);
		result->member = left->member;
		result->op = scanner.get_next_symbol();
		result->right = parse_precedence(scanner, Precedence::Assignment);
		return result;
	}

	template<typename VariableOrMemberRead>
	ExpressionPtr try_assign(std::unique_ptr<VariableOrMemberRead> left, Scanner& scanner)
	{
		switch (scanner.peek_next_symbol().type)
		{
		case Terminal::OP_ASSIGN:
		case Terminal::OP_ASSIGN_MUL:
		case Terminal::OP_ASSIGN_DIV:
		case Terminal::OP_ASSIGN_ADD:
		case Terminal::OP_ASSIGN_SUB:
			return assign(std::move(left), scanner);
		default:
			return left;
		}
	}

	// ------------------------------------------------------------------------------------

	ExpressionPtr build_in_type_declaration(Scanner& scanner)
	{
		auto result = std::make_unique<BuildInTypeDeclaration>();
		result->terminal = scanner.get_next_symbol();
		switch (result->terminal.type)
		{
		case Terminal::WK_VOID:
			result->type = BuildInType::Void;
			break;
		case Terminal::WK_INT8:
			result->type = BuildInType::I8;
			break;
		case Terminal::WK_INT16:
			result->type = BuildInType::I16;
			break;
		case Terminal::WK_INT32:
			result->type = BuildInType::I32;
			break;
		case Terminal::WK_INT64:
			result->type = BuildInType::I64;
			break;
		case Terminal::WK_UINT8:
			result->type = BuildInType::U8;
			break;
		case Terminal::WK_UINT16:
			result->type = BuildInType::U16;
			break;
		case Terminal::WK_UINT32:
			result->type = BuildInType::U32;
			break;
		case Terminal::WK_UINT64:
			result->type = BuildInType::U64;
			break;
		case Terminal::WK_FLOAT32:
			result->type = BuildInType::U32;
			break;
		case Terminal::WK_FLOAT64:
			result->type = BuildInType::U64;
			break;
		case Terminal::WK_BOOL:
			result->type = BuildInType::Bool;
			break;
		case Terminal::WK_TYPEDEF:
			result->type = BuildInType::Typedef;
			break;
		default:
			throw unexpected_type_exception(result->terminal);
		}
		return result;
	}

	ExpressionPtr procedure_declaration(Scanner& scanner)
	{
		auto result = std::make_unique<ProcedureDeclaration>();
		if (scanner.peek_next_symbol().type == Terminal::WK_FUNCTION)
		{
			result->kind = consume(Terminal::WK_FUNCTION, scanner);
		}
		else
		{
			result->kind = consume(Terminal::WK_PROCEDURE, scanner);
		}

		consume(Terminal::BRACKET_ROUND_OPEN, scanner);
		result->parameter_tuple = std::make_unique<TupleDeclaration>();

		while (scanner.peek_next_symbol().type == Terminal::IDENTIFIER)
		{
			result->parameter_tuple->field_names.push_back(consume(Terminal::IDENTIFIER, scanner));

			while (scanner.peek_next_symbol().type == Terminal::OP_COMMA)
			{
				consume(Terminal::OP_COMMA, scanner);
				result->parameter_tuple->field_names.push_back(consume(Terminal::IDENTIFIER, scanner));
			}

			consume(Terminal::OP_COLON, scanner);

			if (scanner.peek_next_symbol().type == Terminal::OP_ASSIGN)
			{
				consume(Terminal::OP_ASSIGN, scanner);
				result->parameter_tuple->field_types.push_back(nullptr);
				result->parameter_tuple->field_initializers.push_back(expression(scanner));
			}
			else
			{
				result->parameter_tuple->field_types.push_back(type_declaration(scanner));

				if (scanner.peek_next_symbol().type == Terminal::OP_ASSIGN)
				{
					consume(Terminal::OP_ASSIGN, scanner);
					result->parameter_tuple->field_initializers.push_back(expression(scanner));
					// TODO uninitialized(?)
				}
				else
				{
					result->parameter_tuple->field_initializers.push_back(nullptr);
				}
			}

			assert(result->parameter_tuple->field_initializers.size() == result->parameter_tuple->field_types.size());

			while (result->parameter_tuple->field_types.size() < result->parameter_tuple->field_names.size())
			{
				result->parameter_tuple->field_types.push_back(nullptr);
				result->parameter_tuple->field_initializers.push_back(nullptr);
			}

			assert(result->parameter_tuple->field_types.size() == result->parameter_tuple->field_names.size());
			assert(result->parameter_tuple->field_initializers.size() == result->parameter_tuple->field_names.size());

			// -----------------

			if (scanner.peek_next_symbol().type == Terminal::OP_COMMA)
			{
				consume(Terminal::OP_COMMA, scanner);
				if (scanner.peek_next_symbol().type != Terminal::BRACKET_CURLY_CLOSE && scanner.peek_next_symbol().type != Terminal::IDENTIFIER)
				{
					consume(Terminal::IDENTIFIER, scanner); // little hack to produce correct error
				}
			}
		}

		consume(Terminal::BRACKET_ROUND_CLOSE, scanner);

		if (scanner.peek_next_symbol().type == Terminal::OP_ARROW)
		{
			consume(Terminal::OP_ARROW, scanner);
			result->return_type = expression(scanner);
		}

		result->body = statement(scanner);

		return result;
	}

	ExpressionPtr grouping(Scanner& scanner)
	{
		auto result = std::make_unique<Grouping>();
		result->open = consume(Terminal::BRACKET_ROUND_OPEN, scanner);
		result->expr = expression(scanner);
		result->close = consume(Terminal::BRACKET_ROUND_CLOSE, scanner);
		return result;
	}

	ExpressionPtr identifier_literal(Scanner& scanner)
	{
		auto result = std::make_unique<VariableRead>();
		result->identifier = consume(Terminal::IDENTIFIER, scanner);

		return try_assign(std::move(result), scanner);
	}

	ExpressionPtr initializer_list(Scanner& scanner)
	{
		auto result = std::make_unique<InitializerList>();
		result->open = consume(Terminal::BRACKET_CURLY_OPEN, scanner);

		if (scanner.peek_next_symbol().type != Terminal::BRACKET_CURLY_CLOSE)
		{
			for(;;)
			{
				if (scanner.peek_next_symbol(0).type == Terminal::IDENTIFIER && scanner.peek_next_symbol(1).type == Terminal::OP_ASSIGN)
				{
					result->names.push_back(consume(Terminal::IDENTIFIER, scanner));
					consume(Terminal::OP_ASSIGN, scanner);
				}
				else
				{
					result->names.push_back(std::nullopt);
				}

				result->expressions.push_back(expression(scanner));

				if (scanner.peek_next_symbol().type != Terminal::OP_COMMA)
				{
					break;
				}
				else
				{
					consume(Terminal::OP_COMMA, scanner);
					if (scanner.peek_next_symbol().type == Terminal::BRACKET_CURLY_CLOSE)
					{
						break;
					}
				}
			}
		}

		result->close = consume(Terminal::BRACKET_CURLY_CLOSE, scanner);
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
				result->type_representation = BuildInType::I32;
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
				result->type_representation = BuildInType::I32;
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
				result->type_representation = BuildInType::I32;
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
				result->type_representation = BuildInType::I32;
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
			result->type_representation = BuildInType::I32;
		}

		return result;
	}

	ExpressionPtr table_type_declaration(Scanner& scanner)
	{
		auto result = std::make_unique<TableDeclaration>();
		result->table_terminal = consume(Terminal::WK_TABLE, scanner);

		if (scanner.peek_next_symbol().type == Terminal::IDENTIFIER)
		{
			result->tuple_name = result->last_terminal = consume(Terminal::IDENTIFIER, scanner);
		}
		else
		{
			consume(Terminal::BRACKET_CURLY_OPEN, scanner);

			result->inner_tuple = std::make_unique<TupleDeclaration>();

			while (scanner.peek_next_symbol().type == Terminal::IDENTIFIER)
			{
				result->inner_tuple->field_names.push_back(consume(Terminal::IDENTIFIER, scanner));

				while (scanner.peek_next_symbol().type == Terminal::OP_COMMA)
				{
					consume(Terminal::OP_COMMA, scanner);
					result->inner_tuple->field_names.push_back(consume(Terminal::IDENTIFIER, scanner));
				}

				consume(Terminal::OP_COLON, scanner);

				if (scanner.peek_next_symbol().type == Terminal::OP_ASSIGN)
				{
					consume(Terminal::OP_ASSIGN, scanner);
					result->inner_tuple->field_types.push_back(nullptr);
					result->inner_tuple->field_initializers.push_back(expression(scanner));
				}
				else
				{
					result->inner_tuple->field_types.push_back(type_declaration(scanner));

					if (scanner.peek_next_symbol().type == Terminal::OP_ASSIGN)
					{
						consume(Terminal::OP_ASSIGN, scanner);
						result->inner_tuple->field_initializers.push_back(expression(scanner));
						// TODO uninitialized(?)
					}
					else
					{
						result->inner_tuple->field_initializers.push_back(nullptr);
					}
				}

				assert(result->inner_tuple->field_initializers.size() == result->inner_tuple->field_types.size());

				while (result->inner_tuple->field_types.size() < result->inner_tuple->field_names.size())
				{
					result->inner_tuple->field_types.push_back(nullptr);
					result->inner_tuple->field_initializers.push_back(nullptr);
				}

				assert(result->inner_tuple->field_types.size() == result->inner_tuple->field_names.size());
				assert(result->inner_tuple->field_initializers.size() == result->inner_tuple->field_names.size());

				// -----------------

				if (scanner.peek_next_symbol().type == Terminal::OP_COMMA)
				{
					consume(Terminal::OP_COMMA, scanner);
					if (scanner.peek_next_symbol().type != Terminal::BRACKET_CURLY_CLOSE && scanner.peek_next_symbol().type != Terminal::IDENTIFIER)
					{
						consume(Terminal::IDENTIFIER, scanner); // little hack to produce correct error
					}
				}
			}
			result->last_terminal = consume(Terminal::BRACKET_CURLY_CLOSE, scanner);
		}

		return result;
	}

	ExpressionPtr tuple_type_declaration(Scanner& scanner)
	{
		auto result = std::make_unique<TupleDeclaration>();
		result->tuple_terminal = consume(Terminal::WK_TUPLE, scanner);
		consume(Terminal::BRACKET_CURLY_OPEN, scanner);


		while (scanner.peek_next_symbol().type == Terminal::IDENTIFIER)
		{
			result->field_names.push_back(consume(Terminal::IDENTIFIER, scanner));

			while (scanner.peek_next_symbol().type == Terminal::OP_COMMA)
			{
				consume(Terminal::OP_COMMA, scanner);
				result->field_names.push_back(consume(Terminal::IDENTIFIER, scanner));
			}

			consume(Terminal::OP_COLON, scanner);

			if (scanner.peek_next_symbol().type == Terminal::OP_ASSIGN)
			{
				consume(Terminal::OP_ASSIGN, scanner);
				result->field_types.push_back(nullptr);
				result->field_initializers.push_back(expression(scanner));
			}
			else
			{
				result->field_types.push_back(type_declaration(scanner));
				
				if (scanner.peek_next_symbol().type == Terminal::OP_ASSIGN)
				{
					consume(Terminal::OP_ASSIGN, scanner);
					result->field_initializers.push_back(expression(scanner));
					// TODO uninitialized(?)
				}
				else
				{
					result->field_initializers.push_back(nullptr);
				}
			}

			assert(result->field_initializers.size() == result->field_types.size());

			while (result->field_types.size() < result->field_names.size())
			{
				result->field_types.push_back(nullptr);
				result->field_initializers.push_back(nullptr);
			}

			assert(result->field_types.size() == result->field_names.size());
			assert(result->field_initializers.size() == result->field_names.size());

			// -----------------

			if (scanner.peek_next_symbol().type == Terminal::OP_COMMA)
			{
				consume(Terminal::OP_COMMA, scanner);
				if (scanner.peek_next_symbol().type != Terminal::BRACKET_CURLY_CLOSE && scanner.peek_next_symbol().type != Terminal::IDENTIFIER)
				{
					consume(Terminal::IDENTIFIER, scanner); // little hack to produce correct error
				}
			}
		}

		result->closing_bracket = consume(Terminal::BRACKET_CURLY_CLOSE, scanner);

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

		return result;
	}

	ExpressionPtr call(ExpressionPtr left, Precedence current_precendence, Scanner& scanner)
	{
		auto result = std::make_unique<Call>();
		result->callee = std::move(left);
		result->arguments.open = consume(Terminal::BRACKET_ROUND_OPEN, scanner);

		if (scanner.peek_next_symbol().type != Terminal::BRACKET_ROUND_CLOSE)
		{
			for (;;)
			{
				if (scanner.peek_next_symbol(0).type == Terminal::IDENTIFIER && scanner.peek_next_symbol(1).type == Terminal::OP_ASSIGN)
				{
					result->arguments.names.push_back(consume(Terminal::IDENTIFIER, scanner));
					consume(Terminal::OP_ASSIGN, scanner);
				}
				else
				{
					result->arguments.names.push_back(std::nullopt);
				}

				result->arguments.expressions.push_back(expression(scanner));

				if (scanner.peek_next_symbol().type != Terminal::OP_COMMA)
				{
					break;
				}
				else
				{
					consume(Terminal::OP_COMMA, scanner);
					if (scanner.peek_next_symbol().type == Terminal::BRACKET_ROUND_CLOSE)
					{
						break;
					}
				}
			}
		}

		result->arguments.close = consume(Terminal::BRACKET_ROUND_CLOSE, scanner);
		return result;
	}

	ExpressionPtr member_read(ExpressionPtr left, Precedence current_precendence, Scanner& scanner)
	{
		auto result = std::make_unique<MemberRead>();
		result->left = std::move(left);
		consume(Terminal::OP_DOT, scanner);
		result->member = consume(Terminal::IDENTIFIER, scanner);

		return try_assign(std::move(result), scanner);
	}

	ExpressionPtr type_declaration(Scanner& scanner)
	{
		if (scanner.peek_next_symbol().type == Terminal::IDENTIFIER)
		{
			auto result = std::make_unique<VariableRead>();
			result->identifier = consume(Terminal::IDENTIFIER, scanner);
			return result;
		}
		else if (scanner.peek_next_symbol().type == Terminal::WK_TABLE)
		{
			return table_type_declaration(scanner);
		}
		else if (scanner.peek_next_symbol().type == Terminal::WK_TUPLE)
		{
			return tuple_type_declaration(scanner);
		}
		else
		{
			// TODO tuples & tables
			return build_in_type_declaration(scanner);
		}
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
		pratt_prefixes[(int)Terminal::BRACKET_ROUND_OPEN] = &grouping;
		pratt_prefixes[(int)Terminal::OP_SUB] = &unary;
		pratt_prefixes[(int)Terminal::OP_ADD] = &unary;
		pratt_prefixes[(int)Terminal::OP_NOT] = &unary;
		pratt_prefixes[(int)Terminal::OP_BIT_NOT] = &unary;
		pratt_prefixes[(int)Terminal::INTEGER_LITERAL] = &integer_literal;
		pratt_prefixes[(int)Terminal::IDENTIFIER] = &identifier_literal;
		pratt_prefixes[(int)Terminal::BRACKET_CURLY_OPEN] = &initializer_list;

		//	case Terminal::FLOAT_LITERAL: return std::make_unique<Literal>(parse_float(scanner.get_next_symbol()));
		//	case Terminal::CHAR_LITERAL: return std::make_unique<Literal>(parse_char(scanner.get_next_symbol()));
		//	case Terminal::STRING_LITERAL: return std::make_unique<Literal>(parse_string(scanner.get_next_symbol()));
		//	case Terminal::BOOL_LITERAL: return std::make_unique<Literal>(parse_bool(scanner.get_next_symbol()));


		pratt_prefixes[(int)Terminal::WK_VOID] = &build_in_type_declaration;
		pratt_prefixes[(int)Terminal::WK_INT8] = &build_in_type_declaration;
		pratt_prefixes[(int)Terminal::WK_INT16] = &build_in_type_declaration;
		pratt_prefixes[(int)Terminal::WK_INT32] = &build_in_type_declaration;
		pratt_prefixes[(int)Terminal::WK_INT64] = &build_in_type_declaration;
		pratt_prefixes[(int)Terminal::WK_UINT8] = &build_in_type_declaration;
		pratt_prefixes[(int)Terminal::WK_UINT16] = &build_in_type_declaration;
		pratt_prefixes[(int)Terminal::WK_UINT32] = &build_in_type_declaration;
		pratt_prefixes[(int)Terminal::WK_UINT64] = &build_in_type_declaration;
		pratt_prefixes[(int)Terminal::WK_FLOAT32] = &build_in_type_declaration;
		pratt_prefixes[(int)Terminal::WK_FLOAT64] = &build_in_type_declaration;
		pratt_prefixes[(int)Terminal::WK_BOOL] = &build_in_type_declaration;
		pratt_prefixes[(int)Terminal::WK_TYPEDEF] = &build_in_type_declaration;
		pratt_prefixes[(int)Terminal::WK_TABLE] = &table_type_declaration;
		pratt_prefixes[(int)Terminal::WK_TUPLE] = &tuple_type_declaration;
		pratt_prefixes[(int)Terminal::WK_FUNCTION] = &procedure_declaration;
		pratt_prefixes[(int)Terminal::WK_PROCEDURE] = &procedure_declaration;


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
		pratt_infixes[(int)Terminal::BRACKET_ROUND_OPEN] = &call;
		pratt_precedences[(int)Terminal::BRACKET_ROUND_OPEN] = Precedence::Call;
		pratt_infixes[(int)Terminal::OP_DOT] = &member_read;
		pratt_precedences[(int)Terminal::OP_DOT] = Precedence::Call;
	}


	// ------------------------------------------------------------------------------------
	// ------------------------------------------------------------------------------------
	// ------------------------------------------------------------------------------------

	ExpressionPtr parse_precedence(Scanner& scanner, Precedence precedence)
	{
		PrattPrefix prefix_rule = pratt_prefixes[(int)scanner.peek_next_symbol().type];
		if (prefix_rule == nullptr)
		{
			throw unexpected_prefix(scanner.peek_next_symbol());
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
	// ------------------------------------------------------------------------------------
	// ------------------------------------------------------------------------------------

	StatementPtr expression_statement(Scanner& scanner)
	{
		auto result = std::make_unique<ExpressionStatement>();
		result->exp = expression(scanner);
		result->semicolon = consume(Terminal::OP_SEMICOLON, scanner);

		return result;
	}

	// ------------------------------------------------------------------------------------

	StatementPtr return_statement(Scanner& scanner)
	{
		auto result = std::make_unique<ReturnStatement>();
		result->return_keyword = consume(Terminal::WK_RETURN, scanner);
		result->exp = expression(scanner);
		result->semicolon = consume(Terminal::OP_SEMICOLON, scanner);

		return result;
	}

	// ------------------------------------------------------------------------------------

	StatementPtr variable_definition(Scanner& scanner)
	{
		auto result = std::make_unique<VariableDefinition>();
		result->variable = consume(Terminal::IDENTIFIER, scanner);
		consume(Terminal::OP_COLON, scanner);

		if (scanner.peek_next_symbol().type != Terminal::OP_COLON && scanner.peek_next_symbol().type != Terminal::OP_ASSIGN)
		{
			result->type_definition = type_declaration(scanner);
		}

		if (scanner.peek_next_symbol().type == Terminal::OP_COLON)
		{
			consume(Terminal::OP_COLON, scanner);
			result->constant = true;
		}
		else if (scanner.peek_next_symbol().type != Terminal::OP_SEMICOLON)
		{
			consume(Terminal::OP_ASSIGN, scanner);
		}

		if (scanner.peek_next_symbol().type != Terminal::OP_SEMICOLON)
		{
			if (scanner.peek_next_symbol().type != Terminal::UNINITIALIZED)
			{
				result->initialization = expression(scanner);
			}
			else
			{
				assert(result->type.has_value());
				consume(Terminal::UNINITIALIZED, scanner);
				result->explicitly_uninitialized = true;
			}
		}
		else
		{
			assert(result->type_definition != nullptr); // TODO make proper error?
		}

		result->semicolon = consume(Terminal::OP_SEMICOLON, scanner);

		return result;
	}

	// ------------------------------------------------------------------------------------

	StatementPtr block(Scanner& scanner)
	{
		auto block = std::make_unique<Block>();
		block->open = consume(Terminal::BRACKET_CURLY_OPEN, scanner);

		while (scanner.peek_next_symbol().type != Terminal::BRACKET_CURLY_CLOSE)
		{
			block->statements.emplace_back(statement(scanner));

			if (scanner.peek_next_symbol().type == Terminal::END)
			{
				throw unexpected_terminal_exception(Terminal::BRACKET_CURLY_CLOSE, scanner.peek_next_symbol());
			}
		}
		block->close = consume(Terminal::BRACKET_CURLY_CLOSE, scanner);
		return block;
	}

	// ------------------------------------------------------------------------------------

	StatementPtr statement(Scanner& scanner)
	{
		if (scanner.peek_next_symbol().type == Terminal::WK_RETURN)
		{
			return return_statement(scanner);
		}
		else if (scanner.peek_next_symbol().type == Terminal::BRACKET_CURLY_OPEN)
		{
			return block(scanner);
		}
		else if (scanner.peek_next_symbol().type == Terminal::IDENTIFIER && scanner.peek_next_symbol(1).type == Terminal::OP_COLON)
		{
			return variable_definition(scanner);
		}
		else 
		{
			return expression_statement(scanner);
		}
	}

	StatementPtr generate_AST(Scanner code)
	{
		initialize_pratt_parser();

		auto result = std::make_unique<Block>();
		result->is_global = true;

		while (code.peek_next_symbol().type != Terminal::END)
		{
			result->statements.push_back(statement(code));
		}
		return result;
	}
}
