
#include "pretty.hpp"

#include <string>

using namespace std;
using namespace Glay;
using namespace Glay::Pipe;
using namespace Glay::System;
using namespace Tesca::Arithmetic;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Render
	{
		PrettyPrinter::PrettyPrinter (const Config& config)
		{
			string	align (config.get ("align", ""));
			string	pad (config.get ("pad", ""));

			if (!Convert::toInteger (&this->align, align.c_str (), align.length ()) || this->align < 1)
				this->align = 4;

			if (!Convert::toInteger (&this->pad, pad.c_str (), pad.length ()))
				this->pad = 1;
		}

		void	PrettyPrinter::print (OStream& stream, const Table& table) const
		{
			const Table::Columns&	columns (table.getColumns ());
			Int32u*					length;
			Int32u					lengths[table.getWidth ()];
			string					output;
			Int32u					margin;
			Variant*				value;
			Int32u					width (table.getWidth ());
			FormatWriter			writer (stream);

			memset (lengths, 0, width * sizeof (*lengths));

			margin = this->align + this->pad - 1;

			for (auto row = table.begin (); row != table.end (); ++row)
			{
				length = lengths;
				value = *row;

				for (Int32u i = 0; i < width; ++i)
				{
					if (value->toString (&output))
						*length = max (*length, ((output.length () + margin) / this->align) * this->align);

					++length;
					++value;
				}
			}

			if (true)
			{
				length = lengths;

				for (Int32u i = 0; i < width; ++i)
				{
					const string&	key = columns[i].getKey ();

					*length = max (*length, ((key.length () + 2 + margin) / this->align) * this->align);

					writer.write ('[');
					writer.write (key);
					writer.write (']');

					for (Int32u j = *length - key.length () - 2; j-- > 0; )
						writer.write (' ');

					++length;
				}

				writer.write ('\n');
			}

			for (auto row = table.begin (); row != table.end (); ++row)
			{
				length = lengths;
				value = *row;

				for (Int32u i = 0; i < width; ++i)
				{
					if (value->toString (&output))
						writer.write (output);
					else
						output.clear ();

					for (Int32u j = *length - output.length (); j-- > 0; )
						writer.write (' ');

					++length;
					++value;
				}

				writer.write ('\n');
			}
		}
	}
}
