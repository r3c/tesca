# Tesca: Text Stream Calculator
# Makefile resource file

TARGET	= tesca
OBJ		= obj
SRC		= src

SOURCE	= \
	arithmetic/bucket.cpp \
	arithmetic/column/aggregate.cpp \
	arithmetic/column/average.cpp \
	arithmetic/column/constant.cpp \
	arithmetic/column/field.cpp \
	arithmetic/column/map.cpp \
	arithmetic/column/sum.cpp \
	arithmetic/column/value.cpp \
	arithmetic/column.cpp \
	arithmetic/row.cpp \
	arithmetic/slot/average.cpp \
	arithmetic/slot/last.cpp \
	arithmetic/slot/sum.cpp \
	arithmetic/slot.cpp \
	arithmetic/table.cpp \
	arithmetic/value/boolean.cpp \
	arithmetic/value/number.cpp \
	arithmetic/value/string.cpp \
	arithmetic/value/void.cpp \
	arithmetic/value.cpp \
	glay/parallel/mutex.cpp \
	glay/parallel/signal.cpp \
	glay/pipe/reader/binary.cpp \
	glay/pipe/stream/file.cpp \
	glay/pipe/stream/seek.cpp \
	glay/pipe/stream/memory.cpp \
	glay/pipe/writer/binary.cpp \
	glay/pipe/reader.cpp \
	glay/pipe/writer.cpp \
	glay/system/endian.cpp \
	glay/system/stopwatch.cpp \
	main.cpp
