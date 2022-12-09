module;

#include <cassert>

#include <memory>
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

		struct FunctionContainer
		{
			std::vector<std::string> override_paramenters;
			std::shared_ptr<FunctionRepresentation> actual_function;
		};
		struct VirtualTable
		{
			std::vector<int> field_mapping;
			std::vector<std::shared_ptr<FunctionRepresentation>> single_dispatch_functions;
			std::vector<std::vector<FunctionContainer>> multi_dispatch_functions;
		};

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

			std::unordered_map<std::string, TupleType>& implementations = implementation_map[interface.name];

			implementations[(std::string)tuple.get_name()] = tuple;

			return true;
		}

		bool add_function_override(std::shared_ptr<FunctionRepresentation> override_function, std::string_view virtual_function_name)
		{
			ConceptType::VirtualFunction const& virtual_function = type.get_function(virtual_function_name);

			assert(virtual_function.type.parameters.get_num_fields() == override_function->get_type().parameters.get_num_fields());

			FunctionContainer container;
			for (int parameter_index : virtual_function.interface_paramenters)
			{
				auto as_interface = get<InterfaceType>(virtual_function.type.parameters.get_field_type(parameter_index));
				auto as_tuple = get<TupleType>(override_function->get_type().parameters.get_field_type(parameter_index));
				assert(as_interface);
				assert(as_tuple);
				auto implementations = implementation_map.find(as_interface->name);
				assert (implementations != implementation_map.end());
				assert(implementations->second.contains((std::string)as_tuple->get_name()));

				container.override_paramenters.push_back((std::string)as_tuple->get_name());
			}

			container.actual_function = std::move(override_function);
			// TODO check for double implementation
			function_map[(std::string)virtual_function_name].push_back( std::move(container) );
			return true;
		}

		bool is_interface_implementation(TupleType const &tuple, InterfaceType const& interface) const
		{
			std::unordered_map<std::string, TupleType> const& implementations = implementation_map.find(interface.name)->second;

			return (implementations.find((std::string)tuple.get_name()) != implementations.end());
		}

		bool is_interface_implementation(TupleType const& tuple, std::string_view interface_name) const
		{
			return is_interface_implementation(tuple, type.get_interface(interface_name));
		}

		bool is_complete_interface_implementation(TupleType const &tuple, InterfaceType const& interface) const
		{
			std::unordered_map<std::string, TupleType> const& implementations = implementation_map.find(interface.name)->second;

			if (implementations.find((std::string)tuple.get_name()) == implementations.end())
			{
				return false;
			}
			
			if (function_map.size() < type.get_num_functions())
			{
				return false;
			}

			for (auto const& function_data : function_map)
			{
				bool implementation_found = false;
				for (auto const& function_container : function_data.second)
				{
					for (auto const& override_paramenter : function_container.override_paramenters)
					{
						if (override_paramenter == tuple.get_name())
						{
							implementation_found = true;
							break;
						}
					}
				}
				if (!implementation_found)
					return false;
			}

			return true;
		}

		bool is_complete_interface_implementation(TupleType const& tuple, std::string_view interface_name) const
		{
			return is_complete_interface_implementation(tuple, type.get_interface(interface_name));
		}

		VirtualTable get_virtual_table(TupleType const& tuple, InterfaceType const& interface) const
		{
			auto it = virtual_tables.find(interface.name);
			assert(it != virtual_tables.end());
			auto it2 = it->second.find((std::string)tuple.get_name());
			assert(it2 != it->second.end());
			return it2->second;
		}

		void prepare_virtual_tables()
		{
			virtual_tables.clear();
			for (auto const& interfaces : implementation_map)
			{
				for (auto const& tuple_type : interfaces.second)
				{
					VirtualTable &virtual_table = virtual_tables[interfaces.first][(std::string)tuple_type.second.get_name()];

					std::string_view interface_name(interfaces.first.c_str() + interfaces.first.find_last_of('.') + 1);
					InterfaceType const& interface_type = type.get_interface(interface_name);
					for (int f = 0; f < interface_type.base_tuple.get_num_fields(); ++f)
					{
						int tuple_field_index = tuple_type.second.get_field_index(interface_type.base_tuple.get_field_name(f));
						virtual_table.field_mapping.push_back(tuple_field_index);
					}

					for (auto const& function_implementations : function_map)
					{
						ConceptType::VirtualFunction const& virtual_function = type.get_function(function_implementations.first);
						for (FunctionContainer const& function_container : function_implementations.second)
						{
							if (function_container.override_paramenters.size() == 1)
							{
								if (function_container.override_paramenters[0] == tuple_type.second.get_name())
								{
									if (virtual_function.index >= virtual_table.single_dispatch_functions.size())
									{
										virtual_table.single_dispatch_functions.resize(virtual_function.index + 1);
									}
									virtual_table.single_dispatch_functions[virtual_function.index] = function_container.actual_function;
								}
							}
							else
							{
								assert(function_container.override_paramenters.size() > 1);
								assert(false); // TODO
							}
						}
					}
				}
			}
		}

	private:


		std::unordered_map<std::string, std::unordered_map<std::string, TupleType>> implementation_map;
		std::unordered_map<std::string, std::unordered_map<std::string, VirtualTable>> virtual_tables;
		std::unordered_map<std::string, std::vector<FunctionContainer>> function_map;
	};

	struct Interface final : public TupleReference
	{
		InterfaceType type;
		Concept::VirtualTable virtual_table;
		Tuple tuple;


		virtual Value& get_field(int index)
		{
			return tuple.fields[virtual_table.field_mapping[index]];
		}

		virtual Tuple as_tuple() const
		{
			assert(false);
			return tuple;
		}

		bool operator==(Interface const& other) const noexcept
		{
			return type == other.type && tuple == other.tuple;
		}

		operator Value() const
		{
			return (std::shared_ptr<ComplexValue>)std::make_shared<Interface>(*this);
		}

	protected:
		bool equals(ComplexValue const& other) const override
		{
			if (auto t = dynamic_cast<Interface const*>(&other))
				return *this == *t;
			else
				return false;
		}
	};
};
