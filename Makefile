OBJS = lsh.o VectorItem.o hash.o
SOURCE = lsh.cpp VectorItem.cpp hash.cpp
HEADER = structs.h hash.h
OUT = lsh
CC = g++
FLAGS = -g3 -c

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

lsh.o: lsh.cpp
	$(CC) $(FLAGS) lsh.cpp

VectorItem.o: VectorItem.cpp
	$(CC) $(FLAGS) VectorItem.cpp

hash.o: hash.cpp
	$(CC) $(FLAGS) hash.cpp

clean:
	rm -f $(OBJS) $(OUT)
