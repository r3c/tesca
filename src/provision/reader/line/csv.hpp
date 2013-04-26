
#ifndef __TESCA_PROVISION_READER_LINE_CSV_HPP
#define __TESCA_PROVISION_READER_LINE_CSV_HPP

#include <cstdlib>
#include <functional>
#include <vector>
#include "../../../storage/config.hpp"
#include "../../row/array.hpp"
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
				CSVLineReader (Glay::Pipe::IStream*, const Lookup&, const Storage::Config&);

				CSVLineReader&	operator = (const CSVLineReader&);

				virtual const Row&	current () const;

			protected:
				virtual bool	parse (const char*, Glay::Int32u);

			private:
				typedef std::function<void (Glay::Int32u, const char*, Glay::Int32u)>	Callback;
				typedef std::vector<Glay::Int32u>										Mapping;

				void	split (const char*, Glay::Int32u, Callback);

				Mapping		mapping;
				ArrayRow	row;
				char*		types;
		};
	}
}

#endif
