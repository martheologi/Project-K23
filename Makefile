OBJS1 = lsh.o VectorItem.o hash.o funct.o bucket.o
SOURCE1 = lsh.cpp VectorItem.cpp hash.cpp funct.cpp bucket.cpp
HEADER1 = structs.h hash.h funct.h
OUT1 = lsh

OBJS2 = cube.o VectorItem.o Hypercube_vertices.o hash.o funct.o bucket.o
SOURCE2 = cube.cpp VectorItem.cpp Hypercube_vertices.cpp hash.cpp funct.cpp bucket.cpp
HEADER2 = structs.h hash.h funct.h
OUT2 = cube

OBJS3 = curve_grid_lsh.o Point.o Curve.o curve_funct.o bucket.o VectorItem.o funct.o hash.o Hypercube_vertices.o
SOURCE3 = curve_grid_lsh.cpp Point.cpp Curve.cpp curve_funct.cpp bucket.cpp VectorItem.cpp funct.cpp hash.cpp Hypercube_vertices.cpp
HEADER3 = structs.h curve_funct.h funct.h
OUT3 = curve_grid_lsh

OBJS4 = curve_grid_hypercube.o Point.o Curve.o Hypercube_vertices.o curve_funct.o bucket.o VectorItem.o funct.o hash.o
SOURCE4 = curve_grid_hypercube.cpp Point.cpp Curve.cpp Hypercube_vertices.cpp curve_funct.cpp bucket.cpp VectorItem.cpp funct.cpp hash.cpp
HEADER4 = structs.h curve_funct.h funct.h
OUT4 = curve_grid_hypercube

CC = g++
FLAGS = -g3 -c

lsh: $(OBJS1)
	$(CC) -g $(OBJS1) -o $(OUT1)

cube: $(OBJS2)
	$(CC) -g $(OBJS2) -o $(OUT2)

cg_lsh: $(OBJS3)
	$(CC) -g $(OBJS3) -o $(OUT3)

cg_hypercube: $(OBJS4)
	$(CC) -g $(OBJS4) -o $(OUT4)

lsh.o: lsh.cpp
	$(CC) $(FLAGS) lsh.cpp

VectorItem.o: VectorItem.cpp
	$(CC) $(FLAGS) VectorItem.cpp

Hypercube_vertices.o: Hypercube_vertices.cpp
	$(CC) $(FLAGS) Hypercube_vertices.cpp

hash.o: hash.cpp
	$(CC) $(FLAGS) hash.cpp

bucket.o: bucket.cpp
	$(CC) $(FLAGS) bucket.cpp

funct.o: funct.cpp
	$(CC) $(FLAGS) funct.cpp

cube.o: cube.cpp
	$(CC) $(FLAGS) cube.cpp

Point.o: Point.cpp
	$(CC) $(FLAGS) Point.cpp

Curve.o: Curve.cpp
	$(CC) $(FLAGS) Curve.cpp

curve_funct.o: curve_funct.cpp
	$(CC) $(FLAGS) curve_funct.cpp

curve_grid_lsh.o: curve_grid_lsh.cpp
	$(CC) $(FLAGS) curve_grid_lsh.cpp

curve_grid_hypercube.o: curve_grid_hypercube.cpp
	$(CC) $(FLAGS) curve_grid_hypercube.cpp

clean:
	rm -f $(OBJS1) $(OUT1) $(OBJS2) $(OUT2) $(OBJS3) $(OUT3) $(OBJS4) $(OUT4) output_*
