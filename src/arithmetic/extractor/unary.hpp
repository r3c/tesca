
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_UNARY_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_UNARY_HPP

#include <string>
#include "../extractor.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class UnaryExtractor : public Extractor
		{
			public:
				UnaryExtractor (const Extractor*, const std::string&);

				virtual std::string createName (Glay::Int32u) const;

				virtual Storage::Variant compute (const Aggregator* const*) const;
				virtual Storage::Variant extract (const Provision::Row&) const;

			protected:
				virtual Storage::Variant evaluate (const Storage::Variant&) const = 0;
				virtual void recurse (RecurseCallback) const;

			private:
				const Extractor* operand;
				std::string prefix;
		};
	}
}

#endif
