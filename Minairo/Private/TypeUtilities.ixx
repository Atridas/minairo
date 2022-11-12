export module Minairo.AST.TypePass:TypeUtilities;

import Minairo.AST;
import Minairo.TypesAndValues;

export namespace minairo
{
	struct TypeInformation
	{
		TypeRepresentation type;
		bool constant;
	};

	TypeInformation deduce_type(Expression const& expression);

	bool all_paths_lead_to_a_return(Statement const& statement);
}
