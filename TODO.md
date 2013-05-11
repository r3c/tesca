Tesca TODO list
===============

TODO
----

- Handle escaped quotes in CSV format

DONE
----

- Implement output formatting
- Value => Variant
- Split column & aggregator
- Shared string pointer for variants
- Perform automatic casts on compare
- Move lookup to stream
- Implement chained aggregations
- Allow options in printer expressions
- Move Variant & Config classes to common namespace
- Implement CSV printer
- Handle quotes in CSV format
- Allow common binary & unary operators in expressions
- Split expression parser into lexer/parser classes
- Speed up JSON reader by removing stringstream
- Implement a cleaner error messages system
- Implement JSON reader
- Change expressions syntax to something like "$row.0: name, avg(max($row.1, 0)): time"
- Detect inconsistent expressions such as "avg(#0) + #1"
