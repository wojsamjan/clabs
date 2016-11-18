CC = gcc
GTK_CFLAGS := $(shell pkg-config --cflags gtk+-2.0)
GTK_LDFLAGS := $(shell pkg-config --libs gtk+-2.0)
CFLAGS = -O2 -Wall -D_GNU_SOURCE $(GTK_CFLAGS)

objects = main.o draw.o mazelib.o random.o maze.o direction_stack.o maze_traced.o menu.o gui.o

app: $(objects)
	gcc -o gtklabirynt $(objects) $(GTK_LDFLAGS) -lm

.PHONY: clean

clean:
	$(RM) gtklabirynt $(objects) *~ core
