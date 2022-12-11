module;

#include <cassert>

#include <algorithm>
#include <memory>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <variant>

module Minairo.TypesAndValues:TypeRepresentation;

using namespace minairo;


std::shared_ptr<InterfaceType> ConceptType::VirtualFunctionType::get_indexed_overriden_parameter(int index) const
{
	return get<InterfaceType>(parameters.get_field_type(interface_paramenters[index]));
}

void ConceptType::add_function(std::string_view function_name, FunctionType const& function, std::vector<int>&& interface_paramenters)
{
	assert(interfaces.find((std::string)function_name) == interfaces.end());
	assert(functions.find((std::string)function_name) == functions.end());
	assert(interface_paramenters.size() > 0);

	std::shared_ptr<InterfaceType> interface_parameter = get<InterfaceType>(function.parameters.get_field_type(interface_paramenters[0]));
	assert(interface_parameter);

	assert(interface_parameter->get_concept_name() == name);
	std::string interface_name = (std::string)interface_parameter->get_interface_name();
	
	assert(single_dispatch_functions.find(interface_name) != single_dispatch_functions.end());
	assert(multi_dispatch_functions.find(interface_name) != multi_dispatch_functions.end());

	int index;
	if (interface_paramenters.size() == 1)
	{
		index = single_dispatch_functions[interface_name]++;
	}
	else
	{
		assert(interface_paramenters.size() > 1);
		index = multi_dispatch_functions[interface_name]++;
	}

	functions[(std::string)function_name] = VirtualFunctionType{ function, std::move(interface_paramenters), index };
}