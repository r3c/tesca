
#ifndef __TESCA_PROVISION_READER_LINE_CSV_HPP
#define __TESCA_PROVISION_READER_LINE_CSV_HPP

#include <cstdlib>
#include <functional>
#include <map>
#include "../../row/array.hpp"
#include "../../config.hpp"
#include "../../lookup.hpp"
#include "../line.hpp"

namespace	Tesca
{
	namespace	Provision
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

				void	split (const char*, Glay::Int32u, Callback);

				Mapping		mapping;
				ArrayRow	row;
				char*		types;
		};
	}
}

#endif
