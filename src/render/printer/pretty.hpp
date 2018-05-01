
#ifndef __TESCA_RENDER_PRINTER_PRETTY_HPP
#define __TESCA_RENDER_PRINTER_PRETTY_HPP

#include <cstring>
#include "../../../lib/glay/src/glay.hpp"
#include "../../storage/config.hpp"
#include "../printer.hpp"

namespace Tesca
{
	namespace Render
	{
		class PrettyPrinter : public Printer
		{
			public:
				PrettyPrinter (PrettyPrinter const&);
				PrettyPrinter (Storage::Config const&);

				PrettyPrinter& operator = (PrettyPrinter const&);

				virtual void print (Glay::Pipe::OStream&, Arithmetic::Table const&) const;

			private:
				Glay::Int32u align;
				Glay::Int32u pad;
		};
	}
}

#endif
