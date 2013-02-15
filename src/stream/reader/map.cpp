
#include "map.hpp"

namespace	Tesca
{
	MapReader::MapReader ()
	{
	}

	const Row&	MapReader::current () const
	{
		return this->row;
	}

	bool	MapReader::next ()
	{
		this->row.clear ();

		if (this->lines.empty ())
			return false;

		const Fields&	fields = this->lines.front ();

		for (auto i = fields.begin (); i != fields.end (); ++i)
			this->row.push (i->first, i->second);

		this->lines.pop_front ();

		return true;
	}

	void	MapReader::push ()
	{
		this->lines.push_back (Fields ());
	}

	bool	MapReader::set (const std::string& key, const Variant& value)
	{
		if (this->lines.empty ())
			return false;

		this->lines.back ().push_back (std::make_pair (key, value));

		return true;
	}
}
