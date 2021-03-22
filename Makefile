CXX := g++
LDLIBS := -lpthread
CXXFLAGS = -std=c++17

all: ejplattP4 

ejplattP4: main.o board.o agent.o interface.o log.o zobrist.o transposition.o
	$(CXX) -o $@ $^ $(LDLIBS)  $(CXXFLAGS)

main.o: main.cpp board.h agent.h interface.h log.h

board.o: board.cpp board.h zobrist.h

agent.o: agent.cpp agent.h board.h zobrist.h transposition.h

interface.o: interface.cpp interface.h board.h log.h

log.o: log.cpp log.h

zobrist.o: zobrist.cpp zobrist.h

transposition.o: transposition.cpp transposition.h

clean:
	rm -f *.o

.PHONY: all clean
