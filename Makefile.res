# Tesca: Text Stream Calculator
# Makefile resource file

TARGET	= tesca
OBJ		= obj
SRC		= .

SOURCE	= \
	lib/glay/src/parallel/mutex.cpp \
	lib/glay/src/parallel/signal.cpp \
	lib/glay/src/pipe/reader/binary.cpp \
	lib/glay/src/pipe/reader/type.cpp \
	lib/glay/src/pipe/stream/file.cpp \
	lib/glay/src/pipe/stream/memory.cpp \
	lib/glay/src/pipe/stream/seek.cpp \
	lib/glay/src/pipe/writer/binary.cpp \
	lib/glay/src/pipe/writer/format.cpp \
	lib/glay/src/pipe/writer/type.cpp \
	lib/glay/src/pipe/reader.cpp \
	lib/glay/src/pipe/stream.cpp \
	lib/glay/src/pipe/writer.cpp \
	lib/glay/src/system/convert.cpp \
	lib/glay/src/system/endian.cpp \
	lib/glay/src/system/stopwatch.cpp \
	src/arithmetic/accessor/binary/callback.cpp \
	src/arithmetic/accessor/binary/number.cpp \
	src/arithmetic/accessor/binary.cpp \
	src/arithmetic/accessor/constant.cpp \
	src/arithmetic/accessor/field.cpp \
	src/arithmetic/accessor/if.cpp \
	src/arithmetic/accessor/logical/and.cpp \
	src/arithmetic/accessor/logical/or.cpp \
	src/arithmetic/accessor/logical.cpp \
	src/arithmetic/accessor/unary/boolean.cpp \
	src/arithmetic/accessor/unary/callback.cpp \
	src/arithmetic/accessor/unary/number.cpp \
	src/arithmetic/accessor/unary/string.cpp \
	src/arithmetic/accessor/unary.cpp \
	src/arithmetic/accessor/vector/callback.cpp \
	src/arithmetic/accessor/vector.cpp \
	src/arithmetic/accessor/void.cpp \
	src/arithmetic/accessor.cpp \
	src/arithmetic/bucket.cpp \
	src/arithmetic/column/value.cpp \
	src/arithmetic/column.cpp \
	src/arithmetic/slot/average.cpp \
	src/arithmetic/slot/count.cpp \
	src/arithmetic/slot/last.cpp \
	src/arithmetic/slot/sum.cpp \
	src/arithmetic/slot/variance.cpp \
	src/arithmetic/slot.cpp \
	src/arithmetic/table.cpp \
	src/expression/aggregator.cpp \
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
	src/render/format.cpp \
	src/render/output.cpp \
	src/render/printer.cpp \
	src/main.cpp
