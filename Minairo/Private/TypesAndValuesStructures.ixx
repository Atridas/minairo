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

		String,

		InitializerList,
		Typedef
	};

	std::size_t compute_hash(std::vector<std::string> names)
	{
		if (names.empty())
			return 0;

		std::string full_path = names[0];
		for (int i = 1; i < (int)names.size(); ++i)
		{
			full_path += "." + names[i];
		}

		return std::hash<std::string_view>()(full_path);
	}

	std::size_t compute_hash(std::vector<std::string> names, std::string_view leaf)
	{
		assert(!leaf.empty());

		if (names.empty())
			return std::hash<std::string_view>()(leaf);

		std::string full_path = names[0];
		for (int i = 1; i < (int)names.size(); ++i)
		{
			full_path += "." + names[i];
		}

		full_path += "." + (std::string)leaf;

		return std::hash<std::string_view>()(full_path);
	}

	std::size_t compute_hash(std::string_view leaf)
	{
		assert(!leaf.empty());

		return std::hash<std::string_view>()(leaf);
	}

	struct TypePath
	{
		TypePath()
			: names()
			, hash(0)
		{}

		explicit TypePath(std::string_view _name)
			: hash(compute_hash(_name))
		{
			names.push_back((std::string)_name);
		}
		TypePath(TypePath path, std::string_view _name)
			: names(std::move(path.names))
		{
			names.push_back((std::string)_name);
			hash = compute_hash(names);
		}
		explicit TypePath(std::vector<std::string> _names)
			: names(std::move(_names))
		{
			hash = compute_hash(names);
		}

		bool is_empty() const
		{
			return names.empty();
		}

		bool operator==(TypePath const& other) const
		{
			return hash == other.hash && names == other.names;
		}

	private:
		std::vector<std::string> names;
		std::size_t hash;

		friend struct TypeNameHash;
		friend struct TypeFullName;
	};

	struct TypeShortName
	{
		TypeShortName()
			: name()
			, hash(0)
		{}
		explicit TypeShortName(std::string_view _name)
			: name(_name)
			, hash(compute_hash(name))
		{}

		bool operator==(TypeShortName const& other) const
		{
			return name == other.name;
		}

	private:
		std::string name;
		std::size_t hash;

		friend struct TypeNameHash;
		friend struct TypeFullName;
	};

	struct TypeFullName
	{
		TypeFullName()
			: path()
			, short_name()
			, hash(0)
			, has_value(false)
		{}
		TypeFullName(TypePath _path, TypeShortName _short_name)
			: path(std::move(_path))
			, short_name(std::move(_short_name))
			, has_value(true)
		{
			assert(!short_name.name.empty());

			hash = compute_hash(path.names, short_name.name);
		}
		explicit TypeFullName(TypePath _path)
			: has_value(true)
		{
			assert(!_path.names.empty());
			short_name = TypeShortName{ _path.names.back() };
			_path.names.pop_back();
			path = TypePath{ _path.names };

			hash = compute_hash(path.names, short_name.name);
		}

		TypePath const& get_path() const
		{
			return path;
		}

		TypeShortName const& get_short_name() const
		{
			return short_name;
		}

		bool is_empty() const
		{
			return !has_value;
		}

		std::string print() const
		{
			if (path.is_empty())
				return (std::string)short_name.name;

			std::string full_path = path.names[0];
			for (int i = 1; i < (int)path.names.size(); ++i)
			{
				full_path += "." + path.names[i];
			}

			full_path += "." + (std::string)short_name.name;
			return full_path;
		}

		bool operator==(TypeFullName const& other) const
		{
			return hash == other.hash && has_value && other.has_value && path == other.path && short_name == other.short_name;
		}

	private:
		TypePath path;
		TypeShortName short_name;
		std::size_t hash;
		bool has_value;

		friend struct TypeNameHash;
	};

	struct TypeNameHash
	{
		std::size_t operator()(TypePath const& path) const
		{
			return path.hash;
		}
		std::size_t operator()(TypeShortName const& short_name) const
		{
			return short_name.hash;
		}
		std::size_t operator()(TypeFullName const& full_name) const
		{
			return full_name.hash;
		}
	};

	template<typename T>
	using TypePathMap = std::unordered_map<TypePath, T, TypeNameHash>;
	template<typename T>
	using TypeShortNameMap = std::unordered_map<TypeShortName, T, TypeNameHash>;
	template<typename T>
	using TypeFullNameMap = std::unordered_map<TypeFullName, T, TypeNameHash>;

	class ComplexType
	{
	public:
		bool operator==(ComplexType const& o) const
		{
			return equals(o);
		}

		virtual void set_name(TypeFullName _name) = 0;

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

		bool is_buildin() const { return std::holds_alternative<BuildInType>(*this); }
		bool is_integral() const;
		bool is_float() const;

		void set_name(TypeFullName _name)
		{
			if (std::holds_alternative<std::shared_ptr<ComplexType>>(*this))
			{
				std::get<std::shared_ptr<ComplexType>>(*this)->set_name(std::move(_name));
			}
		}
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
		Value(std::string const& i) : Base{ i } {};
		Value(std::string&& i) : Base{ std::move(i) } {};
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
