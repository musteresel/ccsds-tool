SOURCES := libclang.cc
TARGET := ccsds-tool-libclang
TESTFILE := test.hh
CC ?= g++


default: $(TARGET)
all: $(TARGET) test

$(TARGET): $(SOURCES)
	$(CC) --std=c++11 -o $(@) $(filter %.cc, $(^)) -lclang

.PHONY: clean

clean:
	rm $(TARGET)

test:
	./$(TARGET) $(TESTFILE)
