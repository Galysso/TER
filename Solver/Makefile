CXX = g++
SOURCES = Graph/Edges.cpp Functions/Functions.cpp Algorithms/MonoObj.cpp Algorithms/Naive.cpp Algorithms/MGabowTarjan.cpp
CFLAGS = -Wall -g -Ofast
LDFLAGS =
.PHONY = clean

all: main

main: $(SOURCES:.cpp=.o) $(LDFLAGS)

clean:
	rm main
	rm Graph/*.o
	rm Functions/*.o
	rm Algorithms/*.o
