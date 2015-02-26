SOURCES := main.cc \
  libclang/visit.cc libclang/visit.hh libclang/data.hh \
  libclang/filter.hh libclang/filter.cc libclang/stdsupport.hh \
  output/serialization.hh output/serialization.cc output/data.hh
TARGET := ccsds-tool
TESTFILE := libclang/test.hh
CXX ?= g++


default: $(TARGET)
all: $(TARGET) test

$(TARGET): $(SOURCES)
	$(CXX) -g --std=c++11 -I./ -o $(@) $(filter %.cc, $(^)) -lclang

.PHONY: clean test

clean:
	rm $(TARGET)

test: $(TARGET)
	./$(TARGET) $(TESTFILE)
