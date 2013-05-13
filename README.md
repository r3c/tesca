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

	./tesca -e '#0, sum(#1), avg(#2)' results.csv

Output looks like this:

	#0      #1      #2
	Dendrob 30000   26.3
	Physali 90000   27.25
	Zephyra 220000  43

Input text files should contain structured data, one row per line, and use a
supported format (currently only CSV and JSON, then anything that can be
matched through regular expressions as soon as MinGW/GCC has a decent support
for new C++11 &lt;regex&gt; header). Then you have to describe what kind of
data contains each row and how result must be computed from those data.

Installation
------------

Grab a C++ compiler compatible with basic C++11 features (mainly lambda
expressions) such as GCC, update the Makefile.conf if needed and run make.

Build only tested on Windows (should work on any system with a C++11-compliant
GCC though, just remove the "-lwinmm" parameter from LDFLAGS variable in
Makefile.conf).

Usage
-----

Run Tesca on a text stream by either specifying files as command line arguments
or using stdin. Use following options to control how stream is read and what is
computed from its rows:

### Calculator expression (-e &lt;expression&gt;):

List of values that must be calculated from input stream, as a list of
sub-expressions separated by commas (example: ``#0, avg(#1), sum(#2) / 5``).
Result is automatically grouped by values obtained from expressions that do not
contain any aggregation function (like the first sub-expression in previous
example).

Sub-expressions can contains:

  * Field references (example: ``#0``, ``row.key`` ; see 'input stream format'
  section to know what to use as field names depending on input format).
  * Scalar functions (example: ``max(field, 5)``, ``len("Hello, World!")``).
  * Aggregation functions (example: ``avg(field)``, ``sum(value)``).
  * Common mathematical operators (example: ``field * 2``, ``value + 1``).
  * Boolean constants (example: ``true``, ``false``).
  * Numeric constants (example: ``1``, ``42.17``).
  * String constants (example: ``"Hello, World!"``).
  * Void constant (example: ``void``).

Available mathematical operators are (sorted by decreasing precedence):

  * Unary operators ``+n``, ``-n``, ``!n`` (logical 'not n')
  * Binary operators ``a * b``, ``a / b``, ``a % b`` (modulo)
  * Binary operators ``a + b``, ``a - b``
  * Comparison operators ``a < b``, ``a <= b``, ``a = b``, ``a >= b``,
  ``a > b``, ``a != b`` (different)
  * Logical operators ``a & b`` (logical 'a and b'), ``a | b`` (logical 'a or
  b')

Available scalar functions are:

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

Available aggregation functions are:

  * ``avg(n)``: computes average of expression ``n`` results.
  * ``count()``: counts number of aggregated rows.
  * ``first(n)``: keeps only first value of expression ``n`` results.
  * ``last(n)``: keeps only last value of expression ``n`` results.
  * ``max(n)``: keeps the highest value of expression ``n`` results.
  * ``min(n)``: keeps the lowest value of expression ``n`` results.
  * ``sum(n)``: computes sum of expression ``n`` results.
  * ``var(n)``: computes variance of expression ``n`` results.

Sub-expressions can be named (otherwise their automatic names are ``#0``,
``#1`` and so on) by appending ``: name`` after it (example: ``sum(#0):
scores_sum``). Valid characters in names are letters, digits, '#', '_' and '.'.

### Filter condition (-f &lt;condition&gt;):

Apply a filter on each row and use it only if filter is true (see description
of ``if`` scalar function for details). Syntax for filters is the same than the
one used for sub-expressions.

### Input stream format (-i &lt;format&gt;):

Defines how values are extracted from each line of input file. Formats can be
cutomized by specifying options after the format name like this:
``format:option1=value1;option2=value2``. Valid values for input stream format
are:

  * ``-i csv`` (default value): read lines as comma-separated values, fields
  can be referred to as ``#0``, ``#1``, ``#2`` and so on in expression (unless
  you use the 'headers' option).
    * use option 'headers' without argument to use first line as a header, its
    values will be used to define field names (example: ``-i 'csv:headers'``).
    * use option 'headers' with comma-separated arguments to define fixed field
    names (example: ``-i 'csv:headers=first,second,third'``).
    * use option 'splits' to change separator character (example:
    ``-i 'csv:splits=|'``).
  * ``-i json``: read lines as JSON objects, fields can be referred to as
  ``row.key`` where ``key`` is a key in JSON object.
    * use option 'member' to change the character used to select a member from
    a sub-object (example: ``-i 'json:member=/'``), default is '.' (dot).
    * use option 'root' to change the name of root JSON object (example: ``-i
    'json:root=line'``), default is 'row'.

### Output stream format (-o &lt;format&gt;):

Defines how result is printed to standard output. Valid values for output
stream format are:

  * ``-o csv``: render result as comma-separated values.
    * use option 'headers' to print headers before result values (example: ``-o
    'csv:headers'``).
  * ``-o name``: render result as name-value pairs.
  * ``-o pretty`` (default value): render result as a pretty-printed table.

### Examples:

  * ``./tesca -i 'csv' -e '#0: name, sum(#1): score, avg(#1): average_score'
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
