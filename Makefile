OBJS = lsh.o VectorItem.o hash.o funct.o
SOURCE = lsh.cpp VectorItem.cpp hash.cpp funct.cpp
HEADER = structs.h hash.h funct.cpp
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

funct.o: funct.cpp
	$(CC) $(FLAGS) funct.cpp

clean:
	rm -f $(OBJS) $(OUT)
