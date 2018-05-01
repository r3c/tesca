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

	./tesca '_0, sum(_1), avg(_2)' results.csv

Output looks like this:

	[_0]    [sum__1] [avg__2]
	Dendrob 30000    26.3
	Physali 90000    27.25
	Zephyra 220000   43

Input text files should contain structured data, one row per line, and use a
supported format (currently only CSV and JSON). Then you have to define four
things:

  * What is the data format in input file (default is CSV) ;
  * What rows should be filtered from input data (no filtering by default) ;
  * What should be computed from these data ;
  * How result should be printed (default is a human-readable format).

See the "Usage" section below for more information about these steps.

Installation
------------

Use a C++ compiler compatible with C++17 features such as Clang or GCC and
run `make`. You may have to tweak a few options in `Makefile.conf` if you're
using a different setup than the one I used (Cygwin & GCC).

Usage
-----

Run Tesca on a text stream by either specifying files as command line arguments
(``./tesca 'expr' input.csv``) or from stdin when no file is specified
(``some_program | ./tesca expr``). Use following options to control how stream
is read and what is computed from its rows:

### Calculator expression:

The only mandatory parameter for Tesca is a comma-separated list of column
definitions which define what should be calculated and/or aggregated from
input data. Each column definition is a single row-level mathematical
expression that either produces a result for each row, or compute an
aggregated value over multiple rows. Here is a simple example of calulator
expression:

    name, slice(hash, 0, 10), avg(value), sum(value) + 1

In this example four columns are defined, and the last two use the ``avg``
(average) and ``sum`` (sum of values) aggregation functions. This will make
Tesca compute the average and sum incremented by one for all rows that share
the same value for all other columns ; in other words it will compute an
average and a sum for each distinct couple of ``name`` and first 10 characters
of ``hash`` values (using the ``slice`` function) from input.

Note that you can aggregate a value computed from a row-level sub-expression,
but you cannot mix result of an aggregation function with other row-level
constructions. This means ``avg(max(_0, 5) + 2)`` is a valid column definition
but valid but ``sum(_0) + _1`` is not: Tesca streams data in one pass and
cannot compute the sum of some value for all rows and the value of a specific
row.

As you can notice in previous examples, expression can contain field names to
access their values each input row. Only alphanumeric characters, '.' and '_'
can be used as is in field names, other characters must be escaped with a
backslash character, e.g. ``my\-field``). Field names depend on the input
format (and parameters) you used, see the "Input stream format" section for
details.

Column definitions can contains:

  * Aggregation functions (example: ``avg(score)``, ``sum(53)``).
  * Mathematical operators (example: ``power * 2``, ``17 + 1``).
  * Row-level functions (example: ``max(cost, 5)``, ``len("Hello, World!")``).
  * Field references (example: ``_0``, ``row.key``).
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
  * ``case(x, v1, r1[, v2, r2, ...][, f])``: returns ``r1`` if ``x = v1``,
  ``r2`` if ``x = v2`` and same for every pair specified in arguments, or
  ``f`` if ``x`` was not equal to any ``vN``, or ``void`` if no ``f`` value was
    specified.
  * ``ceil(x)``: returns ``x`` rounded up to a whole number.
  * ``cmp(a, b)``: returns ``-1`` if ``a < b``, ``0`` if ``a = b``, 1 else.
  * ``default(a[, b])``: return ``a`` if ``a`` is true of equivalent (non-empty
    string or non-zero number), ``b`` else (or ``void`` if missing).
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
  * ``log(a)``: returns the natural logarithm of ``a``.
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
  * ``type(x)``: returns type of ``x`` as a string, can be either "boolean",
    "number", "string" or "none".
  * ``ucase(str)``: returns uppercase conversion of string ``str``.

Column definitions can also declare a name by using the naming operator ``:``
after your definition, followed by a variable used as column name (example:
``sum(_0): total_score``). Columns that don't define a name will be assigned
one automatically.

Note that their are two ``max`` and two ``min`` functions: an aggregation
function and a row function for each. They differ by the number of arguments
they expect, as the aggregation variants require one argument where the row
ones require at least 2 arguments. Don't confuse one with the other as they
have very different behaviors.

### Filter condition (-f &lt;condition&gt;):

Apply a filter on each row and use it only if filter is true (see description
of ``if`` scalar function for details). Syntax for filters is the same than the
one used for column definitions (example: ``-f '_0 >= 0 & _0 < 8'``).

### Input stream format (-i &lt;format&gt;):

Defines how values are extracted from each line of input file and which name
should be used to access them in expressions. Formats can be cutomized by
specifying options after the format name like this:
``-i 'format:option1=value1:option2=value2'``. Valid values for input stream
format are:

  * ``-i csv`` (default value): read lines as comma-separated values, default
  field names are ``_0``, ``_1``, ``_2`` and so on in expression unless
  you use the 'headers' option.
    * use option 'headers' without associated value to use first line as header
	definition: field names will be defined from its value instead of default
	names (example: ``-i 'csv:headers'``).
    * use option 'headers' with comma-separated arguments to define fixed field
    names (example: ``-i 'csv:headers=first,second,third'`` to name the three
    first columns of your file ``first``, ``second`` and ``third``).
    * use option 'splits' to replace default separator character ',' (comma)
    by any characters list you want (example: ``-i 'csv:splits=|_'`` to split
    on pipe and underscore characters).
    * use option 'quotes' to replace default escaping character '"' (double
    quote) by any characters list you want (example: ``-i 'csv:quotes=`'`` to
    use backquote as an escape character).
  * ``-i json``: read lines as JSON objects, fields can be referred to as
  ``row.key`` where ``key`` is a key in JSON object (example: to read values
  from JSON object ``{"first": 1, "second": [2], "third": {"x": true, "y":
  false}}`` you can use ``row.first``, ``row.second.0``, ``row.third.x`` and
  ``row.third.y`` in your expressions).
    * use option 'member' to replace default character '.' (dot) used to
    select a member from an object or array by any valid column name character
    (see "Calculator expression" section for details, example: ``-i
    'json:member=_'`` to use underscore as a member selector).
    * use option 'root' to replace default name of top-level JSON object 'row'
    by any name you want (example: ``-i 'json:root=line'`` to use 'line' as
    the name of the root JSON element).

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

  * ``./tesca -i 'csv' '_0: name, sum(_1): score, avg(_1): average_score'
  file.csv``
  * ``./tesca -i 'csv:headers=x,y' 'x, y, if(x > y * 2, x, y)' points.csv``
  * ``cat bench.json | ./tesca -i 'json' 'row.id: identifier, avg(row.time):
  time'``

Licence
-------

This project is open-source, released under MIT licence. See "LICENSE.md" file
for more information. Any contribution would be of course highly welcomed!

Author
------

Rémi Caput (github [at] mirari [dot] fr)
http://remi.caput.fr/
