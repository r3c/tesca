# Tesca: Text Stream Calculator
# Makefile resource file

TARGET	= tesca
OBJ		= obj
SRC		= .

SOURCE	= \
	lib/glay/src/parallel/mutex.cpp \
	lib/glay/src/parallel/signal.cpp \
	lib/glay/src/pipe/reader/binary.cpp \
	lib/glay/src/pipe/stream/file.cpp \
	lib/glay/src/pipe/stream/memory.cpp \
	lib/glay/src/pipe/stream/seek.cpp \
	lib/glay/src/pipe/writer/binary.cpp \
	lib/glay/src/pipe/writer/format.cpp \
	lib/glay/src/pipe/reader.cpp \
	lib/glay/src/pipe/stream.cpp \
	lib/glay/src/pipe/writer.cpp \
	lib/glay/src/system/convert.cpp \
	lib/glay/src/system/endian.cpp \
	lib/glay/src/system/stopwatch.cpp \
	src/arithmetic/aggregator/average.cpp \
	src/arithmetic/aggregator/count.cpp \
	src/arithmetic/aggregator/first.cpp \
	src/arithmetic/aggregator/last.cpp \
	src/arithmetic/aggregator/max.cpp \
	src/arithmetic/aggregator/min.cpp \
	src/arithmetic/aggregator/sum.cpp \
	src/arithmetic/aggregator/variance.cpp \
	src/arithmetic/aggregator.cpp \
	src/arithmetic/bucket.cpp \
	src/arithmetic/column.cpp \
	src/arithmetic/extractor/binary/number.cpp \
	src/arithmetic/extractor/binary/variant.cpp \
	src/arithmetic/extractor/binary.cpp \
	src/arithmetic/extractor/composite.cpp \
	src/arithmetic/extractor/constant.cpp \
	src/arithmetic/extractor/field.cpp \
	src/arithmetic/extractor/if.cpp \
	src/arithmetic/extractor/logical/and.cpp \
	src/arithmetic/extractor/logical/or.cpp \
	src/arithmetic/extractor/logical.cpp \
	src/arithmetic/extractor/unary/boolean.cpp \
	src/arithmetic/extractor/unary/number.cpp \
	src/arithmetic/extractor/unary/string.cpp \
	src/arithmetic/extractor/unary.cpp \
	src/arithmetic/extractor/vector/callback.cpp \
	src/arithmetic/extractor/vector/lazy.cpp \
	src/arithmetic/extractor/vector.cpp \
	src/arithmetic/extractor/void.cpp \
	src/arithmetic/extractor.cpp \
	src/arithmetic/table.cpp \
	src/expression/calculator.cpp \
	src/expression/constant.cpp \
	src/expression/filter.cpp \
	src/expression/function.cpp \
	src/expression/lexer.cpp \
	src/expression/parser.cpp \
	src/provision/format.cpp \
	src/provision/input.cpp \
	src/provision/lookup.cpp \
	src/provision/reader/line/csv.cpp \
	src/provision/reader/line/json.cpp \
	src/provision/reader/line.cpp \
	src/provision/reader/constant.cpp \
	src/provision/reader/map.cpp \
	src/provision/reader.cpp \
	src/provision/row/array.cpp \
	src/provision/row.cpp \
	src/storage/config.cpp \
	src/storage/variant.cpp \
	src/render/printer/csv.cpp \
	src/render/printer/name.cpp \
	src/render/printer/pretty.cpp \
	src/render/format.cpp \
	src/render/output.cpp \
	src/render/printer.cpp \
	src/main.cpp
