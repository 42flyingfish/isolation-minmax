CXX := g++
LDLIBS := -lpthread
CXXFLAGS = -std=c++14

all: ejplattP4 

ejplattP4: main.o board.o agent.o interface.o log.o
	$(CXX) -o $@ $^ $(LDLIBS)  $(CXXFLAGS)

main.o: main.cpp board.h agent.h interface.h log.h

board.o: board.cpp board.h

agent.o: agent.cpp agent.h

interface.o: interface.cpp interface.h board.h log.h

log.o: log.cpp log.h

clean:
	rm -f *.o

.PHONY: all clean
