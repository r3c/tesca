
#ifndef __TESCA_READER_LINE_CSV_HPP
#define __TESCA_READER_LINE_CSV_HPP

#include <map>
#include "../../row/array.hpp"
#include "../line.hpp"

namespace	Tesca
{
	class	CSVLineReader : public LineReader
	{
		public:
			typedef std::map<std::string, Glay::Int32u>	Fields;

			CSVLineReader (const CSVLineReader&);
			CSVLineReader (Glay::Pipe::IStream*, const Fields*, bool);

			CSVLineReader&	operator = (const CSVLineReader&);

			virtual const Row&	current () const;

		protected:
			virtual void	parse (const std::string&);

		private:
			typedef std::map<Glay::Int32u, Glay::Int32u>	Lookup;

			Lookup		lookup;
			ArrayRow	row;


	};
}

#endif
