
#ifndef __TESCA_STREAM_READER_LINE_CSV_HPP
#define __TESCA_STREAM_READER_LINE_CSV_HPP

#include <functional>
#include <map>
#include "../../row/array.hpp"
#include "../line.hpp"

namespace	Tesca
{
	class	CSVLineReader : public LineReader
	{
		public:
			CSVLineReader (const CSVLineReader&);
			CSVLineReader (Glay::Pipe::IStream*, const Fields*, bool, char);

			CSVLineReader&	operator = (const CSVLineReader&);

			virtual const Row&	current () const;

		protected:
			virtual void	parse (const char*, Glay::Int32u);

		private:
			typedef std::function<void (Glay::Int32u, const char*, Glay::Int32u)>	Callback;
			typedef std::map<Glay::Int32u, Glay::Int32u>							Lookup;

			virtual void	split (const char*, Glay::Int32u, Callback);

			Lookup		lookup;
			ArrayRow	row;
			char		separator;


	};
}

#endif
