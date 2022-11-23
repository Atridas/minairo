module;

#include <cassert>

#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

export module Minairo.TypesAndValues:Values;

import :FunctionRepresentation;
import :Structures;
import :TypeRepresentation;

export namespace minairo
{
	struct Table final: public ComplexValue
	{
		TableType type;
		int rows = 0;
		// TODO allocate this in one go as we know the table type(?)
		std::vector<std::vector<Value>> fields;

		bool operator==(Table const& other) const noexcept
		{
			return rows == other.rows && type == other.type && fields == other.fields;
		}

		operator Value() const
		{
			return (std::shared_ptr<ComplexValue>)std::make_shared<Table>(*this);
		}

	protected:
		bool equals(ComplexValue const& other) const override
		{
			if (auto t = dynamic_cast<Table const*>(&other))
				return *this == *t;
			else
				return false;
		}
	};

	struct Tuple final: public ComplexValue
	{
		TupleType type;
		std::vector<Value> fields;

		bool operator==(Tuple const& other) const noexcept
		{
			return type == other.type && fields == other.fields;
		}

		operator Value() const
		{
			return (std::shared_ptr<ComplexValue>)std::make_shared<Tuple>(*this);
		}

	protected:
		bool equals(ComplexValue const& other) const override
		{
			if (auto t = dynamic_cast<Tuple const*>(&other))
				return *this == *t;
			else
				return false;
		}
	};

	struct TupleReference : public ComplexValue
	{
		virtual Value& get_field(int index) = 0;

		virtual Tuple as_tuple() const = 0;
	};

	struct TupleReferenceOnStack final: public TupleReference
	{
		std::shared_ptr<Tuple> tuple;

		Value& get_field(int index) override
		{
			return tuple->fields[index];
		}

		Tuple as_tuple() const override
		{
			return *tuple;
		}

		operator Value() const
		{
			return (std::shared_ptr<ComplexValue>)std::make_shared<TupleReferenceOnStack>(*this);
		}

	protected:
		bool equals(ComplexValue const& other) const override
		{
			if (auto t = dynamic_cast<TupleReferenceOnStack const*>(&other))
				return this->tuple == t->tuple;
			else
				return false;
		}
	};

	struct TupleReferenceOnATable final: public TupleReference
	{
		std::shared_ptr<Table> table;
		int row;

		Value& get_field(int index) override
		{
			return table->fields[index][row];
		}

		Tuple as_tuple() const override
		{
			Tuple result;
			result.type = table->type.base_tuple;
			result.fields.reserve(table->fields.size());
			for (auto& column : table->fields)
				result.fields.push_back(column[row]);

			return result;
		}

		operator Value() const
		{
			return (std::shared_ptr<ComplexValue>)std::make_shared<TupleReferenceOnATable>(*this);
		}

	protected:
		bool equals(ComplexValue const& other) const override
		{
			if (auto t = dynamic_cast<TupleReferenceOnATable const*>(&other))
				return row == row && this->table == t->table;
			else
				return false;
		}
	};

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
		case BuildInType::String:
			return std::get<std::string>(value);
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

	Value get_default_value(std::shared_ptr<ComplexType> const& type)
	{
		if (ConceptType const* concept_type = dynamic_cast<ConceptType*>(type.get()))
		{
			return BuildInType::Void;
		}
		else if (FunctionType const* function_type = dynamic_cast<FunctionType*>(type.get()))
		{
			DefaultFunction result;
			result.type = *function_type;
			return (std::shared_ptr<ComplexValue>)std::move(result.deep_copy());
		}
		else if (TableType const* table_type = dynamic_cast<TableType*>(type.get()))
		{
			Table result;
			result.type = *table_type;

			result.fields.resize(table_type->base_tuple.get_num_fields());

			return result;
		}
		else if (TupleType const* tuple_type = dynamic_cast<TupleType*>(type.get()))
		{
			Tuple result;
			result.type = *tuple_type;

			for (int i = 0; i < tuple_type->get_num_fields(); ++i)
			{
				if (auto default_value = tuple_type->get_field_init_value(i))
					result.fields.push_back(*default_value);
				else
					result.fields.push_back(get_default_value(tuple_type->get_field_type(i)));
			}

			return result;
		}
		else
		{
			assert(false);
			return {};
		}
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
			case BuildInType::Void:
				//value = BuildInType::Void;
				return nullptr;
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

	template<typename T>
	auto get(Value const& value)
	{
		if constexpr (std::is_same_v<T, BuildInType> || std::is_base_of_v<ComplexType, T>)
		{
			if (std::holds_alternative<TypeRepresentation>(value))
			{
				return get<T>(std::get<TypeRepresentation>(value));
			}
			else
			{
				return decltype(get<T>(TypeRepresentation{})){};
			}
		}
		else if constexpr (std::is_base_of_v<ComplexValue, T>)
		{
			if (std::holds_alternative<std::shared_ptr<ComplexValue>>(value))
			{
				if (std::shared_ptr<T> p = std::dynamic_pointer_cast<T>(std::get< std::shared_ptr<ComplexValue>>(value)))
					return p;
			}
			return std::shared_ptr<T>{};
		}
		else
		{
			if (std::holds_alternative<T>(value))
			{
				return (std::optional<T>)std::get<T>(value);
			}
			else
			{
				return std::optional<T>{};
			}
		}
	}
}
