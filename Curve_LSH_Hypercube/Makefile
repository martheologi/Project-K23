OBJS1 = curve_grid_lsh.o
SOURCE1 = curve_grid_lsh.cpp
HEADER1 = structs.h
OUT1 = curve_grid_lsh

CC = g++
FLAGS = -g3 -c

curve_lsh: $(OBJS1)
	$(CC) -g $(OBJS1) -o $(OUT1)

curve_grid_lsh.o: curve_grid_lsh.cpp
	$(CC) $(FLAGS) curve_grid_lsh.cpp

clean:
	rm -f $(OBJS1) $(OUT1) $(OBJS2) $(OUT2) output_*
