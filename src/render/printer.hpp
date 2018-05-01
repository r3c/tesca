
#ifndef __TESCA_RENDER_PRINTER_HPP
#define __TESCA_RENDER_PRINTER_HPP

#include "../../lib/glay/src/glay.hpp"
#include "../arithmetic/table.hpp"

namespace Tesca
{
	namespace Render
	{
		class Printer
		{
			public:
						Printer (Printer const&);
						Printer ();
				virtual ~Printer ();

				Printer& operator = (Printer const&);

				virtual void print (Glay::Pipe::OStream&, Arithmetic::Table const&) const = 0;
		};
	}
}

#endif
