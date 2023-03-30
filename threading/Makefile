# definizione del compilatore e dei flag di compilazione
# che vengono usate dalle regole implicite
CC=gcc
CFLAGS=-std=c11 -g -O -pthread
LDLIBS=-lm -lrt -pthread


buffer: buffer_rand_num.c xerrori.c xerrori.h
	gcc -g buffer_rand_num.c xerrori.c -o buff -lrt -pthread


queue: queue.c xerrori.c xerrori.h
	gcc -g queue.c xerrori.c -o queue -lrt -pthread

coda: coda_clang.c 
	clang -g coda_clang.c -o coda -lrt -pthread
