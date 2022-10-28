module;

#include <cassert>

#include <algorithm>
#include <optional>
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

		TypeRepresentation const& get_field_type(std::string_view name) const;
		int get_field_index(std::string_view name) const;

		int get_num_fields() const { return (int)fields.size(); }
		std::string_view get_field_name(int index) const { return fields[index]; }
		TypeRepresentation const& get_field_type(int index) const { return types[index]; }

		void add_field(std::string_view name, TypeRepresentation const& type);
		void add_field(std::string_view name, TypeRepresentation&& type);

		bool operator==(TupleType const&) const noexcept;
	private:

		std::vector<std::string> fields;
		std::vector<TypeRepresentation> types;
	};

	class TableType
	{
	public:
		bool has_field(std::string_view name) const noexcept
		{
			return base_tuple.has_field(name);
		}

		TypeRepresentation const& get_field_type(std::string_view name) const
		{
			return base_tuple.get_field_type(name);
		}
		int get_field_index(std::string_view name) const
		{
			return base_tuple.get_field_index(name);
		}

		int get_num_fields() const
		{
			return base_tuple.get_num_fields();
		}
		std::string_view get_field_name(int index) const
		{
			return base_tuple.get_field_name(index);
		}
		TypeRepresentation const& get_field_type(int index) const
		{
			return base_tuple.get_field_type(index);
		}

		void add_field(std::string_view name, TypeRepresentation const& type)
		{
			return base_tuple.add_field(name, type);
		}
		void add_field(std::string_view name, TypeRepresentation&& type)
		{
			return base_tuple.add_field(name, std::move(type));
		}

		bool operator==(TableType const& other) const noexcept
		{
			return base_tuple == other.base_tuple;
		}
	private:
		TupleType base_tuple;
	};


	class TypeRepresentation : public std::variant<BuildInType, TupleType, TableType>
	{
	public:
		TypeRepresentation() = default;
		TypeRepresentation(BuildInType const& b) : std::variant<BuildInType, TupleType, TableType>{ b } {};
		TypeRepresentation(TupleType const& t) : std::variant<BuildInType, TupleType, TableType>{ t } {};
		TypeRepresentation(TableType const& t) : std::variant<BuildInType, TupleType, TableType>{ t } {};

		TypeRepresentation(TypeRepresentation const&) = default;
		TypeRepresentation(TypeRepresentation&&) = default;
		TypeRepresentation& operator=(TypeRepresentation const&) = default;
		TypeRepresentation& operator=(TypeRepresentation&&) = default;

		bool is_tuple() const
		{
			return std::holds_alternative<TupleType>(*this);
		}

		std::optional<TupleType> as_tuple() const
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

		bool is_table() const
		{
			return std::holds_alternative<TableType>(*this);
		}

		std::optional<TableType> as_table() const
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

	void TupleType::add_field(std::string_view name, TypeRepresentation const& type)
	{
		assert(!has_field(name));
		auto it = fields.insert(std::upper_bound(fields.begin(), fields.end(), name), (std::string)name);
		types.insert(types.begin() + (it - fields.begin()), type);
	}

	void TupleType::add_field(std::string_view name, TypeRepresentation&& type)
	{
		assert(!has_field(name));
		auto it = fields.insert(std::upper_bound(fields.begin(), fields.end(), name), (std::string)name);
		types.insert(types.begin() + (it - fields.begin()), std::move(type));
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
}
