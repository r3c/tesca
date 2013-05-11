
#ifndef __TESCA_RENDER_PRINTER_PRETTY_HPP
#define __TESCA_RENDER_PRINTER_PRETTY_HPP

#include <cstring>
#include "../../../lib/glay/src/include.hpp"
#include "../../storage/config.hpp"
#include "../printer.hpp"

namespace	Tesca
{
	namespace	Render
	{
		class	PrettyPrinter : public Printer
		{
			public:
				PrettyPrinter (const PrettyPrinter&);
				PrettyPrinter (const Storage::Config&);

				PrettyPrinter&	operator = (const PrettyPrinter&);

				virtual void	print (Glay::Pipe::OStream&, const Arithmetic::Table&);

			private:
				Glay::Int32u	align;
				Glay::Int32u	pad;
		};
	}
}

#endif
