CC = g++	# use g++ for compiling c++ code
CFLAGS = -g -Wall -std=c++17		# compilation flags: -g for debugging. Change to -O or -O2 for optimized code.

all: prog9
SRCS = graph.cpp prog9.cpp
DEPS = $(SRCS:.cpp=.d)

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

prog9: prog9.o graph.o
	$(CC) prog9.o graph.o -o prog9
	
clean:
	rm *.o prog9