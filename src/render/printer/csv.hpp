
#ifndef __TESCA_RENDER_PRINTER_CSV_HPP
#define __TESCA_RENDER_PRINTER_CSV_HPP

#include <string>
#include "../../../lib/glay/src/glay.hpp"
#include "../../storage/config.hpp"
#include "../printer.hpp"

namespace Tesca
{
	namespace Render
	{
		class CSVPrinter : public Printer
		{
			public:
				CSVPrinter (CSVPrinter const&);
				CSVPrinter (Storage::Config const&);

				CSVPrinter& operator = (CSVPrinter const&);

				virtual void print (Glay::Pipe::OStream&, Arithmetic::Table const&) const;

			private:
				void write (Glay::Pipe::FormatWriter&, const std::string&) const;

				bool headers;
				std::string quote;
				std::string split;
		};
	}
}

#endif
