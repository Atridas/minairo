// Auto-generated file. Do not manually modify

module;

#include <cassert>

#include <any>

export module Minairo.Scanner;

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
		BOOL_LITERAL,
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
		OP_SEMICOLON,
		OP_MUL,
		OP_DIV,
		OP_MOD,
		OP_ADD,
		OP_SUB,
		OP_NOT,
		OP_BIT_NOT,
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
		OP_PARENTHESIS_OPEN,
		OP_PARENTHESIS_CLOSE,
		UNINITIALIZED,
		IDENTIFIER,
		COUNT
	};
	
	inline const char* to_string(Terminal terminal)
	{
		switch(terminal)
		{
		case Terminal::ERROR: return "ERROR";
		case Terminal::END: return "END";
		case Terminal::INTEGER_LITERAL: return "INTEGER_LITERAL";
		case Terminal::FLOAT_LITERAL: return "FLOAT_LITERAL";
		case Terminal::CHAR_LITERAL: return "CHAR_LITERAL";
		case Terminal::STRING_LITERAL: return "STRING_LITERAL";
		case Terminal::BOOL_LITERAL: return "BOOL_LITERAL";
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
		case Terminal::OP_SEMICOLON: return "OP_SEMICOLON";
		case Terminal::OP_MUL: return "OP_MUL";
		case Terminal::OP_DIV: return "OP_DIV";
		case Terminal::OP_MOD: return "OP_MOD";
		case Terminal::OP_ADD: return "OP_ADD";
		case Terminal::OP_SUB: return "OP_SUB";
		case Terminal::OP_NOT: return "OP_NOT";
		case Terminal::OP_BIT_NOT: return "OP_BIT_NOT";
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
		case Terminal::OP_PARENTHESIS_OPEN: return "OP_PARENTHESIS_OPEN";
		case Terminal::OP_PARENTHESIS_CLOSE: return "OP_PARENTHESIS_CLOSE";
		case Terminal::UNINITIALIZED: return "UNINITIALIZED";
		case Terminal::IDENTIFIER: return "IDENTIFIER";
		case Terminal::COUNT: return "COUNT";
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
					case '(':
						state = 7;
						break;
					case ')':
						state = 8;
						break;
					case '*':
						state = 9;
						break;
					case '+':
						state = 10;
						break;
					case ',':
						state = 11;
						break;
					case '-':
						state = 12;
						break;
					case '.':
						state = 13;
						break;
					case '/':
						state = 14;
						break;
					case '0':
						state = 15;
						break;
					case ':':
						state = 17;
						break;
					case ';':
						state = 18;
						break;
					case '<':
						state = 19;
						break;
					case '=':
						state = 20;
						break;
					case '>':
						state = 21;
						break;
					case '?':
						state = 22;
						break;
					case 'L':
					case 'U':
						state = 24;
						break;
					case '^':
						state = 25;
						break;
					case '_':
						state = 26;
						break;
					case 'a':
						state = 27;
						break;
					case 'b':
						state = 28;
						break;
					case 'd':
						state = 29;
						break;
					case 'e':
						state = 30;
						break;
					case 'f':
						state = 31;
						break;
					case 'g':
						state = 32;
						break;
					case 'i':
						state = 33;
						break;
					case 'j':
						state = 34;
						break;
					case 'm':
						state = 35;
						break;
					case 'p':
						state = 36;
						break;
					case 'r':
						state = 37;
						break;
					case 's':
						state = 38;
						break;
					case 't':
						state = 39;
						break;
					case 'u':
						state = 40;
						break;
					case 'w':
						state = 41;
						break;
					case 'y':
						state = 42;
						break;
					case '|':
						state = 43;
						break;
					case '~':
						state = 44;
						break;
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '1' && character <= '9' ) )
						{
							state = 16;
							break;
						}
						if ( ( character >= 'A' && character != 'L' && character != 'U' && character <= 'Z' ) || ( character >= 'c' && character <= 'c' ) || ( character >= 'h' && character <= 'h' ) || ( character >= 'k' && character != 'm' && character != 'p' && character <= 'q' ) || ( character >= 'v' && character != 'w' && character != 'y' && character <= 'z' ) )
						{
							state = 23;
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
						state = 48;
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
						state = 49;
						break;
					case '\\':
						state = 50;
						break;
					case 195:
						state = 51;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 52;
						break;
					case 201:
						state = 53;
						break;
					default:
						if ( ( character >= 'A' && character <= 'Z' ) || ( character >= 'a' && character <= 'z' ) )
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
						state = 54;
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
						state = 56;
						break;
					case 195:
						state = 57;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 58;
						break;
					case 201:
						state = 59;
						break;
					default:
						if ( ( character >= 'A' && character <= 'Z' ) || ( character >= 'a' && character <= 'z' ) )
						{
							state = 55;
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
					{
						return TerminalData(Terminal::OP_PARENTHESIS_OPEN, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 8:
					{
						return TerminalData(Terminal::OP_PARENTHESIS_CLOSE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 9:
					switch (character)
					{
					case '=':
						state = 60;
						break;
					default:
						{
							return TerminalData(Terminal::OP_MUL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 10:
					switch (character)
					{
					case '=':
						state = 61;
						break;
					default:
						{
							return TerminalData(Terminal::OP_ADD, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 11:
					{
						return TerminalData(Terminal::OP_COMMA, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 12:
					switch (character)
					{
					case '-':
						state = 62;
						break;
					case '=':
						state = 63;
						break;
					default:
						{
							return TerminalData(Terminal::OP_SUB, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 13:
					if ( ( character >= '0' && character <= '9' ) )
					{
						state = 64;
						break;
					}
					else
					{
						return TerminalData(Terminal::OP_DOT, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 14:
					switch (character)
					{
					case '*':
						state = 65;
						break;
					case '/':
						state = 66;
						break;
					case '=':
						state = 67;
						break;
					default:
						{
							return TerminalData(Terminal::OP_DIV, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 15:
					switch (character)
					{
					case '\'':
						state = 68;
						break;
					case '.':
						state = 69;
						break;
					case '8':
					case '9':
						state = 71;
						break;
					case 'B':
					case 'b':
						state = 72;
						break;
					case 'E':
					case 'e':
						state = 73;
						break;
					case 'L':
						state = 74;
						break;
					case 'U':
					case 'u':
						state = 75;
						break;
					case 'X':
					case 'x':
						state = 76;
						break;
					case 'Z':
					case 'z':
						state = 77;
						break;
					case 'l':
						state = 78;
						break;
					default:
						if ( ( character >= '0' && character <= '7' ) )
						{
							state = 70;
							break;
						}
						else
						{
							return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 16:
					switch (character)
					{
					case '.':
						state = 69;
						break;
					case 'E':
					case 'e':
						state = 73;
						break;
					case 'L':
						state = 74;
						break;
					case 'U':
					case 'u':
						state = 75;
						break;
					case 'Z':
					case 'z':
						state = 77;
						break;
					case 'l':
						state = 78;
						break;
					case '\'':
						state = 79;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) )
						{
							// state = 16;
							break;
						}
						else
						{
							return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 17:
					{
						return TerminalData(Terminal::OP_COLON, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 18:
					{
						return TerminalData(Terminal::OP_SEMICOLON, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 19:
					switch (character)
					{
					case '=':
						state = 80;
						break;
					default:
						{
							return TerminalData(Terminal::OP_LT, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 20:
					switch (character)
					{
					case '=':
						state = 81;
						break;
					default:
						{
							return TerminalData(Terminal::OP_ASSIGN, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 21:
					switch (character)
					{
					case '=':
						state = 82;
						break;
					default:
						{
							return TerminalData(Terminal::OP_GT, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 22:
					{
						return TerminalData(Terminal::OP_QUEST, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 23:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							// state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 24:
					switch (character)
					{
					case '\"':
						state = 3;
						break;
					case '\'':
						state = 6;
						break;
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
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
					{
						return TerminalData(Terminal::OP_BIT_XOR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 26:
					switch (character)
					{
					case '_':
						// state = 26;
						break;
					case 195:
						state = 84;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 85;
						break;
					case 201:
						state = 86;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= 'a' && character <= 'z' ) )
						{
							state = 83;
							break;
						}
						else
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 27:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 's':
						state = 87;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 's' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'y':
						state = 88;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'y' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'e':
						state = 89;
						break;
					case 'o':
						state = 90;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'e' && character != 'o' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'l':
						state = 91;
						break;
					case 'x':
						state = 92;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'l' && character != 'x' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'a':
						state = 93;
						break;
					case 'l':
						state = 94;
						break;
					case 'o':
						state = 95;
						break;
					case 'u':
						state = 96;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character <= '_' ) || ( character >= 'b' && character != 'l' && character != 'o' && character != 'u' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'r':
						state = 97;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'r' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'f':
						state = 98;
						break;
					case 'm':
						state = 99;
						break;
					case 'n':
						state = 100;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'f' && character <= 'l' ) || ( character >= 'o' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'o':
						state = 101;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'o' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'o':
						state = 102;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'o' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'r':
						state = 103;
						break;
					case 'u':
						state = 104;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'r' && character != 'u' && character <= 'z' ) )
						{
							state = 23;
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
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'e':
						state = 105;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'e' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'o':
						state = 106;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'o' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'a':
						state = 107;
						break;
					case 'r':
						state = 108;
						break;
					case 'u':
						state = 109;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character <= '_' ) || ( character >= 'b' && character != 'r' && character != 'u' && character <= 'z' ) )
						{
							state = 23;
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
					case '\"':
						state = 3;
						break;
					case '\'':
						state = 6;
						break;
					case '8':
						state = 24;
						break;
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'i':
						state = 110;
						break;
					default:
						if ( ( character >= '0' && character != '8' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'i' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 41:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'h':
						state = 111;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'h' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 42:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'i':
						state = 112;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'i' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 43:
					switch (character)
					{
					case '|':
						state = 113;
						break;
					default:
						{
							return TerminalData(Terminal::OP_BIT_OR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 44:
					{
						return TerminalData(Terminal::OP_BIT_NOT, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 45:
					if ( ( character >= 128 && character != 151 && character != 183 && character <= 191 ) )
					{
						state = 23;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 46:
					if ( ( character >= 128 && character <= 191 ) )
					{
						state = 23;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 47:
					if ( ( character >= 128 && character <= 143 ) )
					{
						state = 23;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 48:
					{
						return TerminalData(Terminal::OP_NEQ, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 49:
					{
						return TerminalData(Terminal::STRING_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 50:
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
						if ( ( character >= '\"' && character <= '\"' ) || ( character >= '\'' && character <= '\'' ) || ( character >= '?' && character <= '?' ) || ( character >= '\\' && character <= '\\' ) || ( character >= 'a' && character <= 'b' ) || ( character >= 'f' && character <= 'f' ) || ( character >= 'n' && character <= 'n' ) || ( character >= 'r' && character != 's' && character != 'u' && character <= 'v' ) )
						{
							state = 3;
							break;
						}
						if ( ( character >= '0' && character <= '7' ) )
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
				case 51:
					if ( ( character >= 128 && character != 151 && character != 183 && character <= 191 ) )
					{
						state = 3;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 52:
					if ( ( character >= 128 && character <= 191 ) )
					{
						state = 3;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 53:
					if ( ( character >= 128 && character <= 143 ) )
					{
						state = 3;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 54:
					{
						return TerminalData(Terminal::OP_AND, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 55:
					switch (character)
					{
					case '\'':
						state = 118;
						break;
					default:
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 56:
					switch (character)
					{
					case 'U':
						state = 120;
						break;
					case 'u':
						state = 121;
						break;
					case 'x':
						state = 122;
						break;
					default:
						if ( ( character >= '\"' && character <= '\"' ) || ( character >= '\'' && character <= '\'' ) || ( character >= '?' && character <= '?' ) || ( character >= '\\' && character <= '\\' ) || ( character >= 'a' && character <= 'b' ) || ( character >= 'f' && character <= 'f' ) || ( character >= 'n' && character <= 'n' ) || ( character >= 'r' && character != 's' && character != 'u' && character <= 'v' ) )
						{
							state = 55;
							break;
						}
						if ( ( character >= '0' && character <= '7' ) )
						{
							state = 119;
							break;
						}
						else
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 57:
					if ( ( character >= 128 && character != 151 && character != 183 && character <= 191 ) )
					{
						state = 55;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 58:
					if ( ( character >= 128 && character <= 191 ) )
					{
						state = 55;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 59:
					if ( ( character >= 128 && character <= 143 ) )
					{
						state = 55;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 60:
					{
						return TerminalData(Terminal::OP_ASSIGN_MUL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 61:
					{
						return TerminalData(Terminal::OP_ASSIGN_ADD, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 62:
					switch (character)
					{
					case '-':
						state = 123;
						break;
					default:
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 63:
					{
						return TerminalData(Terminal::OP_ASSIGN_SUB, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 64:
					switch (character)
					{
					case '\'':
						state = 124;
						break;
					case 'E':
					case 'e':
						state = 125;
						break;
					case 'F':
					case 'L':
					case 'f':
					case 'l':
						state = 126;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) )
						{
							// state = 64;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 65:
					{
						int recursivities = 1;
						int comment_state = 0;
						for (;;) 
						{
							bool comment_finished = false;
							switch ( comment_state )
							{
							case 0:
								switch ( text[current_text_index] )
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
								switch ( text[current_text_index] )
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
								switch ( text[current_text_index] )
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
								switch ( text[current_text_index] )
								{
								case 0:
									return Terminal::END;
									break;
								default:
									if ( --recursivities == 0 )
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
								switch ( text[current_text_index] )
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
							if ( comment_finished == true )
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
				case 66:
					{
						++current_text_index;
						while(text[current_text_index] != '\n' && text[current_text_index] != '\r' && text[current_text_index] != '\0')
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
				case 67:
					{
						return TerminalData(Terminal::OP_ASSIGN_DIV, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 68:
					switch (character)
					{
					case '8':
					case '9':
						state = 71;
						break;
					default:
						if ( ( character >= '0' && character <= '7' ) )
						{
							state = 70;
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
					case 'F':
					case 'L':
					case 'f':
					case 'l':
						state = 126;
						break;
					case 'E':
					case 'e':
						state = 127;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) )
						{
							state = 64;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 70:
					switch (character)
					{
					case '\'':
						state = 68;
						break;
					case '.':
						state = 69;
						break;
					case '8':
					case '9':
						state = 71;
						break;
					case 'E':
					case 'e':
						state = 73;
						break;
					case 'L':
						state = 74;
						break;
					case 'U':
					case 'u':
						state = 75;
						break;
					case 'Z':
					case 'z':
						state = 77;
						break;
					case 'l':
						state = 78;
						break;
					default:
						if ( ( character >= '0' && character <= '7' ) )
						{
							// state = 70;
							break;
						}
						else
						{
							return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 71:
					switch (character)
					{
					case '.':
						state = 69;
						break;
					case 'E':
					case 'e':
						state = 73;
						break;
					case '\'':
						state = 128;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) )
						{
							// state = 71;
							break;
						}
						else
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 72:
					switch (character)
					{
					case '\'':
						state = 129;
						break;
					case '0':
					case '1':
						state = 130;
						break;
					default:
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 73:
					switch (character)
					{
					case '+':
					case '-':
						state = 131;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) )
						{
							state = 132;
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
					case 'L':
						state = 77;
						break;
					case 'U':
					case 'u':
						state = 133;
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
					case 'Z':
					case 'z':
						state = 133;
						break;
					case 'L':
						state = 134;
						break;
					case 'l':
						state = 135;
						break;
					default:
						{
							return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 76:
					switch (character)
					{
					case '\'':
						state = 136;
						break;
					case '.':
						state = 137;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
						{
							state = 138;
							break;
						}
						else
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 77:
					switch (character)
					{
					case 'U':
					case 'u':
						state = 133;
						break;
					default:
						{
							return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 78:
					switch (character)
					{
					case 'l':
						state = 77;
						break;
					case 'U':
					case 'u':
						state = 133;
						break;
					default:
						{
							return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 79:
					if ( ( character >= '0' && character <= '9' ) )
					{
						state = 16;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 80:
					{
						return TerminalData(Terminal::OP_LTE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 81:
					{
						return TerminalData(Terminal::OP_EQ, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 82:
					{
						return TerminalData(Terminal::OP_GTE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 83:
					switch (character)
					{
					case 195:
						state = 84;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 85;
						break;
					case 201:
						state = 86;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							// state = 83;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 84:
					if ( ( character >= 128 && character != 151 && character != 183 && character <= 191 ) )
					{
						state = 83;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 85:
					if ( ( character >= 128 && character <= 191 ) )
					{
						state = 83;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 86:
					if ( ( character >= 128 && character <= 143 ) )
					{
						state = 83;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 87:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'c':
						state = 139;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'c' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 88:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_BY, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 89:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 's':
						state = 140;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 's' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'u':
						state = 141;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'u' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_DO, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 91:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 's':
						state = 142;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 's' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'p':
						state = 143;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'p' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'l':
						state = 144;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'l' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'o':
						state = 145;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'o' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 95:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'r':
						state = 146;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'r' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'n':
						state = 147;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'n' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'o':
						state = 148;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'o' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_IF, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 99:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'p':
						state = 149;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'p' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 't':
						state = 150;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 't' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'i':
						state = 151;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'i' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'd':
						state = 152;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'd' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'o':
						state = 153;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'o' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'b':
						state = 154;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'b' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 't':
						state = 155;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 't' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'r':
						state = 156;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'r' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'b':
						state = 157;
						break;
					case 'k':
						state = 158;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'b' && character != 'k' && character <= 'z' ) )
						{
							state = 23;
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
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'u':
						state = 159;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'u' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 109:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'p':
						state = 160;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'p' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 110:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'n':
						state = 161;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'n' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 111:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'e':
						state = 162;
						break;
					case 'i':
						state = 163;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'e' && character != 'i' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 112:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'e':
						state = 164;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'e' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 113:
					{
						return TerminalData(Terminal::OP_OR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 114:
					if ( ( character >= '0' && character <= '7' ) )
					{
						state = 165;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 115:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 166;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 116:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 167;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 117:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 168;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 118:
					{
						return TerminalData(Terminal::CHAR_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 119:
					if ( ( character >= '0' && character <= '7' ) )
					{
						state = 169;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 120:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 170;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 121:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 171;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 122:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 172;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 123:
					{
						return TerminalData(Terminal::UNINITIALIZED, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 124:
					if ( ( character >= '0' && character <= '9' ) )
					{
						state = 64;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 125:
					switch (character)
					{
					case '+':
					case '-':
						state = 173;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) )
						{
							state = 174;
							break;
						}
						else
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 126:
					{
						return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 127:
					switch (character)
					{
					case '+':
					case '-':
						state = 175;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) )
						{
							state = 176;
							break;
						}
						else
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 128:
					if ( ( character >= '0' && character <= '9' ) )
					{
						state = 71;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 129:
					switch (character)
					{
					case '0':
					case '1':
						state = 130;
						break;
					default:
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 130:
					switch (character)
					{
					case 'L':
						state = 74;
						break;
					case 'U':
					case 'u':
						state = 75;
						break;
					case 'Z':
					case 'z':
						state = 77;
						break;
					case 'l':
						state = 78;
						break;
					case '\'':
						state = 129;
						break;
					case '0':
					case '1':
						// state = 130;
						break;
					default:
						{
							return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 131:
					if ( ( character >= '0' && character <= '9' ) )
					{
						state = 132;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 132:
					switch (character)
					{
					case 'F':
					case 'L':
					case 'f':
					case 'l':
						state = 126;
						break;
					case '\'':
						state = 131;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) )
						{
							// state = 132;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 133:
					{
						return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 134:
					switch (character)
					{
					case 'L':
						state = 133;
						break;
					default:
						{
							return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 135:
					switch (character)
					{
					case 'l':
						state = 133;
						break;
					default:
						{
							return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 136:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 177;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 137:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 178;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 138:
					switch (character)
					{
					case 'L':
						state = 74;
						break;
					case 'U':
					case 'u':
						state = 75;
						break;
					case 'Z':
					case 'z':
						state = 77;
						break;
					case 'l':
						state = 78;
						break;
					case '\'':
						state = 179;
						break;
					case '.':
						state = 180;
						break;
					case 'P':
					case 'p':
						state = 181;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
						{
							// state = 138;
							break;
						}
						else
						{
							return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 139:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_ASC, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 140:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'c':
						state = 182;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'c' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 141:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'b':
						state = 183;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'b' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'e':
						state = 184;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'e' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'o':
						state = 185;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'o' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 's':
						state = 159;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 's' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'a':
						state = 186;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character <= '_' ) || ( character >= 'b' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_FOR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 147:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'c':
						state = 187;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'c' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'u':
						state = 188;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'u' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'o':
						state = 189;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'o' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case '1':
						state = 190;
						break;
					case '3':
						state = 191;
						break;
					case '6':
						state = 192;
						break;
					case '8':
						state = 193;
						break;
					default:
						if ( ( character >= '0' && character != '1' && character != '3' && character != '6' && character != '8' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'n':
						state = 194;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'n' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'u':
						state = 195;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'u' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'c':
						state = 196;
						break;
					case 'j':
						state = 197;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'c' && character != 'j' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'l':
						state = 198;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'l' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'u':
						state = 199;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'u' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 't':
						state = 200;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 't' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'l':
						state = 201;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'l' && character <= 'z' ) )
						{
							state = 23;
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
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'e':
						state = 202;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'e' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 159:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'e':
						state = 203;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'e' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 160:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'l':
						state = 204;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'l' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 161:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 't':
						state = 205;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 't' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 162:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'r':
						state = 206;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'r' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 163:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'l':
						state = 207;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'l' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 164:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'l':
						state = 208;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'l' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 165:
					if ( ( character >= '0' && character <= '7' ) )
					{
						state = 3;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 166:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 209;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 167:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 117;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 168:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 3;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 169:
					if ( ( character >= '0' && character <= '7' ) )
					{
						state = 55;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 170:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 210;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 171:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 122;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 172:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 55;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 173:
					if ( ( character >= '0' && character <= '9' ) )
					{
						state = 174;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 174:
					switch (character)
					{
					case 'F':
					case 'L':
					case 'f':
					case 'l':
						state = 126;
						break;
					case '\'':
						state = 173;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) )
						{
							// state = 174;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 175:
					if ( ( character >= '0' && character <= '9' ) )
					{
						state = 176;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 176:
					switch (character)
					{
					case 'F':
					case 'L':
					case 'f':
					case 'l':
						state = 126;
						break;
					case '\'':
						state = 175;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) )
						{
							// state = 176;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 177:
					switch (character)
					{
					case 'L':
						state = 74;
						break;
					case 'U':
					case 'u':
						state = 75;
						break;
					case 'Z':
					case 'z':
						state = 77;
						break;
					case 'l':
						state = 78;
						break;
					case '\'':
						state = 136;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
						{
							// state = 177;
							break;
						}
						else
						{
							return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 178:
					switch (character)
					{
					case 'L':
					case 'l':
						state = 126;
						break;
					case '\'':
						state = 137;
						break;
					case 'P':
					case 'p':
						state = 211;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
						{
							// state = 178;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 179:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 138;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 180:
					switch (character)
					{
					case 'L':
					case 'l':
						state = 126;
						break;
					case 'P':
					case 'p':
						state = 212;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
						{
							state = 178;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 181:
					switch (character)
					{
					case '+':
					case '-':
						state = 213;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
						{
							state = 214;
							break;
						}
						else
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 182:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_DESC, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 183:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'l':
						state = 215;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'l' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_ELSE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 185:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'r':
						state = 216;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'r' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 't':
						state = 217;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 't' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 187:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 't':
						state = 218;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 't' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 188:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'p':
						state = 219;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'p' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'r':
						state = 220;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'r' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case '6':
						state = 221;
						break;
					default:
						if ( ( character >= '0' && character != '6' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case '2':
						state = 222;
						break;
					default:
						if ( ( character >= '0' && character != '2' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case '4':
						state = 223;
						break;
					default:
						if ( ( character >= '0' && character != '4' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_INT8, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 194:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_JOIN, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 195:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'l':
						state = 224;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'l' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 196:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'e':
						state = 225;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'e' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'e':
						state = 226;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'e' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'i':
						state = 227;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'i' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'r':
						state = 228;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'r' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_SORT, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 201:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'e':
						state = 229;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'e' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 202:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_TAKE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 203:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::BOOL_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 204:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'e':
						state = 230;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'e' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 205:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case '1':
						state = 231;
						break;
					case '3':
						state = 232;
						break;
					case '6':
						state = 233;
						break;
					case '8':
						state = 234;
						break;
					default:
						if ( ( character >= '0' && character != '1' && character != '3' && character != '6' && character != '8' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 206:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'e':
						state = 235;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'e' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 207:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'e':
						state = 236;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'e' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'd':
						state = 237;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'd' && character <= 'z' ) )
						{
							state = 23;
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
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 238;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 210:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 239;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 211:
					switch (character)
					{
					case '+':
					case '-':
						state = 240;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
						{
							state = 241;
							break;
						}
						else
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 212:
					switch (character)
					{
					case '+':
					case '-':
						state = 242;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
						{
							state = 243;
							break;
						}
						else
						{
							return Terminal::ERROR;
						}
						break;
					}
					break;
				case 213:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 214;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 214:
					switch (character)
					{
					case 'L':
					case 'l':
						state = 126;
						break;
					case '\'':
						state = 213;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
						{
							// state = 214;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 215:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'e':
						state = 244;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'e' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 216:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 't':
						state = 245;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 't' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_FLOAT, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 218:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'i':
						state = 246;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'i' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_GROUP, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 220:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 't':
						state = 247;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 't' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_INT16, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 222:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_INT32, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 223:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_INT64, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 224:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'e':
						state = 248;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'e' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'd':
						state = 249;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'd' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'c':
						state = 250;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'c' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 227:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'c':
						state = 251;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'c' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 228:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'n':
						state = 252;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'n' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 229:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_TABLE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 230:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_TUPLE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 231:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case '6':
						state = 253;
						break;
					default:
						if ( ( character >= '0' && character != '6' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 232:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case '2':
						state = 254;
						break;
					default:
						if ( ( character >= '0' && character != '2' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 233:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case '4':
						state = 255;
						break;
					default:
						if ( ( character >= '0' && character != '4' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 234:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_UINT8, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 235:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_WHERE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 236:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_WHILE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 237:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_YIELD, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 238:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 116;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 239:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 121;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 240:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 241;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 241:
					switch (character)
					{
					case 'L':
					case 'l':
						state = 126;
						break;
					case '\'':
						state = 240;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
						{
							// state = 241;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 242:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 243;
						break;
					}
					else
					{
						return Terminal::ERROR;
					}
					break;
				case 243:
					switch (character)
					{
					case 'L':
					case 'l':
						state = 126;
						break;
					case '\'':
						state = 242;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
						{
							// state = 243;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 244:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_DOUBLE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 245:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_EXPORT, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 246:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'o':
						state = 256;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'o' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 247:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_IMPORT, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 248:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_MODULE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 249:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'u':
						state = 257;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'u' && character <= 'z' ) )
						{
							state = 23;
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
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 't':
						state = 258;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 't' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 251:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_PUBLIC, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 252:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_RETURN, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 253:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_UINT16, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 254:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_UINT32, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 255:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_UINT64, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 256:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'n':
						state = 259;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'n' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 257:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'r':
						state = 260;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'r' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 258:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_PROJECT, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 259:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::WK_FUNCTION, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 260:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					case 'e':
						state = 261;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'e' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::IDENTIFIER, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 261:
					switch (character)
					{
					case 195:
						state = 45;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 46;
						break;
					case 201:
						state = 47;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
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
