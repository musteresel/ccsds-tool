CXX ?= g++

serialize: serialize.cc serialize.hh serialize-gen.cc
	$(CXX) -o $@ $(filter .cc, $^) -I./

test:
	./serialize

