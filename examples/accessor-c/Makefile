HEADERDIR=../../include/accessor-c/
CC=clang
CCFLAGS=-fopenmp -fopenmp-targets=nvptx64 -O3 -gline-tables-only -I $(HEADERDIR)

vec_add:
	$(CC) $(CCFLAGS) vec_add.c -o vec_add.exe
clean:
	rm -rf *.exe

