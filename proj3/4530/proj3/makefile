all:		in2post.x

in2post.x:	in2post.o
		g++ -std=c++11 -Wall -pedantic -o in2post.x in2post.o

in2post.o:	in2post.cpp
		g++ -std=c++11 -c -Wall -pedantic in2post.cpp

clean:
		rm *.x *.o
