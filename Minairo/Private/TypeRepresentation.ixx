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

export module Minairo.TypesAndValues:TypeRepresentation;

import :Structures;

export namespace minairo
{
	class TupleType final : public ComplexType
	{
	public:
		void set_name(std::string_view _name) noexcept override { name = (std::string)_name; }
		std::string_view get_name() const noexcept { return name; }

		bool has_field(std::string_view name) const noexcept;

		TypeRepresentation const& get_field_type(std::string_view name) const;
		int get_field_index(std::string_view name) const;

		int get_num_fields() const { return (int)sorted_fields.size(); }
		std::string_view get_field_name(int index) const { return field_names[index]; }
		TypeRepresentation const& get_field_type(int index) const { return types[index]; }
		std::optional<Value> get_field_init_value(int index) const { return init_values[index]; }
		std::span<TypeRepresentation const> get_types() const { return types; }

		void add_field(std::string_view name, TypeRepresentation const& type, std::optional<Value> init_value);
		void add_field(std::string_view name, TypeRepresentation const& type) { add_field(name, type, std::nullopt); }
		void add_field(std::string_view name, TypeRepresentation const& type, Value const& init_value) { add_field(name, type, std::optional<Value>(init_value)); }

		bool operator==(TupleType const&) const noexcept;

		operator TypeRepresentation() const
		{
			return (std::shared_ptr<ComplexType>)std::make_shared<TupleType>(*this);
		}

		operator Value() const
		{
			return (std::shared_ptr<ComplexType>)std::make_shared<TupleType>(*this);
		}

	protected:
		bool equals(ComplexType const& other) const override
		{
			return *this == other;
		}
	private:


		std::string name;
		std::vector<std::string> sorted_fields;
		std::vector<std::string> field_names;
		std::vector<int> indexes;
		std::vector<TypeRepresentation> types;
		std::vector<std::optional<Value>> init_values;
	};

	class TupleReferenceType : public ComplexType
	{
	public:
		TupleType tuple;
		bool constant;

		void set_name(std::string_view _name) override
		{
			// TODO ??
			assert(false);
		}

		operator TypeRepresentation() const
		{
			return (std::shared_ptr<ComplexType>)std::make_shared<TupleReferenceType>(*this);
		}

		operator Value() const
		{
			return (std::shared_ptr<ComplexType>)std::make_shared<TupleReferenceType>(*this);
		}

	protected:
		bool equals(ComplexType const& other) const override
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
	};

	class InterfaceType : public ComplexType
	{
		std::string name;
		std::string_view concept_name, interface_name;
	public:
		int index;
		TupleType base_tuple;

		InterfaceType() = default;
		InterfaceType(InterfaceType const& other)
			: name(other.name)
			, concept_name(name.c_str(), other.concept_name.size())
			, interface_name(name.c_str() + other.concept_name.size() + 1)
			, index(other.index)
			, base_tuple(other.base_tuple)
		{
		}
		InterfaceType(InterfaceType&&) = default;
		InterfaceType& operator=(InterfaceType const& other)
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
		InterfaceType& operator=(InterfaceType&&) = default;

		void set_name(std::string_view _name) override
		{
			name = _name;
			size_t dot = name.find_last_of('.');
			concept_name = std::string_view(name.c_str(), dot);
			interface_name = std::string_view(name.c_str() + dot + 1);
		}

		std::string_view get_name() const
		{
			return name;
		}

		std::string_view get_concept_name() const
		{
			return concept_name;
		}
		std::string_view get_interface_name() const
		{
			return interface_name;
		}

		bool operator==(InterfaceType const& other) const noexcept
		{
			if (name.empty() && other.name.empty())
				return base_tuple == other.base_tuple;
			else
				return name == other.name;
		}

		operator TypeRepresentation() const
		{
			return (std::shared_ptr<ComplexType>)std::make_shared<InterfaceType>(*this);
		}

		operator Value() const
		{
			return (std::shared_ptr<ComplexType>)std::make_shared<InterfaceType>(*this);
		}
	protected:
		bool equals(ComplexType const& other) const override
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
	};

	class TableType : public ComplexType
	{
	public:
		std::string name;
		TupleType base_tuple;

		void set_name(std::string_view _name) override
		{
			name = _name;
		}

		bool operator==(TableType const& other) const noexcept
		{
			if (name.empty() && other.name.empty())
				return base_tuple == other.base_tuple;
			else
				return name == other.name;
		}

		operator TypeRepresentation() const
		{
			return (std::shared_ptr<ComplexType>)std::make_shared<TableType>(*this);
		}

		operator Value() const
		{
			return (std::shared_ptr<ComplexType>)std::make_shared<TableType>(*this);
		}
	protected:
		bool equals(ComplexType const& other) const override
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
	};

	class FunctionType : public ComplexType
	{
	public:
		std::string name;
		TupleType parameters;

		TypeRepresentation return_type;
		bool is_pure;

		void set_name(std::string_view _name) override
		{
			name = _name;
		}

		bool operator==(FunctionType const& other) const noexcept
		{
			if (name.empty() && other.name.empty())
				return parameters == other.parameters;
			else
				return name == other.name;
		}

		operator TypeRepresentation() const
		{
			return (std::shared_ptr<ComplexType>)std::make_shared<FunctionType>(*this);
		}

		operator Value() const
		{
			return (std::shared_ptr<ComplexType>)std::make_shared<FunctionType>(*this);
		}
	protected:
		bool equals(ComplexType const& other) const override
		{
			if (FunctionType const* as_function_type = dynamic_cast<FunctionType const*>(&other))
				return *this == *as_function_type;
			else
				return false;
		}
	};

	class ConceptType : public ComplexType
	{
	public:
		std::string name;
		struct VirtualFunctionType : public FunctionType
		{
			std::vector<int> interface_paramenters;
			int index;

			VirtualFunctionType() = default;
			VirtualFunctionType(FunctionType const& _function_type, std::vector<int>&& _interface_paramenters, int _index)
				: FunctionType(_function_type)
				, interface_paramenters(std::move(_interface_paramenters))
				, index(_index)
			{}

			std::shared_ptr<InterfaceType> get_indexed_overriden_parameter(int index) const;

			bool operator==(VirtualFunctionType const& other) const
			{
				if (index != other.index)
					return false;
				if ((FunctionType)*this != (FunctionType)other)
					return false;
				assert(interface_paramenters == other.interface_paramenters);
				return true;
			}

			operator TypeRepresentation() const
			{
				return (std::shared_ptr<ComplexType>)std::make_shared<VirtualFunctionType>(*this);
			}

			operator Value() const
			{
				return (std::shared_ptr<ComplexType>)std::make_shared<VirtualFunctionType>(*this);
			}
		protected:
			bool equals(ComplexType const& other) const override
			{
				if (VirtualFunctionType const* as_function_type = dynamic_cast<VirtualFunctionType const*>(&other))
					return *this == *as_function_type;
				else
					return false;
			}
		};

		void set_name(std::string_view _name) override
		{
			name = _name;
		}

		void add_interface(std::string_view name, InterfaceType const& interface)
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

		InterfaceType const& get_interface(std::string_view interface_name) const
		{
			if (interface_name.starts_with(name) && interface_name.size() > name.size() && interface_name[name.size()] == '.')
			{
				interface_name = interface_name.substr(name.size() + 1);
			}
			assert(interfaces.find((std::string)interface_name) != interfaces.end());

			return interfaces.find((std::string)interface_name)->second;
		}

		void add_function(std::string_view name, FunctionType const& function, std::vector<int>&& interface_paramenters);

		VirtualFunctionType const& get_function(std::string_view function_name) const
		{
			if (function_name.starts_with(name) && function_name.size() > name.size() && function_name[name.size()] == '.')
			{
				function_name = function_name.substr(name.size() + 1);
			}
			assert(functions.find((std::string)function_name) != functions.end());

			return functions.find((std::string)function_name)->second;
		}

		int get_num_single_dispatch_functions(std::string_view interface_name) const
		{
			if (interface_name.starts_with(name) && interface_name.size() > name.size() && interface_name[name.size()] == '.')
			{
				interface_name = interface_name.substr(name.size() + 1);
			}
			assert(single_dispatch_functions.find((std::string)interface_name) != single_dispatch_functions.end());

			return single_dispatch_functions.find((std::string)interface_name)->second;
		}

		int get_num_multi_dispatch_functions(std::string_view interface_name) const
		{
			if (interface_name.starts_with(name) && interface_name.size() > name.size() && interface_name[name.size()] == '.')
			{
				interface_name = interface_name.substr(name.size() + 1);
			}
			assert(multi_dispatch_functions.find((std::string)interface_name) != multi_dispatch_functions.end());

			return multi_dispatch_functions.find((std::string)interface_name)->second;
		}

		enum class Kind
		{
			Interface, Function, None
		};

		Kind get_member_kind(std::string_view name) const
		{
			if (interfaces.find((std::string)name) != interfaces.end())
				return Kind::Interface;
			else if (functions.find((std::string)name) != functions.end())
				return Kind::Function;
			else
				return Kind::None;
		}


		bool operator==(ConceptType const& other) const noexcept
		{
			if (name.empty() && other.name.empty())
				return interfaces == other.interfaces && functions == other.functions;
			else
				return name == other.name;
		}

		operator TypeRepresentation() const
		{
			return (std::shared_ptr<ComplexType>)std::make_shared<ConceptType>(*this);
		}

		operator Value() const
		{
			return (std::shared_ptr<ComplexType>)std::make_shared<ConceptType>(*this);
		}
	protected:
		bool equals(ComplexType const& other) const override
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

		std::unordered_map<std::string, InterfaceType> interfaces;
		std::unordered_map<std::string, VirtualFunctionType> functions;
		std::unordered_map<std::string, int>  single_dispatch_functions;
		std::unordered_map<std::string, int>  multi_dispatch_functions;
	};

	class MultifunctionType : public ComplexType
	{
	public:
		std::string name;
		std::vector<FunctionType> functions;
		bool is_pure;

		void set_name(std::string_view _name) override
		{
			name = _name;
		}

		bool operator==(MultifunctionType const& other) const noexcept
		{
			if (name.empty() && other.name.empty())
				return functions == other.functions;
			else
				return name == other.name;
		}

		operator TypeRepresentation() const
		{
			return (std::shared_ptr<ComplexType>)std::make_shared<MultifunctionType>(*this);
		}

		operator Value() const
		{
			return (std::shared_ptr<ComplexType>)std::make_shared<MultifunctionType>(*this);
		}

	protected:
		bool equals(ComplexType const& other) const override
		{
			if (MultifunctionType const* as_multifunction_type = dynamic_cast<MultifunctionType const*>(&other))
				return *this == *as_multifunction_type;
			else
				return false;
		}
	};

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

	template<typename T>
	TypeRepresentation get_type_representation()
	{
		assert(false);
		return BuildInType::Void;
	}

	template<>
	TypeRepresentation get_type_representation<void>()
	{
		return BuildInType::Void;
	}

	template<>
	TypeRepresentation get_type_representation<int8_t>()
	{
		return BuildInType::I8;
	}

	template<>
	TypeRepresentation get_type_representation<int16_t>()
	{
		return BuildInType::I16;
	}

	template<>
	TypeRepresentation get_type_representation<int32_t>()
	{
		return BuildInType::I32;
	}

	template<>
	TypeRepresentation get_type_representation<int64_t>()
	{
		return BuildInType::I64;
	}

	template<>
	TypeRepresentation get_type_representation<uint8_t>()
	{
		return BuildInType::U8;
	}

	template<>
	TypeRepresentation get_type_representation<uint16_t>()
	{
		return BuildInType::U16;
	}

	template<>
	TypeRepresentation get_type_representation<uint32_t>()
	{
		return BuildInType::U32;
	}

	template<>
	TypeRepresentation get_type_representation<uint64_t>()
	{
		return BuildInType::U64;
	}

	template<>
	TypeRepresentation get_type_representation<float>()
	{
		return BuildInType::F32;
	}

	template<>
	TypeRepresentation get_type_representation<double>()
	{
		return BuildInType::F64;
	}

	template<>
	TypeRepresentation get_type_representation<bool>()
	{
		return BuildInType::Bool;
	}

	template<>
	TypeRepresentation get_type_representation<std::string>()
	{
		return BuildInType::String;
	}

	template<typename T>
	auto get(TypeRepresentation const& type_representation)
	{
		if constexpr (std::is_same_v<T, BuildInType>)
		{
			if (std::holds_alternative<BuildInType>(type_representation))
			{
				return std::optional<BuildInType>(std::get<BuildInType>(type_representation));
			}
			else
			{
				return std::optional<BuildInType>(std::nullopt);
			}
		}
		else if constexpr (std::is_base_of_v<ComplexType, T>)
		{
			if (std::holds_alternative<std::shared_ptr<ComplexType>>(type_representation))
			{
				if (std::shared_ptr<T> p = std::dynamic_pointer_cast<T>(std::get< std::shared_ptr<ComplexType>>(type_representation)))
					return p;
			}
			return std::shared_ptr<T>{};
		}
	}
}
