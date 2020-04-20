CXX := g++
LDLIBS := -lpthread
CPPFLAGS := -g -Wall

all: out

out: main.o board.o minMax.o
	$(CXX) -o $@ $^ $(LDLIBS) $(CPPFLAGS)

main.o: main.cpp board.h minMax.h

board.o: board.cpp board.h

minMax.o: minMax.cpp minMax.h

.PHONY: all
