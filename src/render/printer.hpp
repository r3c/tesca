
#ifndef __TESCA_RENDER_PRINTER_HPP
#define __TESCA_RENDER_PRINTER_HPP

#include "../../lib/glay/src/include.hpp"
#include "../arithmetic/table.hpp"

namespace	Tesca
{
	namespace	Render
	{
		class	Printer
		{
			public:
						Printer (const Printer&);
						Printer ();
				virtual	~Printer ();

				Printer&	operator = (const Printer&);

				virtual void	print (Glay::Pipe::OStream&, const Arithmetic::Table&) = 0;
		};
	}
}

#endif
