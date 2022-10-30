module;

#include <cassert>

#include <algorithm>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>

export module Minairo.TypesAndValues:TypeRepresentation;

import :Structures;

export namespace minairo
{
	bool operator==(TypeRepresentation const& a, TypeRepresentation const &b)
	{
		if (std::holds_alternative<BuildInType>(a) && std::holds_alternative<BuildInType>(b))
		{
			return std::get<BuildInType>(a) == std::get<BuildInType>(b);
		}
		else if (std::holds_alternative<TupleType>(a) && std::holds_alternative<TupleType>(b))
		{
			return std::get<TupleType>(a) == std::get<TupleType>(b);
		}
		else if (std::holds_alternative<TableType>(a) && std::holds_alternative<TableType>(b))
		{
			return std::get<TableType>(a) == std::get<TableType>(b);
		}
		else
		{
			//assert(false);
			return false;
		}
	}

	bool operator!=(TypeRepresentation const& a, TypeRepresentation const& b)
	{
		return !(a == b);
	}

	bool TupleType::has_field(std::string_view name) const noexcept
	{
		return std::binary_search(fields.begin(), fields.end(), name);
	}

	TypeRepresentation const& TupleType::get_field_type(std::string_view name) const
	{
		return types[get_field_index(name)];
	}

	int TupleType::get_field_index(std::string_view name) const
	{
		assert(has_field(name));
		return (int)(std::lower_bound(fields.begin(), fields.end(), name) - fields.begin());
	}

	void TupleType::add_field(std::string_view name, TypeRepresentation const& type, Value const &init_value)
	{
		assert(!has_field(name));
		auto it = fields.insert(std::upper_bound(fields.begin(), fields.end(), name), (std::string)name);
		types.insert(types.begin() + (it - fields.begin()), type);
		init_values.insert(init_values.begin() + (it - fields.begin()), init_value);
	}

	bool TupleType::operator==(TupleType const& other) const noexcept
	{
		if (fields.size() != other.fields.size())
		{
			return false;
		}
		for (int i = 0; i < fields.size(); ++i)
		{
			if (fields[i] != other.fields[i])
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

	bool TypeRepresentation::is_build_in() const
	{
		return std::holds_alternative<BuildInType>(*this);
	}

	std::optional<BuildInType> TypeRepresentation::as_build_in() const
	{
		if (std::holds_alternative<BuildInType>(*this))
		{
			return std::get<BuildInType>(*this);
		}
		else
		{
			return std::nullopt;
		}
	}

	bool TypeRepresentation::is_tuple() const
	{
		return std::holds_alternative<TupleType>(*this);
	}

	std::optional<TupleType> TypeRepresentation::as_tuple() const
	{
		if (std::holds_alternative<TupleType>(*this))
		{
			return std::get<TupleType>(*this);
		}
		else
		{
			return std::nullopt;
		}
	}

	bool TypeRepresentation::is_tuple_reference() const
	{
		return std::holds_alternative<TupleReferenceType>(*this);
	}

	std::optional<TupleReferenceType> TypeRepresentation::as_tuple_reference() const
	{
		if (std::holds_alternative<TupleReferenceType>(*this))
		{
			return std::get<TupleReferenceType>(*this);
		}
		else
		{
			return std::nullopt;
		}
	}

	bool TypeRepresentation::is_table() const
	{
		return std::holds_alternative<TableType>(*this);
	}

	std::optional<TableType> TypeRepresentation::as_table() const
	{
		if (std::holds_alternative<TableType>(*this))
		{
			return std::get<TableType>(*this);
		}
		else
		{
			return std::nullopt;
		}
	}
}
