gcc_options = -std=c++17 -Wall -O2 --pedantic-errors

calc_greenwich_time: calc_greenwich_time.o greenwich.o bpn.o cip_cio.o era_eors.o fandamental_argument.o matrix.o obliquity.o nutation.o delta_t.o time.o file.o common.o
	g++102 $(gcc_options) -o $@ $^

calc_greenwich_time.o : calc_greenwich_time.cpp
	g++102 $(gcc_options) -c $<

greenwich.o : greenwich.cpp
	g++102 $(gcc_options) -c $<

bpn.o : bpn.cpp
	g++102 $(gcc_options) -c $<

cip_cio.o : cip_cio.cpp
	g++102 $(gcc_options) -c $<

era_eors.o : era_eors.cpp
	g++102 $(gcc_options) -c $<

fandamental_argument.o : fandamental_argument.cpp
	g++102 $(gcc_options) -c $<

matrix.o : matrix.cpp
	g++102 $(gcc_options) -c $<

obliquity.o : obliquity.cpp
	g++102 $(gcc_options) -c $<

nutation.o : nutation.cpp
	g++102 $(gcc_options) -c $<

delta_t.o : delta_t.cpp
	g++102 $(gcc_options) -c $<

time.o : time.cpp
	g++102 $(gcc_options) -c $<

file.o : file.cpp
	g++102 $(gcc_options) -c $<

common.o : common.cpp
	g++102 $(gcc_options) -c $<

run : calc_greenwich_time
	./calc_greenwich_time

clean :
	rm -f ./calc_greenwich_time
	rm -f ./*.o

.PHONY : run clean

