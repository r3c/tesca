
#ifndef __TESCA_RENDER_PRINTER_NAME_HPP
#define __TESCA_RENDER_PRINTER_NAME_HPP

#include "../../../lib/glay/src/glay.hpp"
#include "../../storage/config.hpp"
#include "../printer.hpp"

namespace Tesca
{
	namespace Render
	{
		class NamePrinter : public Printer
		{
			public:
				NamePrinter (NamePrinter const&);
				NamePrinter (Storage::Config const&);

				NamePrinter& operator = (NamePrinter const&);

				virtual void print (Glay::Pipe::OStream&, Arithmetic::Table const&) const;
		};
	}
}

#endif
