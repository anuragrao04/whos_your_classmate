CC = gcc

CFLAGS = -Wall -g

SRCS = main.c anshita/anshita.c arjun/arjun.c yaswanth/yaswanth.c anurag/anurag.c pbPlots/pbPlots.c pbPlots/supportLib.c

OBJS = $(SRCS:.c=.o)

MAIN = whos_your_classmate

.PHONY: depend clean

all:   $(MAIN)
	@printf "\n\nProgram has been compiled! Run ./whos_your_classmate to execute the program.\n"

$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(MAIN)

depend: $(SRCS)
	makedepend $^
