module;

#include <cassert>

#include <optional>

export module Minairo.AST.TypePass:TypeUtilities;

import Minairo.AST;
import Minairo.TypesAndValues;

export namespace minairo
{
	struct TypeInformation
	{
		TypeRepresentation type;
		bool constant;
	};

	bool all_paths_lead_to_a_return(Statement const& statement);
	TypeInformation deduce_type(Expression const& expression);
	std::optional<Value> get_compile_time_value(Expression const& expression);

	template<typename T = TypeRepresentation>
	auto get_compile_time_type_value(Expression const& expression)
	{
		auto value = get_compile_time_value(expression);
		assert(value.has_value());
		auto type = get<TypeRepresentation>(*value);
		assert(type.has_value());
		if constexpr (std::is_same_v<T, TypeRepresentation>)
			return *type;
		else
			return get<T>(*type);
	}
}
