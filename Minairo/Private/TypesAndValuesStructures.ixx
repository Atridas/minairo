module;

#include <cassert>

#include <algorithm>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>

export module Minairo.TypesAndValues:Structures;

export namespace minairo
{
	class TypeRepresentation;
	class Value;

	// -----------------------------------------------------------------------------------------------
	// -----------------------------------------------------------------------------------------------
	// -----------------------------------------------------------------------------------------------

	enum class BuildInType
	{
		Void,
		Bool,
		I8, I16, I32, I64,
		U8, U16, U32, U64,
		F32, F64,

		InitializerList,
		Typedef,
		ProcedureDef
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
		Value const& get_field_init_value(int index) const { return init_values[index]; }

		void add_field(std::string_view name, TypeRepresentation const& type, Value const &init_value);

		bool operator==(TupleType const&) const noexcept;
	private:

		std::vector<std::string> fields;
		std::vector<TypeRepresentation> types;
		std::vector<Value> init_values;
	};

	class TupleReferenceType
	{
	public:
		TupleType tuple;
		bool constant;
	};

	class TableType
	{
	public:
		TupleType base_tuple;

		bool operator==(TableType const& other) const noexcept
		{
			return base_tuple == other.base_tuple;
		}
	};


	class TypeRepresentation : public std::variant<BuildInType, TupleType, TupleReferenceType, TableType>
	{
		using Base = std::variant<BuildInType, TupleType, TupleReferenceType, TableType>;
	public:
		TypeRepresentation() = default;
		TypeRepresentation(BuildInType const& b) : Base{ b } {};
		TypeRepresentation(TupleType const& t) : Base{ t } {};
		TypeRepresentation(TupleReferenceType const& t) : Base{ t } {};
		TypeRepresentation(TableType const& t) : Base{ t } {};

		TypeRepresentation(TypeRepresentation const&) = default;
		TypeRepresentation(TypeRepresentation&&) = default;
		TypeRepresentation& operator=(TypeRepresentation const&) = default;
		TypeRepresentation& operator=(TypeRepresentation&&) = default;

		bool is_build_in() const;
		std::optional<BuildInType> as_build_in() const;

		bool is_tuple() const;
		std::optional<TupleType> as_tuple() const;

		bool is_tuple_reference() const;
		std::optional<TupleReferenceType> as_tuple_reference() const;

		bool is_table() const;
		std::optional<TableType> as_table() const;
	};

	// -----------------------------------------------------------------------------------------------
	// -----------------------------------------------------------------------------------------------
	// -----------------------------------------------------------------------------------------------

	struct Table
	{
		TableType type;
		int rows = 0;
		// TODO allocate this in one go as we know the table type(?)
		std::vector<std::vector<Value>> fields;
	};

	struct Tuple
	{
		TupleType type;
		std::vector<Value> fields;
	};

	struct TupleReferenceOnStack
	{
		Tuple* tuple;

		Value& get_field(int index)
		{
			return tuple->fields[index];
		}

		Tuple& as_tuple() const
		{
			return *tuple;
		}
	};

	struct TupleReference : public std::variant<TupleReferenceOnStack>
	{
		Value& get_field(int index)
		{
			return std::visit([index](auto self) -> Value&
				{
					return self.get_field(index);
				}, *this);
		}

		Tuple as_tuple() const
		{
			return std::visit([](auto self) -> Tuple&
				{
					return self.as_tuple();
				}, *this);
		}
	};

	class Value : public std::variant<
		int8_t, int16_t, int32_t, int64_t,
		uint8_t, uint16_t, uint32_t, uint64_t,
		float, double,
		std::string,
		char32_t,
		bool,
		TypeRepresentation,
		Table,
		Tuple,
		TupleReference>
	{
		using Base = std::variant<
			int8_t, int16_t, int32_t, int64_t,
			uint8_t, uint16_t, uint32_t, uint64_t,
			float, double,
			std::string,
			char32_t,
			bool,
			TypeRepresentation,
			Table,
			Tuple,
			TupleReference>;


	public:
		Value() = default;
		Value(int8_t const& i) : Base{ i } {};
		Value(int16_t const& i) : Base{ i } {};
		Value(int32_t const& i) : Base{ i } {};
		Value(int64_t const& i) : Base{ i } {};
		Value(uint8_t const& i) : Base{ i } {};
		Value(uint16_t const& i) : Base{ i } {};
		Value(uint32_t const& i) : Base{ i } {};
		Value(uint64_t const& i) : Base{ i } {};
		Value(float const& i) : Base{ i } {};
		Value(double const& i) : Base{ i } {};
		Value(bool const& i) : Base{ i } {};
		Value(TypeRepresentation const& i) : Base{ i } {};
		Value(BuildInType const& i) : Base{ (TypeRepresentation)i } {};
		Value(TableType const& i) : Base{ (TypeRepresentation)i } {};
		Value(TupleType const& i) : Base{ (TypeRepresentation)i } {};
		Value(Table const& i) : Base{ i } {};
		Value(Tuple const& i) : Base{ i } {};
		Value(TupleReferenceOnStack const& i) : Base{ (TupleReference)i } {};

		Value(Value const&) = default;
		Value(Value&&) = default;
		Value& operator=(Value const&) = default;
		Value& operator=(Value&&) = default;
	};
}
