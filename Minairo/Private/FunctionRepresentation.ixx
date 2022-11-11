module;

#include <cassert>

#include <functional>
#include <memory>
#include <span>
#include <string_view>
#include <vector>

export module Minairo.TypesAndValues:FunctionRepresentation;

import :TypeRepresentation;

export namespace minairo
{
	class FunctionRepresentation : public ComplexValue
	{
	public:
		virtual ~FunctionRepresentation() = default;

		virtual TypeRepresentation get_return_type() const noexcept = 0;
		virtual bool has_parameter_types(std::span<TypeRepresentation const> _parameter_types) const noexcept = 0;
		virtual std::span<TypeRepresentation const> get_parameter_types() const noexcept = 0;
		virtual FunctionType get_type() const noexcept = 0;

		virtual void call(void* return_value, std::span<void*> _arguments) const noexcept = 0;

		virtual std::unique_ptr<FunctionRepresentation> deep_copy() const = 0;

	private:
		friend class FunctionMap;
	};

	template<bool Pure, typename Ret, typename... Params>
	class TypedFunctionRepresentation final : public FunctionRepresentation
	{
	public:
		TypedFunctionRepresentation() = default;

		TypeRepresentation get_return_type() const noexcept override
		{
			return get_type_representation<Ret>();
		}

		void set_callable(std::function<Ret(Params...)> _callable)
		{
			callable = std::move(_callable);
		}

		bool has_parameter_types(std::span<TypeRepresentation const> _parameter_types) const noexcept final override
		{
			if (_parameter_types.size() != sizeof...(Params))
			{
				return false;
			}
			else
			{
				TypeRepresentation params[sizeof...(Params)] = { get_type_representation<Params>()... };
				for (int i = 0; i < sizeof...(Params); ++i)
				{
					if (_parameter_types[i] != params[i])
						return false;
				}
				return true;
			}
		}
		std::span<TypeRepresentation const> get_parameter_types() const noexcept final override
		{
			static TypeRepresentation params[sizeof...(Params)] = { get_type_representation<Params>()... };
			return params;
		}
		FunctionType get_type() const noexcept override
		{
			FunctionType result;
			result.is_pure = Pure;
			result.return_type = get_type_representation<Ret>();
			std::string c = "a";
			for (TypeRepresentation const& t : get_parameter_types())
			{
				result.parameters.add_field(c, t);

				if (c[0] == 'z')
					c[0] = 'A';
				else if (c[0] == 'Z')
					assert(false); // TODO
				else
					++c[0];

			}

			return result;
		}


		void call(void* return_value, std::span<void*> _arguments) const noexcept override
		{
			assert(_arguments.size() == sizeof...(Params));

			if constexpr (std::is_same_v<Ret, void>)
			{
				call_internal(_arguments);
			}
			else if(return_value == nullptr)
			{
				call_internal(_arguments);
			}
			else
			{
				*((Ret*)return_value) = call_internal(_arguments);
			}
		}

		std::unique_ptr<FunctionRepresentation> deep_copy() const override
		{
			return std::make_unique<TypedFunctionRepresentation<Pure, Ret, Params...>>(*this);
		}

	protected:
		virtual bool equals(ComplexValue const&) const
		{
			assert(false); // TODO
			return false;
		}

	private:
		std::function<Ret(Params...)> callable;


		template<typename... T>
		Ret call_internal(std::span<void*> span_arguments, T... _arguments) const noexcept
		{
			if constexpr (sizeof...(T) == sizeof...(Params))
			{
				return callable(*(Params*)_arguments...);
			}
			else
			{
				return call_internal(span_arguments, _arguments..., span_arguments[sizeof...(T)]);
			}
		}
	};




	class FunctionMap
	{
	public:

		void store(std::string_view name, std::unique_ptr<FunctionRepresentation> function_representation) noexcept;
		std::vector<std::unique_ptr<FunctionRepresentation>> const* get(std::string_view name) const noexcept;

		FunctionRepresentation const* get(std::string_view name, std::span<TypeRepresentation> parameter_types) const noexcept;

	private:
		static const size_t intern_block_size = 4 * 1024;
		static const size_t tree_node_size = 8;

		int tree_depth = 0, root_node = 0;

		// interning
		std::vector<char> internal_strings;
		std::vector<std::vector<std::unique_ptr<FunctionRepresentation>>> functions;

		struct BTreeNode
		{
			uint8_t str_size[tree_node_size] = {};
			uint32_t str_begin[tree_node_size];
			uint32_t children_indices[tree_node_size + 1];
		};
		std::vector<BTreeNode> nodes;
	};
}