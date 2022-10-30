module;

#include <cassert>

#include <string>
#include <string_view>
#include <variant>
#include <vector>

export module Minairo.TypesAndValues:Values;

import :Structures;
import :TypeRepresentation;

export namespace minairo
{

	TypeRepresentation get_type_representation(Value value)
	{
		return std::visit([]<typename T>(T v) -> TypeRepresentation
		{
			if constexpr (std::is_same_v<T, int8_t>)
			{
				return BuildInType::I8;
			}
			else if constexpr (std::is_same_v<T, int16_t>)
			{
				return BuildInType::I16;
			}
			else if constexpr (std::is_same_v<T, int32_t>)
			{
				return BuildInType::I32;
			}
			else if constexpr (std::is_same_v<T, int64_t>)
			{
				return BuildInType::I64;
			}
			else if constexpr (std::is_same_v<T, uint8_t>)
			{
				return BuildInType::U8;
			}
			else if constexpr (std::is_same_v<T, uint16_t>)
			{
				return BuildInType::U16;
			}
			else if constexpr (std::is_same_v<T, uint32_t>)
			{
				return BuildInType::U32;
			}
			else if constexpr (std::is_same_v<T, uint64_t>)
			{
				return BuildInType::U64;
			}
			else if constexpr (std::is_same_v<T, float>)
			{
				return BuildInType::F32;
			}
			else if constexpr (std::is_same_v<T, double>)
			{
				return BuildInType::F64;
			}
			else if constexpr (std::is_same_v<T, bool>)
			{
				return BuildInType::Bool;
			}
			else if constexpr (std::is_same_v<T, TypeRepresentation>)
			{
				return BuildInType::Typedef;
			}
			else
			{
				assert(false);
				return BuildInType::Void;
			}
		}, value);
	}

	Value cast(BuildInType type, std::variant<uint64_t, double, std::string, char32_t, bool> const& value)
	{
		switch (type)
		{
		case BuildInType::I8:
			return (int8_t)std::get<uint64_t>(value);
		case BuildInType::I16:
			return (int16_t)std::get<uint64_t>(value);
		case BuildInType::I32:
			return (int32_t)std::get<uint64_t>(value);
		case BuildInType::I64:
			return (int64_t)std::get<uint64_t>(value);
		case BuildInType::U8:
			return (uint8_t)std::get<uint64_t>(value);
		case BuildInType::U16:
			return (uint16_t)std::get<uint64_t>(value);
		case BuildInType::U32:
			return (uint32_t)std::get<uint64_t>(value);
		case BuildInType::U64:
			return (uint64_t)std::get<uint64_t>(value);
		case BuildInType::F32:
			return (float)std::get<double>(value);
		case BuildInType::F64:
			return (double)std::get<double>(value);
		case BuildInType::Bool:
			return std::get<bool>(value);
		default:
			assert(false);
			return (int32_t)0;
		}
	}

	Value get_default_value(BuildInType type);
	Value get_default_value(TableType const& type);
	Value get_default_value(TupleType const& type);
	Value get_default_value(TypeRepresentation const& type);

	Value get_default_value(BuildInType type)
	{
		switch (type)
		{
		case BuildInType::I8:
			return (int8_t)0;
		case BuildInType::I16:
			return (int16_t)0;
		case BuildInType::I32:
			return (int32_t)0;
		case BuildInType::I64:
			return (int64_t)0;
		case BuildInType::U8:
			return (uint8_t)0;
		case BuildInType::U16:
			return (uint16_t)0;
		case BuildInType::U32:
			return (uint32_t)0;
		case BuildInType::U64:
			return (uint64_t)0;
		case BuildInType::F32:
			return (float)0;
		case BuildInType::F64:
			return (double)0;
		case BuildInType::Bool:
			return false;
		case BuildInType::Typedef:
			return BuildInType::Void;
		default:
			assert(false);
			return BuildInType::Void;
		}
	}

	Value get_default_value(TableType const& type)
	{
		Table result;
		result.type = type;

		result.fields.resize(type.base_tuple.get_num_fields());

		return result;
	}

	Value get_default_value(TupleType const& type)
	{
		Tuple result;
		result.type = type;

		for (int i = 0; i < type.get_num_fields(); ++i)
		{
			result.fields.push_back(type.get_field_init_value(i));
		}

		return result;
	}

	Value get_default_value(TypeRepresentation const& type)
	{
		return std::visit([](auto t) { return get_default_value(t); }, type);
	}

	void* get_ptr(Value& value)
	{
		return std::visit([]<typename T>(T & v) -> void*
		{
			return (void*)&v;
		}, value);
	}

	void* set_to_type(Value& value, TypeRepresentation type)
	{
		if (std::holds_alternative<BuildInType>(type))
		{
			switch (std::get<BuildInType>(type))
			{
			case BuildInType::I8:
				value = (int8_t)0;
				return (void*)&std::get<int8_t>(value);
			case BuildInType::I16:
				value = (int16_t)0;
				return (void*)&std::get<int16_t>(value);
			case BuildInType::I32:
				value = (int32_t)0;
				return (void*)&std::get<int32_t>(value);
			case BuildInType::I64:
				value = (int64_t)0;
				return (void*)&std::get<int64_t>(value);
			case BuildInType::U8:
				value = (uint8_t)0;
				return (void*)&std::get<uint8_t>(value);
			case BuildInType::U16:
				value = (uint16_t)0;
				return (void*)&std::get<uint16_t>(value);
			case BuildInType::U32:
				value = (uint32_t)0;
				return (void*)&std::get<uint32_t>(value);
			case BuildInType::U64:
				value = (uint64_t)0;
				return (void*)&std::get<uint64_t>(value);
			case BuildInType::F32:
				value = (float)0;
				return (void*)&std::get<float>(value);
			case BuildInType::F64:
				value = (double)0;
				return (void*)&std::get<double>(value);
			case BuildInType::Bool:
				value = false;
				return (void*)&std::get<bool>(value);
			case BuildInType::Typedef:
				value = BuildInType::Void;
				return (void*)&std::get<TypeRepresentation>(value);
			default:
				assert(false);
				return nullptr;
			}
		}
		else
		{
			assert(false);
			return nullptr;
		}
	}
}
