
#ifndef __TESCA_STREAM_READER_LINE_CSV_HPP
#define __TESCA_STREAM_READER_LINE_CSV_HPP

#include <cstdlib>
#include <functional>
#include <map>
#include "../../row/array.hpp"
#include "../../lookup.hpp"
#include "../line.hpp"

namespace	Tesca
{
	namespace	Stream
	{
		class	CSVLineReader : public LineReader
		{
			public:
				CSVLineReader (const CSVLineReader&);
				CSVLineReader (Glay::Pipe::IStream*, const Lookup&, const Config&);

				CSVLineReader&	operator = (const CSVLineReader&);

				virtual const Row&	current () const;

			protected:
				virtual void	parse (const char*, Glay::Int32u);

			private:
				typedef std::function<void (Glay::Int32u, const char*, Glay::Int32u)>	Callback;
				typedef std::map<Glay::Int32u, Glay::Int32u>							Mapping;

				virtual void	split (const char*, Glay::Int32u, Callback);

				Mapping		mapping;
				ArrayRow	row;
				char*		splits;


		};
	}
}

#endif
