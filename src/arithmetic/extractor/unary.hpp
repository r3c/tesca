
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
				typedef std::function<Storage::Variant (Storage::Variant const&)> Callback;

				UnaryExtractor (Extractor const*, const std::string&, Callback);

				virtual std::string createName (Glay::Int32u) const;

				virtual Storage::Variant collect (Aggregator const* const*) const;
				virtual Storage::Variant extract (Provision::Row const&) const;

			protected:
				virtual void recurse (RecurseCallback) const;

			private:
				Callback callback;
				Extractor const* operand;
				std::string prefix;
		};
	}
}

#endif
