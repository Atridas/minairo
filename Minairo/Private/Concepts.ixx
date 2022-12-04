module;

#include <cassert>

#include <optional>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

export module Minairo.Concepts;

import Minairo.TypesAndValues;

export namespace minairo
{
	class Concept
	{
	public:
		ConceptType type;

		bool add_interface_implementation(TupleType tuple, std::string_view interface_name)
		{
			InterfaceType const &interface = type.get_interface(interface_name);

			// TODO better errors for this
			for (int i = 0; i < interface.base_tuple.get_num_fields(); ++i)
			{
				std::string_view field = interface.base_tuple.get_field_name(i);
				if (!tuple.has_field(field))
				{
					return false;
				}
				if (tuple.get_field_type(field) != interface.base_tuple.get_field_type(i))
				{
					return false;
				}
			}

			assert(tuple.get_name() != "");
			assert(interface.name != "");

			std::unordered_set<std::string>& implementations = implementation_map[interface.name];

			implementations.insert((std::string)tuple.get_name());

			return true;
		}

		bool add_function_override(std::shared_ptr<FunctionRepresentation> override_function, std::string_view virtual_function_name)
		{
			FunctionType const& virtual_function = type.get_function(virtual_function_name);

			if (virtual_function.parameters.get_num_fields() != override_function->get_type().parameters.get_num_fields())
			{
				return false;
			}

			FunctionContainer container;
			for (int i = 0; i < virtual_function.parameters.get_num_fields(); ++i)
			{
				if (virtual_function.parameters.get_field_name(i) != override_function->get_type().parameters.get_field_name(i))
				{
					return false;
				}
				else if (virtual_function.parameters.get_field_type(i) != override_function->get_type().parameters.get_field_type(i))
				{
					if (auto as_interface = get<InterfaceType>(virtual_function.parameters.get_field_type(i)))
					{
						auto implementations = implementation_map.find(as_interface->name);
						if (implementations != implementation_map.end())
						{
							if (auto as_tuple = get<TupleType>(override_function->get_type().parameters.get_field_type(i)))
							{
								if (implementations->second.contains((std::string)as_tuple->get_name()))
								{
									container.override_paramenters.push_back((std::string)as_tuple->get_name());
									continue;
								}
							}
						}
						
					}
					return false;
				}
			}

			container.actual_function = std::move(override_function);
			// TODO check for double implementation
			function_map[virtual_function.name].push_back( std::move(container) );
			return true;
		}

		bool is_interface_implementation(TupleType const &tuple, InterfaceType const& interface)
		{
			std::unordered_set<std::string>& implementations = implementation_map[interface.name];

			return (implementations.find((std::string)tuple.get_name()) != implementations.end());
		}

		bool is_interface_implementation(TupleType const& tuple, std::string_view interface_name)
		{
			return is_interface_implementation(tuple, type.get_interface(interface_name));
		}

	private:

		struct FunctionContainer
		{
			std::vector<std::string> override_paramenters;
			std::shared_ptr<FunctionRepresentation> actual_function;
		};

		std::unordered_map<std::string, std::unordered_set<std::string>> implementation_map;
		std::unordered_map<std::string, std::vector<FunctionContainer>> function_map;
	};
};
