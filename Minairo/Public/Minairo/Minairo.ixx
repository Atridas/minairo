module;

#include <iostream>

export module Minairo;

namespace minairo
{
	struct VMImpl;

	export using VM = VMImpl*;

	export API VM create_VM();
	export API void destroy_VM(VM state);

	export API void interpret(std::string_view code);
	export API void interpret(VM state, std::string_view code, std::ostream &out = std::cout);
}
