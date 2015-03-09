SOURCES := serialize.cc serialize.hh debug-comma.hh debug-comma.cc
CXX ?= g++

serialize: $(SOURCES) serialize-gen.cc
	$(CXX) -std=c++11  -o $@ $(filter %.cc, $^) -I./

serialize-gen.cc: serialize.hh
	ccsds-tool $? $${NIX_CFLAGS_COMPILE} > $@

test: serialize
	./serialize

clean:
	rm serialize serialize-gen.cc

.PHONY: clean test

all: test

