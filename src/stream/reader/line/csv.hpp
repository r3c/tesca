
#ifndef __TESCA_READER_LINE_CSV_HPP
#define __TESCA_READER_LINE_CSV_HPP

#include <functional>
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
			CSVLineReader (Glay::Pipe::IStream*, const Fields*, bool, char);

			CSVLineReader&	operator = (const CSVLineReader&);

			virtual const Row&	current () const;

		protected:
			virtual void	parse (const std::string&);

		private:
			typedef std::function<void (Glay::Int32u, const std::string&)>	Callback;
			typedef std::map<Glay::Int32u, Glay::Int32u>					Lookup;

			virtual void	split (const std::string&, const Callback&);

			Lookup		lookup;
			ArrayRow	row;
			char		separator;


	};
}

#endif
