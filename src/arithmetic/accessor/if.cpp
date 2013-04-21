
#include "if.hpp"

#include "void.hpp"

using namespace Tesca::Provision;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
	{
		IfAccessor::IfAccessor (const Accessor* condition, const Accessor* onTrue, const Accessor* onFalse) :
			condition (condition),
			onFalse (onFalse),
			onTrue (onTrue)
		{
		}

		IfAccessor::IfAccessor (const Accessor* condition, const Accessor* onTrue) :
			condition (condition),
			onFalse (&VoidAccessor::instance),
			onTrue (onTrue)
		{
		}

		Variant	IfAccessor::read (const Row& row) const
		{
			bool	test;

			if (this->condition->read (row).toBoolean (&test) && test)
				return this->onTrue->read (row);
			else
				return this->onFalse->read (row);
		}
	}
}
