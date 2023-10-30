CC = gcc

CFLAGS = -Wall -g

SRCS = main.c anshita/anshita.c arjun/arjun.c yaswanth/yaswanth.c

OBJS = $(SRCS:.c=.o)

MAIN = main

.PHONY: depend clean

all:   $(MAIN)
	@echo Program has been compiled

$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(MAIN)

depend: $(SRCS)
	makedepend $^
