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
		KW_ASC,
		KW_BY,
		KW_DESC,
		KW_EXPORT,
		KW_FUNCTION,
		KW_IMPORT,
		KW_MODULE,
		KW_MULTIFUNCTION,
		KW_PUBLIC,
		KW_TABLE,
		KW_TUPLE,
		KW_DO,
		KW_ELSE,
		KW_FOR,
		KW_FOREACH,
		KW_GROUP,
		KW_IF,
		KW_JOIN,
		KW_PROJECT,
		KW_RETURN,
		KW_SORT,
		KW_TAKE,
		KW_YIELD,
		KW_WHERE,
		KW_WHILE,
		KW_VOID,
		KW_BOOL,
		KW_INT8,
		KW_INT16,
		KW_INT32,
		KW_INT64,
		KW_UINT8,
		KW_UINT16,
		KW_UINT32,
		KW_UINT64,
		KW_FLOAT32,
		KW_FLOAT64,
		KW_TYPEDEF,
		KW_STRING,
		OP_ARROW,
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
		OP_ASSIGN_MOD,
		BRACKET_ROUND_OPEN,
		BRACKET_ROUND_CLOSE,
		BRACKET_SQUARE_OPEN,
		BRACKET_SQUARE_CLOSE,
		BRACKET_CURLY_OPEN,
		BRACKET_CURLY_CLOSE,
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
		case Terminal::KW_ASC: return "KW_ASC";
		case Terminal::KW_BY: return "KW_BY";
		case Terminal::KW_DESC: return "KW_DESC";
		case Terminal::KW_EXPORT: return "KW_EXPORT";
		case Terminal::KW_FUNCTION: return "KW_FUNCTION";
		case Terminal::KW_IMPORT: return "KW_IMPORT";
		case Terminal::KW_MODULE: return "KW_MODULE";
		case Terminal::KW_MULTIFUNCTION: return "KW_MULTIFUNCTION";
		case Terminal::KW_PUBLIC: return "KW_PUBLIC";
		case Terminal::KW_TABLE: return "KW_TABLE";
		case Terminal::KW_TUPLE: return "KW_TUPLE";
		case Terminal::KW_DO: return "KW_DO";
		case Terminal::KW_ELSE: return "KW_ELSE";
		case Terminal::KW_FOR: return "KW_FOR";
		case Terminal::KW_FOREACH: return "KW_FOREACH";
		case Terminal::KW_GROUP: return "KW_GROUP";
		case Terminal::KW_IF: return "KW_IF";
		case Terminal::KW_JOIN: return "KW_JOIN";
		case Terminal::KW_PROJECT: return "KW_PROJECT";
		case Terminal::KW_RETURN: return "KW_RETURN";
		case Terminal::KW_SORT: return "KW_SORT";
		case Terminal::KW_TAKE: return "KW_TAKE";
		case Terminal::KW_YIELD: return "KW_YIELD";
		case Terminal::KW_WHERE: return "KW_WHERE";
		case Terminal::KW_WHILE: return "KW_WHILE";
		case Terminal::KW_VOID: return "KW_VOID";
		case Terminal::KW_BOOL: return "KW_BOOL";
		case Terminal::KW_INT8: return "KW_INT8";
		case Terminal::KW_INT16: return "KW_INT16";
		case Terminal::KW_INT32: return "KW_INT32";
		case Terminal::KW_INT64: return "KW_INT64";
		case Terminal::KW_UINT8: return "KW_UINT8";
		case Terminal::KW_UINT16: return "KW_UINT16";
		case Terminal::KW_UINT32: return "KW_UINT32";
		case Terminal::KW_UINT64: return "KW_UINT64";
		case Terminal::KW_FLOAT32: return "KW_FLOAT32";
		case Terminal::KW_FLOAT64: return "KW_FLOAT64";
		case Terminal::KW_TYPEDEF: return "KW_TYPEDEF";
		case Terminal::KW_STRING: return "KW_STRING";
		case Terminal::OP_ARROW: return "OP_ARROW";
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
		case Terminal::OP_ASSIGN_MOD: return "OP_ASSIGN_MOD";
		case Terminal::BRACKET_ROUND_OPEN: return "BRACKET_ROUND_OPEN";
		case Terminal::BRACKET_ROUND_CLOSE: return "BRACKET_ROUND_CLOSE";
		case Terminal::BRACKET_SQUARE_OPEN: return "BRACKET_SQUARE_OPEN";
		case Terminal::BRACKET_SQUARE_CLOSE: return "BRACKET_SQUARE_CLOSE";
		case Terminal::BRACKET_CURLY_OPEN: return "BRACKET_CURLY_OPEN";
		case Terminal::BRACKET_CURLY_CLOSE: return "BRACKET_CURLY_CLOSE";
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
					case '[':
						state = 24;
						break;
					case ']':
						state = 25;
						break;
					case '^':
						state = 26;
						break;
					case '_':
						state = 27;
						break;
					case 'a':
						state = 28;
						break;
					case 'b':
						state = 29;
						break;
					case 'd':
						state = 30;
						break;
					case 'e':
						state = 31;
						break;
					case 'f':
						state = 32;
						break;
					case 'g':
						state = 33;
						break;
					case 'i':
						state = 34;
						break;
					case 'j':
						state = 35;
						break;
					case 'm':
						state = 36;
						break;
					case 'p':
						state = 37;
						break;
					case 'r':
						state = 38;
						break;
					case 's':
						state = 39;
						break;
					case 't':
						state = 40;
						break;
					case 'u':
						state = 41;
						break;
					case 'v':
						state = 42;
						break;
					case 'w':
						state = 43;
						break;
					case 'y':
						state = 44;
						break;
					case '{':
						state = 45;
						break;
					case '|':
						state = 46;
						break;
					case '}':
						state = 47;
						break;
					case '~':
						state = 48;
						break;
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '1' && character <= '9' ) )
						{
							state = 16;
							break;
						}
						if ( ( character >= 'A' && character <= 'Z' ) || ( character >= 'c' && character <= 'c' ) || ( character >= 'h' && character <= 'h' ) || ( character >= 'k' && character != 'm' && character != 'p' && character <= 'q' ) || ( character >= 'x' && character != 'y' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
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
						state = 52;
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
						state = 53;
						break;
					case '\\':
						state = 54;
						break;
					case 195:
						state = 55;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 56;
						break;
					case 201:
						state = 57;
						break;
					default:
						if ( ( character >= ' ' && character <= ' ' ) || ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= 'a' && character <= 'z' ) )
						{
							// state = 3;
							break;
						}
						else
						{
							return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 4:
					switch (character)
					{
					case '=':
						state = 58;
						break;
					default:
						{
							return TerminalData(Terminal::OP_MOD, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 5:
					switch (character)
					{
					case '&':
						state = 59;
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
						state = 61;
						break;
					case 195:
						state = 62;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 63;
						break;
					case 201:
						state = 64;
						break;
					default:
						if ( ( character >= ' ' && character <= ' ' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= 'a' && character <= 'z' ) )
						{
							state = 60;
							break;
						}
						else
						{
							return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 7:
					{
						return TerminalData(Terminal::BRACKET_ROUND_OPEN, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 8:
					{
						return TerminalData(Terminal::BRACKET_ROUND_CLOSE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 9:
					switch (character)
					{
					case '=':
						state = 65;
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
						state = 66;
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
						state = 67;
						break;
					case '=':
						state = 68;
						break;
					case '>':
						state = 69;
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
						state = 70;
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
						state = 71;
						break;
					case '/':
						state = 72;
						break;
					case '=':
						state = 73;
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
						state = 74;
						break;
					case '.':
						state = 75;
						break;
					case '8':
					case '9':
						state = 77;
						break;
					case 'B':
					case 'b':
						state = 78;
						break;
					case 'E':
					case 'e':
						state = 79;
						break;
					case 'U':
					case 'u':
						state = 80;
						break;
					case 'X':
					case 'x':
						state = 81;
						break;
					default:
						if ( ( character >= '0' && character <= '7' ) )
						{
							state = 76;
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
						state = 75;
						break;
					case 'E':
					case 'e':
						state = 79;
						break;
					case 'U':
					case 'u':
						state = 80;
						break;
					case '\'':
						state = 82;
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
						state = 83;
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
						state = 84;
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
						state = 85;
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
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
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
					{
						return TerminalData(Terminal::BRACKET_SQUARE_OPEN, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 25:
					{
						return TerminalData(Terminal::BRACKET_SQUARE_CLOSE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 26:
					{
						return TerminalData(Terminal::OP_BIT_XOR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 27:
					switch (character)
					{
					case '_':
						// state = 27;
						break;
					case 195:
						state = 87;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 88;
						break;
					case 201:
						state = 89;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= 'a' && character <= 'z' ) )
						{
							state = 86;
							break;
						}
						else
						{
							return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 28:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 's':
						state = 90;
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
				case 29:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'o':
						state = 91;
						break;
					case 'y':
						state = 92;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'o' && character != 'y' && character <= 'z' ) )
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
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'e':
						state = 93;
						break;
					case 'o':
						state = 94;
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
				case 31:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'l':
						state = 95;
						break;
					case 'x':
						state = 96;
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
				case 32:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'a':
						state = 97;
						break;
					case 'l':
						state = 98;
						break;
					case 'o':
						state = 99;
						break;
					case 'u':
						state = 100;
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
				case 33:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'r':
						state = 101;
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
				case 34:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case '1':
						state = 102;
						break;
					case '3':
						state = 103;
						break;
					case '6':
						state = 104;
						break;
					case '8':
						state = 105;
						break;
					case 'f':
						state = 106;
						break;
					case 'm':
						state = 107;
						break;
					case 'n':
						state = 108;
						break;
					default:
						if ( ( character >= '0' && character != '1' && character != '3' && character != '6' && character != '8' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'f' && character <= 'l' ) || ( character >= 'o' && character <= 'z' ) )
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
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'o':
						state = 109;
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
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'o':
						state = 110;
						break;
					case 'u':
						state = 111;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'o' && character != 'u' && character <= 'z' ) )
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
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'r':
						state = 112;
						break;
					case 'u':
						state = 113;
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
				case 38:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'e':
						state = 114;
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
				case 39:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'o':
						state = 115;
						break;
					case 't':
						state = 116;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'o' && character != 't' && character <= 'z' ) )
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
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'a':
						state = 117;
						break;
					case 'r':
						state = 118;
						break;
					case 'u':
						state = 119;
						break;
					case 'y':
						state = 120;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character <= '_' ) || ( character >= 'b' && character != 'r' && character != 'u' && character != 'y' && character <= 'z' ) )
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
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case '1':
						state = 121;
						break;
					case '3':
						state = 122;
						break;
					case '6':
						state = 123;
						break;
					case '8':
						state = 124;
						break;
					case 'i':
						state = 125;
						break;
					default:
						if ( ( character >= '0' && character != '1' && character != '3' && character != '6' && character != '8' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'i' && character <= 'z' ) )
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
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'o':
						state = 126;
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
				case 43:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'h':
						state = 127;
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
				case 44:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'i':
						state = 128;
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
				case 45:
					{
						return TerminalData(Terminal::BRACKET_CURLY_OPEN, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 46:
					switch (character)
					{
					case '|':
						state = 129;
						break;
					default:
						{
							return TerminalData(Terminal::OP_BIT_OR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 47:
					{
						return TerminalData(Terminal::BRACKET_CURLY_CLOSE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 48:
					{
						return TerminalData(Terminal::OP_BIT_NOT, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 49:
					if ( ( character >= 128 && character != 151 && character != 183 && character <= 191 ) )
					{
						state = 23;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 50:
					if ( ( character >= 128 && character <= 191 ) )
					{
						state = 23;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 51:
					if ( ( character >= 128 && character <= 143 ) )
					{
						state = 23;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 52:
					{
						return TerminalData(Terminal::OP_NEQ, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 53:
					{
						return TerminalData(Terminal::STRING_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 54:
					switch (character)
					{
					case 'U':
						state = 131;
						break;
					case 'u':
						state = 132;
						break;
					case 'x':
						state = 133;
						break;
					default:
						if ( ( character >= '\"' && character <= '\"' ) || ( character >= '\'' && character <= '\'' ) || ( character >= '?' && character <= '?' ) || ( character >= '\\' && character <= '\\' ) || ( character >= 'a' && character <= 'b' ) || ( character >= 'f' && character <= 'f' ) || ( character >= 'n' && character <= 'n' ) || ( character >= 'r' && character != 's' && character != 'u' && character <= 'v' ) )
						{
							state = 3;
							break;
						}
						if ( ( character >= '0' && character <= '7' ) )
						{
							state = 130;
							break;
						}
						else
						{
							return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 55:
					if ( ( character >= 128 && character != 151 && character != 183 && character <= 191 ) )
					{
						state = 3;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 56:
					if ( ( character >= 128 && character <= 191 ) )
					{
						state = 3;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 57:
					if ( ( character >= 128 && character <= 143 ) )
					{
						state = 3;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 58:
					{
						return TerminalData(Terminal::OP_ASSIGN_MOD, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 59:
					{
						return TerminalData(Terminal::OP_AND, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 60:
					switch (character)
					{
					case '\'':
						state = 134;
						break;
					default:
						{
							return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 61:
					switch (character)
					{
					case 'U':
						state = 136;
						break;
					case 'u':
						state = 137;
						break;
					case 'x':
						state = 138;
						break;
					default:
						if ( ( character >= '\"' && character <= '\"' ) || ( character >= '\'' && character <= '\'' ) || ( character >= '?' && character <= '?' ) || ( character >= '\\' && character <= '\\' ) || ( character >= 'a' && character <= 'b' ) || ( character >= 'f' && character <= 'f' ) || ( character >= 'n' && character <= 'n' ) || ( character >= 'r' && character != 's' && character != 'u' && character <= 'v' ) )
						{
							state = 60;
							break;
						}
						if ( ( character >= '0' && character <= '7' ) )
						{
							state = 135;
							break;
						}
						else
						{
							return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 62:
					if ( ( character >= 128 && character != 151 && character != 183 && character <= 191 ) )
					{
						state = 60;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 63:
					if ( ( character >= 128 && character <= 191 ) )
					{
						state = 60;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 64:
					if ( ( character >= 128 && character <= 143 ) )
					{
						state = 60;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 65:
					{
						return TerminalData(Terminal::OP_ASSIGN_MUL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 66:
					{
						return TerminalData(Terminal::OP_ASSIGN_ADD, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 67:
					switch (character)
					{
					case '-':
						state = 139;
						break;
					default:
						{
							return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 68:
					{
						return TerminalData(Terminal::OP_ASSIGN_SUB, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 69:
					{
						return TerminalData(Terminal::OP_ARROW, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 70:
					switch (character)
					{
					case '\'':
						state = 140;
						break;
					case 'E':
					case 'e':
						state = 141;
						break;
					case 'F':
					case 'L':
					case 'f':
					case 'l':
						state = 142;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) )
						{
							// state = 70;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 71:
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
				case 72:
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
				case 73:
					{
						return TerminalData(Terminal::OP_ASSIGN_DIV, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 74:
					switch (character)
					{
					case '8':
					case '9':
						state = 77;
						break;
					default:
						if ( ( character >= '0' && character <= '7' ) )
						{
							state = 76;
							break;
						}
						else
						{
							return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 75:
					switch (character)
					{
					case 'F':
					case 'L':
					case 'f':
					case 'l':
						state = 142;
						break;
					case 'E':
					case 'e':
						state = 143;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) )
						{
							state = 70;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 76:
					switch (character)
					{
					case '\'':
						state = 74;
						break;
					case '.':
						state = 75;
						break;
					case '8':
					case '9':
						state = 77;
						break;
					case 'E':
					case 'e':
						state = 79;
						break;
					case 'U':
					case 'u':
						state = 80;
						break;
					default:
						if ( ( character >= '0' && character <= '7' ) )
						{
							// state = 76;
							break;
						}
						else
						{
							return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 77:
					switch (character)
					{
					case '.':
						state = 75;
						break;
					case 'E':
					case 'e':
						state = 79;
						break;
					case '\'':
						state = 144;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) )
						{
							// state = 77;
							break;
						}
						else
						{
							return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 78:
					switch (character)
					{
					case '\'':
						state = 145;
						break;
					case '0':
					case '1':
						state = 146;
						break;
					default:
						{
							return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 79:
					switch (character)
					{
					case '+':
					case '-':
						state = 147;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) )
						{
							state = 148;
							break;
						}
						else
						{
							return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 80:
					{
						return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 81:
					switch (character)
					{
					case '\'':
						state = 149;
						break;
					case '.':
						state = 150;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
						{
							state = 151;
							break;
						}
						else
						{
							return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 82:
					if ( ( character >= '0' && character <= '9' ) )
					{
						state = 16;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 83:
					{
						return TerminalData(Terminal::OP_LTE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 84:
					{
						return TerminalData(Terminal::OP_EQ, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 85:
					{
						return TerminalData(Terminal::OP_GTE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 86:
					switch (character)
					{
					case 195:
						state = 87;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 88;
						break;
					case 201:
						state = 89;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							// state = 86;
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
					if ( ( character >= 128 && character != 151 && character != 183 && character <= 191 ) )
					{
						state = 86;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 88:
					if ( ( character >= 128 && character <= 191 ) )
					{
						state = 86;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 89:
					if ( ( character >= 128 && character <= 143 ) )
					{
						state = 86;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 90:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'c':
						state = 152;
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
				case 91:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
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
				case 92:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_BY, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 93:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 's':
						state = 154;
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
				case 94:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'u':
						state = 155;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'u' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_DO, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 95:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 's':
						state = 156;
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
				case 96:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'p':
						state = 157;
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
				case 97:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'l':
						state = 158;
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
				case 98:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'o':
						state = 159;
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
				case 99:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'r':
						state = 160;
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
				case 100:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
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
				case 101:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'o':
						state = 162;
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
				case 102:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case '6':
						state = 163;
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
				case 103:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case '2':
						state = 164;
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
				case 104:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case '4':
						state = 165;
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
				case 105:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_INT8, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 106:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_IF, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 107:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'p':
						state = 166;
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
				case 108:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 't':
						state = 167;
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
				case 109:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'i':
						state = 168;
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
				case 110:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'd':
						state = 169;
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
				case 111:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'l':
						state = 170;
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
				case 112:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'o':
						state = 171;
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
				case 113:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'b':
						state = 172;
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
				case 114:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 't':
						state = 173;
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
				case 115:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'r':
						state = 174;
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
				case 116:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'r':
						state = 175;
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
				case 117:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'b':
						state = 176;
						break;
					case 'k':
						state = 177;
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
				case 118:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'u':
						state = 178;
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
				case 119:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'p':
						state = 179;
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
				case 120:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'p':
						state = 180;
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
				case 121:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case '6':
						state = 181;
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
				case 122:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case '2':
						state = 182;
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
				case 123:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case '4':
						state = 183;
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
				case 124:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_UINT8, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 125:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'n':
						state = 184;
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
				case 126:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'i':
						state = 185;
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
				case 127:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'e':
						state = 186;
						break;
					case 'i':
						state = 187;
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
				case 128:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'e':
						state = 188;
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
				case 129:
					{
						return TerminalData(Terminal::OP_OR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 130:
					if ( ( character >= '0' && character <= '7' ) )
					{
						state = 189;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 131:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 190;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 132:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 191;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 133:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 192;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 134:
					{
						return TerminalData(Terminal::CHAR_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 135:
					if ( ( character >= '0' && character <= '7' ) )
					{
						state = 193;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 136:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 194;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 137:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 195;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 138:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 196;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 139:
					{
						return TerminalData(Terminal::UNINITIALIZED, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 140:
					if ( ( character >= '0' && character <= '9' ) )
					{
						state = 70;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 141:
					switch (character)
					{
					case '+':
					case '-':
						state = 197;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) )
						{
							state = 198;
							break;
						}
						else
						{
							return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 142:
					{
						return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 143:
					switch (character)
					{
					case '+':
					case '-':
						state = 199;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) )
						{
							state = 200;
							break;
						}
						else
						{
							return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 144:
					if ( ( character >= '0' && character <= '9' ) )
					{
						state = 77;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 145:
					switch (character)
					{
					case '0':
					case '1':
						state = 146;
						break;
					default:
						{
							return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 146:
					switch (character)
					{
					case 'U':
					case 'u':
						state = 80;
						break;
					case '\'':
						state = 145;
						break;
					case '0':
					case '1':
						// state = 146;
						break;
					default:
						{
							return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 147:
					if ( ( character >= '0' && character <= '9' ) )
					{
						state = 148;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 148:
					switch (character)
					{
					case 'F':
					case 'L':
					case 'f':
					case 'l':
						state = 142;
						break;
					case '\'':
						state = 147;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) )
						{
							// state = 148;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 149:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 201;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 150:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 202;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 151:
					switch (character)
					{
					case 'U':
					case 'u':
						state = 80;
						break;
					case '\'':
						state = 203;
						break;
					case '.':
						state = 204;
						break;
					case 'P':
					case 'p':
						state = 205;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
						{
							// state = 151;
							break;
						}
						else
						{
							return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 152:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_ASC, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 153:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'l':
						state = 206;
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
				case 154:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'c':
						state = 207;
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
				case 155:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'b':
						state = 208;
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
				case 156:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'e':
						state = 209;
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
				case 157:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'o':
						state = 210;
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
				case 158:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 's':
						state = 178;
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
				case 159:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'a':
						state = 211;
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
				case 160:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'e':
						state = 212;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'e' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_FOR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 161:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'c':
						state = 213;
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
				case 162:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'u':
						state = 214;
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
				case 163:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_INT16, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 164:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_INT32, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 165:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_INT64, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 166:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'o':
						state = 215;
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
				case 167:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case '1':
						state = 102;
						break;
					case '3':
						state = 103;
						break;
					case '6':
						state = 104;
						break;
					case '8':
						state = 105;
						break;
					default:
						if ( ( character >= '0' && character != '1' && character != '3' && character != '6' && character != '8' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_INT32, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 168:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'n':
						state = 216;
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
				case 169:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'u':
						state = 217;
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
				case 170:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
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
				case 171:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'j':
						state = 219;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'j' && character <= 'z' ) )
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
				case 172:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'l':
						state = 220;
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
				case 173:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'u':
						state = 221;
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
				case 174:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 't':
						state = 222;
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
				case 175:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'i':
						state = 223;
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
				case 176:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
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
				case 177:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
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
				case 178:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
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
				case 179:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'l':
						state = 227;
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
				case 180:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'e':
						state = 228;
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
				case 181:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_UINT16, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 182:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_UINT32, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 183:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_UINT64, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 184:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 't':
						state = 229;
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
				case 185:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'd':
						state = 230;
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
				case 186:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'r':
						state = 231;
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
				case 187:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'l':
						state = 232;
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
				case 188:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'l':
						state = 233;
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
				case 189:
					if ( ( character >= '0' && character <= '7' ) )
					{
						state = 3;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 190:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 234;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 191:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 133;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 192:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 3;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 193:
					if ( ( character >= '0' && character <= '7' ) )
					{
						state = 60;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 194:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 235;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 195:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 138;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 196:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 60;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 197:
					if ( ( character >= '0' && character <= '9' ) )
					{
						state = 198;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 198:
					switch (character)
					{
					case 'F':
					case 'L':
					case 'f':
					case 'l':
						state = 142;
						break;
					case '\'':
						state = 197;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) )
						{
							// state = 198;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 199:
					if ( ( character >= '0' && character <= '9' ) )
					{
						state = 200;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 200:
					switch (character)
					{
					case 'F':
					case 'L':
					case 'f':
					case 'l':
						state = 142;
						break;
					case '\'':
						state = 199;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) )
						{
							// state = 200;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 201:
					switch (character)
					{
					case 'U':
					case 'u':
						state = 80;
						break;
					case '\'':
						state = 149;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
						{
							// state = 201;
							break;
						}
						else
						{
							return TerminalData(Terminal::INTEGER_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 202:
					switch (character)
					{
					case 'L':
					case 'l':
						state = 142;
						break;
					case '\'':
						state = 150;
						break;
					case 'P':
					case 'p':
						state = 236;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
						{
							// state = 202;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 203:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 151;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 204:
					switch (character)
					{
					case 'L':
					case 'l':
						state = 142;
						break;
					case 'P':
					case 'p':
						state = 237;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
						{
							state = 202;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 205:
					switch (character)
					{
					case '+':
					case '-':
						state = 238;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
						{
							state = 239;
							break;
						}
						else
						{
							return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 206:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'e':
						state = 240;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'e' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_BOOL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 207:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_DESC, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 208:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'l':
						state = 241;
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
				case 209:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_ELSE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 210:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'r':
						state = 242;
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
				case 211:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 't':
						state = 243;
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
				case 212:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'a':
						state = 244;
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
				case 213:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
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
				case 214:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'p':
						state = 246;
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
				case 215:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'r':
						state = 247;
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
				case 216:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_JOIN, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 217:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'l':
						state = 248;
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
				case 218:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'i':
						state = 249;
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
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'e':
						state = 250;
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
				case 220:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'i':
						state = 251;
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
				case 221:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'r':
						state = 252;
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
				case 222:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_SORT, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 223:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'n':
						state = 253;
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
				case 224:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'e':
						state = 254;
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
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_TAKE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 226:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
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
				case 227:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'e':
						state = 255;
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
				case 228:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'd':
						state = 256;
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
				case 229:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case '1':
						state = 121;
						break;
					case '3':
						state = 122;
						break;
					case '6':
						state = 123;
						break;
					case '8':
						state = 124;
						break;
					default:
						if ( ( character >= '0' && character != '1' && character != '3' && character != '6' && character != '8' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_UINT32, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 230:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_VOID, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 231:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'e':
						state = 257;
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
				case 232:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'e':
						state = 258;
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
				case 233:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'd':
						state = 259;
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
				case 234:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 260;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 235:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 261;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 236:
					switch (character)
					{
					case '+':
					case '-':
						state = 262;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
						{
							state = 263;
							break;
						}
						else
						{
							return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 237:
					switch (character)
					{
					case '+':
					case '-':
						state = 264;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
						{
							state = 265;
							break;
						}
						else
						{
							return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 238:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 239;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 239:
					switch (character)
					{
					case 'L':
					case 'l':
						state = 142;
						break;
					case '\'':
						state = 238;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
						{
							// state = 239;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 240:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'a':
						state = 266;
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
				case 241:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'e':
						state = 267;
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
				case 242:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 't':
						state = 268;
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
				case 243:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case '3':
						state = 269;
						break;
					case '6':
						state = 270;
						break;
					default:
						if ( ( character >= '0' && character != '3' && character != '6' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_FLOAT32, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 244:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'c':
						state = 271;
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
				case 245:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'i':
						state = 272;
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
				case 246:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_GROUP, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 247:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 't':
						state = 273;
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
				case 248:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'e':
						state = 274;
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
				case 249:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'f':
						state = 275;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'f' && character <= 'z' ) )
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
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'c':
						state = 276;
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
				case 251:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'c':
						state = 277;
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
				case 252:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'n':
						state = 278;
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
				case 253:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'g':
						state = 279;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'g' && character <= 'z' ) )
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
				case 254:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_TABLE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 255:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_TUPLE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 256:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'e':
						state = 280;
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
				case 257:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_WHERE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 258:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_WHILE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 259:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_YIELD, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 260:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 132;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 261:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 137;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 262:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 263;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 263:
					switch (character)
					{
					case 'L':
					case 'l':
						state = 142;
						break;
					case '\'':
						state = 262;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
						{
							// state = 263;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 264:
					if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
					{
						state = 265;
						break;
					}
					else
					{
						return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
					}
					break;
				case 265:
					switch (character)
					{
					case 'L':
					case 'l':
						state = 142;
						break;
					case '\'':
						state = 264;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'F' ) || ( character >= 'a' && character <= 'f' ) )
						{
							// state = 265;
							break;
						}
						else
						{
							return TerminalData(Terminal::FLOAT_LITERAL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 266:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'n':
						state = 281;
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
				case 267:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_FLOAT64, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 268:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_EXPORT, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 269:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case '2':
						state = 282;
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
				case 270:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case '4':
						state = 267;
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
				case 271:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'h':
						state = 283;
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
				case 272:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'o':
						state = 284;
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
				case 273:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_IMPORT, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 274:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_MODULE, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 275:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'u':
						state = 285;
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
				case 276:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 't':
						state = 286;
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
				case 277:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_PUBLIC, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 278:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_RETURN, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 279:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_STRING, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 280:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'f':
						state = 287;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character != 'f' && character <= 'z' ) )
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
				case 281:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_BOOL, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 282:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_FLOAT32, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 283:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_FOREACH, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 284:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'n':
						state = 288;
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
				case 285:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'n':
						state = 289;
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
				case 286:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_PROJECT, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 287:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_TYPEDEF, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 288:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_FUNCTION, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				case 289:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'c':
						state = 290;
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
				case 290:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 't':
						state = 291;
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
				case 291:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'i':
						state = 292;
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
				case 292:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'o':
						state = 293;
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
				case 293:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					case 'n':
						state = 294;
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
				case 294:
					switch (character)
					{
					case 195:
						state = 49;
						break;
					case 196:
					case 197:
					case 198:
					case 199:
					case 200:
						state = 50;
						break;
					case 201:
						state = 51;
						break;
					default:
						if ( ( character >= '0' && character <= '9' ) || ( character >= 'A' && character <= 'Z' ) || ( character >= '_' && character != '`' && character <= 'z' ) )
						{
							state = 23;
							break;
						}
						else
						{
							return TerminalData(Terminal::KW_MULTIFUNCTION, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
						}
						break;
					}
					break;
				default:
					return TerminalData(Terminal::ERROR, text.substr(terminal_begin_index, current_text_index - terminal_begin_index), terminal_line_text, current_line_text, terminal_line);
				}
				++current_text_index;
			}
		}
	};
	
}
