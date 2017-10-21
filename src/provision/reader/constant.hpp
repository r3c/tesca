
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
				ConstantReader (const ConstantReader&);
				ConstantReader (const Lookup&, Glay::Int32u);

				ConstantReader& operator = (const ConstantReader&);

				bool assign (const std::string&, const Storage::Variant&);
				virtual const Row& current () const;
				virtual bool next ();

			private:
				Glay::Int32u count;
				Lookup lookup;
				ArrayRow row;
		};
	}
}

#endif
