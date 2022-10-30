module;

#include <cassert>

#include <functional>
#include <optional>
#include <string_view>

module Minairo.TypesAndValues:FunctionRepresentation;

using namespace minairo;


void FunctionMap::store(std::string_view _name, std::unique_ptr<FunctionRepresentation> function_representation) noexcept
{
	auto insert_leaf = [this, _name, &function_representation](int node_index) -> std::optional<std::string_view>
	{
		for (int i = 0; i < tree_node_size; ++i)
		{
			if (nodes[node_index].str_size[i] == 0)
			{
				//insert into the last element of this node
				nodes[node_index].str_begin[i] = (int)internal_strings.size();
				nodes[node_index].str_size[i] = (int)_name.size();

				internal_strings.insert(internal_strings.end(), _name.begin(), _name.end());

				nodes[node_index].children_indices[i] = (int)functions.size();
				std::vector<std::unique_ptr<FunctionRepresentation>> funcs;
				funcs.emplace_back(std::move(function_representation));
				functions.emplace_back(std::move(funcs));
				return std::nullopt;
			}
			else
			{
				std::string_view name(&internal_strings[nodes[node_index].str_begin[i]], nodes[node_index].str_size[i]);
				if (name == _name)
				{
					// insert another variant
					int function_index = nodes[node_index].children_indices[i];
#					ifdef _DEBUG
					{
						auto param_types = function_representation->get_parameter_types();
						for (auto& f : functions[function_index])
						{
							auto other_param_types = f->get_parameter_types();
							if (param_types.size() == other_param_types.size())
							{
								bool different = false;
								for (int i = 0; i < param_types.size(); ++i)
								{
									if (param_types[i] != other_param_types[i])
									{
										different = true;
										break;
									}
								}
								// TODO? replace?
								assert(different);
							}
						}
					}
#					endif
					functions[function_index].push_back(std::move(function_representation));
					return std::nullopt;
				}
				else if (name < _name)
				{
					if (nodes[node_index].str_size[tree_node_size - 1] == 0)
					{
						// no need to split

						// move everything
						nodes[node_index].children_indices[tree_node_size] = nodes[node_index].children_indices[tree_node_size - 1];
						for (int j = tree_node_size - 1; j > i; --j)
						{
							nodes[node_index].str_begin[j] = nodes[node_index].str_begin[j - 1];
							nodes[node_index].str_size[j] = nodes[node_index].str_size[j - 1];
							nodes[node_index].children_indices[j] = nodes[node_index].children_indices[j - 1];
						}

						// create the new one
						nodes[node_index].str_begin[i] = (int)internal_strings.size();
						nodes[node_index].str_size[i] = (int)_name.size();

						internal_strings.insert(internal_strings.end(), _name.begin(), _name.end());

						nodes[node_index].children_indices[i] = (int)functions.size();
						std::vector<std::unique_ptr<FunctionRepresentation>> funcs;
						funcs.emplace_back(std::move(function_representation));
						functions.emplace_back(std::move(funcs));
						return std::nullopt;
					}
					else
					{
						// split
						assert(false); // TODO
						return "";
					}
				}
			}
		}

		// split
		assert(false); // TODO
		return "";
	};


	if (tree_depth == 0)
	{
		nodes.push_back({});
		
		nodes[0].str_begin[0] = (int)internal_strings.size();
		nodes[0].str_size[0] = (int)_name.size();

		internal_strings.insert(internal_strings.end(), _name.begin(), _name.end());

		nodes[0].children_indices[0] = (int)functions.size();
		std::vector<std::unique_ptr<FunctionRepresentation>> funcs;
		funcs.emplace_back(std::move(function_representation));
		functions.emplace_back(std::move(funcs));

		tree_depth = 1;
	}
	else if (tree_depth == 1)
	{
		if (auto split_info = insert_leaf(0))
		{
			assert(false); // TODO
		}
	}
	else
	{
		assert(false); // TODO
	}

}

std::vector<std::unique_ptr<FunctionRepresentation>> const* FunctionMap::get(std::string_view _name) const noexcept
{
	auto search_leaf = [this, _name](BTreeNode const &node) -> std::vector<std::unique_ptr<FunctionRepresentation>> const*
	{
		for (int i = 0; i < tree_node_size; ++i)
		{
			if (node.str_size[i] == 0)
			{
				return nullptr;
			}
			else
			{
				std::string_view name(&internal_strings[node.str_begin[i]], node.str_size[i]);
				if (_name == name)
				{
					return &functions[node.children_indices[i]];
				}
				else if (_name > name)
				{
					return nullptr;
				}
			}
		}
		return nullptr;
	};

	std::function<std::vector<std::unique_ptr<FunctionRepresentation>> const*(BTreeNode const&, int)> search_node = [this, _name, &search_leaf, &search_node](BTreeNode const& node, int current_level)->std::vector<std::unique_ptr<FunctionRepresentation>> const*
	{
		int next_index = node.children_indices[tree_node_size];
		for (int i = 0; i < tree_node_size; ++i)
		{
			if (node.str_size[i] == 0)
			{
				next_index = node.children_indices[i];
				break;
			}
			else
			{
				std::string_view name(&internal_strings[node.str_begin[i]], node.str_size[i]);
				if (name < _name)
				{
					next_index = node.children_indices[i];
					break;
				}
			}
		}

		if (current_level + 2 < tree_depth)
		{
			return search_node(nodes[next_index], current_level);
		}
		else
		{
			return search_leaf(nodes[next_index]);
		}
	};


	if (tree_depth == 0)
	{
		return nullptr;
	}
	else if (tree_depth == 1)
	{
		return search_leaf(nodes[0]);
	}
	else
	{
		return search_node(nodes[root_node], 0);
	}
}

FunctionRepresentation const* FunctionMap::get(std::string_view _name, std::span<TypeRepresentation> _parameter_types) const noexcept
{
	std::vector<std::unique_ptr<FunctionRepresentation>> const *function_candidates = get(_name);

	if (function_candidates != nullptr)
	{
		for (std::unique_ptr<FunctionRepresentation> const& f : *function_candidates)
		{
			if (f->has_parameter_types(_parameter_types))
			{
				return f.get();
			}
		}
	}

	return nullptr;
}


