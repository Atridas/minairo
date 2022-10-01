// Auto-generated file. Do not manually modify

module;

#include <cassert>

#include <any>

export module MinairoScanner;

import <memory>;
import <optional>;
import <typeindex>;
import <typeinfo>;
import <string_view>;
import <variant>;

export namespace minairo
{


	enum class Terminal
	{
		ERROR,
		END,
		INTEGER_LITERAL,
		FLOAT_LITERAL,
		CHAR_LITERAL,
		STRING_LITERAL,
		WK_ASC,
		WK_BY,
		WK_DESC,
		WK_EXPORT,
		WK_FUNCTION,
		WK_IMPORT,
		WK_MODULE,
		WK_PROCEDURE,
		WK_PUBLIC,
		WK_TABLE,
		WK_TUPLE,
		WK_DO,
		WK_ELSE,
		WK_FOR,
		WK_GROUP,
		WK_IF,
		WK_JOIN,
		WK_PROJECT,
		WK_RETURN,
		WK_SORT,
		WK_TAKE,
		WK_YIELD,
		WK_WHERE,
		WK_WHILE,
		WK_INT8,
		WK_INT16,
		WK_INT32,
		WK_INT64,
		WK_UINT8,
		WK_UINT16,
		WK_UINT32,
		WK_UINT64,
		WK_FLOAT,
		WK_DOUBLE,
		OP_DOT,
		OP_COMMA,
		OP_QUEST,
		OP_COLON,
		OP_MUL,
		OP_DIV,
		OP_MOD,
		OP_ADD,
		OP_SUB,
		OP_NOT,
		OP_bit_NOT,
		OP_EQ,
		OP_NEQ,
		OP_LT,
		OP_GT,
		OP_LTE,
		OP_GTE,
		OP_AND,
		OP_OR,
		OP_BIT_AND,
		OP_BIT_OR,
		OP_BIT_XOR,
		OP_ASSIGN,
		OP_ASSIGN_MUL,
		OP_ASSIGN_DIV,
		OP_ASSIGN_ADD,
		OP_ASSIGN_SUB,
		UNINITIALIZED,
		IDENTIFIER,
	};

	inline const char* to_string(Terminal terminal)
	{
		switch (terminal)
		{
		case Terminal::ERROR: return "ERROR";
		case Terminal::END: return "END";
		case Terminal::INTEGER_LITERAL: return "INTEGER_LITERAL";
		case Terminal::FLOAT_LITERAL: return "FLOAT_LITERAL";
		case Terminal::CHAR_LITERAL: return "CHAR_LITERAL";
		case Terminal::STRING_LITERAL: return "STRING_LITERAL";
		case Terminal::WK_ASC: return "WK_ASC";
		case Terminal::WK_BY: return "WK_BY";
		case Terminal::WK_DESC: return "WK_DESC";
		case Terminal::WK_EXPORT: return "WK_EXPORT";
		case Terminal::WK_FUNCTION: return "WK_FUNCTION";
		case Terminal::WK_IMPORT: return "WK_IMPORT";
		case Terminal::WK_MODULE: return "WK_MODULE";
		case Terminal::WK_PROCEDURE: return "WK_PROCEDURE";
		case Terminal::WK_PUBLIC: return "WK_PUBLIC";
		case Terminal::WK_TABLE: return "WK_TABLE";
		case Terminal::WK_TUPLE: return "WK_TUPLE";
		case Terminal::WK_DO: return "WK_DO";
		case Terminal::WK_ELSE: return "WK_ELSE";
		case Terminal::WK_FOR: return "WK_FOR";
		case Terminal::WK_GROUP: return "WK_GROUP";
		case Terminal::WK_IF: return "WK_IF";
		case Terminal::WK_JOIN: return "WK_JOIN";
		case Terminal::WK_PROJECT: return "WK_PROJECT";
		case Terminal::WK_RETURN: return "WK_RETURN";
		case Terminal::WK_SORT: return "WK_SORT";
		case Terminal::WK_TAKE: return "WK_TAKE";
		case Terminal::WK_YIELD: return "WK_YIELD";
		case Terminal::WK_WHERE: return "WK_WHERE";
		case Terminal::WK_WHILE: return "WK_WHILE";
		case Terminal::WK_INT8: return "WK_INT8";
		case Terminal::WK_INT16: return "WK_INT16";
		case Terminal::WK_INT32: return "WK_INT32";
		case Terminal::WK_INT64: return "WK_INT64";
		case Terminal::WK_UINT8: return "WK_UINT8";
		case Terminal::WK_UINT16: return "WK_UINT16";
		case Terminal::WK_UINT32: return "WK_UINT32";
		case Terminal::WK_UINT64: return "WK_UINT64";
		case Terminal::WK_FLOAT: return "WK_FLOAT";
		case Terminal::WK_DOUBLE: return "WK_DOUBLE";
		case Terminal::OP_DOT: return "OP_DOT";
		case Terminal::OP_COMMA: return "OP_COMMA";
		case Terminal::OP_QUEST: return "OP_QUEST";
		case Terminal::OP_COLON: return "OP_COLON";
		case Terminal::OP_MUL: return "OP_MUL";
		case Terminal::OP_DIV: return "OP_DIV";
		case Terminal::OP_MOD: return "OP_MOD";
		case Terminal::OP_ADD: return "OP_ADD";
		case Terminal::OP_SUB: return "OP_SUB";
		case Terminal::OP_NOT: return "OP_NOT";
		case Terminal::OP_bit_NOT: return "OP_bit_NOT";
		case Terminal::OP_EQ: return "OP_EQ";
		case Terminal::OP_NEQ: return "OP_NEQ";
		case Terminal::OP_LT: return "OP_LT";
		case Terminal::OP_GT: return "OP_GT";
		case Terminal::OP_LTE: return "OP_LTE";
		case Terminal::OP_GTE: return "OP_GTE";
		case Terminal::OP_AND: return "OP_AND";
		case Terminal::OP_OR: return "OP_OR";
		case Terminal::OP_BIT_AND: return "OP_BIT_AND";
		case Terminal::OP_BIT_OR: return "OP_BIT_OR";
		case Terminal::OP_BIT_XOR: return "OP_BIT_XOR";
		case Terminal::OP_ASSIGN: return "OP_ASSIGN";
		case Terminal::OP_ASSIGN_MUL: return "OP_ASSIGN_MUL";
		case Terminal::OP_ASSIGN_DIV: return "OP_ASSIGN_DIV";
		case Terminal::OP_ASSIGN_ADD: return "OP_ASSIGN_ADD";
		case Terminal::OP_ASSIGN_SUB: return "OP_ASSIGN_SUB";
		case Terminal::UNINITIALIZED: return "UNINITIALIZED";
		case Terminal::IDENTIFIER: return "IDENTIFIER";
		default: return "UNKNOWN TERMINAL!";
		}
	}

	struct TerminalData
	{
		Terminal type;
		int line;
		std::string_view text, line_begin, line_end;
		std::any user_data;

		TerminalData() noexcept = default;
		TerminalData(Terminal type) noexcept : type(type), text() {}
		TerminalData(Terminal type, std::string_view _text, std::string_view _line_begin, std::string_view _line_end, int _line) noexcept : type(type), text(_text), line_begin(_line_begin), line_end(_line_end), line(_line) {}
	};


	class Scanner
	{
	public:
		static const int LLk = 3;

		const std::string_view text;
		int current_text_index = 0;
		TerminalData next_symbols[LLk];
		int current_saved_symbols = 0;

		int line_count = 0;
		std::string_view current_line_text;


		Scanner(std::string_view _text) noexcept
			:text(_text)
		{
			int line_size = 0;
			for (; line_size < text.size() && text[line_size] != '\n' && text[line_size] != '\r'; ++line_size);

			current_line_text = text.substr(0, line_size);
		}


		TerminalData peek_next_symbol(int index = 0) noexcept
		{
			assert(index < LLk);
			while (index >= current_saved_symbols)
			{
				next_symbols[current_saved_symbols] = get_next_symbol_internal();
				++current_saved_symbols;
			}
			return next_symbols[index];
		}


		TerminalData get_next_symbol() noexcept
		{
			if (current_saved_symbols > 0)
			{
				TerminalData result = next_symbols[0];
				--current_saved_symbols;
				for (int i = 0; i < current_saved_symbols; ++i)
					next_symbols[i] = next_symbols[i + 1];
				return result;
			}

			return get_next_symbol_internal();
		}

		TerminalData get_next_symbol_internal() noexcept
		{
			int state = 0;
			int terminal_begin_index = current_text_index;
			int terminal_line = line_count + 1;
			std::string_view terminal_line_text = current_line_text;


			for (;;)
			{
				unsigned char character = current_text_index < text.size() ? text[current_text_index] : 0;

				if (character == '\n')
				{
					int last_line_begin = current_text_index + 1;
					++line_count;
					int line_size = 0;
					for (; last_line_begin + line_size < text.size() && text[last_line_begin + line_size] != '\n' && text[last_line_begin + line_size] != '\r'; ++line_size);

					current_line_text = text.substr(last_line_begin, line_size);
				}

				switch (state)
				{
				case 0:
					switch (character)
					{
					case 0:
						return Terminal::END;
					case 9:
					case 10:
					case 13:
					case ' ':
						state = 1;
						break;
					case '!':
						state = 2;
						break;
					case '\"':
						state = 3;
						break;
					case '%':
						state = 4;
						break;
					case '&':
						state = 5;
						break;
					case '\'':
						state = 6;
						break;
					case '*':
						state = 7;
						break;
					case '+':
						state = 8;
						break;
					case ',':
						state = 9;
						break;
					case '-':
						state = 10;
						break;
					case '.':
						state = 11;
						break;
					case '/':
						state = 12;
						break;
					case '0':
						state = 13;
						break;
					case ':':
						state = 15;
						break;
					case '<':
						state = 16;
						break;
					case '=':
						state = 17;
						break;
					case '>':
						state = 18;
						break;
					case '?':
						state = 19;
						break;
					case 'L':
					case 'U':
						state = 21;
						break;
					case '^':
						state = 22;
						break;
					case '_':
						state = 23;
						break;
					case 'a':
						state = 24;
						break;
					case 'b':
						state = 25;
						break;
					case 'd':
						state = 26;
						break;
					case 'e':
						state = 27;
						break;
					case 'f':
						state = 28;
						break;
					case 'g':
						state = 29;
						break;
					case 'i':
						state = 30;
						break;
					case 'j':
						state = 31;
						break;
					case 'm':
						state = 32;
						break;
					case 'p':
						state = 33;
						break;
					case 'r':
						state = 34;
						break;
					case 's':
						state = 35;
						break;
					case 't':
						state = 36;
						break;
					case 'u':
						state = 37;
						break;
					case 'w':
						state = 38;
						break;
					case 'y':
						state = 39;
						break;
					case '|':
						state = 40;
						break;
					case '~':
						state = 41;
						break;
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '1' && character <= '9'))
						{
							state = 14;
							break;
						}
						if ((character >= 'A' && character != 'L' && character != 'U' && character <= 'Z') || (character >= 'c' && character <= 'c') || (character >= 'h' && character <= 'h') || (character >= 'k' && character != 'm' && character != 'p' && character <= 'q') || (character >= 'v' && character != 'w' && character != 'y' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 1:
					switch (character)
					{
					case 9:
					case 10:
					case 13:
					case ' ':
						// state = 1;
						break;
					default:
					{
						terminal_begin_index = current_text_index;
						terminal_line = line_count + 1;
						terminal_line_text = current_line_text;
						state = 0;
						--current_text_index;
					}
					break;
					}
					break;
				case 2:
					switch (character)
					{
					case '=':
						state = 45;
						break;
					default:
					{
						return TerminalData(Terminal::OP_NOT, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
					}
					break;
				case 3:
					switch (character)
					{
					case '\"':
						state = 46;
						break;
					case '\\':
						state = 47;
						break;
					case 195:
						state = 48;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 49;
						break;
					case 201:
						state = 50;
						break;
					default:
						if ((character >= 'A' && character <= 'Z') || (character >= 'a' && character <= 'z'))
						{
							// state = 3;
							break;
						}
						else
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 4:
				{
					return TerminalData(Terminal::OP_MOD, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
				}
				break;
				case 5:
					switch (character)
					{
					case '&':
						state = 51;
						break;
					default:
					{
						return TerminalData(Terminal::OP_BIT_AND, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
					}
					break;
				case 6:
					switch (character)
					{
					case '\\':
						state = 53;
						break;
					case 195:
						state = 54;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 55;
						break;
					case 201:
						state = 56;
						break;
					default:
						if ((character >= 'A' && character <= 'Z') || (character >= 'a' && character <= 'z'))
						{
							state = 52;
							break;
						}
						else
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 7:
					switch (character)
					{
					case '=':
						state = 57;
						break;
					default:
					{
						return TerminalData(Terminal::OP_MUL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
					}
					break;
				case 8:
					switch (character)
					{
					case '=':
						state = 58;
						break;
					default:
					{
						return TerminalData(Terminal::OP_ADD, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
					}
					break;
				case 9:
				{
					return TerminalData(Terminal::OP_COMMA, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
				}
				break;
				case 10:
					switch (character)
					{
					case '-':
						state = 59;
						break;
					case '=':
						state = 60;
						break;
					default:
					{
						return TerminalData(Terminal::OP_SUB, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
					}
					break;
				case 11:
					if ((character >= '0' && character <= '9'))
					{
						state = 61;
						break;
					}
					else
					{
						return TerminalData(Terminal::OP_DOT, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 12:
					switch (character)
					{
					case '*':
						state = 62;
						break;
					case '/':
						state = 63;
						break;
					case '=':
						state = 64;
						break;
					default:
					{
						return TerminalData(Terminal::OP_DIV, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
					}
					break;
				case 13:
					switch (character)
					{
					case '\'':
						state = 65;
						break;
					case '.':
						state = 66;
						break;
					case '8':
					case '9':
						state = 68;
						break;
					case 'B':
					case 'b':
						state = 69;
						break;
					case 'E':
					case 'e':
						state = 70;
						break;
					case 'L':
						state = 71;
						break;
					case 'U':
					case 'u':
						state = 72;
						break;
					case 'X':
					case 'x':
						state = 73;
						break;
					case 'Z':
					case 'z':
						state = 74;
						break;
					case 'l':
						state = 75;
						break;
					default:
						if ((character >= '0' && character <= '7'))
						{
							state = 67;
							break;
						}
						else
						{
							return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 14:
					switch (character)
					{
					case '.':
						state = 66;
						break;
					case 'E':
					case 'e':
						state = 70;
						break;
					case 'L':
						state = 71;
						break;
					case 'U':
					case 'u':
						state = 72;
						break;
					case 'Z':
					case 'z':
						state = 74;
						break;
					case 'l':
						state = 75;
						break;
					case '\'':
						state = 76;
						break;
					default:
						if ((character >= '0' && character <= '9'))
						{
							// state = 14;
							break;
						}
						else
						{
							return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 15:
				{
					return TerminalData(Terminal::OP_COLON, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
				}
				break;
				case 16:
					switch (character)
					{
					case '=':
						state = 77;
						break;
					default:
					{
						return TerminalData(Terminal::OP_LT, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
					}
					break;
				case 17:
					switch (character)
					{
					case '=':
						state = 78;
						break;
					default:
					{
						return TerminalData(Terminal::OP_ASSIGN, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
					}
					break;
				case 18:
					switch (character)
					{
					case '=':
						state = 79;
						break;
					default:
					{
						return TerminalData(Terminal::OP_GT, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
					}
					break;
				case 19:
				{
					return TerminalData(Terminal::OP_QUEST, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
				}
				break;
				case 20:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							// state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 21:
					switch (character)
					{
					case '\"':
						state = 3;
						break;
					case '\'':
						state = 6;
						break;
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 22:
				{
					return TerminalData(Terminal::OP_BIT_XOR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
				}
				break;
				case 23:
					switch (character)
					{
					case '_':
						// state = 23;
						break;
					case 195:
						state = 81;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 82;
						break;
					case 201:
						state = 83;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= 'a' && character <= 'z'))
						{
							state = 80;
							break;
						}
						else
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 24:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 's':
						state = 84;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 's' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 25:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'y':
						state = 85;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'y' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 26:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'e':
						state = 86;
						break;
					case 'o':
						state = 87;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'e' && character != 'o' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 27:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'l':
						state = 88;
						break;
					case 'x':
						state = 89;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'l' && character != 'x' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 28:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'l':
						state = 90;
						break;
					case 'o':
						state = 91;
						break;
					case 'u':
						state = 92;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'l' && character != 'o' && character != 'u' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 29:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'r':
						state = 93;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'r' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 30:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'f':
						state = 94;
						break;
					case 'm':
						state = 95;
						break;
					case 'n':
						state = 96;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'f' && character <= 'l') || (character >= 'o' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 31:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'o':
						state = 97;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'o' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 32:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'o':
						state = 98;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'o' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 33:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'r':
						state = 99;
						break;
					case 'u':
						state = 100;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'r' && character != 'u' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 34:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'e':
						state = 101;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'e' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 35:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'o':
						state = 102;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'o' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 36:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'a':
						state = 103;
						break;
					case 'u':
						state = 104;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character <= '_') || (character >= 'b' && character != 'u' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 37:
					switch (character)
					{
					case '\"':
						state = 3;
						break;
					case '\'':
						state = 6;
						break;
					case '8':
						state = 21;
						break;
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'i':
						state = 105;
						break;
					default:
						if ((character >= '0' && character != '8' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'i' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 38:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'h':
						state = 106;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'h' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 39:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'i':
						state = 107;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'i' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 40:
					switch (character)
					{
					case '|':
						state = 108;
						break;
					default:
					{
						return TerminalData(Terminal::OP_BIT_OR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
					}
					break;
				case 41:
				{
					return TerminalData(Terminal::OP_bit_NOT, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
				}
				break;
				case 42:
					if ((character >= 128 && character != 151 && character != 183 && character <= 191))
					{
						state = 20;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 43:
					if ((character >= 128 && character <= 191))
					{
						state = 20;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 44:
					if ((character >= 128 && character <= 143))
					{
						state = 20;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 45:
				{
					return TerminalData(Terminal::OP_NEQ, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
				}
				break;
				case 46:
				{
					return TerminalData(Terminal::STRING_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
				}
				break;
				case 47:
					switch (character)
					{
					case 'U':
						state = 110;
						break;
					case 'u':
						state = 111;
						break;
					case 'x':
						state = 112;
						break;
					default:
						if ((character >= '\"' && character <= '\"') || (character >= '\'' && character <= '\'') || (character >= '?' && character <= '?') || (character >= '\\' && character <= '\\') || (character >= 'a' && character <= 'b') || (character >= 'f' && character <= 'f') || (character >= 'n' && character <= 'n') || (character >= 'r' && character != 's' && character != 'u' && character <= 'v'))
						{
							state = 3;
							break;
						}
						if ((character >= '0' && character <= '7'))
						{
							state = 109;
							break;
						}
						else
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 48:
					if ((character >= 128 && character != 151 && character != 183 && character <= 191))
					{
						state = 3;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 49:
					if ((character >= 128 && character <= 191))
					{
						state = 3;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 50:
					if ((character >= 128 && character <= 143))
					{
						state = 3;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 51:
				{
					return TerminalData(Terminal::OP_AND, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
				}
				break;
				case 52:
					switch (character)
					{
					case '\'':
						state = 113;
						break;
					default:
					{
						return Terminal::ERROR;
					}
					break;
					}
					break;
				case 53:
					switch (character)
					{
					case 'U':
						state = 115;
						break;
					case 'u':
						state = 116;
						break;
					case 'x':
						state = 117;
						break;
					default:
						if ((character >= '\"' && character <= '\"') || (character >= '\'' && character <= '\'') || (character >= '?' && character <= '?') || (character >= '\\' && character <= '\\') || (character >= 'a' && character <= 'b') || (character >= 'f' && character <= 'f') || (character >= 'n' && character <= 'n') || (character >= 'r' && character != 's' && character != 'u' && character <= 'v'))
						{
							state = 52;
							break;
						}
						if ((character >= '0' && character <= '7'))
						{
							state = 114;
							break;
						}
						else
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 54:
					if ((character >= 128 && character != 151 && character != 183 && character <= 191))
					{
						state = 52;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 55:
					if ((character >= 128 && character <= 191))
					{
						state = 52;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 56:
					if ((character >= 128 && character <= 143))
					{
						state = 52;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 57:
				{
					return TerminalData(Terminal::OP_ASSIGN_MUL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
				}
				break;
				case 58:
				{
					return TerminalData(Terminal::OP_ASSIGN_ADD, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
				}
				break;
				case 59:
					switch (character)
					{
					case '-':
						state = 118;
						break;
					default:
					{
						return Terminal::ERROR;
					}
					break;
					}
					break;
				case 60:
				{
					return TerminalData(Terminal::OP_ASSIGN_SUB, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
				}
				break;
				case 61:
					switch (character)
					{
					case '\'':
						state = 119;
						break;
					case 'E':
					case 'e':
						state = 120;
						break;
					case 'F':
					case 'L':
					case 'f':
					case 'l':
						state = 121;
						break;
					default:
						if ((character >= '0' && character <= '9'))
						{
							// state = 61;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 62:
				{
					int recursivities = 1;
					int comment_state = 0;
					for (;;)
					{
						bool comment_finished = false;
						switch (comment_state)
						{
						case 0:
							switch (text[current_text_index])
							{
							case 0:
								return Terminal::END;
								break;
							case '*':
								comment_state = 1;
								break;
							case '/':
								comment_state = 2;
								break;
							default:
								break;
							}
							break;
						case 1:
							switch (text[current_text_index])
							{
							case 0:
								return Terminal::END;
								break;
							case '/':
								comment_state = 3;
								break;
							default:
								comment_state = 0;
								break;
							}
							break;
						case 2:
							switch (text[current_text_index])
							{
							case 0:
								return Terminal::END;
								break;
							case '*':
								comment_state = 4;
								break;
							default:
								comment_state = 0;
								break;
							}
							break;
						case 3:
							switch (text[current_text_index])
							{
							case 0:
								return Terminal::END;
								break;
							default:
								if (--recursivities == 0)
								{
									comment_finished = true;
								}
								else
								{
									comment_state = 0;
								}
								break;
							}
							break;
						case 4:
							switch (text[current_text_index])
							{
							case 0:
								return Terminal::END;
								break;
							default:
								++recursivities;
								comment_state = 0;
								break;
							}
							break;
						}
						if (comment_finished == true)
						{
							terminal_begin_index = current_text_index;
							terminal_line = line_count + 1;
							terminal_line_text = current_line_text;
							--current_text_index;
							state = 0;
							break;
						}
						else
						{
							++current_text_index;
						}
					}
				}
				break;
				case 63:
				{
					++current_text_index;
					while (text[current_text_index] != '\n' && text[current_text_index] != '\r' && text[current_text_index] != '\0')
					{
						++current_text_index;
					}
					terminal_begin_index = current_text_index;
					terminal_line = line_count + 1;
					terminal_line_text = current_line_text;
					--current_text_index;
					state = 0;
				}
				break;
				case 64:
				{
					return TerminalData(Terminal::OP_ASSIGN_DIV, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
				}
				break;
				case 65:
					switch (character)
					{
					case '8':
					case '9':
						state = 68;
						break;
					default:
						if ((character >= '0' && character <= '7'))
						{
							state = 67;
							break;
						}
						else
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 66:
					switch (character)
					{
					case 'F':
					case 'L':
					case 'f':
					case 'l':
						state = 121;
						break;
					case 'E':
					case 'e':
						state = 122;
						break;
					default:
						if ((character >= '0' && character <= '9'))
						{
							state = 61;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 67:
					switch (character)
					{
					case '\'':
						state = 65;
						break;
					case '.':
						state = 66;
						break;
					case '8':
					case '9':
						state = 68;
						break;
					case 'E':
					case 'e':
						state = 70;
						break;
					case 'L':
						state = 71;
						break;
					case 'U':
					case 'u':
						state = 72;
						break;
					case 'Z':
					case 'z':
						state = 74;
						break;
					case 'l':
						state = 75;
						break;
					default:
						if ((character >= '0' && character <= '7'))
						{
							// state = 67;
							break;
						}
						else
						{
							return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 68:
					switch (character)
					{
					case '.':
						state = 66;
						break;
					case 'E':
					case 'e':
						state = 70;
						break;
					case '\'':
						state = 123;
						break;
					default:
						if ((character >= '0' && character <= '9'))
						{
							// state = 68;
							break;
						}
						else
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 69:
					switch (character)
					{
					case '\'':
						state = 124;
						break;
					case '0':
					case '1':
						state = 125;
						break;
					default:
					{
						return Terminal::ERROR;
					}
					break;
					}
					break;
				case 70:
					switch (character)
					{
					case '+':
					case '-':
						state = 126;
						break;
					default:
						if ((character >= '0' && character <= '9'))
						{
							state = 127;
							break;
						}
						else
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 71:
					switch (character)
					{
					case 'L':
						state = 74;
						break;
					case 'U':
					case 'u':
						state = 128;
						break;
					default:
					{
						return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
					}
					break;
				case 72:
					switch (character)
					{
					case 'Z':
					case 'z':
						state = 128;
						break;
					case 'L':
						state = 129;
						break;
					case 'l':
						state = 130;
						break;
					default:
					{
						return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
					}
					break;
				case 73:
					switch (character)
					{
					case '\'':
						state = 131;
						break;
					case '.':
						state = 132;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
						{
							state = 133;
							break;
						}
						else
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 74:
					switch (character)
					{
					case 'U':
					case 'u':
						state = 128;
						break;
					default:
					{
						return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
					}
					break;
				case 75:
					switch (character)
					{
					case 'l':
						state = 74;
						break;
					case 'U':
					case 'u':
						state = 128;
						break;
					default:
					{
						return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
					}
					break;
				case 76:
					if ((character >= '0' && character <= '9'))
					{
						state = 14;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 77:
				{
					return TerminalData(Terminal::OP_LTE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
				}
				break;
				case 78:
				{
					return TerminalData(Terminal::OP_EQ, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
				}
				break;
				case 79:
				{
					return TerminalData(Terminal::OP_GTE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
				}
				break;
				case 80:
					switch (character)
					{
					case 195:
						state = 81;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 82;
						break;
					case 201:
						state = 83;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							// state = 80;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 81:
					if ((character >= 128 && character != 151 && character != 183 && character <= 191))
					{
						state = 80;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 82:
					if ((character >= 128 && character <= 191))
					{
						state = 80;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 83:
					if ((character >= 128 && character <= 143))
					{
						state = 80;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 84:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'c':
						state = 134;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'c' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 85:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_BY, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 86:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 's':
						state = 135;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 's' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 87:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'u':
						state = 136;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'u' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_DO, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 88:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 's':
						state = 137;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 's' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 89:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'p':
						state = 138;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'p' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 90:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'o':
						state = 139;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'o' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 91:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'r':
						state = 140;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'r' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 92:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'n':
						state = 141;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'n' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 93:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'o':
						state = 142;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'o' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 94:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_IF, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 95:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'p':
						state = 143;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'p' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 96:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 't':
						state = 144;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 't' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 97:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'i':
						state = 145;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'i' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 98:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'd':
						state = 146;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'd' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 99:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'o':
						state = 147;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'o' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 100:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'b':
						state = 148;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'b' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 101:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 't':
						state = 149;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 't' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 102:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'r':
						state = 150;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'r' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 103:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'b':
						state = 151;
						break;
					case 'k':
						state = 152;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'b' && character != 'k' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 104:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'p':
						state = 153;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'p' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 105:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'n':
						state = 154;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'n' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 106:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'e':
						state = 155;
						break;
					case 'i':
						state = 156;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'e' && character != 'i' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 107:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'e':
						state = 157;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'e' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 108:
				{
					return TerminalData(Terminal::OP_OR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
				}
				break;
				case 109:
					if ((character >= '0' && character <= '7'))
					{
						state = 158;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 110:
					if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
					{
						state = 159;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 111:
					if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
					{
						state = 160;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 112:
					if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
					{
						state = 161;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 113:
				{
					return TerminalData(Terminal::CHAR_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
				}
				break;
				case 114:
					if ((character >= '0' && character <= '7'))
					{
						state = 162;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 115:
					if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
					{
						state = 163;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 116:
					if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
					{
						state = 164;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 117:
					if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
					{
						state = 165;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 118:
				{
					return TerminalData(Terminal::UNINITIALIZED, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
				}
				break;
				case 119:
					if ((character >= '0' && character <= '9'))
					{
						state = 61;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 120:
					switch (character)
					{
					case '+':
					case '-':
						state = 166;
						break;
					default:
						if ((character >= '0' && character <= '9'))
						{
							state = 167;
							break;
						}
						else
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 121:
				{
					return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
				}
				break;
				case 122:
					switch (character)
					{
					case '+':
					case '-':
						state = 168;
						break;
					default:
						if ((character >= '0' && character <= '9'))
						{
							state = 169;
							break;
						}
						else
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 123:
					if ((character >= '0' && character <= '9'))
					{
						state = 68;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 124:
					switch (character)
					{
					case '0':
					case '1':
						state = 125;
						break;
					default:
					{
						return Terminal::ERROR;
					}
					break;
					}
					break;
				case 125:
					switch (character)
					{
					case 'L':
						state = 71;
						break;
					case 'U':
					case 'u':
						state = 72;
						break;
					case 'Z':
					case 'z':
						state = 74;
						break;
					case 'l':
						state = 75;
						break;
					case '\'':
						state = 124;
						break;
					case '0':
					case '1':
						// state = 125;
						break;
					default:
					{
						return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
					}
					break;
				case 126:
					if ((character >= '0' && character <= '9'))
					{
						state = 127;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 127:
					switch (character)
					{
					case 'F':
					case 'L':
					case 'f':
					case 'l':
						state = 121;
						break;
					case '\'':
						state = 126;
						break;
					default:
						if ((character >= '0' && character <= '9'))
						{
							// state = 127;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 128:
				{
					return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
				}
				break;
				case 129:
					switch (character)
					{
					case 'L':
						state = 128;
						break;
					default:
					{
						return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
					}
					break;
				case 130:
					switch (character)
					{
					case 'l':
						state = 128;
						break;
					default:
					{
						return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
					}
					break;
				case 131:
					if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
					{
						state = 170;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 132:
					if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
					{
						state = 171;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 133:
					switch (character)
					{
					case 'L':
						state = 71;
						break;
					case 'U':
					case 'u':
						state = 72;
						break;
					case 'Z':
					case 'z':
						state = 74;
						break;
					case 'l':
						state = 75;
						break;
					case '\'':
						state = 172;
						break;
					case '.':
						state = 173;
						break;
					case 'P':
					case 'p':
						state = 174;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
						{
							// state = 133;
							break;
						}
						else
						{
							return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 134:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_ASC, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 135:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'c':
						state = 175;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'c' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 136:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'b':
						state = 176;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'b' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 137:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'e':
						state = 177;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'e' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 138:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'o':
						state = 178;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'o' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 139:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'a':
						state = 179;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character <= '_') || (character >= 'b' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 140:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_FOR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 141:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'c':
						state = 180;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'c' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 142:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'u':
						state = 181;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'u' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 143:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'o':
						state = 182;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'o' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 144:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case '1':
						state = 183;
						break;
					case '3':
						state = 184;
						break;
					case '6':
						state = 185;
						break;
					case '8':
						state = 186;
						break;
					default:
						if ((character >= '0' && character != '1' && character != '3' && character != '6' && character != '8' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 145:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'n':
						state = 187;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'n' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 146:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'u':
						state = 188;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'u' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 147:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'c':
						state = 189;
						break;
					case 'j':
						state = 190;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'c' && character != 'j' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 148:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'l':
						state = 191;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'l' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 149:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'u':
						state = 192;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'u' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 150:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 't':
						state = 193;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 't' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 151:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'l':
						state = 194;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'l' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 152:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'e':
						state = 195;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'e' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 153:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'l':
						state = 196;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'l' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 154:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 't':
						state = 197;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 't' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 155:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'r':
						state = 198;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'r' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 156:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'l':
						state = 199;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'l' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 157:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'l':
						state = 200;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'l' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 158:
					if ((character >= '0' && character <= '7'))
					{
						state = 3;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 159:
					if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
					{
						state = 201;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 160:
					if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
					{
						state = 112;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 161:
					if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
					{
						state = 3;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 162:
					if ((character >= '0' && character <= '7'))
					{
						state = 52;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 163:
					if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
					{
						state = 202;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 164:
					if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
					{
						state = 117;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 165:
					if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
					{
						state = 52;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 166:
					if ((character >= '0' && character <= '9'))
					{
						state = 167;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 167:
					switch (character)
					{
					case 'F':
					case 'L':
					case 'f':
					case 'l':
						state = 121;
						break;
					case '\'':
						state = 166;
						break;
					default:
						if ((character >= '0' && character <= '9'))
						{
							// state = 167;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 168:
					if ((character >= '0' && character <= '9'))
					{
						state = 169;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 169:
					switch (character)
					{
					case 'F':
					case 'L':
					case 'f':
					case 'l':
						state = 121;
						break;
					case '\'':
						state = 168;
						break;
					default:
						if ((character >= '0' && character <= '9'))
						{
							// state = 169;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 170:
					switch (character)
					{
					case 'L':
						state = 71;
						break;
					case 'U':
					case 'u':
						state = 72;
						break;
					case 'Z':
					case 'z':
						state = 74;
						break;
					case 'l':
						state = 75;
						break;
					case '\'':
						state = 131;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
						{
							// state = 170;
							break;
						}
						else
						{
							return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 171:
					switch (character)
					{
					case 'L':
					case 'l':
						state = 121;
						break;
					case '\'':
						state = 132;
						break;
					case 'P':
					case 'p':
						state = 203;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
						{
							// state = 171;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 172:
					if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
					{
						state = 133;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 173:
					switch (character)
					{
					case 'L':
					case 'l':
						state = 121;
						break;
					case 'P':
					case 'p':
						state = 204;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
						{
							state = 171;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 174:
					switch (character)
					{
					case '+':
					case '-':
						state = 205;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
						{
							state = 206;
							break;
						}
						else
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 175:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_DESC, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 176:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'l':
						state = 207;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'l' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 177:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_ELSE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 178:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'r':
						state = 208;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'r' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 179:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 't':
						state = 209;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 't' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 180:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 't':
						state = 210;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 't' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 181:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'p':
						state = 211;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'p' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 182:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'r':
						state = 212;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'r' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 183:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case '6':
						state = 213;
						break;
					default:
						if ((character >= '0' && character != '6' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 184:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case '2':
						state = 214;
						break;
					default:
						if ((character >= '0' && character != '2' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 185:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case '4':
						state = 215;
						break;
					default:
						if ((character >= '0' && character != '4' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 186:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_INT8, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 187:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_JOIN, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 188:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'l':
						state = 216;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'l' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 189:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'e':
						state = 217;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'e' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 190:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'e':
						state = 218;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'e' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 191:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'i':
						state = 219;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'i' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 192:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'r':
						state = 220;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'r' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 193:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_SORT, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 194:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'e':
						state = 221;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'e' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 195:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_TAKE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 196:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'e':
						state = 222;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'e' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 197:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case '1':
						state = 223;
						break;
					case '3':
						state = 224;
						break;
					case '6':
						state = 225;
						break;
					case '8':
						state = 226;
						break;
					default:
						if ((character >= '0' && character != '1' && character != '3' && character != '6' && character != '8' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 198:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'e':
						state = 227;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'e' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 199:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'e':
						state = 228;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'e' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 200:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'd':
						state = 229;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'd' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 201:
					if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
					{
						state = 230;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 202:
					if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
					{
						state = 231;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 203:
					switch (character)
					{
					case '+':
					case '-':
						state = 232;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
						{
							state = 233;
							break;
						}
						else
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 204:
					switch (character)
					{
					case '+':
					case '-':
						state = 234;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
						{
							state = 235;
							break;
						}
						else
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 205:
					if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
					{
						state = 206;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 206:
					switch (character)
					{
					case 'L':
					case 'l':
						state = 121;
						break;
					case '\'':
						state = 205;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
						{
							// state = 206;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 207:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'e':
						state = 236;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'e' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 208:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 't':
						state = 237;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 't' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 209:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_FLOAT, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 210:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'i':
						state = 238;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'i' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 211:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_GROUP, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 212:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 't':
						state = 239;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 't' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 213:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_INT16, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 214:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_INT32, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 215:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_INT64, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 216:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'e':
						state = 240;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'e' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 217:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'd':
						state = 241;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'd' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 218:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'c':
						state = 242;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'c' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 219:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'c':
						state = 243;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'c' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 220:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'n':
						state = 244;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'n' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 221:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_TABLE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 222:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_TUPLE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 223:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case '6':
						state = 245;
						break;
					default:
						if ((character >= '0' && character != '6' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 224:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case '2':
						state = 246;
						break;
					default:
						if ((character >= '0' && character != '2' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 225:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case '4':
						state = 247;
						break;
					default:
						if ((character >= '0' && character != '4' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 226:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_UINT8, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 227:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_WHERE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 228:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_WHILE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 229:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_YIELD, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 230:
					if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
					{
						state = 111;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 231:
					if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
					{
						state = 116;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 232:
					if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
					{
						state = 233;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 233:
					switch (character)
					{
					case 'L':
					case 'l':
						state = 121;
						break;
					case '\'':
						state = 232;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
						{
							// state = 233;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 234:
					if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
					{
						state = 235;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 235:
					switch (character)
					{
					case 'L':
					case 'l':
						state = 121;
						break;
					case '\'':
						state = 234;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f'))
						{
							// state = 235;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 236:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_DOUBLE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 237:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_EXPORT, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 238:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'o':
						state = 248;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'o' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 239:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_IMPORT, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 240:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_MODULE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 241:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'u':
						state = 249;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'u' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 242:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 't':
						state = 250;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 't' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 243:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_PUBLIC, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 244:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_RETURN, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 245:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_UINT16, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 246:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_UINT32, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 247:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_UINT64, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 248:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'n':
						state = 251;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'n' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 249:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'r':
						state = 252;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'r' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 250:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_PROJECT, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 251:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_FUNCTION, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 252:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					case 'e':
						state = 253;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character != 'e' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 253:
					switch (character)
					{
					case 195:
						state = 42;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 43;
						break;
					case 201:
						state = 44;
						break;
					default:
						if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= '_' && character != '`' && character <= 'z'))
						{
							state = 20;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_PROCEDURE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				default:
					return Terminal::ERROR;
				}
				++current_text_index;
			}
		}
	};

}
