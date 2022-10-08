module;

#include <cassert>

#include <variant>

export module Minairo.TypeRepresentation;

export namespace minairo
{
	enum class BuildInType
	{
		Void,
		I8, I16, I32, I64,
		U8, U16, U32, U64,
		F32, F64,
		Bool
	};


	using TypeRepresentation = std::variant<BuildInType>;

	bool operator==(TypeRepresentation const& a, TypeRepresentation const &b)
	{
		if (std::holds_alternative<BuildInType>(a) && std::holds_alternative<BuildInType>(b))
		{
			return std::get<BuildInType>(a) == std::get<BuildInType>(b);
		}
		else
		{
			assert(false);
			return false;
		}
	}

	bool operator!=(TypeRepresentation const& a, TypeRepresentation const& b)
	{
		return !(a == b);
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
}
