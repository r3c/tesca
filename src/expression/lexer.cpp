
#include "lexer.hpp"

#include <cstring>

using namespace std;
using namespace Glay;

namespace Tesca
{
	namespace Expression
	{
		Lexer::Lexer (const char* input) :
			eof (false),
			index (0),
			lexemType (UNKNOWN),
			reader (stream),
			stream (input, strlen (input))
		{
			this->read ();
			this->next ();
		}

		Size Lexer::getIndex () const
		{
			return this->index;
		}

		const string& Lexer::getLexemText () const
		{
			return this->lexemText;
		}

		Lexer::LexemType Lexer::getLexemType () const
		{
			return this->lexemType;
		}

		bool Lexer::next ()
		{
			stringstream buffer;

			if (this->eof)
			{
				this->lexemType = END;

				return false;
			}

			while (this->character <= ' ')
			{
				if (!this->read ())
				{
					this->lexemType = END;

					return false;
				}
			}

			// Scan identifier
			if ((this->character >= 'A' && this->character <= 'Z') ||
			    (this->character >= 'a' && this->character <= 'z') ||
			    (this->character == '_') ||
				(this->character == '\\'))
			{
				do
				{
					if (this->character == '\\')
					{
						if (!this->read ())
							return false;
					}
					else if ((this->character < '0' || this->character > '9') &&
				             (this->character < 'A' || this->character > 'Z') &&
				             (this->character < 'a' || this->character > 'z') &&
				             (this->character != '.') &&
				             (this->character != '_'))
						break;

					buffer.put (this->character);
				}
				while (this->read ());

				this->lexemText = buffer.str ();
				this->lexemType = IDENTIFIER;

				return true;
			}

			// Scan number
			if ((this->character >= '0' && this->character <= '9') ||
			    (this->character == '.'))
			{
				buffer.put (this->character);

				while ((this->read ()) &&
				       ((this->character >= '0' && this->character <= '9') ||
				        (this->character == '.')))
					buffer.put (this->character);

				this->lexemText = buffer.str ();
				this->lexemType = NUMBER;

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

				this->lexemText = buffer.str ();
				this->lexemType = STRING;

				return true;
			}

			// Scan operator
			switch (this->character)
			{
				case '&':
					this->read ();
					this->lexemType = AMPERSAND;

					break;

				case ',':
					this->read ();
					this->lexemType = COMMA;

					break;

				case '!':
					if (this->read () && this->character == '=')
					{
						this->read ();
						this->lexemType = DIFFERENT;
					}
					else
						this->lexemType = NOT;

					break;

				case '/':
					this->read ();
					this->lexemType = DIVIDE;

					break;

				case '=':
					this->read ();
					this->lexemType = EQUAL;

					break;

				case '>':
					if (this->read () && this->character == '=')
					{
						this->read ();
						this->lexemType = GREATER_EQUAL;
					}
					else
						this->lexemType = GREATER_THAN;

					break;

				case '<':
					if (this->read () && this->character == '=')
					{
						this->read ();
						this->lexemType = LOWER_EQUAL;
					}
					else
						this->lexemType = LOWER_THAN;

					break;

				case '-':
					this->read ();
					this->lexemType = MINUS;

					break;

				case '%':
					this->read ();
					this->lexemType = MODULO;

					break;

				case '*':
					this->read ();
					this->lexemType = MULTIPLY;

					break;

				case ':':
					this->read ();
					this->lexemType = NAME;

					break;

				case '(':
					this->read ();
					this->lexemType = PARENTHESIS_BEGIN;

					break;

				case ')':
					this->read ();
					this->lexemType = PARENTHESIS_END;

					break;

				case '|':
					this->read ();
					this->lexemType = PIPE;

					break;

				case '+':
					this->read ();
					this->lexemType = PLUS;

					break;

				default:
					this->lexemType = UNKNOWN;

					return false;
			}

			return true;
		}

		bool Lexer::read ()
		{
			if (reader.readType (&this->character))
			{
				++this->index;

				return true;
			}

			this->eof = true;

			return false;
		}
	}
}
