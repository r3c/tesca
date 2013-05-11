Tesca README file
=================

Overview
--------

Tesca (TExt Stream CAlculator) is a small utility intended to compute simple
aggregations (sums, averages, etc) on big (gigabytes or more) text files using
a simple query syntax.

Text files should contain structured data, one row per line, and use a
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
Result is automatically grouped by values from expressions that do not contain
any aggregation function (like the first sub-expression in previous example).

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

Available scalar functions are:

  * FIXME

Available aggregation functions are:

  * FIXME

### Filter condition (-f &lt;condition&gt;):

Apply a filter on each row and use it only if filter returns a boolean "true"
value or equivalent.

### Input stream format (-i &lt;format&gt;):

Defines how values are extracted from each line of input file. Valid values for
input stream format are:

  * ``-i csv``: read lines as comma-separated values, fields can be referred to
  as ``$0``, ``$1``, ``$2`` and so on in expression.
    * use option 'headers' without argument to use first line as a header, its
	values will be used as field names (example: ``-i 'csv:headers'``).
    * use option 'headers' with comma-separated arguments to define field names
	(example: ``-i 'csv:headers:first,second,third'``).
    * use option 'splits' to change separator character (example:
	``-i 'csv:splits=|'``).
  * ``-i json``: read lines as JSON objects, fields can be referred to as
  ``row.key`` where ``key`` is a key in JSON object.
    * use option 'member' to change the character used to select a field from a
	sub-object (example: ``-i 'json:member=/'``), default is '.' (dot).
    * use option 'root' to change the root JSON object name (example: ``-i
	'json:root=line'``), default is 'row'.

### Output stream format (-o &lt;format&gt;):

Defines how result is printed to standard output. Valid values for output
stream format are:

  * ``-o csv``: render result as comma-separated values.
    * use option 'headers' to print headers before result values (example: ``-o
	'csv:headers'``).
  * ``-o name``: render result as name-value pairs.
  * ``-o pretty``: render result as a pretty-printed table.

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
