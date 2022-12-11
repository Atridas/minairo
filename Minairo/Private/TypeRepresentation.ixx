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
		bool equals(ComplexType const& other) const override;
	};

	class InterfaceType : public ComplexType
	{
		std::string name;
		std::string_view concept_name, interface_name;
	public:
		int index;
		TupleType base_tuple;

		InterfaceType() = default;
		InterfaceType(InterfaceType const& other);
		InterfaceType(InterfaceType&&) = default;
		InterfaceType& operator=(InterfaceType const& other);
		InterfaceType& operator=(InterfaceType&&) = default;

		void set_name(std::string_view _name) override;
		std::string_view get_name() const { return name; }
		std::string_view get_concept_name() const { return concept_name; }
		std::string_view get_interface_name() const { return interface_name; }

		bool operator==(InterfaceType const& other) const noexcept;

		operator TypeRepresentation() const
		{
			return (std::shared_ptr<ComplexType>)std::make_shared<InterfaceType>(*this);
		}

		operator Value() const
		{
			return (std::shared_ptr<ComplexType>)std::make_shared<InterfaceType>(*this);
		}
	protected:
		bool equals(ComplexType const& other) const override;
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

		bool operator==(TableType const& other) const noexcept;

		operator TypeRepresentation() const
		{
			return (std::shared_ptr<ComplexType>)std::make_shared<TableType>(*this);
		}

		operator Value() const
		{
			return (std::shared_ptr<ComplexType>)std::make_shared<TableType>(*this);
		}
	protected:
		bool equals(ComplexType const& other) const override;
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

		bool operator==(FunctionType const& other) const noexcept;

		operator TypeRepresentation() const
		{
			return (std::shared_ptr<ComplexType>)std::make_shared<FunctionType>(*this);
		}

		operator Value() const
		{
			return (std::shared_ptr<ComplexType>)std::make_shared<FunctionType>(*this);
		}
	protected:
		bool equals(ComplexType const& other) const override;
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

	class ConceptType : public ComplexType
	{
	public:
		std::string name;
		struct VirtualFunctionType : public FunctionType
		{
			std::vector<int> interface_paramenters;
			int index;

			VirtualFunctionType() = default;
			VirtualFunctionType(FunctionType const& _function_type, std::vector<int>&& _interface_paramenters, int _index);

			std::shared_ptr<InterfaceType> get_indexed_overriden_parameter(int index) const;

			bool operator==(VirtualFunctionType const& other) const;

			operator TypeRepresentation() const
			{
				return (std::shared_ptr<ComplexType>)std::make_shared<VirtualFunctionType>(*this);
			}

			operator Value() const
			{
				return (std::shared_ptr<ComplexType>)std::make_shared<VirtualFunctionType>(*this);
			}
		protected:
			bool equals(ComplexType const& other) const override;
		};

		void set_name(std::string_view _name) override { name = _name; }

		void add_interface(std::string_view name, InterfaceType const& interface);
		InterfaceType const& get_interface(std::string_view interface_name) const;

		void add_function(std::string_view name, FunctionType const& function, std::vector<int>&& interface_paramenters);
		VirtualFunctionType const& get_function(std::string_view function_name) const;

		int get_num_single_dispatch_functions(std::string_view interface_name) const;
		int get_num_multi_dispatch_functions(std::string_view interface_name) const;

		enum class Kind
		{
			Interface, Function, None
		};
		Kind get_member_kind(std::string_view name) const;

		bool operator==(ConceptType const& other) const noexcept;

		operator TypeRepresentation() const
		{
			return (std::shared_ptr<ComplexType>)std::make_shared<ConceptType>(*this);
		}

		operator Value() const
		{
			return (std::shared_ptr<ComplexType>)std::make_shared<ConceptType>(*this);
		}
	protected:
		bool equals(ComplexType const& other) const override;

		std::unordered_map<std::string, InterfaceType> interfaces;
		std::unordered_map<std::string, VirtualFunctionType> functions;
		std::unordered_map<std::string, int>  single_dispatch_functions;
		std::unordered_map<std::string, int>  multi_dispatch_functions;
	};

	// -----------------------------------------------------------------------------------------------
	// -----------------------------------------------------------------------------------------------
	// -----------------------------------------------------------------------------------------------

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
