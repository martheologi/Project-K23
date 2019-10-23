OBJS1 = lsh.o VectorItem.o hash.o funct.o
SOURCE1 = lsh.cpp VectorItem.cpp hash.cpp funct.cpp
HEADER1 = structs.h hash.h funct.h
OUT1 = lsh

OBJS2 = cube.o VectorItem.o Hypercube_vertices.o hash.o funct.o
SOURCE2 = cube.cpp VectorItem.cpp Hypercube_vertices.cpp hash.cpp funct.cpp
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

Hypercube_vertices.o: Hypercube_vertices.cpp
	$(CC) $(FLAGS) Hypercube_vertices.cpp

hash.o: hash.cpp
	$(CC) $(FLAGS) hash.cpp

funct.o: funct.cpp
	$(CC) $(FLAGS) funct.cpp

cube.o: cube.cpp
	$(CC) $(FLAGS) cube.cpp

clean:
	rm -f $(OBJS1) $(OUT1) $(OBJS2) $(OUT2) output_*
