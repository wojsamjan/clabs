flex = username.l keywords.l css21.l
cflex = $(flex:%.l=%.c)
programs = $(flex:%.l=%)

# brew info flex

LDFLAGS = -L/usr/local/opt/flex/lib
CPPFLAGS = -I/usr/local/opt/flex/include -Wno-unused-function

CFLAGS = -Wall

username : username.o main.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -lfl

keywords : keywords.o main.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -lfl

css21 : css21.o main2.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -lfl

username.c : username.l
	flex -ousername.c username.l

keywords.c : keywords.l
	flex -okeywords.c keywords.l

css21.c : css21.l css21.h
	flex -ocss21.c css21.l


.PHONY : clean

clean:
	rm -f core *.o *~ $(programs) $(cflex)
