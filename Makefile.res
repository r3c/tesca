# Tesca: Text Stream Calculator
# Makefile resource file

TARGET	= tesca
OBJ		= obj
SRC		= src

SOURCE	= \
	arithmetic/bucket.cpp \
	arithmetic/column/value.cpp \
	arithmetic/column.cpp \
	arithmetic/reader/binary.cpp \
	arithmetic/reader/constant.cpp \
	arithmetic/reader/field.cpp \
	arithmetic/reader/unary.cpp \
	arithmetic/reader.cpp \
	arithmetic/row.cpp \
	arithmetic/slot/average.cpp \
	arithmetic/slot/last.cpp \
	arithmetic/slot/sum.cpp \
	arithmetic/slot.cpp \
	arithmetic/table.cpp \
	arithmetic/variant.cpp \
	expression/aggregator.cpp \
	expression/formula.cpp \
	expression/function.cpp \
	expression/lexer.cpp \
	glay/parallel/mutex.cpp \
	glay/parallel/signal.cpp \
	glay/pipe/reader/binary.cpp \
	glay/pipe/reader/type.cpp \
	glay/pipe/stream/file.cpp \
	glay/pipe/stream/seek.cpp \
	glay/pipe/stream/memory.cpp \
	glay/pipe/writer/binary.cpp \
	glay/pipe/writer/type.cpp \
	glay/pipe/reader.cpp \
	glay/pipe/writer.cpp \
	glay/system/endian.cpp \
	glay/system/stopwatch.cpp \
	main.cpp
