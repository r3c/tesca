
#ifndef __TESCA_RENDER_PRINTER_CSV_HPP
#define __TESCA_RENDER_PRINTER_CSV_HPP

#include <string>
#include "../../../lib/glay/src/include.hpp"
#include "../../storage/config.hpp"
#include "../printer.hpp"

namespace	Tesca
{
	namespace	Render
	{
		class	CSVPrinter : public Printer
		{
			public:
				CSVPrinter (const CSVPrinter&);
				CSVPrinter (const Storage::Config&);
				virtual	~CSVPrinter ();

				CSVPrinter&	operator = (const CSVPrinter&);

				virtual void	print (Glay::Pipe::OStream&, const Arithmetic::Table&);

			private:
				bool		headers;
				std::string	quote;
				std::string	split;
		};
	}
}

#endif
