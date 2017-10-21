
#include "lookup.hpp"

using namespace std;
using namespace Glay;

namespace Tesca
{
	namespace Provision
	{
		Lookup::State::State () :
			defined (false),
			value (0)
		{
		}

		bool Lookup::State::fetch (Int32u* value) const
		{
			*value = this->value;

			return this->defined;
		}

		bool Lookup::State::next (char character, const Lookup::State** out) const
		{
			auto i = this->branches.find (character);

			if (i == this->branches.end ())
				return false;

			*out = &i->second;

			return true;
		}

		void Lookup::State::set (const string& key, Int32u index, Int32u value)
		{
			if (index >= key.length ())
			{
				this->defined = true;
				this->value = value;

				return;
			}

			this->branches[key[index]].set (key, index + 1, value);
		}

		Lookup::Lookup (const Lookup& other) :
			initial (other.initial),
			keys (other.keys),
			states (other.states)
		{
			this->current = &this->initial;
		}

		Lookup::Lookup ()
		{
			this->current = &this->initial;
		}

		Lookup::const_iterator Lookup::begin () const
		{
			return this->keys.begin ();
		}

		Lookup::const_iterator Lookup::end () const
		{
			return this->keys.end ();
		}

		Int32u Lookup::count () const
		{
			return this->keys.size ();
		}

		bool Lookup::fetch (Int32u* field) const
		{
			return this->current && this->current->fetch (field);
		}

		bool Lookup::find (const string& key, Int32u* field) const
		{
			const char* character;
			const State* current;
			Int32u length;

			character = key.data ();
			current = &this->initial;

			for (length = key.length (); length > 0; --length)
			{
				if (!current->next (*character, &current))
					return false;

				++character;
			}

			return current->fetch (field);
		}

		void Lookup::enter ()
		{
			this->states.push (this->current);
		}

		void Lookup::leave ()
		{
			this->current = this->states.top ();

			this->states.pop ();
		}

		void Lookup::next (char character)
		{
			if (this->current && !this->current->next (character, &this->current))
				this->current = 0;
		}

		Int32u Lookup::store (const string& key)
		{
			Int32u field;

			if (this->find (key, &field))
				return field;

			field = this->keys.size ();

			this->initial.set (key, 0, field);
			this->keys.push_back (key);

			return field;
		}
	}
}
