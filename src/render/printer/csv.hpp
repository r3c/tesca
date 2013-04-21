
#ifndef __TESCA_RENDER_PRINTER_CSV_HPP
#define __TESCA_RENDER_PRINTER_CSV_HPP

#include "../../../lib/glay/src/include.hpp"
#include "../printer.hpp"

namespace	Tesca
{
	namespace	Render
	{
		class	CSVPrinter : public Printer
		{
			public:
						CSVPrinter (const CSVPrinter&);
						CSVPrinter ();
				virtual	~CSVPrinter ();

				CSVPrinter&	operator = (const CSVPrinter&);

				virtual void	print (Glay::Pipe::OStream&, const Arithmetic::Table&);
		};
	}
}

#endif
