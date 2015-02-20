SOURCES := libclang.cc
TARGET := ccsds-tool-libclang
CC ?= g++


default: $(TARGET)
all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) -o $(@) $(filter %.cc, $(^)) -lclang

.PHONY: clean

clean:
	rm $(TARGET)

