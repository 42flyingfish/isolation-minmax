CXX := g++
LDLIBS := -lpthread
CPPFLAGS := -g -Wall -pedantic

all: out

out: main.o board.o agent.o interface.o weightedOffenA.o weightedDefA.o bucketAgent.o
	$(CXX) -o $@ $^ $(LDLIBS) $(CPPFLAGS)

main.o: main.cpp board.h agent.h interface.h weightedOffenA.h weightedDefA.h bucketAgent.h

board.o: board.cpp board.h

agent.o: agent.cpp agent.h

interface.o: interface.cpp interface.h board.h

weightedOffenA.o: weightedOffenA.cpp weightedOffenA.h

weightedDefA.o: weightedDefA.cpp weightedDefA.h

bucketAgent.o: bucketAgent.cpp bucketAgent.h

clean:
	rm -f *.o

.PHONY: all clean
