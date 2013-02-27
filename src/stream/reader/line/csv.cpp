
#include "csv.hpp"

using namespace std;
using namespace Glay;
using namespace Glay::System;

namespace	Tesca
{
	CSVLineReader::CSVLineReader (Pipe::IStream* input, const Lookup& lookup, const Config& config) :
		LineReader (input),
		row (lookup.count ())
	{
		const char*	buffer;
		Int32u		index;
		Int32u		length;

		// Read headers or use numbered default
		auto	headers = config.find ("headers");

		if (headers != config.end () && this->fetch (&buffer, &length))
		{
			this->split (buffer, length, [&] (Int32u index, const char* buffer, Int32u length)
			{
				Int32u	target;

				if (lookup.find (string (buffer, length), &target))
					this->mapping[index] = target;
			});
		}
		else
		{
			for (auto i = lookup.begin (); i != lookup.end (); ++i)
			{
				if (Convert::toInt32u (&index, i->first.c_str (), i->first.length ()))
					this->mapping[index] = i->second;
			}
		}

		// Read split characters from configuration
		auto	splits = config.find ("splits");

		this->splits = static_cast<char*> (calloc (1 << (sizeof (*this->splits) * 8), sizeof (*this->splits)));

		if (splits != config.end ())
			buffer = splits->second.c_str ();
		else
			buffer = ",";

		while (*buffer)
			this->splits[(Int32u)*buffer++] = 1;
	}

	const Row&	CSVLineReader::current () const
	{
		return this->row;
	}

	void	CSVLineReader::parse (const char* line, Int32u length)
	{
		this->row.clear ();

		this->split (line, length, [&] (Int32u index, const char* buffer, Int32u length)
		{
			auto	field = this->mapping.find (index);

			if (field != this->mapping.end ())
				this->row.set (field->second, Variant (buffer, length));
		});
	}

	void	CSVLineReader::split (const char* line, Int32u length, Callback callback)
	{
		Int32u		index;
		const char*	start;
		const char*	stop;

		index = 0;
		start = line;
		stop = line;

		while (length-- > 0)
		{
			if (this->splits[(Int32u)*stop])
			{
				callback (index++, start, stop - start);

				start = stop + 1;
			}

			++stop;
		}

		callback (index, start, stop - start);
	}
}
