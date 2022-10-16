module;

#include <cassert>

#include <sstream>
#include <string>
#include <string_view>

export module Minairo.Exception;

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
}
