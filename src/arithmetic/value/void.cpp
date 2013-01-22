
#include "void.hpp"

using namespace std;
using namespace Glay;

namespace	Tesca
{
	const VoidValue	VoidValue::instance = VoidValue ();

	VoidValue::VoidValue ()
	{
	}

	Value::ContentType	VoidValue::getType () const
	{
		return ContentType::NONE;
	}

	Value*	VoidValue::clone () const
	{
		return new VoidValue ();
	}

	bool	VoidValue::toBoolean (bool*) const
	{
		return false;
	}

	bool	VoidValue::toNumber (Float64*) const
	{
		return false;
	}

	bool	VoidValue::toString (string*) const
	{
		return false;
	}
}
