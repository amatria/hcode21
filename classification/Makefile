CC=g++
FLAGS=-std=c++11 -O3
LIBS=
OBJS=main.o

all: main

main: $(OBJS)
	$(CC) $(FLAGS) -o $@ $(OBJS) $(LIBS)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< $(LIBS)

clean:
	rm -rf *.o main
