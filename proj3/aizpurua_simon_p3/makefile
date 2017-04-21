CC = g++
CFLAGS = -std=c++11 -Wall -Werror -pedantic
NAME = in2post

all: $(NAME).x

$(NAME).x: $(NAME).o
	$(CC) $(CFLAGS) $(NAME).o -o $(NAME).x

$(NAME).o: $(NAME).cpp
	$(CC) -c $(CFLAGS) $(NAME).cpp

run:
	rm -f *.o $(NAME).x
	clear
	make all

clean:
	clear
	rm -f *.o $(NAME).x
