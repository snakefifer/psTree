CFLAGS=-g -c -Wall -Wextra -Wwrite-strings
LFLAGS=-g

psTree: psTree.o syscalls.o psTreeFuncs.o
	g++ ${LFLAGS} -o psTree psTree.o syscalls.o psTreeFuncs.o
psTree.o: psTree.cpp
	g++ ${CFLAGS} psTree.cpp
syscalls.o: syscalls.c
	g++ ${CFLAGS} syscalls.c
psTreeFuncs.o: psTreeFuncs.cpp
	g++ ${CFLAGS} psTreeFuncs.cpp
clean:
	rm -f *.o
	rm -f psTree