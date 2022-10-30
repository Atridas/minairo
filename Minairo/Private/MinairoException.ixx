module;

#include <cassert>

#include <sstream>
#include <string>
#include <string_view>

export module Minairo.Exception;
import Minairo.Scanner;

namespace minairo
{
	export void print_error_line(std::stringstream& ss, int line, std::string_view text, std::string_view line_begin, std::string_view line_end)
	{
		assert(line_begin == line_end); // TODO multiline errors

		size_t ini = ss.str().size();
		ss << "line " << line << ": ";
		size_t offset = ss.str().size() - ini;

		ss << line_begin << '\n';
		for (int i = 0; i < offset + (int)(&text[0] - &line_begin[0]); ++i)
		{
			ss << ' ';
		}
		for (int i = 0; i < text.size(); ++i)
		{
			ss << '^';
		}
	}

	export void print_error_line(std::stringstream& ss, TerminalData terminal_data)
	{
		print_error_line(ss, terminal_data.line, terminal_data.text, terminal_data.line_begin, terminal_data.line_end);
	}

	export void print_error_line(std::stringstream& ss, TerminalData first, TerminalData last)
	{
		assert(first.text.data() <= last.text.data() );
		std::string_view text = { first.text.data(), (last.text.data() - first.text.data()) + last.text.size()};
		print_error_line(ss, first.line, text, first.line_begin, last.line_end);
	}
}
