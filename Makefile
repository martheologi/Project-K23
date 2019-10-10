OBJS = funct.o VectorItem.o
SOURCE = funct.cpp VectorItem.cpp
HEADER = structs.h
OUT = lsh
CC = g++
FLAGS = -g3 -c

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

funct.o: funct.cpp
	$(CC) $(FLAGS) funct.cpp

VectorItem.o: VectorItem.cpp
	$(CC) $(FLAGS) VectorItem.cpp

clean:
	rm -f $(OBJS) $(OUT)
