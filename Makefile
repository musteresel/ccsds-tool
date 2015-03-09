SOURCES := main.cc \
  libclang/visit.cc libclang/visit.hh libclang/data.hh \
  libclang/filter.hh libclang/filter.cc libclang/stdsupport.hh \
  output/serialization.hh output/serialization.cc output/data.hh
TARGET := ccsds-tool
TESTFILE := libclang/test.hh
CXX ?= g++
INSTALL_PATH ?= /usr/

default: $(TARGET)
all: $(TARGET) test

$(TARGET): $(SOURCES)
	$(CXX) -g --std=c++11 -I./ -o $(@) $(filter %.cc, $(^)) -lclang

.PHONY: clean test

clean:
	rm $(TARGET)

test: $(TARGET)
	./$(TARGET) $(TESTFILE)

install: $(TARGET)
	mkdir -p $(INSTALL_PATH)/bin
	cp $(TARGET) $(INSTALL_PATH)/bin
	mkdir -p $(INSTALL_PATH)/include/ccsds-tool
	cp library/serialize.hh $(INSTALL_PATH)/include/ccsds-tool/

