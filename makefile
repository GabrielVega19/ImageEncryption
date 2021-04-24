all: PhotoMagic

PhotoMagic: PhotoMagic.o FibLFSR.o
	g++ FibLFSR.o PhotoMagic.o -lsfml-graphics -lsfml-window -lsfml-system -o PhotoMagic

FibLFSR.o: FibLFSR.cpp FibLFSR.h
	g++ FibLFSR.cpp -std=c++11 -c -g -Og -Wall -Werror -pedantic

PhotoMagic.o: PhotoMagic.cpp
	g++ PhotoMagic.cpp -std=c++11 -c -g -Og -Wall -Werror -pedantic

clean:
	rm PhotoMagic *.o 