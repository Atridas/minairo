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
		int get_original_order(std::string_view name) const;

		int get_num_fields() const { return (int)sorded_fields.size(); }
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
		std::vector<std::string> sorded_fields;
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
			return *this == other;
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
			return *this == other;
		}
	};

	class ProcedureType : public ComplexType
	{
	public:
		std::string name;
		TupleType parameters;

		TypeRepresentation return_type;
		bool is_function; // Change to "is_pure"

		void set_name(std::string_view _name) override
		{
			name = _name;
		}

		bool operator==(ProcedureType const& other) const noexcept
		{
			if (name.empty() && other.name.empty())
				return parameters == other.parameters;
			else
				return name == other.name;

		}

		operator TypeRepresentation() const
		{
			return (std::shared_ptr<ComplexType>)std::make_shared<ProcedureType>(*this);
		}

		operator Value() const
		{
			return (std::shared_ptr<ComplexType>)std::make_shared<ProcedureType>(*this);
		}
	protected:
		bool equals(ComplexType const& other) const override
		{
			return *this == other;
		}
	};

	bool TupleType::has_field(std::string_view name) const noexcept
	{
		return std::binary_search(sorded_fields.begin(), sorded_fields.end(), name);
	}

	TypeRepresentation const& TupleType::get_field_type(std::string_view name) const
	{
		return types[get_field_index(name)];
	}

	int TupleType::get_field_index(std::string_view name) const
	{
		assert(has_field(name));
		return indexes[(int)(std::lower_bound(sorded_fields.begin(), sorded_fields.end(), name) - sorded_fields.begin())];
	}

	void TupleType::add_field(std::string_view name, TypeRepresentation const& type, std::optional<Value> init_value)
	{
		assert(!has_field(name));
		auto it = sorded_fields.insert(std::upper_bound(sorded_fields.begin(), sorded_fields.end(), name), (std::string)name);
		indexes.insert(indexes.begin() + (it - sorded_fields.begin()), (int)indexes.size());
		field_names.push_back((std::string)name);
		types.push_back(type);
		init_values.push_back(init_value);
	}

	bool TupleType::operator==(TupleType const& other) const noexcept
	{
		if (name.empty() && other.name.empty())
		{
			if (sorded_fields.size() != other.sorded_fields.size())
			{
				return false;
			}
			for (int i = 0; i < sorded_fields.size(); ++i)
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
