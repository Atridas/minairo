module;

#include <iostream>

export module Minairo;

namespace minairo
{
	struct StateImpl;

	export using State = StateImpl*;

	export API State create_repl();
	export API void destroy_repl(State state);

	export API void interpret(std::string_view code);
	export API void interpret(State state, std::string_view code);
}
