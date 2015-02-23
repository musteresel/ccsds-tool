SOURCES := tool.cc
TARGET := ccsds-tool
CXX ?= g++


default: $(TARGET)
all: $(TARGET) test

$(TARGET): $(SOURCES)
	$(CXX) --std=c++11 -o $(@) $(filter %.cc, $(^))

.PHONY: clean test

clean:
	rm $(TARGET)

test: $(TARGET)
	./$(TARGET)
