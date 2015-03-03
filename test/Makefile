CXX ?= g++

serialize: serialize.cc serialize.hh serialize-gen.cc
	$(CXX) -o $@ $(filter .cc, $^) -I./

serialize-gen.cc: serialize.hh
	ccsds-tool $? > $@

test:
	./serialize

