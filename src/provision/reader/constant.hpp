
#ifndef __TESCA_PROVISION_READER_CONSTANT_HPP
#define __TESCA_PROVISION_READER_CONSTANT_HPP

#include <string>
#include "../row/array.hpp"
#include "../lookup.hpp"
#include "../reader.hpp"

namespace Tesca
{
	namespace Provision
	{
		class ConstantReader : public Reader
		{
			public:
				ConstantReader (ConstantReader const&);
				ConstantReader (Lookup const&, Glay::Int32u);

				ConstantReader& operator = (ConstantReader const&);

				bool assign (const std::string&, Storage::Variant const&);
				virtual Row const& current () const;
				virtual bool next ();

			private:
				Glay::Int32u count;
				Lookup lookup;
				ArrayRow row;
		};
	}
}

#endif
