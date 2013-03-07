
#ifndef __TESCA_PROVISION_READER_HPP
#define __TESCA_PROVISION_READER_HPP

#include <map>
#include "../glay/glay.hpp"
#include "row.hpp"

namespace	Tesca
{
	namespace	Provision
	{
		class	Reader
		{
			public:
				typedef Glay::Design::Event<const std::string&>	ErrorEvent;

						Reader (const Reader&);
						Reader ();
				virtual	~Reader ();

				Reader&	operator = (const Reader&);

				const ErrorEvent&	getError () const;
				ErrorEvent&			getError ();

				virtual const Row&	current () const = 0;
				virtual bool		next () = 0;

			protected:
				ErrorEvent	error;
		};
	}
}

#endif
