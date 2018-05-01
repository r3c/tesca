
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_BINARY_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_BINARY_HPP

#include <functional>
#include <string>
#include "../extractor.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class BinaryExtractor : public Extractor
		{
			public:
				typedef std::function<Storage::Variant (Storage::Variant const&, Storage::Variant const&)> Callback;

				BinaryExtractor (Extractor const*, Extractor const*, const std::string&, Callback);

				virtual std::string createName (Glay::Int32u) const;

				virtual Storage::Variant collect (Aggregator const* const*) const;
				virtual Storage::Variant extract (Provision::Row const&) const;

			protected:
				virtual void recurse (RecurseCallback) const;

			private:
				Callback callback;
				std::string infix;
				Extractor const* lhs;
				Extractor const* rhs;
		};
	}
}

#endif
