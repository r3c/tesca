# Tesca: Text Stream Calculator
# Makefile resource file

TARGET	= tesca
OBJ		= obj
SRC		= src

SOURCE	= \
	arithmetic/accessor/binary/callback.cpp \
	arithmetic/accessor/binary/number.cpp \
	arithmetic/accessor/binary.cpp \
	arithmetic/accessor/constant.cpp \
	arithmetic/accessor/field.cpp \
	arithmetic/accessor/if.cpp \
	arithmetic/accessor/logical/and.cpp \
	arithmetic/accessor/logical/or.cpp \
	arithmetic/accessor/logical.cpp \
	arithmetic/accessor/unary/callback.cpp \
	arithmetic/accessor/unary/string.cpp \
	arithmetic/accessor/unary.cpp \
	arithmetic/accessor/vector/callback.cpp \
	arithmetic/accessor/vector.cpp \
	arithmetic/accessor/void.cpp \
	arithmetic/accessor.cpp \
	arithmetic/bucket.cpp \
	arithmetic/column/value.cpp \
	arithmetic/column.cpp \
	arithmetic/lookup.cpp \
	arithmetic/slot/average.cpp \
	arithmetic/slot/count.cpp \
	arithmetic/slot/last.cpp \
	arithmetic/slot/sum.cpp \
	arithmetic/slot/variance.cpp \
	arithmetic/slot.cpp \
	arithmetic/table.cpp \
	expression/aggregator.cpp \
	expression/formula.cpp \
	expression/function.cpp \
	expression/lexer.cpp \
	expression/parser.cpp \
	expression/select.cpp \
	glay/parallel/mutex.cpp \
	glay/parallel/signal.cpp \
	glay/pipe/reader/binary.cpp \
	glay/pipe/reader/type.cpp \
	glay/pipe/stream/file.cpp \
	glay/pipe/stream/memory.cpp \
	glay/pipe/stream/seek.cpp \
	glay/pipe/writer/binary.cpp \
	glay/pipe/writer/type.cpp \
	glay/pipe/reader.cpp \
	glay/pipe/writer.cpp \
	glay/system/convert.cpp \
	glay/system/endian.cpp \
	glay/system/stopwatch.cpp \
	stream/format.cpp \
	stream/parser.cpp \
	stream/reader/line/csv.cpp \
	stream/reader/line.cpp \
	stream/reader/map.cpp \
	stream/reader.cpp \
	stream/row/array.cpp \
	stream/row.cpp \
	stream/variant.cpp \
	main.cpp
