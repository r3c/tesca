
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_VOID_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_VOID_HPP

#include <string>
#include "../extractor.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class VoidExtractor : public Extractor
		{
			public:
				static const VoidExtractor instance;

				virtual std::string createName (Glay::Int32u) const;

				virtual Glay::Int32u getFlags () const;

				virtual Storage::Variant collect (Aggregator const* const* const) const;
				virtual Storage::Variant extract (const Provision::Row&) const;
		};
	}
}

#endif
