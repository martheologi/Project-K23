OBJS1 = curve_grid_lsh.o Point.o Curve.o curve_funct.o
SOURCE1 = curve_grid_lsh.cpp Point.cpp Curve.cpp curve_funct.cpp
HEADER1 = structs.h curve_funct.h
OUT1 = curve_grid_lsh

CC = g++
FLAGS = -g3 -c

curve_lsh: $(OBJS1)
	$(CC) -g $(OBJS1) -o $(OUT1)

Point.o: Point.cpp
	$(CC) $(FLAGS) Point.cpp

Curve.o: Curve.cpp
	$(CC) $(FLAGS) Curve.cpp

curve_funct.o: curve_funct.cpp
	$(CC) $(FLAGS) curve_funct.cpp

curve_grid_lsh.o: curve_grid_lsh.cpp
	$(CC) $(FLAGS) curve_grid_lsh.cpp

clean:
	rm -f $(OBJS1) $(OUT1) output_*
