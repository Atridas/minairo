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

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

bool TupleType::has_field(std::string_view name) const noexcept
{
	return std::binary_search(sorted_fields.begin(), sorted_fields.end(), name);
}

TypeRepresentation const& TupleType::get_field_type(std::string_view name) const
{
	return types[get_field_index(name)];
}

int TupleType::get_field_index(std::string_view name) const
{
	assert(has_field(name));
	return indexes[(int)(std::lower_bound(sorted_fields.begin(), sorted_fields.end(), name) - sorted_fields.begin())];
}

void TupleType::add_field(std::string_view name, TypeRepresentation const& type, std::optional<Value> init_value)
{
	assert(!has_field(name));
	auto it = sorted_fields.insert(std::upper_bound(sorted_fields.begin(), sorted_fields.end(), name), (std::string)name);
	indexes.insert(indexes.begin() + (it - sorted_fields.begin()), (int)indexes.size());
	field_names.push_back((std::string)name);
	types.push_back(type);
	init_values.push_back(init_value);
}

bool TupleType::operator==(TupleType const& other) const noexcept
{
	if (name.empty() && other.name.empty())
	{
		if (sorted_fields.size() != other.sorted_fields.size())
		{
			return false;
		}
		for (int i = 0; i < sorted_fields.size(); ++i)
		{
			if (field_names[i] != other.field_names[i])
			{
				return false;
			}
			else if (types[i] != other.types[i])
			{
				return false;
			}
		}
		return true;
	}
	else
		return name == other.name;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

bool TupleReferenceType::equals(ComplexType const& other) const
{
	if (auto* as_tuple_reference = dynamic_cast<TupleReferenceType const*>(&other))
	{
		assert(false); // TODO
		return *this == *as_tuple_reference;
	}
	else
	{
		return false;
	}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

InterfaceType::InterfaceType(InterfaceType const& other)
	: name(other.name)
	, concept_name(name.c_str(), other.concept_name.size())
	, interface_name(name.c_str() + other.concept_name.size() + 1)
	, index(other.index)
	, base_tuple(other.base_tuple)
{
}

InterfaceType& InterfaceType::operator=(InterfaceType const& other)
{
	if (this != &other)
	{
		name = other.name;
		size_t dot = other.concept_name.size();
		concept_name = std::string_view(name.c_str(), dot);
		interface_name = std::string_view(name.c_str() + dot + 1);
		index = other.index;
		base_tuple = other.base_tuple;
	}
	return *this;
}

void InterfaceType::set_name(std::string_view _name)
{
	name = _name;
	size_t dot = name.find_last_of('.');
	concept_name = std::string_view(name.c_str(), dot);
	interface_name = std::string_view(name.c_str() + dot + 1);
}

bool InterfaceType::operator==(InterfaceType const& other) const noexcept
{
	if (name.empty() && other.name.empty())
		return base_tuple == other.base_tuple;
	else
		return name == other.name;
}

bool InterfaceType::equals(ComplexType const& other) const
{
	if (auto* as_interface = dynamic_cast<InterfaceType const*>(&other))
	{
		return *this == *as_interface;
	}
	else
	{
		return false;
	}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

bool TableType::operator==(TableType const& other) const noexcept
{
	if (name.empty() && other.name.empty())
		return base_tuple == other.base_tuple;
	else
		return name == other.name;
}

bool TableType::equals(ComplexType const& other) const
{
	if (auto* as_table = dynamic_cast<TableType const*>(&other))
	{
		return *this == *as_table;
	}
	else
	{
		return false;
	}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

bool FunctionType::operator==(FunctionType const& other) const noexcept
{
	if (name.empty() && other.name.empty())
		return parameters == other.parameters;
	else
		return name == other.name;
}

bool FunctionType::equals(ComplexType const& other) const
{
	if (FunctionType const* as_function_type = dynamic_cast<FunctionType const*>(&other))
		return *this == *as_function_type;
	else
		return false;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

bool MultifunctionType::operator==(MultifunctionType const& other) const noexcept
{
	if (name.empty() && other.name.empty())
		return functions == other.functions;
	else
		return name == other.name;
}

bool MultifunctionType::equals(ComplexType const& other) const
{
	if (MultifunctionType const* as_multifunction_type = dynamic_cast<MultifunctionType const*>(&other))
		return *this == *as_multifunction_type;
	else
		return false;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ConceptType::VirtualFunctionType::VirtualFunctionType(FunctionType const& _function_type, std::vector<int>&& _interface_paramenters, int _index)
	: FunctionType(_function_type)
	, interface_paramenters(std::move(_interface_paramenters))
	, index(_index)
{}

std::shared_ptr<InterfaceType> ConceptType::VirtualFunctionType::get_indexed_overriden_parameter(int index) const
{
	return get<InterfaceType>(parameters.get_field_type(interface_paramenters[index]));
}

bool ConceptType::VirtualFunctionType::operator==(VirtualFunctionType const& other) const
{
	if (index != other.index)
		return false;
	if ((FunctionType)*this != (FunctionType)other)
		return false;
	assert(interface_paramenters == other.interface_paramenters);
	return true;
}

bool ConceptType::VirtualFunctionType::equals(ComplexType const& other) const
{
	if (VirtualFunctionType const* as_function_type = dynamic_cast<VirtualFunctionType const*>(&other))
		return *this == *as_function_type;
	else
		return false;
}

// ------------------------------------------------------------------------------------------------

void ConceptType::add_interface(std::string_view name, InterfaceType const& interface)
{
	assert(interfaces.find((std::string)name) == interfaces.end());
	assert(functions.find((std::string)name) == functions.end());
	assert(single_dispatch_functions.find((std::string)name) == single_dispatch_functions.end());
	assert(multi_dispatch_functions.find((std::string)name) == multi_dispatch_functions.end());

	int index = (int)interfaces.size();
	InterfaceType& saved = interfaces[(std::string)name] = interface;
	saved.index = index;
	single_dispatch_functions[(std::string)name] = 0;
	multi_dispatch_functions[(std::string)name] = 0;
}

InterfaceType const& ConceptType::get_interface(std::string_view interface_name) const
{
	if (interface_name.starts_with(name) && interface_name.size() > name.size() && interface_name[name.size()] == '.')
	{
		interface_name = interface_name.substr(name.size() + 1);
	}
	assert(interfaces.find((std::string)interface_name) != interfaces.end());

	return interfaces.find((std::string)interface_name)->second;
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

ConceptType::VirtualFunctionType const& ConceptType::get_function(std::string_view function_name) const
{
	if (function_name.starts_with(name) && function_name.size() > name.size() && function_name[name.size()] == '.')
	{
		function_name = function_name.substr(name.size() + 1);
	}
	assert(functions.find((std::string)function_name) != functions.end());

	return functions.find((std::string)function_name)->second;
}

int ConceptType::get_num_single_dispatch_functions(std::string_view interface_name) const
{
	if (interface_name.starts_with(name) && interface_name.size() > name.size() && interface_name[name.size()] == '.')
	{
		interface_name = interface_name.substr(name.size() + 1);
	}
	assert(single_dispatch_functions.find((std::string)interface_name) != single_dispatch_functions.end());

	return single_dispatch_functions.find((std::string)interface_name)->second;
}

int ConceptType::get_num_multi_dispatch_functions(std::string_view interface_name) const
{
	if (interface_name.starts_with(name) && interface_name.size() > name.size() && interface_name[name.size()] == '.')
	{
		interface_name = interface_name.substr(name.size() + 1);
	}
	assert(multi_dispatch_functions.find((std::string)interface_name) != multi_dispatch_functions.end());

	return multi_dispatch_functions.find((std::string)interface_name)->second;
}

ConceptType::Kind ConceptType::get_member_kind(std::string_view name) const
{
	if (interfaces.find((std::string)name) != interfaces.end())
		return Kind::Interface;
	else if (functions.find((std::string)name) != functions.end())
		return Kind::Function;
	else
		return Kind::None;
}

bool ConceptType::operator==(ConceptType const& other) const noexcept
{
	if (name.empty() && other.name.empty())
		return interfaces == other.interfaces && functions == other.functions;
	else
		return name == other.name;
}

bool ConceptType::equals(ComplexType const& other) const
{
	if (auto* as_concept = dynamic_cast<ConceptType const*>(&other))
	{
		return *this == *as_concept;
	}
	else
	{
		return false;
	}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

bool TypeRepresentation::is_integral() const
{
	if (std::holds_alternative<BuildInType>(*this))
	{
		switch (std::get<BuildInType>(*this))
		{
		case BuildInType::I8:
		case BuildInType::I16:
		case BuildInType::I32:
		case BuildInType::I64:
		case BuildInType::U8:
		case BuildInType::U16:
		case BuildInType::U32:
		case BuildInType::U64:
			return true;
		default:
			return false;
		}
	}
	else
	{
		return false;
	}
}
bool TypeRepresentation::is_float() const
{
	if (std::holds_alternative<BuildInType>(*this))
	{
		switch (std::get<BuildInType>(*this))
		{
		case BuildInType::F32:
		case BuildInType::F64:
			return true;
		default:
			return false;
		}
	}
	else
	{
		return false;
	}
}
