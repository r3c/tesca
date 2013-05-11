Tesca README file
=================

Overview
--------

Tesca (TExt Stream CAlculator) is a small utility intended to compute simple
aggregations (sums, averages, etc) on big (gigabytes or more) text files using
a simple query syntax.

Text files should contain structured data, one row per line, and use a
supported format (currently CSV, JSON, and anything that can be matched
through regexps as soon as MinGW/GCC has a decent support for new C++11
&lt;regex&gt; header).
Then you have to describe what kind of data contains each row and how result
must be computed from those data.

Example:

./tesca -i 'csv' -e '#0: name, sum(#1): score, avg(#1): average_score' file.csv

No documentation yet, sorry!

Installation
------------

Currently only builds on Windows.

Grab a C++ compiler compatible with basic C++11 features (mainly lambda
expressions) such as GCC, update the Makefile.conf if needed and run make.

Licence
-------

This project is open-source, released under BSD licence. See "LICENSE" file for
more information. Any contribution would be of course highly welcomed!

Author
------

R�mi Caput (github [at] mirari [dot] fr)
http://remi.caput.fr/
