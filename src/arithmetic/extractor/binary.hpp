
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
				typedef std::function<Storage::Variant (const Storage::Variant&, const Storage::Variant&)> Callback;

				BinaryExtractor (const Extractor*, const Extractor*, const std::string&, Callback);

				virtual std::string createName (Glay::Int32u) const;

				virtual Storage::Variant compute (const Aggregator* const*) const;
				virtual Storage::Variant extract (const Provision::Row&) const;

			protected:
				virtual void recurse (RecurseCallback) const;

			private:
				Callback callback;
				std::string infix;
				const Extractor* lhs;
				const Extractor* rhs;
		};
	}
}

#endif
