CFLAGS = -Wall -pedantic
OBJS = config.o main.o maze.o


all: maze

maze: $(OBJS)
	gcc $(CFLAGS) -o maze $(OBJS) -lncurses
	

.PHONY: clean clear

clean clear: 
	@rm $(OBJS) maze