
#ifndef __TESCA_RENDER_PRINTER_NAME_HPP
#define __TESCA_RENDER_PRINTER_NAME_HPP

#include "../../../lib/glay/src/include.hpp"
#include "../printer.hpp"

namespace	Tesca
{
	namespace	Render
	{
		class	NamePrinter : public Printer
		{
			public:
						NamePrinter (const NamePrinter&);
						NamePrinter ();
				virtual	~NamePrinter ();

				NamePrinter&	operator = (const NamePrinter&);

				virtual void	print (Glay::Pipe::OStream&, const Arithmetic::Table&);
		};
	}
}

#endif
