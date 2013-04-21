
#ifndef __TESCA_PROVISION_READER_LINE_JSON_HPP
#define __TESCA_PROVISION_READER_LINE_JSON_HPP

#include <cstdlib>
#include <functional>
#include <map>
#include <sstream>
#include "../../../storage/config.hpp"
#include "../../row/array.hpp"
#include "../../lookup.hpp"
#include "../line.hpp"

namespace	Tesca
{
	namespace	Provision
	{
		class	JSONLineReader : public LineReader
		{
			public:
				JSONLineReader (const JSONLineReader&);
				JSONLineReader (Glay::Pipe::IStream*, const Lookup&, const Storage::Config&);

				JSONLineReader&	operator = (const JSONLineReader&);

				virtual const Row&	current () const;

			protected:
				virtual bool	parse (const char*, Glay::Int32u);

			private:
				struct	Cursor
				{
					const char*		buffer;
					Glay::Int32u	length;
				};

				typedef std::function<void (Glay::Int32u, const char*, Glay::Int32u)>	Callback;

				bool	readCharacter (Cursor*, char);
				bool	readValue (Cursor*, std::stringstream&);

				Lookup				lookup;
				std::stringstream	prefix;
				std::string			root;				
				ArrayRow			row;
		};
	}
}

#endif
