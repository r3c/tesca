
#ifndef __TESCA_READER_LINE_HPP
#define __TESCA_READER_LINE_HPP

#include <sstream>
#include <string>
#include "../../glay/glay.hpp"
#include "../reader.hpp"

namespace	Tesca
{
	class	LineReader : public Reader
	{
		public:
			LineReader (const LineReader&);
			LineReader (Glay::Pipe::IStream*);

			LineReader&	operator = (const LineReader&);

			virtual bool	next ();

		protected:
			virtual void	parse (const std::string&) = 0;
			bool			read (std::stringstream&);

		private:
			char					current;
			Glay::Pipe::IStream&	input;
			bool					set;


	};
}

#endif
