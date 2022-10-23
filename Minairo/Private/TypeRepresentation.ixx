module;

#include <cassert>

#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>

export module Minairo.TypeRepresentation;

export namespace minairo
{
	class TypeRepresentation;

	enum class BuildInType
	{
		Void,
		Bool,
		I8, I16, I32, I64,
		U8, U16, U32, U64,
		F32, F64,

		Typedef
	};

	class TupleType
	{
	public:
		bool has_field(std::string_view name) const noexcept;
		TypeRepresentation const& get_field_type(std::string_view name);
		void add_field(std::string_view name, TypeRepresentation const& type);
		void add_field(std::string_view name, TypeRepresentation&& type);

		bool operator==(TupleType const&) const noexcept;
	private:

		// TODO not a string map please. I'm just lazy rn
		std::unordered_map<std::string, TypeRepresentation> fields;
	};


	class TypeRepresentation : public std::variant<BuildInType, TupleType>
	{
	public:
		TypeRepresentation() = default;
		TypeRepresentation(BuildInType const& b) : std::variant<BuildInType, TupleType>{ b } {};
		TypeRepresentation(TupleType const& t) : std::variant<BuildInType, TupleType>{ t } {};

		TypeRepresentation(TypeRepresentation const&) = default;
		TypeRepresentation(TypeRepresentation&&) = default;
		TypeRepresentation& operator=(TypeRepresentation const&) = default;
		TypeRepresentation& operator=(TypeRepresentation&&) = default;
	};

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
		return fields.find((std::string)name) != fields.end();
	}

	TypeRepresentation const& TupleType::get_field_type(std::string_view name)
	{
		assert(has_field(name));
		return fields.find((std::string)name)->second;
	}

	void TupleType::add_field(std::string_view name, TypeRepresentation const& type)
	{
		assert(!has_field(name));
		fields[(std::string)name] = type;
	}

	void TupleType::add_field(std::string_view name, TypeRepresentation&& type)
	{
		assert(!has_field(name));
		fields[(std::string)name] = std::move(type);
	}

	bool TupleType::operator==(TupleType const& other) const noexcept
	{
		if (fields.size() != other.fields.size())
		{
			return false;
		}
		for (auto field : fields)
		{
			auto of = other.fields.find(field.first);
			if (of == other.fields.end())
			{
				return false;
			}
			else if (field.second != of->second)
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
}
