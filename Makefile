
LIBS=-lpcap

all:
	cc -g -Wall -DNDEBUG src/main.c -o main $(LIBS)

