Tesca README file
=================

Overview
--------

Tesca (TExt Stream CAlculator) is a small utility intended to compute simple
aggregations (sums, averages, etc) on big (gigabytes or more) text files using
a simple query syntax. Using this sample CSV file containing scores and
completion times for several players:

	Zephyra,100000,59.5
	Physali,80000,41.9
	Zephyra,50000,32.1
	Zephyra,70000,37.4
	Dendrob,30000,26.3
	Physali,10000,12.6

You can get the total score and average time by player using this command:

	./tesca -e '$0, sum($1), avg($2)' results.csv

So output looks like this:

	[0]     [1]     [2]
	Dendrob 30000   26.3
	Physali 90000   27.25
	Zephyra 220000  43

Input text files should contain structured data, one row per line, and use a
supported format (currently only CSV and JSON, and as soon as MinGW/GCC has a
decent support for new C++11 &lt;regex&gt; header anything that can be matched
through regular expressions). Once your input is defined you have to describe
what kind of data contains each row and what do you want to compute from it.

Installation
------------

Grab a C++ compiler compatible with basic C++11 features (mainly lambda
expressions) such as GCC, update the Makefile.conf if needed and run make.

Build has been only tested on Windows using MinGW. It should work on any system
with a C++11-compliant GCC though, just remove the "-lwinmm" parameter from
LDFLAGS variable in Makefile.conf.

Usage
-----

Run Tesca on a text stream by either specifying files as command line arguments
or using stdin. Use following options to control how stream is read and what is
computed from its rows:

### Input stream format (-i &lt;format&gt;):

Defines how values are extracted from each line of input file and which name
should be used to access them in expressions. Formats can be cutomized by
specifying options after the format name like this:
``-i 'format:option1=value1;option2=value2'``. Valid values for input stream
format are:

  * ``-i csv`` (default value): read lines as comma-separated values, default
  field names are ``$0``, ``$1``, ``$2`` and so on in expression unless
  you use the 'headers' option.
    * use option 'headers' without argument to use first line as header
	definition: field names will be defined from its value instead of default
	names (example: ``-i 'csv:headers'``).
    * use option 'headers' with comma-separated arguments to define fixed field
    names (example: ``-i 'csv:headers=first,second,third'`` to name the three
    first columns of your file ``$first``, ``$second`` and ``$third``).
    * use option 'splits' to replace default separator character ',' (comma)
    by any characters list you want (example: ``-i 'csv:splits=|_'`` to split
    on pipe and underscore characters).
    * use option 'quotes' to replace default escaping character '"' (double
    quote) by any characters list you want (example: ``-i 'csv:quotes=`'`` to
    use backquote as an escape character).
  * ``-i json``: read lines as JSON objects, fields can be referred to as
  ``$row.key`` where ``key`` is a key in JSON object (example: to read values
  from JSON object ``{"first": 1, "second": [2], "third": {"x": true, "y":
  false}}`` you can use ``$row.first``, ``$row.second.0``, ``$row.third.x`` and
  ``$row.third.y`` in your expressions).
    * use option 'member' to replace default character '.' (dot) used to
    select a member from an object or array by any valid column name character
    (see "Calculator expression" section for details, example: ``-i
    'json:member=_'`` to use underscore as a member selector).
    * use option 'root' to replace default name of top-level JSON object 'row'
    by any name you want (example: ``-i 'json:root=line'`` to use 'line' as
    the name of the root JSON element).

### Calculator expression (-e &lt;expression&gt;):

List of values that must be calculated from input stream, as a list of
column definitions separated by commas (example: ``slice($0, 0, 10), avg($1) +
1, sum($2)``). As you can notice, column definitions can mix constructions that
compute a result for each row (mathematical operators, row functions) and
instructions that aggregate a result from several combined rows (aggregation
functions).

Is previous example, ``avg(n)`` and ``sum(n)`` are aggregation functions. This
means they'll group all rows sharing the same value for other (non-aggregating)
columns, which in this case is the first column only, and compute an aggregated
result from them.

Note that you can aggregate a value computed from either mathematical operators
and/or row functions, but once you have an aggregated result you can't mix it
with row-level constructions as it would have no sense. This means
``avg(max($0, 5) + 2)`` is valid but ``sum($0) + $1`` is not.

Column definitions can contains:

  * Aggregation functions (example: ``avg($field)``, ``sum(53)``).
  * Mathematical operators (example: ``$field * 2``, ``17 + 1``).
  * Row functions (example: ``max($field, 5)``, ``len("Hello, World!")``).
  * Field references (example: ``$0``, ``$row.key`` ; see 'input stream format'
  section to know what to use as field names depending on input format).
  * Boolean constants (example: ``true``, ``false``).
  * Numeric constants (example: ``1``, ``42.17``).
  * String constants (example: ``"Hello, World!"``).
  * Void constant (example: ``void``).

Available aggregation functions are:

  * ``avg(n)``: computes average of ``n``.
  * ``count()``: counts number of aggregated rows.
  * ``first(n)``: keeps only first value of ``n``.
  * ``last(n)``: keeps only last value of ``n``.
  * ``max(n)``: keeps the highest value of ``n``.
  * ``min(n)``: keeps the lowest value of ``n``.
  * ``sum(n)``: computes sum of ``n``.
  * ``var(n)``: computes variance of ``n``.

Available mathematical operators are (sorted by decreasing precedence):

  * Parenthesis ``(``, ``)``
  * Unary operators ``+n``, ``-n``, ``!n`` (logical 'not n')
  * Binary operators ``a * b``, ``a / b``, ``a % b`` (modulo)
  * Binary operators ``a + b``, ``a - b``
  * Comparison operators ``a < b``, ``a <= b``, ``a = b``, ``a >= b``,
  ``a > b``, ``a != b`` (different)
  * Logical operators ``a & b`` (logical 'a and b'), ``a | b`` (logical 'a or
  b')

Available row functions are:

  * ``abs(x)``: returns absolute value of ``x``.
  * ``at(index, a, b[, c...])``: returns the n-th argument with n = ``index +
  2`` (this function returns ``a`` if ``index = 0``, ``b`` if ``index = 1``,
  etc.).
  * ``ceil(x)``: returns ``x`` rounded up to a whole number.
  * ``cmp(a, b)``: returns ``-1`` if ``a < b``, ``0`` if ``a = b``, 1 else.
  * ``find(str, search[, start])``: searches for string ``search`` in ``str``
  from offset ``start`` (or 0 if missing) and returns position of the first
  character if found, or ``void`` else.
  * ``floor(x)``: returns ``x`` rounded down to a whole number.
  * ``if(test, a[, b])``: returns ``a`` if ``test`` is true or equivalent
  (non-empty string or non-zero number), ``b`` else (or ``void`` if missing).
  * ``in(search, a, b, [, c...])``: returns ``true`` if ``search`` is equal to
  ``a``, ``b``, ``c`` or any following value, or ``false`` else.
  * ``lcase(str)``: returns lowercase conversion of string ``str``.
  * ``len(str)``: returns number of characters in string ``str``.
  * ``max(a, b, [, c...])``: returns highest value among ``a``, ``b``, ``c``
  and following.
  * ``min(a, b, [, c...])``: returns lowest value among ``a``, ``b``, ``c`` and
  following.
  * ``pow(base, exponent)``: returns ``base`` to the power of ``exponent``.
  * ``round(x)``: returns ``x`` rounded to the nearest integral value.
  * ``slice(str, start, [, length])``: returns up to ``length`` characters (or
  all remaining characters if ``length`` is missing) from string ``str``,
  starting at index ``start`` (use a negative ``start`` index to start at the
  ``len(str) + start``-th character).
  * ``ucase(str)``: returns uppercase conversion of string ``str``.

Column definitions can also declare a name (otherwise their automatic names are
``$0``, ``$1`` and so on) by appending ``: name`` after it (example: ``sum($$):
scores_sum``). Valid characters in names are letters, digits, '_' and '.'.

Note that their are two ``max`` and two ``min`` functions: an aggregation
function and a row function for each. They differ by the number of arguments
they expect, as the aggregation variants require one argument where the row
ones require at least 2 arguments. Don't confuse one with the other as they
have very different behaviors.

### Filter condition (-f &lt;condition&gt;):

Apply a filter on each row and use it only if filter is true (see description
of ``if`` scalar function for details). Syntax for filters is the same than the
one used for column definitions (example: ``-f '$0 >= 0 & $0 < 8'``).

### Output stream format (-o &lt;format&gt;):

Defines how result is printed to standard output. Valid values for output
stream format are:

  * ``-o pretty`` (default value): render result as a pretty-printed table.
    * use option 'margin' to define width in character of the minimum margin
    between two columns (example: ``-o 'pretty:margin=8'``), default is 4.
    * use option 'pad' to define width in character of the  padding after
    each column (example: ``-o 'pretty:pad=2'``), default is 1.
  * ``-o csv``: render result as comma-separated values.
    * use option 'headers' to print headers before result values (example: ``-o
    'csv:headers'``).
    * use option 'split' to replace default separator character ',' (comma)
    by any character you want (example: ``-o 'csv:split=_'`` to split fields
    using an underscore character).
    * use option 'quote' to replace default escaping character '"' (double
    quote) by any character you want (example: ``-o 'csv:quote=`'`` to use
    backquote character as an escaping character).
  * ``-o name``: render result as name-value pairs.

### Examples:

  * ``./tesca -i 'csv' -e '$0: name, sum($1): score, avg($1): average_score'
  file.csv``
  * ``./tesca -i 'csv:headers=x,y' -e 'x, y, if(x > y * 2, x, y)' points.csv``
  * ``cat bench.json | ./tesca -i 'json' -e 'row.id: identifier, avg(row.time):
  time'``

Licence
-------

This project is open-source, released under BSD licence. See "LICENSE" file for
more information. Any contribution would be of course highly welcomed!

Author
------

Rémi Caput (github [at] mirari [dot] fr)
http://remi.caput.fr/
