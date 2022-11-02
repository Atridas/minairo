module;

#include <cassert>

#include <algorithm>
#include <memory>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>

export module Minairo.TypesAndValues:Structures;

export namespace minairo
{
	class FunctionRepresentation;
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
		Typedef
	};

	class ComplexType
	{
	public:
		bool operator==(ComplexType const& o) const
		{
			return equals(o);
		}

	protected:
		virtual bool equals(ComplexType const&) const = 0;
	};

	class TypeRepresentation : public std::variant<BuildInType, std::shared_ptr<ComplexType>>
	{
		using Base = std::variant<BuildInType, std::shared_ptr<ComplexType>>;
	public:
		TypeRepresentation() = default;
		TypeRepresentation(BuildInType const& b) : Base{ b } {};
		TypeRepresentation(std::shared_ptr<ComplexType> const& i) : Base{ i } {};
		TypeRepresentation(std::shared_ptr<ComplexType>&& i) : Base{ std::move(i) } {};

		TypeRepresentation(TypeRepresentation const&) = default;
		TypeRepresentation(TypeRepresentation&&) = default;
		TypeRepresentation& operator=(TypeRepresentation const&) = default;
		TypeRepresentation& operator=(TypeRepresentation&&) = default;
	};

	bool operator==(TypeRepresentation const& a, TypeRepresentation const& b)
	{
		if (std::holds_alternative<BuildInType>(a) && std::holds_alternative<BuildInType>(b))
		{
			return std::get<BuildInType>(a) == std::get<BuildInType>(b);
		}
		else if (std::holds_alternative<std::shared_ptr<ComplexType>>(a) && std::holds_alternative<std::shared_ptr<ComplexType>>(b))
		{
			auto& self = std::get<std::shared_ptr<ComplexType>>(a);
			auto& othe = std::get<std::shared_ptr<ComplexType>>(b);
			if (self != nullptr && othe != nullptr)
			{
				return *self == *othe;
			}
			else
			{
				return false;
			}
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

	// -----------------------------------------------------------------------------------------------
	// -----------------------------------------------------------------------------------------------
	// -----------------------------------------------------------------------------------------------

	class ComplexValue
	{
	public:
		bool operator=(ComplexValue const& o) const
		{
			return equals(o);
		}

	protected:
		virtual bool equals(ComplexValue const&) const = 0;
	};

	class Value : public std::variant<
		int8_t, int16_t, int32_t, int64_t,
		uint8_t, uint16_t, uint32_t, uint64_t,
		float, double,
		std::string,
		char32_t,
		bool,
		TypeRepresentation,
		std::shared_ptr<ComplexValue>>
	{
		using Base = std::variant<
			int8_t, int16_t, int32_t, int64_t,
			uint8_t, uint16_t, uint32_t, uint64_t,
			float, double,
			std::string,
			char32_t,
			bool,
			TypeRepresentation,
			std::shared_ptr<ComplexValue>>;


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
		Value(BuildInType const& i) : Base{ (TypeRepresentation)i } {};
		Value(std::shared_ptr<ComplexType> const& i) : Base{ (TypeRepresentation)i } {};
		Value(std::shared_ptr<ComplexType>&& i) : Base{ (TypeRepresentation)std::move(i) } {};
		Value(TypeRepresentation const& i) : Base{ i } {};
		Value(std::shared_ptr<ComplexValue> const& i) : Base{ i } {};
		Value(std::shared_ptr<ComplexValue>&& i) : Base{ std::move(i) } {};

		Value(Value const&) = default;
		Value(Value&&) = default;
		Value& operator=(Value const&) = default;
		Value& operator=(Value&&) = default;
	};

}
