CXX := g++
LDLIBS := -lpthread
CPPFLAGS := -g -Wall -pedantic

all: out

out: main.o board.o agent.o interface.o
	$(CXX) -o $@ $^ $(LDLIBS) $(CPPFLAGS)

main.o: main.cpp board.h agent.h interface.h

board.o: board.cpp board.h

agent.o: agent.cpp agent.h

interface.o: interface.cpp interface.h

clean:
	rm -f *.o

.PHONY: all clean
