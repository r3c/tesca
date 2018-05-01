
#ifndef __TESCA_PROVISION_READER_LINE_JSON_HPP
#define __TESCA_PROVISION_READER_LINE_JSON_HPP

#include <cstdlib>
#include <functional>
#include <map>
#include <string>
#include "../../../storage/config.hpp"
#include "../../row/array.hpp"
#include "../../lookup.hpp"
#include "../line.hpp"

namespace Tesca
{
	namespace Provision
	{
		class JSONLineReader : public LineReader
		{
			public:
				JSONLineReader (JSONLineReader const&);
				JSONLineReader (Glay::Pipe::SeekIStream*, Lookup const&, Storage::Config const&);

				JSONLineReader& operator = (JSONLineReader const&);

				virtual Row const& current () const;

			protected:
				virtual bool parse (const char*, Glay::Size);

			private:
				struct Cursor
				{
					const char* buffer;
					Glay::Size length;
				};

				typedef std::function<void (Glay::Int32u, const char*, Glay::Size)> Callback;

				bool readCharacter (Cursor*, char);
				bool readValue (Cursor*);

				Lookup lookup;
				char member;
				ArrayRow row;
		};
	}
}

#endif
