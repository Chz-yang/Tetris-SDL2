cc = g++
objects = main.o bmp.o window.o tetromino.o image.o

a.out : $(objects)
	$(cc) -o $@ $(objects) -lSDL2

main.o : main.cc RGB.hpp bmp.hpp window.hpp
	$(cc) -g -std=c++11 -c main.cc

bmp.o : bmp.cc bmp.hpp RGB.hpp
	$(cc) -g -std=c++11 -c bmp.cc

window.o : window.cc window.hpp RGB.hpp
	$(cc) -g -std=c++11 -c window.cc

tetromino.o : tetromino.cc tetromino.hpp RGB.hpp
	$(cc) -g -std=c++11 -c tetromino.cc

image.o : image.cc image.hpp RGB.hpp
	$(cc) -g -std=c++11 -c image.cc

.PHONY : clean
clean : 
	-rm a.out $(objects)