HEADERDIR=../../include/Accessor/
CXX=clang++
CXXFLAGS=-std=c++11 -fopenmp -fopenmp-targets=nvptx64 -O3 -gline-tables-only -I $(HEADERDIR)

vec_add:
	$(CXX) $(CXXFLAGS) vec_add.cpp -o vec_add.exe

clean:
	rm -rf *.exe
