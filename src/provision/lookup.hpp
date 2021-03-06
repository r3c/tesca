
#ifndef __TESCA_PROVISION_LOOKUP_HPP
#define __TESCA_PROVISION_LOOKUP_HPP

#include <map>
#include <stack>
#include <string>
#include <vector>
#include "../../lib/glay/src/glay.hpp"

namespace Tesca
{
	namespace Provision
	{
		class Lookup
		{
			public:
				typedef std::vector<std::string> Keys;
				typedef Keys::const_iterator const_iterator;

				Lookup (Lookup const&);
				Lookup ();

				Lookup& operator = (Lookup const&);

				const_iterator begin () const;
				const_iterator end () const;

				Glay::Int32u count () const;
				bool fetch (Glay::Int32u*) const;
				bool find (const std::string&, Glay::Int32u*) const;
				void enter ();
				void leave ();
				void next (char);
				Glay::Int32u store (const std::string&);

			private:
				class State
				{
					public:
						State ();

						bool fetch (Glay::Int32u*) const;
						bool next (char, State const**) const;
						void set (const std::string&, Glay::Int32u, Glay::Int32u);

					private:
						std::map<char, State> branches;
						bool defined;
						Glay::Int32u value;
				};

				State const* current;
				State initial;
				Keys keys;
				std::stack<State const*> states;
		};
	}
}

#endif
