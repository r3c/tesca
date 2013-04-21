
#ifndef __TESCA_PROVISION_READER_HPP
#define __TESCA_PROVISION_READER_HPP

#include "../../lib/glay/src/include.hpp"
#include "row.hpp"

namespace	Tesca
{
	namespace	Provision
	{
		class	Reader
		{
			public:
				typedef Glay::Design::Event<const std::string&>	Error;

						Reader (const Reader&);
						Reader ();
				virtual	~Reader ();

				Reader&	operator = (const Reader&);

				const Error&	getError () const;
				Error&			getError ();

				virtual const Row&	current () const = 0;
				virtual bool		next () = 0;

			protected:
				Error	error;
		};
	}
}

#endif
