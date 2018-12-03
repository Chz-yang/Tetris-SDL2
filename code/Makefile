cc = g++
objects = main.o bmp.o window.o tetromino.o

a.out : $(objects)
	$(cc) -o $@ $(objects) -lSDL2 -std=c++11

main.o : main.cc RGB.hpp bmp.hpp window.hpp
	$(cc) -c main.cc 

bmp.o : bmp.cc bmp.hpp RGB.hpp
	$(cc) -c bmp.cc

window.o : window.cc window.hpp RGB.hpp
	$(cc) -c window.cc

tetromino.o : tetromino.cc tetromino.hpp RGB.hpp
	$(cc) -c tetromino.cc

.PHONY : clean
clean : 
	-rm a.out $(objects)