
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
				typedef std::function<Storage::Variant (const Storage::Variant&)> Callback;

				UnaryExtractor (const Extractor*, const std::string&, Callback);

				virtual std::string createName (Glay::Int32u) const;

				virtual Storage::Variant collect (Aggregator const* const* const) const;
				virtual Storage::Variant extract (const Provision::Row&) const;

			protected:
				virtual void recurse (RecurseCallback) const;

			private:
				Callback callback;
				const Extractor* operand;
				std::string prefix;
		};
	}
}

#endif
