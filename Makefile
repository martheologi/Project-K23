OBJS1 = lsh.o VectorItem.o hash.o funct.o
SOURCE1 = lsh.cpp VectorItem.cpp hash.cpp funct.cpp
HEADER1 = structs.h hash.h funct.h
OUT1 = lsh

OBJS2 = cube.o VectorItem.o hash.o funct.o
SOURCE2 = lsh.cpp VectorItem.cpp hash.cpp funct.cpp
HEADER2 = structs.h hash.h funct.h
OUT2 = cube

CC = g++
FLAGS = -g3 -c

lsh: $(OBJS1)
	$(CC) -g $(OBJS1) -o $(OUT1)

cube: $(OBJS2)
	$(CC) -g $(OBJS2) -o $(OUT2)

lsh.o: lsh.cpp
	$(CC) $(FLAGS) lsh.cpp

VectorItem.o: VectorItem.cpp
	$(CC) $(FLAGS) VectorItem.cpp

hash.o: hash.cpp
	$(CC) $(FLAGS) hash.cpp

funct.o: funct.cpp
	$(CC) $(FLAGS) funct.cpp

cube.o: cube.cpp
	$(CC) $(FLAGS) cube.cpp

clean:
	rm -f $(OBJS1) $(OUT1) $(OBJS2) $(OUT2) output_*
