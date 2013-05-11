
#include "lexer.hpp"

using namespace std;
using namespace Glay;

namespace	Tesca
{
	namespace	Expression
	{
		Lexer::Lexer (const char* input) :
			eof (false),
			index (0),
			reader (stream),
			stream (input, strlen (input)),
			type (UNKNOWN)
		{
			this->read ();
			this->next ();
		}

		const string&	Lexer::getCurrent () const
		{
			return this->current;
		}

		Int32u	Lexer::getIndex () const
		{
			return this->index;
		}

		Lexer::Lexem	Lexer::getType () const
		{
			return this->type;
		}

		bool	Lexer::next ()
		{
			stringstream	buffer;

			if (this->eof)
			{
				this->type = END;

				return false;
			}

			while (this->character <= ' ')
			{
				if (!this->read ())
				{
					this->type = END;

					return false;
				}
			}

			// Scan identifier
			if ((this->character >= 'A' && this->character <= 'Z') ||
			    (this->character >= 'a' && this->character <= 'z') ||
			    (this->character == '#') ||
			    (this->character == '$') ||
			    (this->character == '%') ||
			    (this->character == '&') ||
			    (this->character == '_') ||
			    (this->character == '.'))
			{
				buffer.put (this->character);

				while ((this->read ()) &&
				       ((this->character >= '0' && this->character <= '9') ||
				        (this->character >= 'A' && this->character <= 'Z') ||
				        (this->character >= 'a' && this->character <= 'z') ||
				        (this->character == '#') ||
				        (this->character == '$') ||
				        (this->character == '%') ||
				        (this->character == '&') ||
				        (this->character == '_') ||
				        (this->character == '.')))
					buffer.put (this->character);

				this->current = buffer.str ();
				this->type = IDENTIFIER;

				return true;
			}

			// Scan number
			if (this->character >= '0' && this->character <= '9')
			{
				buffer.put (this->character);

				while ((this->read ()) &&
				       ((this->character >= '0' && this->character <= '9') ||
				        (this->character == '.')))
					buffer.put (this->character);

				this->current = buffer.str ();
				this->type = NUMBER;

				return true;
			}

			// Scan string
			if (this->character == '"')
			{
				if (!this->read ())
					return false;

				while (this->character != '"')
				{
					if (this->character == '\\' && !this->read ())
						return false;

					buffer.put (this->character);

					if (!this->read ())
						return false;
				}

				this->read ();

				this->current = buffer.str ();
				this->type = STRING;

				return true;
			}

			// Scan operator
			switch (this->character)
			{
				case '&':
					this->read ();
					this->type = AMPERSAND;

					break;

				case ':':
					this->read ();
					this->type = COLON;

					break;

				case ',':
					this->read ();
					this->type = COMMA;

					break;

				case '!':
					if (this->read () && this->character == '=')
					{
						this->read ();
						this->type = DIFFERENT;
					}
					else
						this->type = NOT;

					break;

				case '/':
					this->read ();
					this->type = DIVIDE;

					break;

				case '=':
					this->read ();
					this->type = EQUAL;

					break;

				case '>':
					if (this->read () && this->character == '=')
					{
						this->read ();
						this->type = GREATER_EQUAL;
					}
					else
						this->type = GREATER_THAN;

					break;

				case '<':
					if (this->read () && this->character == '=')
					{
						this->read ();
						this->type = LOWER_EQUAL;
					}
					else
						this->type = LOWER_THAN;

					break;

				case '-':
					this->read ();
					this->type = MINUS;

					break;

				case '%':
					this->read ();
					this->type = MODULO;

					break;

				case '*':
					this->read ();
					this->type = MULTIPLY;

					break;

				case '(':
					this->read ();
					this->type = PARENTHESIS_BEGIN;

					break;

				case ')':
					this->read ();
					this->type = PARENTHESIS_END;

					break;

				case '|':
					this->read ();
					this->type = PIPE;

					break;

				case '+':
					this->read ();
					this->type = PLUS;

					break;

				default:
					this->type = UNKNOWN;

					return false;
			}

			return true;
		}

		bool	Lexer::read ()
		{
			if (reader.read (&this->character))
			{
				++this->index;

				return true;
			}

			this->eof = true;

			return false;
		}
	}
}
